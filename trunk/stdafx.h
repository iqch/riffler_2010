#pragma once

#ifdef LINUX
#define DLLEXPORT
#define SIZEOF_VOID_P 8
#else
#define DLLEXPORT __declspec(dllexport)
#endif

// CRT
#include <iostream>
using namespace std;

// RI
#include <ri.h>
#include <RifPlugin.h>

// PYTHON
#include <Python.h>