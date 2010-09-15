/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	stadfx.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Common header
*
*	Version: 0.8
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#pragma once

#ifdef LINUX
//#define DLLEXPORT
//#define SIZEOF_VOID_P 8
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
#undef _DEBUG // NEED TO BUILD DEBUG VERSION
#include <Python.h>