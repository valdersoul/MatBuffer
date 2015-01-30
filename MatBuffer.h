#ifndef _MATBUFFER_H
#define _MATBUFFER_H


#include <iostream>
#include <map>
#include "mat.h"

using namespace std;

class MatBuffer {
	public:
		MatBuffer();
		MatBuffer(const char* filename, const char* type);
		~MatBuffer();

		char** getDir();
		int getDirNum();
		void getData();
		double* getDirData(string name);
		int getElementNum(string name);
		int getColNum(string name);

	protected:
	    map< string, mxArray*> datamap;
		MATFile* matFile;
		int nDir;
		char** dir;
		const char* filename;
		const char* type;
};



#endif