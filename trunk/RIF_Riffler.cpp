/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RIF_Riffler.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Base source
*
*	Version: 0.1
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#include "stdafx.h"

#include "RiCalls.h"
#include "Riffler.h"

class Plugin : public RifPlugin
{
private :
	// REFCOUNT PART
	static unsigned int m_counter;
public:
	Plugin(int argc, char **argv);
	virtual ~Plugin();

	virtual RifFilter& GetFilter();

protected:

	RifFilter* m_filter;
	PyObject* m_module;
	PyObject* m_filterobj;
};

unsigned int Plugin::m_counter = 0;

Plugin::Plugin(int argc, char **argv)
	: m_filter(NULL)
	, m_module(NULL)
	, m_filterobj(NULL)
{
	// ...HOPING, RIF FILTERS ARE BUILT NOT IN PARALLEL
	if(Plugin::m_counter == 0)
	{
		// PRIMARY SETUP
		Py_Initialize();
		Py_InitModule("prman", MethodTable);
	}
	Plugin::m_counter++;

	// LOAD MODULE
	if(argc < 1)
	{
		cout << "RIFFLER: Insufficient parameters - script name is not found" << endl;
		return;
	};

	PyObject *pName = PyString_FromString(argv[0]);

	m_module = PyImport_Import(pName);
	Py_DECREF(pName);

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
		Py_XDECREF(pFunc); // ?
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

	m_filterobj = PyObject_CallObject(pFunc, pArgs);
	Py_DECREF(pArgs);
	Py_XDECREF(pFunc);

	if(m_filterobj == NULL)
	{
		cout << "RIFFLER: calling 'plugin' function failed!" << endl;

		PyErr_Print();
		Py_DECREF(m_module); m_module = NULL;
		return;
	};

	// SETUP FILTER

	m_filter = new Riffler(m_filterobj);
};

Plugin::~Plugin()
{
	// DESTROY
	if(m_filter != NULL) delete m_filter;
	if(m_filterobj != NULL) Py_DECREF(m_filterobj);
	if(m_module != NULL) Py_DECREF(m_module);

	// ...HOPING, RIF FILTERS ARE DESTROYED NOT IN PARALLEL
	Plugin::m_counter--;
	if(m_counter == 0) Py_Finalize();
};

RifFilter& Plugin::GetFilter()
{
	return *m_filter;
};

extern "C" 
{
	DLLEXPORT RifPlugin* RifPluginManufacture(int argc, char **argv)
	{
		return new Plugin(argc,argv);
	};
};

