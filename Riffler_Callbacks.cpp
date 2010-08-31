/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization source - Callbacks
*
*	Version: 0.4
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/

#include "stdafx.h"
#include "Riffler.h"

bool ParseDictionary(PyObject* dict, int n, RtToken tk[], RtPointer vl[]);

#define CALLBACKFN(callback) template<class T> RtVoid Riffler<T>::_##callback

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

#define FORWARD_INT(callback) CALLBACKFN(callback)(RtInt value) { PyObject* pResult = PyObject_CallFunction(_##callback##Func, "i", value); Py_XDECREF(pResult); };

FORWARD_INT(FrameBegin)
FORWARD_INT(Sides)

#define FORWARD_FLOAT(callback) CALLBACKFN(callback)(RtFloat value) { PyObject* pResult = PyObject_CallFunction(_##callback##Func, "f", value); Py_XDECREF(pResult); };

FORWARD_FLOAT(FrameAspectRatio);
FORWARD_FLOAT(PixelVariance);
FORWARD_FLOAT(ShadingRate);
FORWARD_FLOAT(RelativeDetail);
FORWARD_FLOAT(Perspective);

#define FORWARD_COLOR(callback) CALLBACKFN(callback)(RtColor v) \
{ \
	PyObject* pfArgs = Py_BuildValue("(fff)",v[0],v[1],v[2]); \
	PyObject* pArgs = PyTuple_New(1); \
	PyTuple_SetItem(pArgs, 0, pfArgs); \
	PyObject* pResult = PyObject_CallObject(_##callback##Func, pArgs); \
	Py_XDECREF(pResult); \
	Py_XDECREF(pArgs); \
	Py_XDECREF(pfArgs); \
};

FORWARD_COLOR(Color);
FORWARD_COLOR(Opacity);

// BOOLEAN
CALLBACKFN(Matte)(RtBoolean onoff)
{
	PyObject* pResult = PyObject_CallFunction(_MatteFunc, "i", (onoff == 0 ? 0 : 1));
	Py_XDECREF(pResult);
};

// STRINGS
#define FORWARD_STRING(callback) CALLBACKFN(callback)(RtToken v) { PyObject* pResult = PyObject_CallFunction(_##callback##Func, "s", v); Py_XDECREF(pResult); };

FORWARD_STRING(ShadingInterpolation);
FORWARD_STRING(SolidBegin);
FORWARD_STRING(EditAttributeBegin);
FORWARD_STRING(Orientation);
FORWARD_STRING(CoordSysTransform);
FORWARD_STRING(CoordinateSystem);
FORWARD_STRING(ScopedCoordinateSystem);
FORWARD_STRING(System);

// POLY-FLOATS

#define POLY_FLOATS2(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "ff", v1, v2);	Py_XDECREF(pResult); };

POLY_FLOATS2(Clipping);
POLY_FLOATS2(Shutter);
POLY_FLOATS2(Exposure);
POLY_FLOATS2(PixelSamples);

#define POLY_FLOATS3(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "fff", v1, v2, v3);	Py_XDECREF(pResult); };

POLY_FLOATS3(Scale);
POLY_FLOATS3(DepthOfField);
POLY_FLOATS3(Translate);

#define POLY_FLOATS4(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "ffff", v1, v2, v3, v4);	Py_XDECREF(pResult); };

POLY_FLOATS4(CropWindow);
POLY_FLOATS4(ScreenWindow);
POLY_FLOATS4(DetailRange);
POLY_FLOATS4(Rotate);

#define POLY_FLOATS6(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4, RtFloat v5, RtFloat v6) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "ffffff", v1, v2, v3, v4, v5, v6);	Py_XDECREF(pResult); };

POLY_FLOATS6(ClippingPlane);

#define POLY_FLOATS7(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4, RtFloat v5, RtFloat v6, RtFloat v7) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "fffffff", v1, v2, v3, v4, v5, v6, v7);	Py_XDECREF(pResult); };

POLY_FLOATS7(Skew);

#define POLY_FLOATS8(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4, RtFloat v5, RtFloat v6, RtFloat v7, RtFloat v8) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "ffffffff", v1, v2, v3, v4, v5, v6, v7, v8);	Py_XDECREF(pResult); };

POLY_FLOATS8(TextureCoordinates);

// BOUNDS
#define BOUNDS(callback) CALLBACKFN(callback)(RtBound b) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "((ff)(ff)(ff))",b[0],b[1],b[2],b[3],b[4],b[5]);	Py_XDECREF(pResult); };

BOUNDS(Bound);
BOUNDS(Detail);

// MATRICES

#define MATRICES(callback) CALLBACKFN(callback)(RtMatrix b) \
{ PyObject* pResult = PyObject_CallFunction(_##callback##Func, "((ffff)(ffff)(ffff)(ffff))", \
		b[0][0],b[0][1],b[0][2],b[0][3],	\
		b[1][0],b[1][1],b[1][2],b[1][3],	\
		b[2][0],b[2][1],b[2][2],b[2][3],	\
		b[3][0],b[3][1],b[3][2],b[3][3]);	Py_XDECREF(pResult); };

MATRICES(ConcatTransform);
MATRICES(Transform);

// TOKEN-DICTIONARY

#define TOKEN_DICTIONARY(callback) CALLBACKFN(callback)(RtToken name, RtInt n, RtToken tk[], RtPointer vl[]) \
{ \
	PyObject* pArgs = PyTuple_New(2); \
	PyObject* pName = Py_BuildValue("s",name);	\
	PyTuple_SetItem(pArgs, 0, pName); \
	PyObject* pDict = PyDict_New();	\
	PyTuple_SetItem(pArgs, 1, pDict); \
	ParseDictionary(pDict, n, tk, vl);	\
	PyObject* pResult = PyObject_CallObject(_##callback##Func, pArgs); \
	Py_XDECREF(pResult); \
	Py_XDECREF(pArgs); \
	Py_XDECREF(pName); \
	Py_XDECREF(pDict); \
};

TOKEN_DICTIONARY(EditBeginV);
TOKEN_DICTIONARY(IfBeginV);
TOKEN_DICTIONARY(ElseIfV);
TOKEN_DICTIONARY(ProjectionV);
TOKEN_DICTIONARY(HiderV);
TOKEN_DICTIONARY(OptionV);
TOKEN_DICTIONARY(AttributeV);
TOKEN_DICTIONARY(AtmosphereV);
TOKEN_DICTIONARY(DisplacementV);
TOKEN_DICTIONARY(ExteriorV);
TOKEN_DICTIONARY(InteriorV);
TOKEN_DICTIONARY(SurfaceV);
TOKEN_DICTIONARY(GeometryV);
TOKEN_DICTIONARY(PatchV);
TOKEN_DICTIONARY(DisplayChannelV);
TOKEN_DICTIONARY(CameraV);
TOKEN_DICTIONARY(PixelSampleImagerV);
TOKEN_DICTIONARY(EditWorldBeginV);
TOKEN_DICTIONARY(ImagerV);


//template<class T> RtVoid	Riffler<T>::_FrameBegin
//CALLBACKFN(FrameBegin)(RtInt frame)
//{
//PyObject* pArgs = PyTuple_New(2);

//PyTuple_SetItem(pArgs, 0, m_object);

//PyObject* pValue = PyInt_FromLong(frame);
//PyTuple_SetItem(pArgs, 1, pValue);

//PyObject* pResult = PyObject_CallObject(_FrameBeginFunc, pArgs);

//PyObject* pResult = PyObject_CallFunction(_FrameBeginFunc, "i", frame);
//Py_XDECREF(pResult);

//Py_DECREF(pArgs);
//Py_DECREF(pValue);
//};

template class Riffler<bool>;
template class Riffler<int>;