/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RiCalls.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Embedded module source
*
*	Version: 0.1
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#include "stdafx.h"

// FrameBegin
PyObject* _RiFrameBegin(PyObject *self, PyObject *args)
{
	//if(!PyArg_ParseTuple(args, ":numargs")) return NULL;

	RtInt frame = 0;
	if(!PyArg_ParseTuple(args, "i", &frame)) return NULL;

	RiFrameBegin(frame);
	
	return Py_BuildValue("i", 1);
};
