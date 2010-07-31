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

Riffler::Riffler(PyObject* object)
	: m_object(object)
	, _FrameBeginFunc(NULL)
{
	if(object == NULL) return;

	_FrameBeginFunc = PyObject_GetAttrString(object, "FrameBegin");
	if(PyCallable_Check(_FrameBeginFunc)) FrameBegin = _FrameBegin;
	else Py_XDECREF(_FrameBeginFunc);

};

Riffler::~Riffler()
{
	if(_FrameBeginFunc != NULL) Py_XDECREF(_FrameBeginFunc);
};

//RtToken	Riffler::_Declare(char *name, char *declaration)
//{
//
//};

RtVoid	Riffler::_FrameBegin(RtInt frame)
{

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