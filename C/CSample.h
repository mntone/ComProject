#include "CSample_h.h"

#ifndef _CComObjectCSample
#define _CComObjectCSample

struct CSample
{
	ISample interface_;
	ULONG reference_count_;
};

HRESULT STDMETHODCALLTYPE CSample_QueryInterface( ISample* self, REFIID riid, void** obj );
ULONG   STDMETHODCALLTYPE CSample_AddRef( ISample* self );
ULONG   STDMETHODCALLTYPE CSample_Release( ISample* self );
HRESULT STDMETHODCALLTYPE CSample_Add( ISample* self, int x, int y, int* z );
HRESULT STDMETHODCALLTYPE CSample_get_PluginName( ISample* self, BSTR* pluginName );

CSample* CSampleCreateInstance();

#endif