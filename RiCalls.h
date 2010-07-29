#pragma once

PyObject* _RiBegin(PyObject *self, PyObject *args);

static PyMethodDef MethodTable[] = {
	{"RiBegin", _RiBegin, METH_VARARGS,""},
	{NULL, NULL, 0, NULL}
};