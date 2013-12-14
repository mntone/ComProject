#include "stdafx.h"
#include "CSampleFactory.h"
#include "CSample.h"

IClassFactoryVtbl CSampleFactory_vtable =
{
	CSampleFactory_QueryInterface,
	CSampleFactory_AddRef,
	CSampleFactory_Release,
	CSampleFactory_CreateInstance,
	CSampleFactory_LockServer,
};

HRESULT STDMETHODCALLTYPE CSampleFactory_QueryInterface( IClassFactory* self, REFIID riid, void** obj )
{
	if( obj == NULL )
	{
		return E_POINTER;
	}

	if( IsEqualIID( riid, &IID_IUnknown ) )
	{
		*obj = self;
	}
	else if( IsEqualIID( riid, &IID_IClassFactory ) )
	{
		*obj = self;
	}
	else
	{
		*obj = NULL;
		return E_NOINTERFACE;
	}

	self->lpVtbl->AddRef( self );
	return S_OK;
}

ULONG STDMETHODCALLTYPE CSampleFactory_AddRef( IClassFactory* self )
{
	return InterlockedIncrement( &( ( ( CSampleFactory* )self )->reference_count_ ) );
}

ULONG STDMETHODCALLTYPE CSampleFactory_Release( IClassFactory* self )
{
	ULONG ret;
	if( ( ret = InterlockedDecrement( &( ( ( CSampleFactory* )self )->reference_count_ ) ) ) == 0 )
	{
		free( ( CSampleFactory* )self );
	}
	return ret;
}

HRESULT STDMETHODCALLTYPE CSampleFactory_CreateInstance( IClassFactory* self, IUnknown* unknown_outer, REFIID riid, void** obj )
{
	if( unknown_outer != NULL )
	{
		return CLASS_E_NOAGGREGATION;
	}

	if( obj == NULL )
	{
		return E_POINTER;
	}

	*obj = NULL;

	CSample* object = CSampleCreateInstance();
	if( object == NULL )
	{
		return E_OUTOFMEMORY;
	}

	object->interface_.lpVtbl->AddRef( ( ISample* )object );
	HRESULT hr = object->interface_.lpVtbl->QueryInterface( ( ISample* )object, riid, obj );
	object->interface_.lpVtbl->Release( ( ISample* )object );
	return hr;
}

HRESULT STDMETHODCALLTYPE CSampleFactory_LockServer( IClassFactory* self, BOOL lock )
{
	lock ? InterlockedIncrement( &global_reference_ ) : InterlockedDecrement( &global_reference_ );
	return S_OK;
}

CSampleFactory* CSampleCreateFactory()
{
	CSampleFactory* object;

	object = ( CSampleFactory* )malloc( sizeof( CSampleFactory ) );
	if( object == NULL )
	{
		return object;
	}

	object->interface_.lpVtbl = &CSampleFactory_vtable;
	object->reference_count_ = 0;
	return object;
}