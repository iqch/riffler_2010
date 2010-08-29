/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RiCalls.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Embedded module header
*
*	Version: 0.2
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#pragma once

#define DEFINE_RICALL(call) PyObject* _Ri##call(PyObject *self, PyObject *args)

// ONE INT
DEFINE_RICALL(FrameBegin);
DEFINE_RICALL(Sides);

// PLAIN
DEFINE_RICALL(FrameEnd);
DEFINE_RICALL(WorldBegin);
DEFINE_RICALL(WorldEnd);

DEFINE_RICALL(AttributeBegin);
DEFINE_RICALL(AttributeEnd);

DEFINE_RICALL(TransformBegin);
DEFINE_RICALL(TransformEnd);

DEFINE_RICALL(SolidEnd);

//FORWARD_PLAIN(ObjectBegin);
DEFINE_RICALL(ObjectEnd);

DEFINE_RICALL(MotionEnd);

DEFINE_RICALL(Identity);

DEFINE_RICALL(ReverseOrientation);

DEFINE_RICALL(ArchiveEnd);

DEFINE_RICALL(Else);
DEFINE_RICALL(IfEnd);

DEFINE_RICALL(ResourceBegin);
DEFINE_RICALL(ResourceEnd);
DEFINE_RICALL(EditEnd);
DEFINE_RICALL(EditAttributeEnd);
DEFINE_RICALL(EditWorldEnd);

// ONE FLOAT
DEFINE_RICALL(FrameAspectRatio);
DEFINE_RICALL(PixelVariance);
DEFINE_RICALL(ShadingRate);
DEFINE_RICALL(RelativeDetail);
DEFINE_RICALL(Perspective);

// ONE COLOR
DEFINE_RICALL(Color);
DEFINE_RICALL(Opacity);

#define RI_METHOD(method) {#method, _Ri##method, METH_VARARGS,""}

static PyMethodDef MethodTable[] = {
	// ONE INT
	RI_METHOD(FrameBegin),
	RI_METHOD(Sides),
	
	// PLIAN
	RI_METHOD(FrameEnd),

	RI_METHOD(WorldBegin),
	RI_METHOD(WorldEnd),

	RI_METHOD(AttributeBegin),
	RI_METHOD(AttributeEnd),

	RI_METHOD(TransformBegin),
	RI_METHOD(TransformEnd),

	RI_METHOD(SolidEnd),

	//FORWARD_PLAIN(ObjectBegin);
	RI_METHOD(ObjectEnd),

	RI_METHOD(MotionEnd),

	RI_METHOD(Identity),

	RI_METHOD(ReverseOrientation),

	RI_METHOD(ArchiveEnd),

	RI_METHOD(Else),
	RI_METHOD(IfEnd),

	RI_METHOD(ResourceBegin),
	RI_METHOD(ResourceEnd),
	RI_METHOD(EditEnd),
	RI_METHOD(EditAttributeEnd),
	RI_METHOD(EditWorldEnd),

	// ONE FLOAT
	RI_METHOD(FrameAspectRatio),
	RI_METHOD(PixelVariance),
	RI_METHOD(ShadingRate),
	RI_METHOD(RelativeDetail),
	RI_METHOD(Perspective),

	// ONE COLOR
	RI_METHOD(Color),
	RI_METHOD(Opacity),

	{NULL, NULL, 0, NULL}
};