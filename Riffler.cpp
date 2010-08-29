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

#define DEFINE_CALLBACKFN(callback) template<class T>  PyObject* Riffler<T>::_##callback##Func = NULL;

// PLAIN
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

// ONE INT
DEFINE_CALLBACKFN(FrameBegin);
DEFINE_CALLBACKFN(Sides);

// ONE FLOAT
DEFINE_CALLBACKFN(FrameAspectRatio);
DEFINE_CALLBACKFN(PixelVariance);
DEFINE_CALLBACKFN(ShadingRate);
DEFINE_CALLBACKFN(RelativeDetail);
DEFINE_CALLBACKFN(Perspective);

// ONE COLOR
DEFINE_CALLBACKFN(Color);
DEFINE_CALLBACKFN(Opacity);

template class Riffler<bool>;
template class Riffler<int>;
