/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RiCalls.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Embedded module source
*
*	Version: 0.2
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#include "stdafx.h"

#define DEFINE_RICALL(call) PyObject* _Ri##call(PyObject *self, PyObject *args)
#define SUCCESS return Py_BuildValue("i", 1);
#define FAIL return NULL;

// ONE INT
#define ONE_INT_CALL(method) DEFINE_RICALL(method) { 	RtInt value = 0; if(!PyArg_ParseTuple(args, "i", &value)) FAIL; Ri##method(value); SUCCESS };

ONE_INT_CALL(FrameBegin)
ONE_INT_CALL(Sides)

// PLAIN
#define PLAIN_CALL(method) DEFINE_RICALL(method) { Ri##method(); SUCCESS };

PLAIN_CALL(FrameEnd)

PLAIN_CALL(WorldBegin)
PLAIN_CALL(WorldEnd)

PLAIN_CALL(AttributeBegin);
PLAIN_CALL(AttributeEnd);

PLAIN_CALL(TransformBegin);
PLAIN_CALL(TransformEnd);

PLAIN_CALL(SolidEnd);

//FORWARD_PLAIN(ObjectBegin);
PLAIN_CALL(ObjectEnd);

PLAIN_CALL(MotionEnd);

PLAIN_CALL(Identity);

PLAIN_CALL(ReverseOrientation);

PLAIN_CALL(ArchiveEnd);

PLAIN_CALL(Else);
PLAIN_CALL(IfEnd);

PLAIN_CALL(ResourceBegin);
PLAIN_CALL(ResourceEnd);
PLAIN_CALL(EditEnd);
PLAIN_CALL(EditAttributeEnd);
PLAIN_CALL(EditWorldEnd);

// ONE FLOAT
#define ONE_FLOAT_CALL(method) DEFINE_RICALL(method) { 	RtFloat value = 0.0f; if(!PyArg_ParseTuple(args, "f", &value)) FAIL; Ri##method(value); SUCCESS };

ONE_FLOAT_CALL(FrameAspectRatio);
ONE_FLOAT_CALL(PixelVariance);
ONE_FLOAT_CALL(ShadingRate);
ONE_FLOAT_CALL(RelativeDetail);
ONE_FLOAT_CALL(Perspective);

// ONE COLOR
//#define ONE_COLOR_CALL(method) DEFINE_RICALL(method) \
//{ RtColor v = {0.0f,0.0f,0.0f}; \
//if(!PyArg_ParseTuple(args, "f f f", v,v+1,v+2)) FAIL; \
//Ri##method(v); SUCCESS };

#define ONE_COLOR_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* A =  PyTuple_GetItem(args,0);	\
	PyObject* r =  PyTuple_GetItem(A,0);		\
	PyObject* g =  PyTuple_GetItem(A,1);		\
	PyObject* b =  PyTuple_GetItem(A,2);		\
	double R = PyFloat_AsDouble(r);	\
	double G = PyFloat_AsDouble(g);	\
	double B = PyFloat_AsDouble(b);	\
	RtColor c = { R, G, B }; Ri##method(c); SUCCESS \
};

ONE_COLOR_CALL(Color);
ONE_COLOR_CALL(Opacity);