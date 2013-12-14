#include "stdafx.h"
#include "CppSample.h"

CppSample::CppSample()
	: reference_count_( 0 )
{ }

HRESULT CppSample::QueryInterface( REFIID riid, void** obj )
{
	if( obj == NULL )
	{
		return E_POINTER;
	}

	if( riid == IID_IUnknown )
	{
		*obj = this;
	}
	else if( riid == IID_ISample )
	{
		*obj = this;
	}
	else
	{
		*obj = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

ULONG CppSample::AddRef( void )
{
	return InterlockedIncrement( &reference_count_ );
}

ULONG CppSample::Release( void )
{
	ULONG ret;
	if( ( ret = InterlockedDecrement( &reference_count_ ) ) == 0 )
	{
		delete this;
	}
	return ret;
}

HRESULT CppSample::Add( int x, int y, int *z )
{
	*z = x + y;
	return S_OK;
}

HRESULT CppSample::get_PluginName( BSTR* pluginName )
{
	CComBSTR bstr( L"Cpp Sample Plugin" );
	*pluginName = bstr.Detach();
	return S_OK;
}

CppSample* CppSample::CreateInstance()
{
	return new( std::nothrow ) CppSample();
}