/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler_Setup.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization source - Setup functions
*
*	Version: 0.3
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/

#include "stdafx.h"
#include "Riffler.h"

#define PARSE_CALLBACK(callback) _##callback##Func = PyObject_GetAttrString(object, #callback); \
	if(PyCallable_Check(_##callback##Func)) ##callback = &Riffler::_##callback; \
else Py_XDECREF(_##callback##Func);

template<class T> void Riffler<T>::Setup(PyObject* object)
{
	m_object = object;

	if(object == NULL) return;

	// ONE INT
	PARSE_CALLBACK(FrameBegin)
		PARSE_CALLBACK(Sides)
		//_FrameBeginFunc = PyObject_GetAttrString(object, "FrameBegin");
		//#if(PyCallable_Check(_FrameBeginFunc)) FrameBegin = &Riffler::_FrameBegin;
		//else Py_XDECREF(_FrameBeginFunc);

		// PLAIN
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

	// ONE FLOAT
	PARSE_CALLBACK(FrameAspectRatio);
	PARSE_CALLBACK(PixelVariance);
	PARSE_CALLBACK(ShadingRate);
	PARSE_CALLBACK(RelativeDetail);
	PARSE_CALLBACK(Perspective);

	// ONE COLOR
	PARSE_CALLBACK(Color);
	PARSE_CALLBACK(Opacity);

	// BOOLEAN
	PARSE_CALLBACK(Matte);

	// STRINGS
	PARSE_CALLBACK(ShadingInterpolation);
	PARSE_CALLBACK(SolidBegin);
	PARSE_CALLBACK(EditAttributeBegin);
	PARSE_CALLBACK(Orientation);
	PARSE_CALLBACK(CoordSysTransform);
	PARSE_CALLBACK(CoordinateSystem);
	PARSE_CALLBACK(ScopedCoordinateSystem);
	PARSE_CALLBACK(System);

	// POLY-FLOATS

	// 2
	PARSE_CALLBACK(Clipping);
	PARSE_CALLBACK(Shutter);
	PARSE_CALLBACK(Exposure);
	PARSE_CALLBACK(PixelSamples);

	// 3
	PARSE_CALLBACK(Scale);
	PARSE_CALLBACK(DepthOfField);
	PARSE_CALLBACK(Translate);

	// 4
	PARSE_CALLBACK(CropWindow);
	PARSE_CALLBACK(ScreenWindow);
	PARSE_CALLBACK(DetailRange);
	PARSE_CALLBACK(Rotate);

	// 6
	PARSE_CALLBACK(ClippingPlane);

	// 7
	PARSE_CALLBACK(Skew);

	// 8
	PARSE_CALLBACK(TextureCoordinates);

	// BOUNDS
	PARSE_CALLBACK(Bound);
	PARSE_CALLBACK(Detail);

	// MATRICES
	PARSE_CALLBACK(ConcatTransform);
	PARSE_CALLBACK(Transform);
};

template class Riffler<bool>;
template class Riffler<int>;
