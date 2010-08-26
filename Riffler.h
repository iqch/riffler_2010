/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler.h - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Filter realization header
*
*	Version: 0.1
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
	//RtToken 	_Declare(char *name, char *declaration); // - little complex to startpoint
	static RtVoid  	_FrameBegin(RtInt frame);
	static PyObject* _FrameBeginFunc;
	/*RtVoid  	_FrameEnd();
	RtVoid  	_WorldBegin();
	RtVoid  	_WorldEnd();
	RtVoid  	_Clipping(RtFloat hither, RtFloat yon);
	RtVoid  	_ClippingPlane(RtFloat Nx, RtFloat Ny, RtFloat Nz, RtFloat Px, RtFloat Py, RtFloat Pz);
	RtVoid  	_CropWindow(RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax);
	RtVoid  	_DepthOfField(RtFloat fstop, RtFloat focallength, RtFloat focaldistance);
	RtVoid  	_Format(RtInt xres, RtInt yres, RtFloat aspect);
	RtVoid  	_FrameAspectRatio(RtFloat aspect);
	RtVoid  	_ProjectionV(RtToken name, 	RtInt, RtToken[], RtPointer[]);
	RtVoid  	_ScreenWindow(RtFloat left, RtFloat right, RtFloat top, RtFloat bot);
	RtVoid  	_Shutter(RtFloat min, RtFloat max);
	RtVoid  	_DisplayV(char *name, RtToken type, RtToken mode, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_Exposure(RtFloat gain, RtFloat gamma);
	RtVoid  	_ImagerV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_PixelFidelity(RtFloat variation); // OBSOLETE call: see RiPixelVariance
	RtVoid  	_PixelFilter(RtFilterFunc filterFunc, RtFloat xwidth, RtFloat ywidth);
	RtVoid  	_PixelSamples(RtFloat xsamples, RtFloat ysamples);
	RtVoid  	_PixelVariance(RtFloat variation);
	RtVoid  	_Quantize(RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ampl);
	RtVoid  	_HiderV(RtToken type, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_OptionV(RtToken name, RtInt, RtToken[], RtPointer[]);

	RtVoid  	_AttributeBegin();
	RtVoid  	_AttributeEnd();
	RtVoid  	_AttributeV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_Color(RtColor color);
	RtVoid  	_Opacity(RtColor color);
	RtVoid  	_TextureCoordinates(RtFloat s1, RtFloat t1, 	RtFloat s2, RtFloat t2, RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4);
	RtVoid  	_Matte(RtBoolean onoff);
	RtVoid  	_ShadingInterpolation(RtToken type);
	RtVoid  	_ShadingRate(RtFloat size);

	RtLightHandle	_AreaLightSourceV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtLightHandle	_LightSourceV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_Illuminate(RtLightHandle light, RtBoolean onoff);
	RtVoid  	_AtmosphereV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_DisplacementV(RtToken name,	RtInt, RtToken[], RtPointer[]);
	RtVoid  	_ExteriorV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_InteriorV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_SurfaceV(RtToken name,	RtInt, RtToken[], RtPointer[]);

	RtVoid  	_TransformBegin();
	RtVoid  	_TransformEnd();
	RtVoid  	_Bound(RtBound bound);
	RtVoid  	_Detail(RtBound bound);
	RtVoid  	_DetailRange(RtFloat minv, RtFloat lowtran, RtFloat uptran, RtFloat maxv);
	RtVoid  	_RelativeDetail(RtFloat relativedetail);
	RtVoid  	_GeometricApproximation(RtToken type, RtFloat value);
	RtVoid  	_Orientation(RtToken orientation);
	RtVoid  	_ReverseOrientation();
	RtVoid  	_Sides(RtInt sides);

	RtVoid  	_ConcatTransform(RtMatrix transform);
	RtVoid  	_CoordSysTransform(RtToken space);
	RtVoid  	_CoordinateSystem(RtToken space);
	RtVoid	_ScopedCoordinateSystem(RtToken space);

	RtVoid  	_Identity();
	RtVoid  	_Perspective(RtFloat fov);
	RtVoid  	_Rotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz);
	RtVoid  	_Scale(RtFloat sx, RtFloat sy, RtFloat sz);
	RtVoid  	_Skew(RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1, RtFloat dx2, RtFloat dy2, RtFloat dz2);
	RtVoid  	_Transform(RtMatrix transform);
	RtVoid  	_Translate(RtFloat dx, RtFloat dy, RtFloat dz);

	RtVoid  	_Basis(RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep);
	RtVoid  	_BlobbyV(RtInt nleaf, RtInt ninst, RtInt inst[], RtInt nflt, RtFloat flt[], RtInt nstr, RtToken str[], RtInt, RtToken[], RtPointer[]);
	RtVoid  	_ConeV(RtFloat height, RtFloat radius, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_CurvesV(RtToken type, RtInt ncurves, RtInt nvert[], RtToken wrap, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_CylinderV(RtFloat rad, RtFloat zmin, RtFloat zmax, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_DiskV(RtFloat height, RtFloat radius, RtFloat tmax,	RtInt, RtToken[], RtPointer[]);
	RtVoid  	_GeneralPolygonV(RtInt nloops, RtInt nverts[], RtInt, RtToken[], RtPointer[]);
	RtVoid  	_GeometryV(RtToken type, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_HyperboloidV(RtPoint point1, RtPoint point2, RtFloat tmax,	RtInt, RtToken[], RtPointer[]);
	RtVoid  	_NuPatchV(RtInt nu, RtInt uorder, RtFloat uknot[], RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder, RtFloat vknot[], RtFloat vmin, RtFloat vmax, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_ParaboloidV(RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_PatchMeshV(RtToken type, RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_PatchV(RtToken type, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_PointsGeneralPolygonsV(RtInt npolys, RtInt nloops[], RtInt nverts[], RtInt verts[], RtInt, RtToken[], RtPointer[]);
	RtVoid  	_PointsPolygonsV(RtInt npolys, RtInt nverts[], RtInt verts[], RtInt, RtToken[], RtPointer[]);
	RtVoid  	_PointsV(RtInt nverts, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_PolygonV(RtInt nverts, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_Procedural(RtPointer data, RtBound bound, RtProcSubdivFunc sdfunc, RtProcFreeFunc freefunc);
	RtVoid  	_SphereV(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_SubdivisionMeshV(RtToken mask, RtInt nf, RtInt nverts[], RtInt verts[], RtInt nt, RtToken tags[], RtInt nargs[], RtInt intargs[], RtFloat floatargs[], RtInt, RtToken[], RtPointer[]);
	RtVoid  	_TorusV(RtFloat majrad, RtFloat minrad, RtFloat phimin, RtFloat phimax, 	RtFloat tmax, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_TrimCurve(RtInt nloops, RtInt ncurves[], RtInt order[], RtFloat knot[], RtFloat min[], RtFloat max[], RtInt n[], RtFloat u[], RtFloat v[], RtFloat w[]);

	RtVoid  	_SolidBegin(RtToken operation);
	RtVoid  	_SolidEnd();

	RtObjectHandle  _ObjectBegin();
	RtVoid	    	_ObjectEnd();
	RtVoid  	_ObjectInstance(RtObjectHandle handle);

	RtVoid  	_MotionBeginV(RtInt n, RtFloat times[]);
	RtVoid  	_MotionEnd();

	RtVoid  	_ResourceV(RtToken handle, RtToken type, RtInt, RtToken[], RtPointer[]);

	RtVoid  	_MakeCubeFaceEnvironmentV(char *px, char *nx, char *py, char *ny,	char *pz, char *nz, char *tex, RtFloat fov,	RtFilterFunc filterFunc,	RtFloat swidth, RtFloat ywidth, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_MakeLatLongEnvironmentV(char *pic, char *tex, RtFilterFunc filterFunc,	RtFloat swidth, RtFloat twidth, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_MakeShadowV(char *pic, char *tex, 	RtInt, RtToken[], RtPointer[]);
	RtVoid  	_MakeTextureV(char *pic, char *tex, 	RtToken swrap, RtToken twrap,	RtFilterFunc filterFunc, RtFloat swidth, RtFloat twidth, RtInt, RtToken[], RtPointer[]);

	RtVoid  	_VArchiveRecord(RtToken type, char *format, va_list vap);
	RtVoid  	_ReadArchiveV(RtToken name, RtArchiveCallback callback, RtInt, RtToken[], RtPointer[]);

	RtArchiveHandle _ArchiveBeginV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_ArchiveEnd();

	RtVoid  	_IfBeginV(char *expr, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_ElseIfV(char *expr, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_Else();
	RtVoid  	_IfEnd();

	RtVoid	_DisplayChannelV(RtToken mode, RtInt, RtToken[], RtPointer[]);

	RtVoid	_MakeBrickMapV(RtInt, RtToken *, RtToken, RtInt, RtToken[], RtPointer[]);
	
	RtVoid  	_HierarchicalSubdivisionMeshV(RtToken mask, RtInt nf, 	RtInt nverts[], RtInt verts[], RtInt nt, RtToken tags[],	RtInt nargs[], RtInt intargs[], RtFloat floatargs[], RtToken stringargs[], RtInt, RtToken[], RtPointer[]);

	RtVoid  	_ResourceBegin();
	RtVoid  	_ResourceEnd();
	RtVoid	_System(char *cmdstring);

	RtVoid  	_ShaderV(RtToken name, RtToken handle, RtInt, RtToken[], RtPointer[]);

	RtVoid  	_CameraV(RtToken name, RtInt, RtToken[], RtPointer[]);

	RtVoid	_ErrorHandler(RtErrorHandler);

	RtVoid  	_EditBeginV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid  	_EditEnd();
	RtVoid  	_EditAttributeBegin(RtToken name);
	RtVoid  	_EditAttributeEnd();
	RtVoid	_EditWorldBeginV(RtToken name, RtInt, RtToken[], RtPointer[]);
	RtVoid	_EditWorldEnd();

	RtVoid  	_PixelSampleImagerV(RtToken name, RtInt, RtToken[], RtPointer[]);*/
};

