#pragma once
#include "CppSample_h.h"

class CppSample
	: public ISample
{
public:
	CppSample();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** obj );
	virtual ULONG STDMETHODCALLTYPE AddRef( void );
	virtual ULONG STDMETHODCALLTYPE Release( void );

	virtual HRESULT STDMETHODCALLTYPE Add( int x,int y, int *z );
	virtual HRESULT STDMETHODCALLTYPE get_PluginName( BSTR* pluginName );

	static CppSample* STDMETHODCALLTYPE CreateInstance();

private:
	ULONG reference_count_;
};