#include "CSampleFactory_h.h"

#ifndef _CSampleFactory
#define _CSampleFactory

struct CSampleFactory
{
	IClassFactory interface_;
	ULONG reference_count_;
};

HRESULT STDMETHODCALLTYPE CSampleFactory_QueryInterface( IClassFactory* self, REFIID riid, void** obj );
ULONG   STDMETHODCALLTYPE CSampleFactory_AddRef( IClassFactory* self );
ULONG   STDMETHODCALLTYPE CSampleFactory_Release( IClassFactory* self );
HRESULT STDMETHODCALLTYPE CSampleFactory_CreateInstance( IClassFactory* self, IUnknown* unknown_outer, REFIID riid, void** obj );
HRESULT STDMETHODCALLTYPE CSampleFactory_LockServer( IClassFactory* self, BOOL lock );

CSampleFactory* CSampleCreateFactory();

#endif