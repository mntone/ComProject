#include "stdafx.h"
#include "CppSampleFactory.h"

BOOL APIENTRY DllMain( HMODULE module, DWORD ul_reason_for_call, LPVOID reserved )
{
	switch( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		global_module_ = module;
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		global_module_ = NULL;
		break;
	}
	return TRUE;
}

HRESULT __stdcall DllGetClassObject( REFCLSID rclsid, REFIID riid, void** obj )
{
	if( obj == NULL )
	{
		return E_POINTER;
	}

	*obj = NULL;

	CppSampleFactory* object = CppSampleFactory::CreateFactory();
	if( object == NULL )
	{
		return E_OUTOFMEMORY;
	}

	object->AddRef();
	HRESULT hr = object->QueryInterface( riid, obj );
	object->Release();
	return hr;
}

HRESULT __stdcall DllCanUnloadNow()
{
	return global_reference_ == 0 ? S_OK : S_FALSE;
}