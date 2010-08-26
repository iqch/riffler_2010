/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization source
*
*	Version: 0.1
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/

#include "stdafx.h"
#include "Riffler.h"

template<class T> PyObject* Riffler<T>::m_object = NULL;

template<class T> Riffler<T>::Riffler<T>() {};

template<class T> void Riffler<T>::Setup(PyObject* object)
{
	m_object = object;
	_FrameBeginFunc = NULL;

	if(object == NULL) return;

	_FrameBeginFunc = PyObject_GetAttrString(object, "FrameBegin");
	if(PyCallable_Check(_FrameBeginFunc)) FrameBegin = &Riffler::_FrameBegin;
	else Py_XDECREF(_FrameBeginFunc);
};

template<class T>  PyObject* Riffler<T>::_FrameBeginFunc = NULL;

template<class T> Riffler<T>::~Riffler()
{
	Py_XDECREF(_FrameBeginFunc);
	Py_XDECREF(m_object);
};

//RtToken	Riffler::_Declare(char *name, char *declaration)
//{
//
//};

template<class T> RtVoid	Riffler<T>::_FrameBegin(RtInt frame)
{
	PyObject* pArgs = PyTuple_New(2);

	PyTuple_SetItem(pArgs, 0, m_object);

	PyObject* pValue = PyInt_FromLong(frame);
	PyTuple_SetItem(pArgs, 1, pValue);

	PyObject* pResult = PyObject_CallObject(_FrameBeginFunc, pArgs);

	Py_XDECREF(pResult);

	Py_DECREF(pArgs);
	Py_DECREF(pValue);
};

/*RtVoid	Riffler::_FrameEnd()
{

};

RtVoid	Riffler::_WorldBegin()
{

};

RtVoid	Riffler::_WorldEnd()
{

};

RtVoid	Riffler::_Clipping(RtFloat hither, RtFloat yon)
{

};*/

template class Riffler<bool>;
template class Riffler<int>;
