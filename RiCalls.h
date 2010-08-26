/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RiCalls.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Embedded module header
*
*	Version: 0.1
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#pragma once

PyObject* _RiFrameBegin(PyObject *self, PyObject *args);

static PyMethodDef MethodTable[] = {
	{"FrameBegin", _RiFrameBegin, METH_VARARGS,""},
	{NULL, NULL, 0, NULL}
};