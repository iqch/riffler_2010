/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RIF_Riffler.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Base source
*
*	Version: 0.4
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#include "stdafx.h"

#include "RiCalls.h"

//#include "Riffler.h"

#define DECLARE_CALLBACK(callback) /*static*/ PyObject* _##callback##Func; static RtVoid _##callback
//#define DEFINE_CALLBACKFN(callback) PyObject* Riffler::_##callback##Func = NULL;

#define PARSE_CALLBACK(callback) _##callback##Func = PyObject_GetAttrString(m_filterobj, #callback); \
	if(PyCallable_Check(_##callback##Func)) ##callback = &Riffler::_##callback; \
else { Py_XDECREF(_##callback##Func); };

#define PARSE_CALLBACKV(callback) _##callback##VFunc = PyObject_GetAttrString(m_filterobj, #callback); \
	if(PyCallable_Check(_##callback##VFunc)) ##callback##V = &Riffler::_##callback##V; \
else Py_XDECREF(_##callback##VFunc);

#define CLEAN_CALLBACK(callback) if(_##callback##Func != NULL) Py_XDECREF(_##callback##Func);

//#define FILTERS_COUNT 2
//
//Riffler<bool> g_bR;
//Riffler<int> g_iR;
//
//SetupLayer* g_FILTERS[FILTERS_COUNT] = { &g_bR, &g_iR };
//int g_current = 0;

class Riffler : public RifPlugin, public RifFilter
{
public:
	Riffler(int argc, char **argv);
	virtual ~Riffler();

	virtual RifFilter& GetFilter();

	// REFCOUNT PART
	static unsigned int m_counter;
protected:

	//RifFilter* m_filter;
	PyObject* m_module;
	PyObject* m_filterobj;

private:
	//static PyObject* m_object;
	//T m_member;
	// CATCHERS

	// ONE INT
	DECLARE_CALLBACK(FrameBegin)(RtInt frame);
	DECLARE_CALLBACK(Sides)(RtInt sides);

	// PLAIN
	DECLARE_CALLBACK(FrameEnd)();

	DECLARE_CALLBACK(WorldBegin)();
	DECLARE_CALLBACK(WorldEnd)();

	DECLARE_CALLBACK(AttributeBegin)();
	DECLARE_CALLBACK(AttributeEnd)();

	DECLARE_CALLBACK(TransformBegin)();
	DECLARE_CALLBACK(TransformEnd)();

	DECLARE_CALLBACK(SolidEnd)();

	DECLARE_CALLBACK(MotionEnd)();

	DECLARE_CALLBACK(Identity)();

	DECLARE_CALLBACK(ReverseOrientation)();

	DECLARE_CALLBACK(ArchiveEnd)();

	DECLARE_CALLBACK(Else)();
	DECLARE_CALLBACK(IfEnd)();

	DECLARE_CALLBACK(ResourceBegin)();
	DECLARE_CALLBACK(ResourceEnd)();
	DECLARE_CALLBACK(EditEnd)();
	DECLARE_CALLBACK(EditAttributeEnd)();
	DECLARE_CALLBACK(EditWorldEnd)();

	// ONE FLOAT
	DECLARE_CALLBACK(FrameAspectRatio)(RtFloat aspect);
	DECLARE_CALLBACK(PixelVariance)(RtFloat variation);
	DECLARE_CALLBACK(ShadingRate)(RtFloat size);
	DECLARE_CALLBACK(RelativeDetail)(RtFloat relativedetail);
	DECLARE_CALLBACK(Perspective)(RtFloat fov);

	// ONE COLOR
	DECLARE_CALLBACK(Color)(RtColor color);
	DECLARE_CALLBACK(Opacity)(RtColor color);

	// BOOLEAN
	DECLARE_CALLBACK(Matte)(RtBoolean onoff);

	// STRINGS
	DECLARE_CALLBACK(ShadingInterpolation)(RtToken type);
	DECLARE_CALLBACK(SolidBegin)(RtToken operation);
	DECLARE_CALLBACK(EditAttributeBegin)(RtToken name);
	DECLARE_CALLBACK(Orientation)(RtToken orientation);
	DECLARE_CALLBACK(CoordSysTransform)(RtToken space);
	DECLARE_CALLBACK(CoordinateSystem)(RtToken space);
	DECLARE_CALLBACK(ScopedCoordinateSystem)(RtToken space);
	DECLARE_CALLBACK(System)(RtToken cmdstring);


	// POLY-FLOATS

	// 2
	DECLARE_CALLBACK(Clipping)(RtFloat hither, RtFloat yon);
	DECLARE_CALLBACK(Shutter)(RtFloat min, RtFloat max);
	DECLARE_CALLBACK(Exposure)(RtFloat gain, RtFloat gamma);
	DECLARE_CALLBACK(PixelSamples)(RtFloat xsamples, RtFloat ysamples);

	// 3
	DECLARE_CALLBACK(Scale)(RtFloat sx, RtFloat sy, RtFloat sz);
	DECLARE_CALLBACK(DepthOfField)(RtFloat fstop, RtFloat focallength, RtFloat focaldistance);
	DECLARE_CALLBACK(Translate)(RtFloat dx, RtFloat dy, RtFloat dz);

	// 4
	DECLARE_CALLBACK(CropWindow)(RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax);
	DECLARE_CALLBACK(ScreenWindow)(RtFloat left, RtFloat right, RtFloat top, RtFloat bot);
	DECLARE_CALLBACK(DetailRange)(RtFloat minv, RtFloat lowtran, RtFloat uptran, RtFloat maxv);
	DECLARE_CALLBACK(Rotate)(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz);

	// 6
	DECLARE_CALLBACK(ClippingPlane)(RtFloat Nx, RtFloat Ny, RtFloat Nz, RtFloat Px, RtFloat Py, RtFloat Pz);

	// 7
	DECLARE_CALLBACK(Skew)(RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1, RtFloat dx2, RtFloat dy2, RtFloat dz2);

	// 8
	DECLARE_CALLBACK(TextureCoordinates)(RtFloat s1, RtFloat t1, 	RtFloat s2, RtFloat t2, RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4);

	// BOUNDS
	DECLARE_CALLBACK(Bound)(RtBound bound);
	DECLARE_CALLBACK(Detail)(RtBound bound);

	// MATRICIES
	DECLARE_CALLBACK(ConcatTransform)(RtMatrix transform);
	DECLARE_CALLBACK(Transform)(RtMatrix transform);

	// TOKEN-DICTIONARY
	DECLARE_CALLBACK(EditBeginV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(IfBeginV)(RtToken expr, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(ElseIfV)(RtToken expr, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(ProjectionV)(RtToken name, 	RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(HiderV)(RtToken type, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(OptionV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(AttributeV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(AtmosphereV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(DisplacementV)(RtToken name,	RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(ExteriorV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(InteriorV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(SurfaceV)(RtToken name,	RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(GeometryV)(RtToken type, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(PatchV)(RtToken type, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(DisplayChannelV)(RtToken mode, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(CameraV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(PixelSampleImagerV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(EditWorldBeginV)(RtToken name, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(ImagerV)(RtToken name, RtInt, RtToken[], RtPointer[]);

	// DUO-TOKENS/DICT
	DECLARE_CALLBACK(ResourceV)(RtToken handle, RtToken type, RtInt, RtToken[], RtPointer[]);
	DECLARE_CALLBACK(ShaderV)(RtToken name, RtToken handle, RtInt, RtToken[], RtPointer[]);

	// TOKEN/DICT WITH HANDLES
	/*static*/ PyObject* _ArchiveBeginVFunc;
	static RtArchiveHandle _ArchiveBeginV(RtToken name, RtInt, RtToken[], RtPointer[]);

	/*static*/ PyObject* _LightSourceVFunc;
	static RtLightHandle	_LightSourceV(RtToken name, RtInt, RtToken[], RtPointer[]);

	// GPRIMS
	//RtVoid  	_BlobbyV(RtInt nleaf, RtInt ninst, RtInt inst[], RtInt nflt, RtFloat flt[], RtInt nstr, RtToken str[], RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_ConeV(RtFloat height, RtFloat radius, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_CurvesV(RtToken type, RtInt ncurves, RtInt nvert[], RtToken wrap, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_CylinderV(RtFloat rad, RtFloat zmin, RtFloat zmax, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_DiskV(RtFloat height, RtFloat radius, RtFloat tmax,	RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_GeneralPolygonV(RtInt nloops, RtInt nverts[], RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_HyperboloidV(RtPoint point1, RtPoint point2, RtFloat tmax,	RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_NuPatchV(RtInt nu, RtInt uorder, RtFloat uknot[], RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder, RtFloat vknot[], RtFloat vmin, RtFloat vmax, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_ParaboloidV(RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_PatchMeshV(RtToken type, RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_PointsGeneralPolygonsV(RtInt npolys, RtInt nloops[], RtInt nverts[], RtInt verts[], RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_PointsPolygonsV(RtInt npolys, RtInt nverts[], RtInt verts[], RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_PointsV(RtInt nverts, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_PolygonV(RtInt nverts, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_Procedural(RtPointer data, RtBound bound, RtProcSubdivFunc sdfunc, RtProcFreeFunc freefunc);
	//RtVoid  	_SphereV(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_SubdivisionMeshV(RtToken mask, RtInt nf, RtInt nverts[], RtInt verts[], RtInt nt, RtToken tags[], RtInt nargs[], RtInt intargs[], RtFloat floatargs[], RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_TorusV(RtFloat majrad, RtFloat minrad, RtFloat phimin, RtFloat phimax, 	RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_TrimCurve(RtInt nloops, RtInt ncurves[], RtInt order[], RtFloat knot[], RtFloat min[], RtFloat max[], RtInt n[], RtFloat u[], RtFloat v[], RtFloat w[]);
	//RtVoid  	_HierarchicalSubdivisionMeshV(RtToken mask, RtInt nf, 	RtInt nverts[], RtInt verts[], RtInt nt, RtToken tags[],	RtInt nargs[], RtInt intargs[], RtFloat floatargs[], RtToken stringargs[], RtInt, RtToken[], RtPointer[]);

	// MAKERS
	//RtVoid  	_MakeCubeFaceEnvironmentV(char *px, char *nx, char *py, char *ny,	char *pz, char *nz, char *tex, RtFloat fov,	RtFilterFunc filterFunc,	RtFloat swidth, RtFloat ywidth, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_MakeLatLongEnvironmentV(char *pic, char *tex, RtFilterFunc filterFunc,	RtFloat swidth, RtFloat twidth, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_MakeShadowV(char *pic, char *tex, 	RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_MakeTextureV(char *pic, char *tex, 	RtToken swrap, RtToken twrap,	RtFilterFunc filterFunc, RtFloat swidth, RtFloat twidth, RtInt, RtToken[], RtPointer[]);
	//RtVoid		_MakeBrickMapV(RtInt, RtToken *, RtToken, RtInt, RtToken[], RtPointer[]);

	// RECENT
	//RtVoid  	_ReadArchiveV(RtToken name, RtArchiveCallback callback, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_MotionBeginV(RtInt n, RtFloat times[]);
	//RtVoid  	_Format(RtInt xres, RtInt yres, RtFloat aspect);
	//RtVoid  	_DisplayV(char *name, RtToken type, RtToken mode, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_PixelFilter(RtFilterFunc filterFunc, RtFloat xwidth, RtFloat ywidth);
	//RtVoid  	_Quantize(RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ampl);
	//RtVoid  	_Illuminate(RtLightHandle light, RtBoolean onoff);
	//RtVoid  	_GeometricApproximation(RtToken type, RtFloat value);
	//RtVoid  	_Basis(RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep);

	// TO SKIP
	//RtVoid  	_VArchiveRecord(RtToken type, char *format, va_list vap);
	//RtToken 	_Declare(char *name, char *declaration);
	//RtVoid  	_PixelFidelity(RtFloat variation); // OBSOLETE call: see RiPixelVariance
	//RtVoid		_ErrorHandler(RtErrorHandler);
	//RtVoid  	_ObjectInstance(RtObjectHandle handle);
	//DECLARE_CALLBACK(ObjectBegin)();
	//DECLARE_CALLBACK(ObjectEnd)();
	//RtLightHandle	_AreaLightSourceV(RtToken name, RtInt, RtToken[], RtPointer[]); // USELESS
};

unsigned int Riffler::m_counter = 0;

Riffler::Riffler(int argc, char **argv)
	//: m_filter(NULL)
	: m_module(NULL)
	, m_filterobj(NULL)
{
	// ...HOPING, RIF FILTERS ARE BUILT NOT IN PARALLEL

	// AMOUNT CHECKING

	//if(g_current == FILTERS_COUNT)
	//{
	//	cout << "RIFFLER: Excessive fiters count" << endl;
	//	return;
	//}

	
	// LOAD MODULE
	if(argc < 1)
	{
		cout << "RIFFLER: Insufficient parameters - script name is not found" << endl;
		return;
	};

	//PyObject *pName = PyString_FromString(argv[0]);

	//m_module = PyImport_Import(pName);

	m_module = PyImport_ImportModuleNoBlock(argv[0]);
	//Py_DECREF(pName);

	if(m_module == NULL)
	{
		cout << "RIFFLER: script " << argv[0] << " is not found" << endl;
		return;
	};

	// FIND FILTER OBJECT
	PyObject *pFunc = PyObject_GetAttrString(m_module, "plugin");

	if(pFunc == NULL)
	{
		cout << "RIFFLER: script " << argv[0] << " does not contain 'plugin'-function" << endl;
		if(PyErr_Occurred()) PyErr_Print();
		Py_DECREF(m_module); m_module = NULL;
		return;
	};
	
	if(!PyCallable_Check(pFunc))
	{
		cout << "RIFFLER: script " << argv[0] << " does not contain 'plugin'-function" << endl;
		if(PyErr_Occurred()) PyErr_Print();
		Py_XDECREF(pFunc); // got 2 references
		Py_DECREF(m_module); m_module = NULL;
		return;
	};

	PyObject *pArgs = PyTuple_New(argc-1);

	for(int i=1; i<argc; i++) 
	{
		PyObject *pVal = PyString_FromString(argv[i]);

		if (pVal == NULL)
		{
			cout << "RIFFLER: cannot convert script's parameters" << endl;
			if(PyErr_Occurred()) PyErr_Print();
			Py_DECREF(pArgs);
			Py_XDECREF(pFunc);
			Py_DECREF(m_module); m_module = NULL;
			return;
		}

		PyTuple_SetItem(pArgs, i-1, pVal);
	};

	PyObject *pArgList = PyTuple_New(1);
	PyTuple_SetItem(pArgList, 0, pArgs);

	m_filterobj = PyObject_CallObject(pFunc, pArgList);
	Py_XDECREF(pArgList);
	Py_XDECREF(pFunc);

	if(m_filterobj == NULL)
	{
		cout << "RIFFLER: calling 'plugin' function failed!" << endl;

		PyErr_Print();
		Py_DECREF(m_module); m_module = NULL;
		return;
	};

	// SETUP AS FILTER
	//m_filter = this;
	//m_filter.ClientData = static_cast<void *>(m_filterobj);

	// ONE INT
	PARSE_CALLBACK(FrameBegin)
	PARSE_CALLBACK(Sides)

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
	//PARSE_CALLBACK(ObjectEnd);

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

	// TOKEN-DICTIONARY
	PARSE_CALLBACKV(EditBegin);
	PARSE_CALLBACKV(IfBegin);
	PARSE_CALLBACKV(ElseIf);
	PARSE_CALLBACKV(Projection);
	PARSE_CALLBACKV(Hider);
	PARSE_CALLBACKV(Option);
	PARSE_CALLBACKV(Attribute);
	PARSE_CALLBACKV(Atmosphere);
	PARSE_CALLBACKV(Displacement);
	PARSE_CALLBACKV(Exterior);
	PARSE_CALLBACKV(Interior);
	PARSE_CALLBACKV(Surface);
	PARSE_CALLBACKV(Geometry);
	PARSE_CALLBACKV(Patch);
	PARSE_CALLBACKV(DisplayChannel);
	PARSE_CALLBACKV(Camera);
	PARSE_CALLBACKV(PixelSampleImager);
	PARSE_CALLBACKV(EditWorldBegin);
	PARSE_CALLBACKV(Imager);

	// DUO-TOKENS/DICT
	PARSE_CALLBACKV(Resource);
	PARSE_CALLBACKV(Shader);

	// DICT WITH HANDLES
	PARSE_CALLBACKV(ArchiveBegin);
	PARSE_CALLBACKV(LightSource);

	//g_FILTERS[g_current]->Setup(m_filterobj);
	//g_current++;
	int i=0;
};

Riffler::~Riffler()
{
	// CLEANUP
	if(m_filterobj != NULL)
	{
		// PLAIN
		//if(_FrameEndFunc != NULL) Py_XDECREF(_FrameEndFunc);
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
	};

	// DESTROY
	//if(m_filter != NULL) delete m_filter;
	if(m_filterobj != NULL) Py_XDECREF(m_filterobj);
	if(m_module != NULL) Py_XDECREF(m_module);

	// ...HOPING, RIF FILTERS ARE DESTROYED NOT IN PARALLEL
	Riffler::m_counter--;
	if(m_counter == 0)
	{
		Py_Finalize();
	}
};

RifFilter& Riffler::GetFilter()
{
	return *this;
};

extern "C" 
{
	DLLEXPORT RifPlugin* RifPluginManufacture(int argc, char **argv)
	{
		if(Riffler::m_counter == 0)
		{
			// PRIMARY SETUP
			Py_Initialize();

			if(Py_IsInitialized() == 0)
			{
				cout << "RIFFLER: python initialization failed!" << endl;
				return NULL;
			}
			Py_InitModule("prman", MethodTable);
			Riffler::m_counter++;
		};

		//for(int i=0;i<argc;i++)
		//{
		//	cout << i << ": \t" << argv[i] << endl;
		//};

		return new Riffler(argc,argv);
	};
};

bool ParseDictionary(PyObject* dict, int n, RtToken tk[], RtPointer vl[]);

#define CALLBACKFN(callback)RtVoid Riffler::_##callback

#define GETFILTER Riffler* filter = static_cast<Riffler*>(RifGetCurrentPlugin());

#define FORWARD_PLAIN(callback) CALLBACKFN(callback)() { GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, NULL); Py_XDECREF(pResult); };

FORWARD_PLAIN(FrameEnd)

FORWARD_PLAIN(WorldBegin)
FORWARD_PLAIN(WorldEnd)

FORWARD_PLAIN(AttributeBegin);
FORWARD_PLAIN(AttributeEnd);

FORWARD_PLAIN(TransformBegin);
FORWARD_PLAIN(TransformEnd);

FORWARD_PLAIN(SolidEnd);

//FORWARD_PLAIN(ObjectBegin);
//FORWARD_PLAIN(ObjectEnd);

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

#define FORWARD_INT(callback) CALLBACKFN(callback)(RtInt value) { GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "i", value); Py_XDECREF(pResult); };

FORWARD_INT(FrameBegin)
FORWARD_INT(Sides)

#define FORWARD_FLOAT(callback) CALLBACKFN(callback)(RtFloat value) { GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "f", value); Py_XDECREF(pResult); };

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
	GETFILTER; \
	PyObject* pResult = PyObject_CallObject(filter->_##callback##Func, pArgs); \
	Py_XDECREF(pResult); \
	Py_XDECREF(pArgs); \
};
//	Py_XDECREF(pfArgs); \

FORWARD_COLOR(Color);
FORWARD_COLOR(Opacity);

// BOOLEAN
CALLBACKFN(Matte)(RtBoolean onoff)
{
	GETFILTER;
	PyObject* pResult = PyObject_CallFunction(filter->_MatteFunc, "i", (onoff == 0 ? 0 : 1));
	Py_XDECREF(pResult);
};

// STRINGS
#define FORWARD_STRING(callback) CALLBACKFN(callback)(RtToken v) { GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "s", v); Py_XDECREF(pResult); };

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
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "ff", v1, v2);	Py_XDECREF(pResult); };

POLY_FLOATS2(Clipping);
POLY_FLOATS2(Shutter);
POLY_FLOATS2(Exposure);
POLY_FLOATS2(PixelSamples);

#define POLY_FLOATS3(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3) \
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "fff", v1, v2, v3);	Py_XDECREF(pResult); };

POLY_FLOATS3(Scale);
POLY_FLOATS3(DepthOfField);
POLY_FLOATS3(Translate);

#define POLY_FLOATS4(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4) \
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "ffff", v1, v2, v3, v4);	Py_XDECREF(pResult); };

POLY_FLOATS4(CropWindow);
POLY_FLOATS4(ScreenWindow);
POLY_FLOATS4(DetailRange);
POLY_FLOATS4(Rotate);

#define POLY_FLOATS6(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4, RtFloat v5, RtFloat v6) \
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "ffffff", v1, v2, v3, v4, v5, v6);	Py_XDECREF(pResult); };

POLY_FLOATS6(ClippingPlane);

#define POLY_FLOATS7(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4, RtFloat v5, RtFloat v6, RtFloat v7) \
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "fffffff", v1, v2, v3, v4, v5, v6, v7);	Py_XDECREF(pResult); };

POLY_FLOATS7(Skew);

#define POLY_FLOATS8(callback) CALLBACKFN(callback)(RtFloat v1, RtFloat v2, RtFloat v3, RtFloat v4, RtFloat v5, RtFloat v6, RtFloat v7, RtFloat v8) \
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "ffffffff", v1, v2, v3, v4, v5, v6, v7, v8);	Py_XDECREF(pResult); };

POLY_FLOATS8(TextureCoordinates);

// BOUNDS
#define BOUNDS(callback) CALLBACKFN(callback)(RtBound b) \
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "((ff)(ff)(ff))",b[0],b[1],b[2],b[3],b[4],b[5]);	Py_XDECREF(pResult); };

BOUNDS(Bound);
BOUNDS(Detail);

// MATRICES

#define MATRICES(callback) CALLBACKFN(callback)(RtMatrix b) \
{ GETFILTER; PyObject* pResult = PyObject_CallFunction(filter->_##callback##Func, "((ffff)(ffff)(ffff)(ffff))", \
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
	GETFILTER; \
	PyObject* pResult = PyObject_CallObject(filter->_##callback##Func, pArgs); \
	Py_XDECREF(pResult); \
	Py_XDECREF(pArgs); \
};
//	Py_XDECREF(pName); \
//	Py_XDECREF(pDict); \

//CALLBACKFN(AttributeV)(RtToken name, RtInt n, RtToken tk[], RtPointer vl[])
//{
//	PyObject* pArgs = PyTuple_New(2);
//	PyObject* pName = Py_BuildValue("s",name);
//	PyTuple_SetItem(pArgs, 0, pName);
//	PyObject* pDict = PyDict_New();
//	PyTuple_SetItem(pArgs, 1, pDict);
//	ParseDictionary(pDict, n, tk, vl);
//	GETFILTER;
//	PyObject* pResult = PyObject_CallObject(filter->_AttributeVFunc, pArgs);
//	Py_XDECREF(pResult);
//	Py_XDECREF(pArgs);
//};

TOKEN_DICTIONARY(AttributeV);
TOKEN_DICTIONARY(EditBeginV);
TOKEN_DICTIONARY(IfBeginV);
TOKEN_DICTIONARY(ElseIfV);
TOKEN_DICTIONARY(ProjectionV);
TOKEN_DICTIONARY(HiderV);
TOKEN_DICTIONARY(OptionV);
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

// DUO-TOKENS/DICT
#define DUO_TOKEN_DICTIONARY(callback) CALLBACKFN(callback)(RtToken one, RtToken two, RtInt n, RtToken tk[], RtPointer vl[]) \
{ \
	PyObject* pArgs = PyTuple_New(3); \
	PyObject* pOne = Py_BuildValue("s",one);	\
	PyTuple_SetItem(pArgs, 0, pOne); \
	PyObject* pTwo = Py_BuildValue("s",two);	\
	PyTuple_SetItem(pArgs, 1, pTwo); \
	PyObject* pDict = PyDict_New();	\
	PyTuple_SetItem(pArgs, 2, pDict); \
	ParseDictionary(pDict, n, tk, vl);	\
	GETFILTER; \
	PyObject* pResult = PyObject_CallObject(filter->_##callback##Func, pArgs); \
	Py_XDECREF(pResult); \
	Py_XDECREF(pArgs); \
};
//	Py_XDECREF(pOne); \
//	Py_XDECREF(pTwo); \
//	Py_XDECREF(pDict); \

DUO_TOKEN_DICTIONARY(ResourceV);
DUO_TOKEN_DICTIONARY(ShaderV);

RtArchiveHandle Riffler::_ArchiveBeginV(RtToken name, RtInt n, RtToken tk[], RtPointer vl[])
{
	PyObject* pArgs = PyTuple_New(2);
	PyObject* pName = Py_BuildValue("s",name);
	PyTuple_SetItem(pArgs, 0, pName);
	PyObject* pDict = PyDict_New();
	PyTuple_SetItem(pArgs, 1, pDict);
	ParseDictionary(pDict, n, tk, vl);
	GETFILTER;
	PyObject* pResult = PyObject_CallObject(filter->_ArchiveBeginVFunc, pArgs);
	Py_XDECREF(pResult);
	Py_XDECREF(pArgs);
	//Py_XDECREF(pName);
	//Py_XDECREF(pDict);

	// STUB
	RtArchiveHandle h;
	return h;
};

RtLightHandle Riffler::_LightSourceV(RtToken name, RtInt n, RtToken tk[], RtPointer vl[])
{
	PyObject* pArgs = PyTuple_New(2);
	PyObject* pName = Py_BuildValue("s",name);
	PyTuple_SetItem(pArgs, 0, pName);
	PyObject* pDict = PyDict_New();
	bool res = ParseDictionary(pDict, n, tk, vl);

	PyTuple_SetItem(pArgs, 1, pDict);

	GETFILTER;
	PyObject* pResult = PyObject_CallObject(filter->_LightSourceVFunc, pArgs);

	Py_XDECREF(pResult);
	Py_XDECREF(pArgs);
	//Py_XDECREF(pName);
	//Py_XDECREF(pDict);

	// STUB
	for(int i=0;i<n;i++)
	{
		if(strcmp(tk[i],"__handleid") == 0)
		{
			RtLightHandle h = strdup((RtToken)vl[i]);
			return h;
		};
	};
	RtLightHandle h = strdup(name);
	return h;
};