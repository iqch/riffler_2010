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

#define CLEAN_CALLBACK(callback) Py_XDECREF(_##callback##Func);
template<class T> Riffler<T>::~Riffler()
{
	// PLAIN
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

	// ONE INT
	CLEAN_CALLBACK(FrameBegin)
	CLEAN_CALLBACK(Sides)

	// ONE FLOAT
	CLEAN_CALLBACK(FrameAspectRatio);
	CLEAN_CALLBACK(PixelVariance);
	CLEAN_CALLBACK(ShadingRate);
	CLEAN_CALLBACK(RelativeDetail);
	CLEAN_CALLBACK(Perspective);

	// ONE COLOR
	CLEAN_CALLBACK(Color);
	CLEAN_CALLBACK(Opacity);

	Py_XDECREF(m_object);
};

template class Riffler<bool>;
template class Riffler<int>;