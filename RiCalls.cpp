/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RiCalls.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Embedded module source
*
*	Version: 0.8
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#include "stdafx.h"

#define DEFINE_RICALL(call) PyObject* _Ri##call(PyObject *self, PyObject *args)
#define SUCCESS return Py_BuildValue("i", 1);
#define FAIL return NULL;

// ONE INT
#define ONE_INT_CALL(method) DEFINE_RICALL(method) { 	RtInt value = 0; if(!PyArg_ParseTuple(args, "i", &value)) FAIL; Ri##method(value); SUCCESS };

ONE_INT_CALL(FrameBegin)
ONE_INT_CALL(Sides)

// PLAIN
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
//PLAIN_CALL(ObjectEnd);

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

// ONE FLOAT
#define ONE_FLOAT_CALL(method) DEFINE_RICALL(method) { 	RtFloat value = 0.0f; if(!PyArg_ParseTuple(args, "f", &value)) FAIL; Ri##method(value); SUCCESS };

ONE_FLOAT_CALL(FrameAspectRatio);
ONE_FLOAT_CALL(PixelVariance);
ONE_FLOAT_CALL(ShadingRate);
ONE_FLOAT_CALL(RelativeDetail);
ONE_FLOAT_CALL(Perspective);

#define ONE_COLOR_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* A =  PyTuple_GetItem(args,0);	\
	PyObject* r =  PyTuple_GetItem(A,0);		\
	PyObject* g =  PyTuple_GetItem(A,1);		\
	PyObject* b =  PyTuple_GetItem(A,2);		\
	double R = PyFloat_AsDouble(r);	\
	double G = PyFloat_AsDouble(g);	\
	double B = PyFloat_AsDouble(b);	\
	RtColor c = { R, G, B }; Ri##method(c); SUCCESS \
};

ONE_COLOR_CALL(Color);
ONE_COLOR_CALL(Opacity);

// BOOLEAN

DEFINE_RICALL(Matte)
{
	int value = 0;
	if(!PyArg_ParseTuple(args, "i", &value)) FAIL;
	RiMatte(value == 0 ? 0 : 1);
	SUCCESS 
};

// STRINGS
#define ONE_TOKEN_CALL(method) DEFINE_RICALL(method) { const char* v; if(!PyArg_ParseTuple(args, "s", &v)) FAIL; Ri##method(v); SUCCESS };

ONE_TOKEN_CALL(ShadingInterpolation);
ONE_TOKEN_CALL(SolidBegin);
ONE_TOKEN_CALL(EditAttributeBegin);
ONE_TOKEN_CALL(Orientation);
ONE_TOKEN_CALL(CoordSysTransform);
ONE_TOKEN_CALL(CoordinateSystem);
ONE_TOKEN_CALL(ScopedCoordinateSystem);
ONE_TOKEN_CALL(System);

// POLY-FLOATS

// 2
#define TWO_FLOATS_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* v0 =  PyTuple_GetItem(args,0);		\
	PyObject* v1 =  PyTuple_GetItem(args,1);		\
	Ri##method(PyFloat_AsDouble(v0), PyFloat_AsDouble(v1)); \
	SUCCESS \
};

TWO_FLOATS_CALL(Clipping);
TWO_FLOATS_CALL(Shutter);
TWO_FLOATS_CALL(Exposure);
TWO_FLOATS_CALL(PixelSamples);

// 3
#define THREE_FLOATS_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* v0 =  PyTuple_GetItem(args,0);		\
	PyObject* v1 =  PyTuple_GetItem(args,1);		\
	PyObject* v2 =  PyTuple_GetItem(args,2);		\
	Ri##method(PyFloat_AsDouble(v0), PyFloat_AsDouble(v1), PyFloat_AsDouble(v2)); \
	SUCCESS \
};

THREE_FLOATS_CALL(Scale);
THREE_FLOATS_CALL(DepthOfField);
THREE_FLOATS_CALL(Translate);

// 4
#define FOUR_FLOATS_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* v0 =  PyTuple_GetItem(args,0);		\
	PyObject* v1 =  PyTuple_GetItem(args,1);		\
	PyObject* v2 =  PyTuple_GetItem(args,2);		\
	PyObject* v3 =  PyTuple_GetItem(args,3);		\
	Ri##method(	PyFloat_AsDouble(v0), PyFloat_AsDouble(v1),	\
						PyFloat_AsDouble(v2), PyFloat_AsDouble(v3)); \
	SUCCESS \
};

FOUR_FLOATS_CALL(CropWindow);
FOUR_FLOATS_CALL(ScreenWindow);
FOUR_FLOATS_CALL(DetailRange);
FOUR_FLOATS_CALL(Rotate);

// 6
#define SIX_FLOATS_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* v0 =  PyTuple_GetItem(args,0);		\
	PyObject* v1 =  PyTuple_GetItem(args,1);		\
	PyObject* v2 =  PyTuple_GetItem(args,2);		\
	PyObject* v3 =  PyTuple_GetItem(args,3);		\
	PyObject* v4 =  PyTuple_GetItem(args,4);		\
	PyObject* v5 =  PyTuple_GetItem(args,5);		\
	Ri##method(	PyFloat_AsDouble(v0), PyFloat_AsDouble(v1),	\
						PyFloat_AsDouble(v2), PyFloat_AsDouble(v3),	\
						PyFloat_AsDouble(v4), PyFloat_AsDouble(v5)); \
	SUCCESS \
};

SIX_FLOATS_CALL(ClippingPlane);

// 7
#define SEVEN_FLOATS_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* v0 =  PyTuple_GetItem(args,0);		\
	PyObject* v1 =  PyTuple_GetItem(args,1);		\
	PyObject* v2 =  PyTuple_GetItem(args,2);		\
	PyObject* v3 =  PyTuple_GetItem(args,3);		\
	PyObject* v4 =  PyTuple_GetItem(args,4);		\
	PyObject* v5 =  PyTuple_GetItem(args,5);		\
	PyObject* v6 =  PyTuple_GetItem(args,6);		\
	Ri##method(	PyFloat_AsDouble(v0), PyFloat_AsDouble(v1),	\
						PyFloat_AsDouble(v2), PyFloat_AsDouble(v3),	\
						PyFloat_AsDouble(v4), PyFloat_AsDouble(v5),	\
						PyFloat_AsDouble(v6)); \
	SUCCESS \
};

SEVEN_FLOATS_CALL(Skew);

// 8
#define EIGHT_FLOATS_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* v0 =  PyTuple_GetItem(args,0);		\
	PyObject* v1 =  PyTuple_GetItem(args,1);		\
	PyObject* v2 =  PyTuple_GetItem(args,2);		\
	PyObject* v3 =  PyTuple_GetItem(args,3);		\
	PyObject* v4 =  PyTuple_GetItem(args,4);		\
	PyObject* v5 =  PyTuple_GetItem(args,5);		\
	PyObject* v6 =  PyTuple_GetItem(args,6);		\
	PyObject* v7 =  PyTuple_GetItem(args,7);		\
	Ri##method(	PyFloat_AsDouble(v0), PyFloat_AsDouble(v1),	\
						PyFloat_AsDouble(v2), PyFloat_AsDouble(v3),	\
						PyFloat_AsDouble(v4), PyFloat_AsDouble(v5),	\
						PyFloat_AsDouble(v6), PyFloat_AsDouble(v7)); \
	SUCCESS \
};

EIGHT_FLOATS_CALL(TextureCoordinates);

// BOUNDS

#define BOUNDS_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* A =  PyTuple_GetItem(args,0);	\
	PyObject* bX =  PyTuple_GetItem(A,0);		\
	PyObject* bY =  PyTuple_GetItem(A,1);		\
	PyObject* bZ =  PyTuple_GetItem(A,2);		\
	RtBound B;	\
	B[0] = PyFloat_AsDouble(PyTuple_GetItem(bX,0));	\
	B[1] = PyFloat_AsDouble(PyTuple_GetItem(bX,1));	\
	B[2] = PyFloat_AsDouble(PyTuple_GetItem(bY,0));	\
	B[3] = PyFloat_AsDouble(PyTuple_GetItem(bY,1));	\
	B[4] = PyFloat_AsDouble(PyTuple_GetItem(bZ,0));	\
	B[5] = PyFloat_AsDouble(PyTuple_GetItem(bZ,1));	\
	Ri##method(B); SUCCESS \
};

BOUNDS_CALL(Bound);
BOUNDS_CALL(Detail);

// MATRICIES

#define MATRICIES_CALL(method) DEFINE_RICALL(method) \
{	\
	PyObject* A =  PyTuple_GetItem(args,0);	\
	RtMatrix M;	\
	PyObject* bX =  PyTuple_GetItem(A,0);		\
	M[0][0] = PyFloat_AsDouble(PyTuple_GetItem(bX,0));	\
	M[0][1] = PyFloat_AsDouble(PyTuple_GetItem(bX,1));	\
	M[0][2] = PyFloat_AsDouble(PyTuple_GetItem(bX,2));	\
	M[0][3] = PyFloat_AsDouble(PyTuple_GetItem(bX,3));	\
	PyObject* bY =  PyTuple_GetItem(A,1);		\
	M[1][0] = PyFloat_AsDouble(PyTuple_GetItem(bY,0));	\
	M[1][1] = PyFloat_AsDouble(PyTuple_GetItem(bY,1));	\
	M[1][2] = PyFloat_AsDouble(PyTuple_GetItem(bY,2));	\
	M[1][3] = PyFloat_AsDouble(PyTuple_GetItem(bY,3));	\
	PyObject* bZ =  PyTuple_GetItem(A,2);		\
	M[2][0] = PyFloat_AsDouble(PyTuple_GetItem(bZ,0));	\
	M[2][1] = PyFloat_AsDouble(PyTuple_GetItem(bZ,1));	\
	M[2][2] = PyFloat_AsDouble(PyTuple_GetItem(bZ,2));	\
	M[2][3] = PyFloat_AsDouble(PyTuple_GetItem(bZ,3));	\
	PyObject* bW =  PyTuple_GetItem(A,3);		\
	M[3][0] = PyFloat_AsDouble(PyTuple_GetItem(bW,0));	\
	M[3][1] = PyFloat_AsDouble(PyTuple_GetItem(bW,1));	\
	M[3][2] = PyFloat_AsDouble(PyTuple_GetItem(bW,2));	\
	M[3][3] = PyFloat_AsDouble(PyTuple_GetItem(bW,3));	\
	Ri##method(M); SUCCESS \
};

MATRICIES_CALL(ConcatTransform);
MATRICIES_CALL(Transform);

// TOKEN-DICTIONARY

bool CollectDictionary(PyObject* dict, int* n, RtToken** tk, RtPointer** vl);
bool DisposeTKVL(int n, RtToken* tk, RtPointer* vl);

#define TOKEN_DICTIONARY_CALL(method) DEFINE_RICALL(method) \
{	\
	RtToken name = PyString_AsString(PyTuple_GetItem(args,0));	\
	PyObject* dict =  PyTuple_GetItem(args,1);		\
	RtInt n = 0; \
	RtToken* tk; \
	RtPointer* vl; \
	if(CollectDictionary(dict,&n, &tk,&vl))	Ri##method(name,n,tk,vl);	\
	DisposeTKVL(n,tk,vl); \
	SUCCESS	\
};

//DEFINE_RICALL(AttributeV)
//{
//	RtToken name = PyString_AsString(PyTuple_GetItem(args,0));
//	PyObject* dict =  PyTuple_GetItem(args,1);
//	RtInt n = 0;
//	RtToken* tk;
//	RtPointer* vl;
//	if(CollectDictionary(dict,&n, &tk,&vl))
//	{
//		RiAttributeV(name,n,tk,vl);
//	};
//	DisposeTKVL(n,tk,vl);
//	SUCCESS
//};

TOKEN_DICTIONARY_CALL(AttributeV);
TOKEN_DICTIONARY_CALL(EditBeginV);
TOKEN_DICTIONARY_CALL(IfBeginV);
TOKEN_DICTIONARY_CALL(ElseIfV);
TOKEN_DICTIONARY_CALL(ProjectionV);
TOKEN_DICTIONARY_CALL(HiderV);
TOKEN_DICTIONARY_CALL(OptionV);
TOKEN_DICTIONARY_CALL(AtmosphereV);
TOKEN_DICTIONARY_CALL(DisplacementV);
TOKEN_DICTIONARY_CALL(ExteriorV);
TOKEN_DICTIONARY_CALL(InteriorV);
TOKEN_DICTIONARY_CALL(SurfaceV);
TOKEN_DICTIONARY_CALL(GeometryV);
TOKEN_DICTIONARY_CALL(PatchV);
TOKEN_DICTIONARY_CALL(DisplayChannelV);
TOKEN_DICTIONARY_CALL(CameraV);
TOKEN_DICTIONARY_CALL(PixelSampleImagerV);
TOKEN_DICTIONARY_CALL(EditWorldBeginV);
TOKEN_DICTIONARY_CALL(ImagerV);

// DUO-TOKENS/DICT
#define DUO_TOKEN_DICTIONARY_CALL(method) DEFINE_RICALL(method) \
{	\
	RtToken one = PyString_AsString(PyTuple_GetItem(args,0));	\
	RtToken two = PyString_AsString(PyTuple_GetItem(args,1));	\
	PyObject* dict =  PyTuple_GetItem(args,2);		\
	RtInt n = 0; \
	RtToken* tk; \
	RtPointer* vl; \
	if(CollectDictionary(dict,&n, &tk,&vl))	Ri##method(one, two,n,tk,vl);	\
	DisposeTKVL(n,tk,vl); \
	SUCCESS	\
};

DUO_TOKEN_DICTIONARY_CALL(ResourceV);
DUO_TOKEN_DICTIONARY_CALL(ShaderV);

// DICT WITH HANDLES == ONE TOKENS WITH DICT
TOKEN_DICTIONARY_CALL(ArchiveBeginV);
TOKEN_DICTIONARY_CALL(LightSourceV);

// MISC
DEFINE_RICALL(ReadArchiveV)
{
	RtToken name = PyString_AsString(PyTuple_GetItem(args,0));
	PyObject* dict =  PyTuple_GetItem(args,1);
	RtInt n = 0;
	RtToken* tk;
	RtPointer* vl;
	if(CollectDictionary(dict,&n, &tk,&vl)) RiReadArchiveV(name,NULL,n,tk,vl);
	DisposeTKVL(n,tk,vl);
	SUCCESS
};

DEFINE_RICALL(MotionBeginV)
{
	PyObject* pT = PyTuple_GetItem(args,0);
	if(!PyTuple_Check(pT)) FAIL;

	RtInt n = PyTuple_Size(pT);
	if(n<1) FAIL;

	float* times = new float[n];
	if(times == NULL) FAIL;
	
	for(int i=0;i<n;i++) times[i] =  PyFloat_AsDouble(PyTuple_GetItem(pT,i));

	RiMotionBeginV(n,times);

	delete [] times;

	SUCCESS
};

DEFINE_RICALL(Format)
{
	if(PyTuple_Size(args) != 3) FAIL;

	int xres = PyInt_AsLong(PyTuple_GetItem(args,0));
	int yres = PyInt_AsLong(PyTuple_GetItem(args,1));
	float aspect = PyFloat_AsDouble(PyTuple_GetItem(args,2));

	RiFormat(xres,yres,aspect);

	SUCCESS
};

DEFINE_RICALL(GeometricApproximation)
{
	if(PyTuple_Size(args) != 2) FAIL;

	RtToken type = PyString_AsString(PyTuple_GetItem(args,0));
	float val = PyFloat_AsDouble(PyTuple_GetItem(args,1));

	RiGeometricApproximation(type,val);

	delete [] type;

	SUCCESS
};

DEFINE_RICALL(Quantize)
{
	if(PyTuple_Size(args) != 5) FAIL;

	RtToken type = PyString_AsString(PyTuple_GetItem(args,0));
	int one = PyInt_AsLong(PyTuple_GetItem(args,1));
	int _min = PyInt_AsLong(PyTuple_GetItem(args,2));
	int _max = PyInt_AsLong(PyTuple_GetItem(args,3));
	float ampl = PyFloat_AsDouble(PyTuple_GetItem(args,4));

	RiQuantize(type,one,_min,_max,ampl);

	delete [] type;

	SUCCESS
};

DEFINE_RICALL(Illuminate)
{
	if(PyTuple_Size(args) != 2) FAIL;

	RtToken light = PyString_AsString(PyTuple_GetItem(args,0));
	RtBoolean on = (PyInt_AsLong(PyTuple_GetItem(args,1)) == 0 ? 0 : 1);

	RiIlluminate((RtLightHandle)light,on);

	delete [] light;

	SUCCESS
};

DEFINE_RICALL(DisplayV)
{
	if(PyTuple_Size(args) != 4) FAIL;

	char* name = PyString_AsString(PyTuple_GetItem(args,0));
	RtToken type = PyString_AsString(PyTuple_GetItem(args,1));
	RtToken mode = PyString_AsString(PyTuple_GetItem(args,2));

	PyObject* dict =  PyTuple_GetItem(args,3);
	RtInt n = 0;
	RtToken* tk;
	RtPointer* vl;
	if(CollectDictionary(dict,&n, &tk,&vl)) RiDisplayV(name,type,mode,n,tk,vl);
	DisposeTKVL(n,tk,vl);

	delete [] name;
	delete [] type;
	delete [] mode;

	SUCCESS
};

RtFilterFunc getFilterFunction(PyObject* obj)
{
	char* name = PyString_AsString(obj);

	RtFilterFunc filterFunc = RiBoxFilter;

	if(strcmp(name,"bessel")==0) filterFunc = RiBesselFilter;
	else if(strcmp(name,"blackman-harris")==0) filterFunc = RiBlackmanHarrisFilter;
	else if(strcmp(name,"box")==0) filterFunc = RiBoxFilter;
	else if(strcmp(name,"catmull-rom")==0) filterFunc = RiCatmullRomFilter;
	else if(strcmp(name,"disk")==0) filterFunc = RiDiskFilter;
	else if(strcmp(name,"gaussian")==0) filterFunc = RiGaussianFilter;
	else if(strcmp(name,"mitchell")==0) filterFunc = RiMitchellFilter;
	else if(strcmp(name,"lanczos")==0) filterFunc = RiLanczosFilter;
	else if(strcmp(name,"separable-catmull-rom")==0) filterFunc = RiSeparableCatmullRomFilter;
	else if(strcmp(name,"sinc")==0) filterFunc = RiSincFilter;
	else if(strcmp(name,"triangle")==0) filterFunc = RiTriangleFilter;

	delete [] name;

	return filterFunc;
};

DEFINE_RICALL(PixelFilter)
{
	if(PyTuple_Size(args) != 3) FAIL;

	RtFilterFunc filterFunc = getFilterFunction(PyTuple_GetItem(args,0));

	RtFloat x = PyFloat_AsDouble(PyTuple_GetItem(args,1));
	RtFloat y = PyFloat_AsDouble(PyTuple_GetItem(args,2));

	RiPixelFilter(filterFunc,x,y);

	SUCCESS
};

DEFINE_RICALL(Basis)
{
	if(PyTuple_Size(args) != 4) FAIL;

	RtBasis ubasis;
	{
		char* uname = PyString_AsString(PyTuple_GetItem(args,0));
		if(strcmp(uname,"bezier")==0) memcpy(ubasis,RiBezierBasis,64);
		else if(strcmp(uname,"spline")==0) memcpy(ubasis,RiBSplineBasis,64);
		else if(strcmp(uname,"catmull-rom")==0) memcpy(ubasis,RiCatmullRomBasis,64);
		else if(strcmp(uname,"hermite")==0) memcpy(ubasis,RiHermiteBasis,64);
		else if(strcmp(uname,"power")==0) memcpy(ubasis,RiPowerBasis,64);
		else FAIL;
		delete [] uname;
	};

	RtBasis vbasis;
	{
		char* vname = PyString_AsString(PyTuple_GetItem(args,2));
		if(strcmp(vname,"bezier")==0) memcpy(vbasis,RiBezierBasis,64);
		else if(strcmp(vname,"spline")==0) memcpy(vbasis,RiBSplineBasis,64);
		else if(strcmp(vname,"catmull-rom")==0) memcpy(vbasis,RiCatmullRomBasis,64);
		else if(strcmp(vname,"hermite")==0) memcpy(vbasis,RiHermiteBasis,64);
		else if(strcmp(vname,"power")==0) memcpy(vbasis,RiPowerBasis,64);
		else FAIL;
		delete [] vname;
	}

	RtFloat x = PyFloat_AsDouble(PyTuple_GetItem(args,1));
	RtFloat y = PyFloat_AsDouble(PyTuple_GetItem(args,3));

	RiBasis(ubasis,x,vbasis,y);

	SUCCESS
};

DEFINE_RICALL(VArchiveRecord)
{
	if(PyTuple_Size(args) != 1) FAIL;

	char* cmnt = PyString_AsString(PyTuple_GetItem(args,0));

	va_list v;

	RiVArchiveRecord(RI_VERBATIM,cmnt,v);

	delete [] cmnt;

	SUCCESS
};

// MAKERS

DEFINE_RICALL(MakeTextureV)
{
	if(PyTuple_Size(args) != 6) FAIL;

	char* pix = PyString_AsString(PyTuple_GetItem(args,0));
	char* tex = PyString_AsString(PyTuple_GetItem(args,1));

	PyObject* pW = PyTuple_GetItem(args,2);
	RtToken sw = PyString_AsString(PyTuple_GetItem(pW,0));
	RtToken tw = PyString_AsString(PyTuple_GetItem(pW,1));

	RtFilterFunc filterFunc = getFilterFunction(PyTuple_GetItem(args,3));

	PyObject* pF = PyTuple_GetItem(args,4);
	float sf = PyFloat_AsDouble(PyTuple_GetItem(pF,0));
	float tf = PyFloat_AsDouble(PyTuple_GetItem(pF,1));

	PyObject* dict =  PyTuple_GetItem(args,5);
	RtInt n = 0;
	RtToken* tk;
	RtPointer* vl;
	if(CollectDictionary(dict,&n, &tk,&vl))
	{
		RiMakeTextureV(pix,tex,sw,tw,filterFunc,sf,tf,n,tk,vl);
	}
	DisposeTKVL(n,tk,vl);

	delete [] sw;
	delete [] tw;
	delete [] tex;
	delete [] pix;

	SUCCESS
};

DEFINE_RICALL(MakeShadowV)
{
	if(PyTuple_Size(args) != 3) FAIL;

	char* pix = PyString_AsString(PyTuple_GetItem(args,0));
	char* tex = PyString_AsString(PyTuple_GetItem(args,1));

	PyObject* dict =  PyTuple_GetItem(args,3);
	RtInt n = 0;
	RtToken* tk;
	RtPointer* vl;
	if(CollectDictionary(dict,&n, &tk,&vl))
	{
		RiMakeShadowV(pix,tex,n,tk,vl);
	}
	DisposeTKVL(n,tk,vl);

	delete [] tex;
	delete [] pix;

	SUCCESS
};

DEFINE_RICALL(MakeCubeFaceEnvironmentV)
{
	if(PyTuple_Size(args) != 6) FAIL;

	PyObject* pP = PyTuple_GetItem(args,0);
	char* px = PyString_AsString(PyTuple_GetItem(pP,0));
	char* nx = PyString_AsString(PyTuple_GetItem(pP,1));
	char* py = PyString_AsString(PyTuple_GetItem(pP,2));
	char* ny = PyString_AsString(PyTuple_GetItem(pP,3));
	char* pz = PyString_AsString(PyTuple_GetItem(pP,4));
	char* nz = PyString_AsString(PyTuple_GetItem(pP,5));

	char* tex = PyString_AsString(PyTuple_GetItem(args,1));

	float fov = PyFloat_AsDouble(PyTuple_GetItem(args,2));

	RtFilterFunc filterFunc = getFilterFunction(PyTuple_GetItem(args,3));

	PyObject* pF = PyTuple_GetItem(args,4);
	float sf = PyFloat_AsDouble(PyTuple_GetItem(pF,0));
	float tf = PyFloat_AsDouble(PyTuple_GetItem(pF,1));

	PyObject* dict =  PyTuple_GetItem(args,5);
	RtInt n = 0;
	RtToken* tk;
	RtPointer* vl;
	if(CollectDictionary(dict,&n, &tk,&vl))
	{
		RiMakeCubeFaceEnvironmentV(
			px,nx,py,ny,pz,nz,tex,
			fov,filterFunc,sf,tf,n,tk,vl);
	}
	DisposeTKVL(n,tk,vl);

	delete [] tex;
	delete [] px; delete [] nx;
	delete [] py; delete [] ny;
	delete [] pz; delete [] nz;

	SUCCESS
};

DEFINE_RICALL(MakeLatLongEnvironmentV)
{
	if(PyTuple_Size(args) != 5) FAIL;

	char* pix = PyString_AsString(PyTuple_GetItem(args,0));
	char* tex = PyString_AsString(PyTuple_GetItem(args,1));

	RtFilterFunc filterFunc = getFilterFunction(PyTuple_GetItem(args,2));

	PyObject* pF = PyTuple_GetItem(args,3);
	float sf = PyFloat_AsDouble(PyTuple_GetItem(pF,0));
	float tf = PyFloat_AsDouble(PyTuple_GetItem(pF,1));

	PyObject* dict =  PyTuple_GetItem(args,4);
	RtInt n = 0;
	RtToken* tk;
	RtPointer* vl;
	if(CollectDictionary(dict,&n, &tk,&vl))
	{
		RiMakeLatLongEnvironmentV(pix,tex,filterFunc,sf,tf,n,tk,vl);
	}
	DisposeTKVL(n,tk,vl);

	delete [] tex;
	delete [] pix;

	SUCCESS
};

DEFINE_RICALL(MakeBrickMapV)
{
	if(PyTuple_Size(args) != 3) FAIL;

	PyObject* pM = PyTuple_GetItem(args,0);

	if(!PyTuple_Check(pM)) FAIL;

	int cnt = PyTuple_Size(pM);

	if(cnt < 1) FAIL;

	RtToken* maps = new RtToken[cnt];

	for(int i=0;i<cnt;i++) maps[i] = PyString_AsString(PyTuple_GetItem(pM,i));

	char* tex = PyString_AsString(PyTuple_GetItem(args,1));

	PyObject* dict =  PyTuple_GetItem(args,2);
	RtInt n = 0;
	RtToken* tk;
	RtPointer* vl;
	if(CollectDictionary(dict,&n, &tk,&vl))
	{
		RiMakeBrickMapV(cnt,(char**)maps,tex,n,tk,vl);
	}
	DisposeTKVL(n,tk,vl);

	delete [] tex;

	for(int i=0;i<cnt;i++) delete [] maps[i];
	delete [] maps;

	SUCCESS
};

// GPRIMS

