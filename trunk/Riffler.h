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

//class SetupLayer :	public RifFilter
//{
//public:
//	virtual void Setup(PyObject*) = 0;
//	virtual ~SetupLayer() {};
//};


//template<class T> 

class Riffler : public RifFilter
//	public SetupLayer
{
public:
	Riffler(PyObject*);
	virtual ~Riffler();

	//virtual void Setup(PyObject*);


};

