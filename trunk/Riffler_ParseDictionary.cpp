/*************************************************************
* Copyright (c) 2010 by Egor N. Chashchin. All Rights Reserved.          *
**************************************************************/

/*
*	Riffler_ParseDictionary.cpp - RenderMan DSO Rif-filter for using python scripts
*  for filtering. Dictionary parsing source
*
*	Version: 0.4
*	Authors: Egor N. Chashchin                   
*	Contact: iqcook@gmail.com 
* 
*/

#include "stdafx.h"

bool ParseDictionary(PyObject* dict, int n, RtToken tk[], RtPointer vl[])
{
	for(int i=0;i<n;i++)
	{
		RtToken t = tk[i];
		RtPointer p =vl[i];
		switch(t[0])
		{
		case 'i': // INT
			if(t[3] == ' ')
			{
				// JUST INTEGER
				PyDict_SetItemString(dict, t+4, Py_BuildValue("i",*((int*)p)));
			}
			else
			{
				if(t[3] != '[') continue;
				// ARRAY
				int quants = atoi(t+4);
				const char* pz = strchr(t+3,']')+2;
				PyObject* pArgs = PyTuple_New(quants);
				int* P = (int*)p;
				for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("i",P[j]));
				PyDict_SetItemString(dict, pz, pArgs);
			};
			break;
		case 'f': // FLOAT
			if(t[5] == ' ')
			{
				// JUST FLOAT
				PyDict_SetItemString(dict, t+6, Py_BuildValue("f",*((float*)p)));
			}
			else
			{
				if(t[5] != '[') continue;
				// ARRAY
				int quants = atoi(t+6);
				const char* pz = strchr(t+5,']')+2;
				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("f",P[j]));
				PyDict_SetItemString(dict, pz, pArgs);
			};
			break;
		case 's': // STRING
			if(t[6] == ' ')
			{
				// JUST STRING
				PyDict_SetItemString(dict, t+7, Py_BuildValue("s",*((RtToken*)p)));
			}
			else
			{
				if(t[6] != '[') continue;
				// ARRAY
				int quants = atoi(t+7);
				const char* pz = strchr(t+6,']')+2;
				PyObject* pArgs = PyTuple_New(quants);
				char** P = (char**)p;
				for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("s",P[j]));
				PyDict_SetItemString(dict, pz, pArgs);
			};
			break;
		case 'c': // COLOR
		case 'p': // POINT
			if(t[5] == ' ')
			{
				// JUST POINT
				float* V = (float*)p;
				PyDict_SetItemString(dict, t+6, Py_BuildValue("(fff)",V[0],V[1],V[2]));
			}
			else
			{
				if(t[5] != '[') continue;
				// ARRAY
				int quants = atoi(t+6);
				const char* pz = strchr(t+5,']')+2;
				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++)
				{
					PyTuple_SetItem(pArgs, j, Py_BuildValue("(fff)",P[0],P[1],P[2]));
					P+=3;
				}
				PyDict_SetItemString(dict, pz, pArgs);
			};
			break;
		case 'n': // NORMAL
		case 'v': // VECTOR
			if(t[6] == ' ')
			{
				// JUST NORMAL
				float* V = (float*)p;
				PyDict_SetItemString(dict, t+7, Py_BuildValue("(fff)",V[0],V[1],V[2]));
			}
			else
			{
				if(t[6] != '[') continue;
				// ARRAY
				int quants = atoi(t+7);
				const char* pz = strchr(t+6,']')+2;
				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++)
				{
					PyTuple_SetItem(pArgs, j, Py_BuildValue("(fff)",P[0],P[1],P[2]));
					P+=3;
				}
				PyDict_SetItemString(dict, pz, pArgs);
			};
			break;
		case 'm': // MATRIX
			if(t[6] == ' ')
			{
				// JUST MATRIX
				float* V = (float*)p;
				PyDict_SetItemString(dict, t+7, Py_BuildValue("((ffff)(ffff)(ffff)(ffff))"
					,V[0],V[1],V[2],V[3],V[4],V[5],V[6],V[7]
					,V[8],V[9],V[10],V[11],V[12],V[13],V[14],V[15]));
			}
			else
			{
				if(t[6] != '[') continue;
				// ARRAY
				int quants = atoi(t+7);
				const char* pz = strchr(t+6,']')+2;
				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++)
				{
					PyTuple_SetItem(pArgs, j, Py_BuildValue("((ffff)(ffff)(ffff)(ffff))"
						,P[0],P[1],P[2],P[3],P[4],P[5],P[6],P[7]
						,P[8],P[9],P[10],P[11],P[12],P[13],P[14],P[15]));
					P+=16;
				}
				PyDict_SetItemString(dict, pz, pArgs);
			};
			break;
		//case 'h': // H POINTS ? 
		//	break;
		default:
			continue;
		};
	};

	return true;
};

bool CollectDictionary(PyObject* dict, int* n, RtToken* tk[], RtPointer* vl[])
{
	return true;
};
