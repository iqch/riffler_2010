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

template<class T> PyObject* Riffler<T>::m_object = NULL;

template<class T> Riffler<T>::Riffler<T>() {};

#define PARSE_CALLBACK(callback) _##callback##Func = PyObject_GetAttrString(object, #callback); \
if(PyCallable_Check(_##callback##Func)) ##callback = &Riffler::_##callback; \
else Py_XDECREF(_##callback##Func);

template<class T> void Riffler<T>::Setup(PyObject* object)
{
	m_object = object;

	if(object == NULL) return;

	PARSE_CALLBACK(FrameBegin)
	//_FrameBeginFunc = PyObject_GetAttrString(object, "FrameBegin");
	//#if(PyCallable_Check(_FrameBeginFunc)) FrameBegin = &Riffler::_FrameBegin;
	//else Py_XDECREF(_FrameBeginFunc);

	PARSE_CALLBACK(FrameEnd)
	PARSE_CALLBACK(WorldBegin)
	PARSE_CALLBACK(WorldEnd)

	PARSE_CALLBACK(AttributeBegin);
	PARSE_CALLBACK(AttributeEnd);

	PARSE_CALLBACK(TransformBegin);
	PARSE_CALLBACK(TransformEnd);

	PARSE_CALLBACK(SolidEnd);

	//PARSE_CALLBACK(ObjectBegin);
	PARSE_CALLBACK(ObjectEnd);

	PARSE_CALLBACK(MotionEnd);

	PARSE_CALLBACK(Identity);

	PARSE_CALLBACK(ReverseOrientation);

	PARSE_CALLBACK(ArchiveEnd);

	PARSE_CALLBACK(Else);
	PARSE_CALLBACK(IfEnd);

	PARSE_CALLBACK(ResourceBegin);
	PARSE_CALLBACK(ResourceEnd);
	PARSE_CALLBACK(EditEnd);
	PARSE_CALLBACK(EditAttributeEnd);
	PARSE_CALLBACK(EditWorldEnd);
};

#define DEFINE_CALLBACKFN(callback) template<class T>  PyObject* Riffler<T>::_##callback##Func = NULL;

DEFINE_CALLBACKFN(FrameBegin)
DEFINE_CALLBACKFN(FrameEnd)
DEFINE_CALLBACKFN(WorldBegin)
DEFINE_CALLBACKFN(WorldEnd)

DEFINE_CALLBACKFN(AttributeBegin);
DEFINE_CALLBACKFN(AttributeEnd);

DEFINE_CALLBACKFN(TransformBegin);
DEFINE_CALLBACKFN(TransformEnd);

DEFINE_CALLBACKFN(SolidEnd);

//DEFINE_CALLBACKFN(ObjectBegin);
DEFINE_CALLBACKFN(ObjectEnd);

DEFINE_CALLBACKFN(MotionEnd);

DEFINE_CALLBACKFN(Identity);

DEFINE_CALLBACKFN(ReverseOrientation);

DEFINE_CALLBACKFN(ArchiveEnd);

DEFINE_CALLBACKFN(Else);
DEFINE_CALLBACKFN(IfEnd);

DEFINE_CALLBACKFN(ResourceBegin);
DEFINE_CALLBACKFN(ResourceEnd);
DEFINE_CALLBACKFN(EditEnd);
DEFINE_CALLBACKFN(EditAttributeEnd);
DEFINE_CALLBACKFN(EditWorldEnd);

#define CLEAN_CALLBACK(callback) Py_XDECREF(_##callback##Func);
template<class T> Riffler<T>::~Riffler()
{
	CLEAN_CALLBACK(FrameBegin)
	CLEAN_CALLBACK(FrameEnd)
	CLEAN_CALLBACK(WorldBegin)
	CLEAN_CALLBACK(WorldEnd)

	CLEAN_CALLBACK(AttributeBegin);
	CLEAN_CALLBACK(AttributeEnd);

	CLEAN_CALLBACK(TransformBegin);
	CLEAN_CALLBACK(TransformEnd);

	CLEAN_CALLBACK(SolidEnd);

	//CLEAN_CALLBACK(ObjectBegin);
	CLEAN_CALLBACK(ObjectEnd);

	CLEAN_CALLBACK(MotionEnd);

	CLEAN_CALLBACK(Identity);

	CLEAN_CALLBACK(ReverseOrientation);

	CLEAN_CALLBACK(ArchiveEnd);

	CLEAN_CALLBACK(Else);
	CLEAN_CALLBACK(IfEnd);

	CLEAN_CALLBACK(ResourceBegin);
	CLEAN_CALLBACK(ResourceEnd);
	CLEAN_CALLBACK(EditEnd);
	CLEAN_CALLBACK(EditAttributeEnd);
	CLEAN_CALLBACK(EditWorldEnd);

	Py_XDECREF(m_object);
};

#define CALLBACKFN(callback) template<class T> RtVoid Riffler<T>::_##callback

//template<class T> RtVoid	Riffler<T>::_FrameBegin
CALLBACKFN(FrameBegin)(RtInt frame)
{
	//PyObject* pArgs = PyTuple_New(2);

	//PyTuple_SetItem(pArgs, 0, m_object);

	//PyObject* pValue = PyInt_FromLong(frame);
	//PyTuple_SetItem(pArgs, 1, pValue);

	//PyObject* pResult = PyObject_CallObject(_FrameBeginFunc, pArgs);
	
	PyObject* pResult = PyObject_CallFunction(_FrameBeginFunc, "i", frame);
	Py_XDECREF(pResult);

	//Py_DECREF(pArgs);
	//Py_DECREF(pValue);
};

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

template class Riffler<bool>;
template class Riffler<int>;
