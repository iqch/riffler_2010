/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization source
*
*	Version: 0.4
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

// BOOLEAN
DEFINE_CALLBACKFN(Matte);

// STRINGS
DEFINE_CALLBACKFN(ShadingInterpolation);
DEFINE_CALLBACKFN(SolidBegin);
DEFINE_CALLBACKFN(EditAttributeBegin);
DEFINE_CALLBACKFN(Orientation);
DEFINE_CALLBACKFN(CoordSysTransform);
DEFINE_CALLBACKFN(CoordinateSystem);
DEFINE_CALLBACKFN(ScopedCoordinateSystem);
DEFINE_CALLBACKFN(System);

// POLY FLOATS

// 2
DEFINE_CALLBACKFN(Clipping);
DEFINE_CALLBACKFN(Shutter);
DEFINE_CALLBACKFN(Exposure);
DEFINE_CALLBACKFN(PixelSamples);

// 3
DEFINE_CALLBACKFN(Scale);
DEFINE_CALLBACKFN(DepthOfField);
DEFINE_CALLBACKFN(Translate);

// 4
DEFINE_CALLBACKFN(CropWindow);
DEFINE_CALLBACKFN(ScreenWindow);
DEFINE_CALLBACKFN(DetailRange);
DEFINE_CALLBACKFN(Rotate);

// 6
DEFINE_CALLBACKFN(ClippingPlane);

// 7
DEFINE_CALLBACKFN(Skew);

// 8
DEFINE_CALLBACKFN(TextureCoordinates);

// BOUNDS
DEFINE_CALLBACKFN(Bound);
DEFINE_CALLBACKFN(Detail);

// MATRICIES
DEFINE_CALLBACKFN(ConcatTransform);
DEFINE_CALLBACKFN(Transform);

// TOKEN-DICTIONARY
DEFINE_CALLBACKFN(EditBeginV);
DEFINE_CALLBACKFN(IfBeginV);
DEFINE_CALLBACKFN(ElseIfV);
DEFINE_CALLBACKFN(ProjectionV);
DEFINE_CALLBACKFN(HiderV);
DEFINE_CALLBACKFN(OptionV);
DEFINE_CALLBACKFN(AttributeV);
DEFINE_CALLBACKFN(AtmosphereV);
DEFINE_CALLBACKFN(DisplacementV);
DEFINE_CALLBACKFN(ExteriorV);
DEFINE_CALLBACKFN(InteriorV);
DEFINE_CALLBACKFN(SurfaceV);
DEFINE_CALLBACKFN(GeometryV);
DEFINE_CALLBACKFN(PatchV);
DEFINE_CALLBACKFN(DisplayChannelV);
DEFINE_CALLBACKFN(CameraV);
DEFINE_CALLBACKFN(PixelSampleImagerV);
DEFINE_CALLBACKFN(EditWorldBeginV);
DEFINE_CALLBACKFN(ImagerV);

template class Riffler<bool>;
template class Riffler<int>;
