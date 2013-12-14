#include "stdafx.h"
#include "CSample.h"
#include "ISample_i.c"

ISampleVtbl CSample_vtable =
{
	CSample_QueryInterface,
	CSample_AddRef,
	CSample_Release,
	CSample_Add,
	CSample_get_PluginName,
};

HRESULT STDMETHODCALLTYPE CSample_QueryInterface( ISample* self, REFIID riid, void** obj )
{
	if( obj == NULL )
	{
		return E_POINTER;
	}

	if( IsEqualIID( riid, &IID_IUnknown ) )
	{
		*obj = self;
	}
	else if( IsEqualIID( riid, &IID_ISample ) )
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

ULONG STDMETHODCALLTYPE CSample_AddRef( ISample* self )
{
	return InterlockedIncrement( &( ( ( CSample* )self )->reference_count_ ) );
}

ULONG STDMETHODCALLTYPE CSample_Release( ISample* self )
{
	ULONG ret;
	if( ( ret = InterlockedDecrement( &( ( ( CSample* )self )->reference_count_ ) ) ) == 0 )
	{
		free( ( CSample* )self );
	}
	return ret;
}

HRESULT STDMETHODCALLTYPE CSample_Add( ISample* self, int x, int y, int* z )
{
	*z = x + y;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CSample_get_PluginName( ISample* self, BSTR* pluginName )
{
	*pluginName = SysAllocString( L"C Sample Plugin" );
	return S_OK;
}

CSample* CSampleCreateInstance()
{
	CSample* object = ( CSample* )malloc( sizeof( CSample ) );
	if( object == NULL )
	{
		return object;
	}

	object->interface_.lpVtbl = &CSample_vtable;
	object->reference_count_ = 0;
	return object;
}