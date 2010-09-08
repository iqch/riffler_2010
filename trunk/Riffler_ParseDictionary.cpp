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
				PyDict_SetItemString(dict, t, Py_BuildValue("i",*((int*)p)));
			}
			else
			{
				if(t[3] != '[') continue;
				// ARRAY
				//int quants = atoi(t+4);
				int quants = 0;
				sscanf(t+4,"%d]",&quants);

				PyObject* pArgs = PyTuple_New(quants);
				int* P = (int*)p;
				for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("i",P[j]));
				PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'f': // FLOAT
			if(t[5] == ' ')
			{
				// JUST FLOAT
				PyDict_SetItemString(dict, t, Py_BuildValue("f",*((float*)p)));
			}
			else
			{
				if(t[5] != '[') continue;
				// ARRAY
				//int quants = atoi(t+6);
				int quants = 0;
				sscanf(t+6,"%d]",&quants);

				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("f",P[j]));
				PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 's': // STRING/SHADER
			if(t[6] == ' ')
			{
				// JUST STRING
				PyDict_SetItemString(dict, t, Py_BuildValue("s",*((RtToken*)p)));
			}
			else
			{
				if(t[6] != '[') continue;
				// ARRAY
				//int quants = atoi(t+7);
				int quants = 0;
				sscanf(t+7,"%d]",&quants);

				PyObject* pArgs = PyTuple_New(quants);
				char** P = (char**)p;
				for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("s",P[j]));
				PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'c': // COLOR
		case 'p': // POINT
			if(t[5] == ' ')
			{
				// JUST POINT
				float* V = (float*)p;
				PyDict_SetItemString(dict, t, Py_BuildValue("(fff)",V[0],V[1],V[2]));
			}
			else
			{
				if(t[5] != '[') continue;
				// ARRAY
				//int quants = atoi(t+6);
				int quants = 0;
				sscanf(t+6,"%d]",&quants);

				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++)
				{
					PyTuple_SetItem(pArgs, j, Py_BuildValue("(fff)",P[0],P[1],P[2]));
					P+=3;
				}
				PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'n': // NORMAL
		case 'v': // VECTOR
			if(t[6] == ' ')
			{
				// JUST NORMAL
				float* V = (float*)p;
				PyDict_SetItemString(dict, t, Py_BuildValue("(fff)",V[0],V[1],V[2]));
			}
			else
			{
				if(t[6] != '[') continue;
				// ARRAY
				//int quants = atoi(t+7);
				int quants = 0;
				sscanf(t+7,"%d]",&quants);

				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++)
				{
					PyTuple_SetItem(pArgs, j, Py_BuildValue("(fff)",P[0],P[1],P[2]));
					P+=3;
				}
				PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'm': // MATRIX
			if(t[6] == ' ')
			{
				// JUST MATRIX
				float* V = (float*)p;
				PyDict_SetItemString(dict, t, Py_BuildValue("((ffff)(ffff)(ffff)(ffff))"
					,V[0],V[1],V[2],V[3],V[4],V[5],V[6],V[7]
					,V[8],V[9],V[10],V[11],V[12],V[13],V[14],V[15]));
			}
			else
			{
				if(t[6] != '[') continue;
				// ARRAY
				//sprintf()
				int quants = 0;
				sscanf(t+7,"%d]",&quants);
				//atoi();
				PyObject* pArgs = PyTuple_New(quants);
				float* P = (float*)p;
				for(int j=0;j<quants;j++)
				{
					PyTuple_SetItem(pArgs, j, Py_BuildValue("((ffff)(ffff)(ffff)(ffff))"
						,P[0],P[1],P[2],P[3],P[4],P[5],P[6],P[7]
						,P[8],P[9],P[10],P[11],P[12],P[13],P[14],P[15]));
					P+=16;
				}
				PyDict_SetItemString(dict, t, pArgs);
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

bool CollectDictionary(PyObject* dict, int* N, RtToken** tk, RtPointer** vl)
{
	if(PyDict_Check(dict) == NULL) return false;

	//PyDict_Clear(dict);

	PyObject* keys = PyDict_Keys(dict);

	//PyObject_Print(keys,stderr,Py_PRINT_RAW);
	int n = PyList_Size(keys);
	if(n == 0) return false;

	*N = n;

	*tk = new RtToken[n];		// WE HAVE TO CLEAN THIS OUTSIDE!
	*vl = new RtPointer[n];	// AND THIS TOO!

	for(int i=0;i<n;i++)
	{
		(*tk)[i] = NULL;
		(*vl)[i] = NULL;

		PyObject *item = PyList_GetItem(keys,i);
		PyObject *value = PyDict_GetItem(dict,item);
		
		// ...INIT value
		RtToken t = PyString_AsString(item);

		if(t == NULL) return false;

		switch(t[0])
		{
		case 'i': // INT
			if(t[3] == ' ')
			{
				// JUST INTEGER
				int* _VL = new int;
				(*vl)[i] = _VL;
				*_VL = PyInt_AsLong(value);
			}
			else
			{
				if(t[3] != '[') return false;
				
				// ARRAY				
				if(!PyTuple_Check(value)) return false;

				int quants = PyTuple_Size(value);
				int* _VL = new int[quants];
				(*vl)[i] = _VL;

				for(int j=0;j<quants;j++) _VL[j] = PyInt_AsLong(PyTuple_GetItem(value,j));
			
				//int quants = 0;
				//sscanf(t+4,"%d]",&quants);

				//PyObject* pArgs = PyTuple_New(quants);
				//int* P = (int*)p;
				//for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("i",P[j]));
				//PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'f': // FLOAT
			if(t[5] == ' ')
			{
				// JUST FLOAT
				float* _VL = new float;
				(*vl)[i] = _VL;
				*_VL = PyFloat_AsDouble(value);
				//PyDict_SetItemString(dict, t, Py_BuildValue("f",*((float*)p)));
			}
			else
			{
				if(t[5] != '[') continue;
				// ARRAY
				if(!PyTuple_Check(value)) return false;

				int quants = PyTuple_Size(value);
				float* _VL = new float[quants];
				(*vl)[i] = _VL;

				for(int j=0;j<quants;j++) _VL[j] = PyFloat_AsDouble(PyTuple_GetItem(value,j));

				//int quants = 0;
				//sscanf(t+6,"%d]",&quants);

				//PyObject* pArgs = PyTuple_New(quants);
				//float* P = (float*)p;
				//for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("f",P[j]));
				//PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 's': // STRING/SHADER
			if(t[6] == ' ')
			{
				// JUST STRING
				char* _VL = PyString_AsString(value);
				(*vl)[i] = _VL;
				//PyDict_SetItemString(dict, t, Py_BuildValue("s",*((RtToken*)p)));
			}
			else
			{
				if(t[6] != '[') continue;
				// ARRAY

				if(!PyTuple_Check(value)) return false;

				int quants = PyTuple_Size(value);
				RtToken* _VL = new RtToken[quants];
				(*vl)[i] = _VL;

				for(int j=0;j<quants;j++)
				{
					_VL[j] = strdup(PyString_AsString((PyTuple_GetItem(value,j))));
				};

				//int quants = 0;
				//sscanf(t+7,"%d]",&quants);

				//PyObject* pArgs = PyTuple_New(quants);
				//char** P = (char**)p;
				//for(int j=0;j<quants;j++) PyTuple_SetItem(pArgs, j, Py_BuildValue("s",P[j]));
				//PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'c': // COLOR
		case 'p': // POINT
			if(t[5] == ' ')
			{
				// JUST POINT/COLOR
				if(!PyTuple_Check(value)) return false;
				if(PyTuple_Size(value) != 3) return false;
				float* _VL = new float[3];
				(*vl)[i] = _VL;
				for(int j=0;j<3;j++) _VL[j] = PyFloat_AsDouble(PyTuple_GetItem(value,j));
				//float* V = (float*)p;
				//PyDict_SetItemString(dict, t, Py_BuildValue("(fff)",V[0],V[1],V[2]));
			}
			else
			{
				if(t[5] != '[') continue;
				// ARRAY
				if(!PyTuple_Check(value)) return false;

				int quants = PyTuple_Size(value);
				float* _VL = new float[3*quants];

				for(int j=0;j<quants;j++)
				{
					PyObject* v = PyTuple_GetItem(value,j);
					if(!PyTuple_Check(v)) return false; // ...LEAKS POSSIBLE
					if(PyTuple_Size(v) != 3) return false; // ...LEAKS POSSIBLE

					for(int k=0;j<3;k++)
					{
						_VL[3*j+k] = PyFloat_AsDouble(PyTuple_GetItem(v,k));
					};
				};
				(*vl)[i] = _VL;

				//int quants = 0;
				//sscanf(t+6,"%d]",&quants);

				//PyObject* pArgs = PyTuple_New(quants);
				//float* P = (float*)p;
				//for(int j=0;j<quants;j++)
				//{
				//	PyTuple_SetItem(pArgs, j, Py_BuildValue("(fff)",P[0],P[1],P[2]));
				//	P+=3;
				//}
				//PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'n': // NORMAL
		case 'v': // VECTOR
			if(t[6] == ' ')
			{
				// JUST NORMAL/VECTOR
				if(!PyTuple_Check(value)) return false;
				if(PyTuple_Size(value) != 3) return false;
				float* _VL = new float[3];
				(*vl)[i] = _VL;
				for(int j=0;j<3;j++) _VL[j] = PyFloat_AsDouble(PyTuple_GetItem(value,j));
				//float* V = (float*)p;
				//PyDict_SetItemString(dict, t, Py_BuildValue("(fff)",V[0],V[1],V[2]));
			}
			else
			{
				if(t[6] != '[') continue;
				
				// ARRAY			
				if(!PyTuple_Check(value)) return false;

				int quants = PyTuple_Size(value);
				float* _VL = new float[3*quants];

				for(int j=0;j<quants;j++)
				{
					PyObject* v = PyTuple_GetItem(value,j);
					if(!PyTuple_Check(v)) return false; // ...LEAKS POSSIBLE
					if(PyTuple_Size(v) != 3) return false; // ...LEAKS POSSIBLE

					for(int k=0;j<3;k++)
					{
						_VL[3*j+k] = PyFloat_AsDouble(PyTuple_GetItem(v,k));
					};
				};
				(*vl)[i] = _VL;
				
				//int quants = 0;
				//sscanf(t+7,"%d]",&quants);

				//PyObject* pArgs = PyTuple_New(quants);
				//float* P = (float*)p;
				//for(int j=0;j<quants;j++)
				//{
				//	PyTuple_SetItem(pArgs, j, Py_BuildValue("(fff)",P[0],P[1],P[2]));
				//	P+=3;
				//}
				//PyDict_SetItemString(dict, t, pArgs);
			};
			break;
		case 'm': // MATRIX
			if(t[6] == ' ')
			{
				// JUST MATRIX

				if(!PyTuple_Check(value)) return false;
				if(PyTuple_Size(value) != 4) return false;

				PyObject* R[4];
				for(int j=0;j<4;j++)
				{
					R[j] = PyTuple_GetItem(value,j);
					if(!PyTuple_Check(R[j])) return false;
					if(PyTuple_Size(R[j]) != 4) return false;
				};

				float* _VL = new float[16];
				(*vl)[i] = _VL;
					
				for(int j=0;j<4;j++)
				{
					for(int k=0;k<4;k++)
					{
						_VL[4*j+k] = PyFloat_AsDouble(PyTuple_GetItem(R[j],k));
					};
				};
				//float* V = (float*)p;
				//PyDict_SetItemString(dict, t, Py_BuildValue("((ffff)(ffff)(ffff)(ffff))"
				//	,V[0],V[1],V[2],V[3],V[4],V[5],V[6],V[7]
				//,V[8],V[9],V[10],V[11],V[12],V[13],V[14],V[15]));
			}
			else
			{
				if(t[6] != '[') continue;
				
				// ARRAY
				if(!PyTuple_Check(value)) return false;

				int quants = PyTuple_Size(value);
				float* _VL = new float[16*quants];

				for(int j=0;j<quants;j++)
				{
					PyObject* v = PyTuple_GetItem(value,j);
					if(!PyTuple_Check(v)) return false; // ...LEAKS POSSIBLE
					if(PyTuple_Size(v) != 4) return false; // ...LEAKS POSSIBLE

					for(int k=0;k<4;k++)
					{
						PyObject* u = PyTuple_GetItem(v,k);
						if(!PyTuple_Check(u)) return false; // ...LEAKS POSSIBLE
						if(PyTuple_Size(u) != 4) return false; // ...LEAKS POSSIBLE

						for(int l=0;l<4;l++)
						{
							_VL[16*j+4*k+l] = PyFloat_AsDouble(PyTuple_GetItem(u,l));
						};
					};
				};
				(*vl)[i] = _VL;

				//int quants = 0;
				//sscanf(t+7,"%d]",&quants);
				////atoi();
				//PyObject* pArgs = PyTuple_New(quants);
				//float* P = (float*)p;
				//for(int j=0;j<quants;j++)
				//{
				//	PyTuple_SetItem(pArgs, j, Py_BuildValue("((ffff)(ffff)(ffff)(ffff))"
				//		,P[0],P[1],P[2],P[3],P[4],P[5],P[6],P[7]
				//	,P[8],P[9],P[10],P[11],P[12],P[13],P[14],P[15]));
				//	P+=16;
				//}
				//PyDict_SetItemString(dict, t, pArgs);
			};
			break;
			//case 'h': // H POINTS ? 
			//	break;
		default:
			return false;
		};

		(*tk)[i] = strdup(t);
	};

	return true;
};

bool DisposeTKVL(int n, RtToken* tk, RtPointer* vl)
{
	for(int i=0;i<n;i++)
	{
		if(tk[i] == NULL) return false;
		if(vl[i] == NULL) return false;
		switch(tk[i][0])
		{
		case 'i': // INT
			if(tk[i][3] == ' ')
			{
				// JUST INTEGER
				delete ((int*)vl[i]);
			}
			else
			{
				if(tk[i][3] != '[') return false;
				// ARRAY
				delete [] ((int*)vl[i]);
			};
			break;
		case 'f': // FLOAT
			if(tk[i][5] == ' ')
			{
				// JUST FLOAT
				delete ((float*)vl[i]);
			}
			else
			{
				if(tk[i][5] != '[') continue;
				// ARRAY
				delete [] ((float*)vl[i]);
			};
			break;
		case 's': // STRING
			if(tk[i][6] == ' ')
			{
				// JUST STRING
				delete ((RtToken*)vl[i]);
			}
			else
			{
				if(tk[i][6] != '[') continue;
				// ARRAY
				int quants = 0;
				sscanf(tk[i]+7,"%d]",&quants);

				char** P = (char**)vl[i];
				for(int j=0;j<quants;j++)
				{
					delete [] P[j];
				}
				delete [] P;
			};
			break;
		case 'c': // COLOR
		case 'p': // POINT
		case 'n': // NORMAL
		case 'v': // VECTOR
		case 'm': // MATRIX
		//case 'h': // H POINTS ? 
			delete [] ((float*)vl[i]);
			break;
		default:
			return false;
		};
		delete [] tk[i];
	};

	delete [] tk;
	delete [] vl;

	return true;
}
