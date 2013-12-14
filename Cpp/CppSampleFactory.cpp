#include "stdafx.h"
#include "CppSampleFactory.h"
#include "CppSample.h"

CppSampleFactory::CppSampleFactory()
	: reference_count_( 0 )
{ }

HRESULT CppSampleFactory::QueryInterface( REFIID riid, void** obj )
{
	if( obj == NULL )
	{
		return E_POINTER;
	}

	if( riid == IID_IUnknown )
	{
		*obj = this;
	}
	else if( riid == IID_IClassFactory )
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

ULONG CppSampleFactory::AddRef()
{
	return InterlockedIncrement( &reference_count_ );
}

ULONG CppSampleFactory::Release()
{
	ULONG ret;
	if( ( ret = InterlockedDecrement( &reference_count_ ) ) == 0 )
	{
		delete this;
	}
	return ret;
}

HRESULT CppSampleFactory::CreateInstance( IUnknown* unknown_outer, REFIID riid, void** obj )
{
	if( unknown_outer != NULL )
	{
		return CLASS_E_NOAGGREGATION;
	}

	if( obj == NULL )
	{
		return E_INVALIDARG;
	}

	*obj = NULL;

	CppSample* object = CppSample::CreateInstance();
	if( object == NULL )
	{
		return E_OUTOFMEMORY;
	}

	object->AddRef();
	HRESULT hr = object->QueryInterface( riid, obj );
	object->Release();
	return hr;
}

HRESULT CppSampleFactory::LockServer( BOOL lock )
{
	lock ? InterlockedIncrement( &global_reference_ ) : InterlockedDecrement( &global_reference_ );
	return S_OK;
}

CppSampleFactory* CppSampleFactory::CreateFactory()
{
	return new( std::nothrow ) CppSampleFactory();
}