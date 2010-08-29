/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization source
*
*	Version: 0.2
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/

#include "stdafx.h"
#include "Riffler.h"

#define CALLBACKFN(callback) template<class T> RtVoid Riffler<T>::_##callback

#define FORWARD_PLAIN(callback) CALLBACKFN(callback)() { PyObject* pResult = PyObject_CallFunction(_##callback##Func, NULL); Py_XDECREF(pResult); };

FORWARD_PLAIN(FrameEnd)

FORWARD_PLAIN(WorldBegin)
FORWARD_PLAIN(WorldEnd)

FORWARD_PLAIN(AttributeBegin);
FORWARD_PLAIN(AttributeEnd);

FORWARD_PLAIN(TransformBegin);
FORWARD_PLAIN(TransformEnd);

FORWARD_PLAIN(SolidEnd);

//FORWARD_PLAIN(ObjectBegin);
FORWARD_PLAIN(ObjectEnd);

FORWARD_PLAIN(MotionEnd);

FORWARD_PLAIN(Identity);

FORWARD_PLAIN(ReverseOrientation);

FORWARD_PLAIN(ArchiveEnd);

FORWARD_PLAIN(Else);
FORWARD_PLAIN(IfEnd);

FORWARD_PLAIN(ResourceBegin);
FORWARD_PLAIN(ResourceEnd);
FORWARD_PLAIN(EditEnd);
FORWARD_PLAIN(EditAttributeEnd);
FORWARD_PLAIN(EditWorldEnd);

#define FORWARD_INT(callback) CALLBACKFN(callback)(RtInt value) { PyObject* pResult = PyObject_CallFunction(_##callback##Func, "i", value); Py_XDECREF(pResult); };

FORWARD_INT(FrameBegin)
FORWARD_INT(Sides)

#define FORWARD_FLOAT(callback) CALLBACKFN(callback)(RtFloat value) { PyObject* pResult = PyObject_CallFunction(_##callback##Func, "f", value); Py_XDECREF(pResult); };

FORWARD_FLOAT(FrameAspectRatio);
FORWARD_FLOAT(PixelVariance);
FORWARD_FLOAT(ShadingRate);
FORWARD_FLOAT(RelativeDetail);
FORWARD_FLOAT(Perspective);

#define FORWARD_COLOR(callback) CALLBACKFN(callback)(RtColor v) \
{ \
	PyObject* pfArgs = Py_BuildValue("(fff)",v[0],v[1],v[2]); \
	PyObject* pArgs = PyTuple_New(1); \
	PyTuple_SetItem(pArgs, 0, pfArgs); \
	PyObject* pResult = PyObject_CallObject(_##callback##Func, pArgs); \
	Py_XDECREF(pResult); \
	Py_XDECREF(pArgs); \
	Py_XDECREF(pfArgs); \
};

FORWARD_COLOR(Color);
FORWARD_COLOR(Opacity);

//template<class T> RtVoid	Riffler<T>::_FrameBegin
//CALLBACKFN(FrameBegin)(RtInt frame)
//{
//PyObject* pArgs = PyTuple_New(2);

//PyTuple_SetItem(pArgs, 0, m_object);

//PyObject* pValue = PyInt_FromLong(frame);
//PyTuple_SetItem(pArgs, 1, pValue);

//PyObject* pResult = PyObject_CallObject(_FrameBeginFunc, pArgs);

//PyObject* pResult = PyObject_CallFunction(_FrameBeginFunc, "i", frame);
//Py_XDECREF(pResult);

//Py_DECREF(pArgs);
//Py_DECREF(pValue);
//};

template class Riffler<bool>;
template class Riffler<int>;