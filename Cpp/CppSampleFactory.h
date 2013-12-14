#pragma once
#include "CppSampleFactory_h.h"

class CppSampleFactory
	: public IClassFactory
{
public:
	CppSampleFactory();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** obj );
	virtual ULONG STDMETHODCALLTYPE AddRef( void );
	virtual ULONG STDMETHODCALLTYPE Release( void );

	virtual HRESULT STDMETHODCALLTYPE CreateInstance( IUnknown* unknown_outer, REFIID riid, void** obj );
	virtual HRESULT STDMETHODCALLTYPE LockServer( BOOL lock );

	static CppSampleFactory* STDMETHODCALLTYPE CreateFactory();

private:
	ULONG reference_count_;
};