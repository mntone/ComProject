#pragma once

#define WIN32_LEAN_AND_MEAN
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

#include <atlbase.h>

static ULONG global_reference_ = 0;
static HMODULE global_module_;