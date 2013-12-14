#include "stdafx.h"
#include "ISample_h.h"
#include "ISample_i.c"

int wmain( int /*argc*/, wchar_t* /*argv*/[] )
{
	HRESULT hr = CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );

	std::array<std::tuple<std::wstring, GUID>, 2> dll_list =
	{
		std::make_tuple<std::wstring, GUID>( std::wstring( L"C" ), { 0x6B6055DF, 0xA1D9, 0x42D9, { 0xBE, 0x0A, 0x7D, 0x94, 0x89, 0xCF, 0x53, 0x23 } } ),
		std::make_tuple<std::wstring, GUID>( std::wstring( L"Cpp" ), { 0x042743DB, 0x068C, 0x4F29, { 0xB8, 0xAA, 0x87, 0x6B, 0x7D, 0xD8, 0x79, 0x09 } } ),
	};

	for( const auto& dll : dll_list )
	{
		std::wcout << L"--------------------" << std::endl;
		std::wcout << std::get<0>( dll ).c_str() << L" loading..." << std::endl;

		HMODULE module = LoadLibrary( ( std::wstring( std::get<0>( dll ) ) + L".dll" ).c_str() );
		LPFNGETCLASSOBJECT fnDllGetClassObject = reinterpret_cast<LPFNGETCLASSOBJECT>( GetProcAddress( module, "DllGetClassObject" ) );

		{
			CComPtr<IClassFactory> factory;
			hr = fnDllGetClassObject( std::get<1>( dll ), IID_IClassFactory, reinterpret_cast<void**>( &factory ) );
			if( FAILED( hr ) )
			{
				FreeLibrary( module );
				return 1;
			}

			CComPtr<ISample> sample;
			hr = factory->CreateInstance( nullptr, IID_ISample, reinterpret_cast<void**>( &sample ) );
			if( FAILED( hr ) )
			{
				FreeLibrary( module );
				return 1;
			}

			BSTR pluginName;
			sample->get_PluginName( &pluginName );
			std::wcout << pluginName << std::endl;

			int ans;
			sample->Add( 1, 2, &ans );
			std::wcout << ans << std::endl;
		}

		FreeLibrary( module );
	}
	std::wcout << L"--------------------" << std::endl;

	CoUninitialize();
	return 0;
}