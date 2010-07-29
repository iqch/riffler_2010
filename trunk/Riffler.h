#pragma once

class Riffler :
	public RifFilter
{
public:
	Riffler(PyObject*);
	virtual ~Riffler();
};
