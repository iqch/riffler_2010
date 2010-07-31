/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Embedded module sourcecode
*
*	Version: 0.1
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#include "stdafx.h"

// RIBEGIN
PyObject* _RiBegin(PyObject *self, PyObject *args)
{
	//if(!PyArg_ParseTuple(args, ":numargs")) return NULL;
	//return Py_BuildValue("i", numargs);
	return Py_BuildValue("i", 0);
};
