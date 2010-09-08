/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization source - Destructor
*
*	Version: 0.4
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
	//CLEAN_CALLBACK(ObjectEnd);

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

	// BOOLEAN
	CLEAN_CALLBACK(Matte);

	// STRINGS
	CLEAN_CALLBACK(ShadingInterpolation);
	CLEAN_CALLBACK(SolidBegin);
	CLEAN_CALLBACK(EditAttributeBegin);
	CLEAN_CALLBACK(Orientation);
	CLEAN_CALLBACK(CoordSysTransform);
	CLEAN_CALLBACK(CoordinateSystem);
	CLEAN_CALLBACK(ScopedCoordinateSystem);
	CLEAN_CALLBACK(System);

	// POLY-FLOATS

	// 2
	CLEAN_CALLBACK(Clipping);
	CLEAN_CALLBACK(Shutter);
	CLEAN_CALLBACK(Exposure);
	CLEAN_CALLBACK(PixelSamples);

	// 3
	CLEAN_CALLBACK(Scale);
	CLEAN_CALLBACK(DepthOfField);
	CLEAN_CALLBACK(Translate);

	// 4
	CLEAN_CALLBACK(CropWindow);
	CLEAN_CALLBACK(ScreenWindow);
	CLEAN_CALLBACK(DetailRange);
	CLEAN_CALLBACK(Rotate);

	// 6
	CLEAN_CALLBACK(ClippingPlane);

	// 7
	CLEAN_CALLBACK(Skew);

	// 8
	CLEAN_CALLBACK(TextureCoordinates);

	// BOUNDS
	CLEAN_CALLBACK(Bound);
	CLEAN_CALLBACK(Detail);

	// MATRICES
	CLEAN_CALLBACK(ConcatTransform);
	CLEAN_CALLBACK(Transform);

	// TOKEN-DICTIONARY
	CLEAN_CALLBACK(EditBeginV);
	CLEAN_CALLBACK(IfBeginV);
	CLEAN_CALLBACK(ElseIfV);
	CLEAN_CALLBACK(ProjectionV);
	CLEAN_CALLBACK(HiderV);
	CLEAN_CALLBACK(OptionV);
	CLEAN_CALLBACK(AttributeV);
	CLEAN_CALLBACK(AtmosphereV);
	CLEAN_CALLBACK(DisplacementV);
	CLEAN_CALLBACK(ExteriorV);
	CLEAN_CALLBACK(InteriorV);
	CLEAN_CALLBACK(SurfaceV);
	CLEAN_CALLBACK(GeometryV);
	CLEAN_CALLBACK(PatchV);
	CLEAN_CALLBACK(DisplayChannelV);
	CLEAN_CALLBACK(CameraV);
	CLEAN_CALLBACK(PixelSampleImagerV);
	CLEAN_CALLBACK(EditWorldBeginV);
	CLEAN_CALLBACK(ImagerV);

	// DUO-TOKENS/DICT
	CLEAN_CALLBACK(ResourceV);
	CLEAN_CALLBACK(ShaderV);

	// DICT WITH HANDLES
	CLEAN_CALLBACK(ArchiveBeginV);
	CLEAN_CALLBACK(LightSourceV);

	// FINALE
	Py_XDECREF(m_object);
};

template class Riffler<bool>;
template class Riffler<int>;