/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	RIF_Riffler.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Base source
*
*	Version: 0.2
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/
#include "stdafx.h"

#include "RiCalls.h"
#include "Riffler.h"

#define FILTERS_COUNT 2

Riffler<bool> g_bR;
Riffler<int> g_iR;

SetupLayer* g_FILTERS[FILTERS_COUNT] = { &g_bR, &g_iR };
int g_current = 0;

class Plugin : public RifPlugin
{
public:
	Plugin(int argc, char **argv);
	virtual ~Plugin();

	virtual RifFilter& GetFilter();

	// REFCOUNT PART
	static unsigned int m_counter;
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


	// AMOUNT CHECKING

	if(g_current == FILTERS_COUNT)
	{
		cout << "RIFFLER: Excessive fiters count" << endl;
		return;
	}

	
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

	PyObject *pArgList = PyTuple_New(1);
	PyTuple_SetItem(pArgList, 0, pArgs);

	m_filterobj = PyObject_CallObject(pFunc, pArgList);
	Py_DECREF(pArgList);
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
	m_filter = g_FILTERS[g_current];
	g_FILTERS[g_current]->Setup(m_filterobj);
	g_current++;
};

Plugin::~Plugin()
{
	// DESTROY
	//if(m_filter != NULL) delete m_filter;
	//if(m_filterobj != NULL) Py_DECREF(m_filterobj);
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
		if(Plugin::m_counter == 0)
		{
			// PRIMARY SETUP
			Py_Initialize();

			if(Py_IsInitialized() == 0)
			{
				cout << "RIFFLER: python initialization failed!" << endl;
				return NULL;
			}
			Py_InitModule("prman", MethodTable);
			Plugin::m_counter++;
		};

		for(int i=0;i<argc;i++)
		{
			cout << i << ": \t" << argv[i] << endl;
		};

		return new Plugin(argc,argv);
	};
};

