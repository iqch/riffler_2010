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

// FrameBegin
//PyObject* _RiFrameBegin(PyObject *self, PyObject *args)
DEFINE_RICALL(FrameBegin)
{
	RtInt frame = 0;
	if(!PyArg_ParseTuple(args, "i", &frame)) FAIL;

	RiFrameBegin(frame);
	
	SUCCESS
};

//PyObject* _RiFrameEnd(PyObject *self, PyObject *args)
//DEFINE_RICALL(FrameEnd)
//{
//	RiFrameEnd();
//	SUCCESS
//};

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