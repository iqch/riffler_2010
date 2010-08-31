/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization header
*
*	Version: 0.4
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#pragma once

class SetupLayer :	public RifFilter
{
public:
	virtual void Setup(PyObject*) = 0;
	virtual ~SetupLayer() {};
};

#define DECLARE_CALLBACK(callback) static PyObject* _##callback##Func; static RtVoid _##callback

template<class T> 

class Riffler :
	public SetupLayer
{
public:
	Riffler();
	virtual ~Riffler();

	virtual void Setup(PyObject*);

private:
	static PyObject* m_object;
	T m_member;
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

	//DECLARE_CALLBACK(ObjectBegin)();
	DECLARE_CALLBACK(ObjectEnd)();

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
		
	// DOU-TOKENS/DICT
	//RtVoid  	_ResourceV(RtToken handle, RtToken type, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_ShaderV(RtToken name, RtToken handle, RtInt, RtToken[], RtPointer[]);

	// HANDLES FROM TOKEN/DICT
	//RtArchiveHandle _ArchiveBeginV(RtToken name, RtInt, RtToken[], RtPointer[]);
	//RtLightHandle	_AreaLightSourceV(RtToken name, RtInt, RtToken[], RtPointer[]);
	//RtLightHandle	_LightSourceV(RtToken name, RtInt, RtToken[], RtPointer[]);

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
	//RtVoid  	_VArchiveRecord(RtToken type, char *format, va_list vap);
	//RtVoid  	_ReadArchiveV(RtToken name, RtArchiveCallback callback, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_MotionBeginV(RtInt n, RtFloat times[]);
	//RtVoid  	_ObjectInstance(RtObjectHandle handle);
	//RtToken 	_Declare(char *name, char *declaration); // - little complex to startpoint
	//RtVoid  	_Format(RtInt xres, RtInt yres, RtFloat aspect);
	//RtVoid  	_DisplayV(char *name, RtToken type, RtToken mode, RtInt, RtToken[], RtPointer[]);
	//RtVoid  	_PixelFidelity(RtFloat variation); // OBSOLETE call: see RiPixelVariance
	//RtVoid  	_PixelFilter(RtFilterFunc filterFunc, RtFloat xwidth, RtFloat ywidth);
	//RtVoid  	_Quantize(RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ampl);
	//RtVoid  	_Illuminate(RtLightHandle light, RtBoolean onoff);
	//RtVoid  	_GeometricApproximation(RtToken type, RtFloat value);
	//RtVoid  	_Basis(RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep);
	//RtVoid		_ErrorHandler(RtErrorHandler);
};

