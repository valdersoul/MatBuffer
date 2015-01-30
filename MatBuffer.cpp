#include <iostream>
#include "mat.h"
#include "MatBuffer.h"

using namespace std;

MatBuffer::MatBuffer(){
	nDir = 0;
}

MatBuffer::MatBuffer(const char* filename, const char* type){
	this->filename = filename;
	this->type = type;
	matFile = matOpen(filename, type);
	if (matFile == NULL){
		cout << "Error open mat file" << endl;
	}
}

char** MatBuffer::getDir(){
	if (matClose(matFile) != 0){
		cout << "Error closing the mat file!" << endl;
	}
	matFile = matOpen(filename, type);
	dir = matGetDir(matFile, &nDir);
	if (dir == NULL){
		cout << "Error reading directory of file" << endl;
		return NULL;
	}
	return dir;
}

int MatBuffer::getDirNum(){
	if (nDir == 0){
		cout << "The number of directory if 0!" << endl;
		return 0;
	}
	return nDir;
}

void MatBuffer::getData(){
	const char* name;
	if (matClose(matFile) != 0){
		cout << "Error closing the mat file!" << endl;
	}
	matFile = matOpen(filename, type);
	for (int i = 0; i < nDir; i++){
		mxArray* pa = matGetNextVariable(matFile, &name);
		if (pa == NULL){
			cout << "Error reading file!" << endl;
		}
		datamap[(string)name] = pa;
	}
	return;
}

double* MatBuffer::getDirData(string name){
	mxArray* pa = NULL;
	if (datamap.find(name) != datamap.end())
		pa = datamap[name];
	else
		cout << "No such directory in data!" << endl;
	int dimenNum = mxGetNumberOfDimensions(pa);
	int eleNum = mxGetNumberOfElements(pa);
	int colNum = mxGetN(pa);
	cout << colNum << endl;
	return (double*)mxGetData(pa);
}

int MatBuffer::getElementNum(string name){
	mxArray* pa = NULL;
	if (datamap.find(name) != datamap.end())
		pa = datamap[name];
	else
		cout << "No such directory in data!" << endl;
	return mxGetNumberOfElements(pa);
}

int MatBuffer::getColNum(string name){
	mxArray* pa = NULL;
	if (datamap.find(name) != datamap.end())
		pa = datamap[name];
	else
		cout << "No such directory in data!" << endl;
	return mxGetN(pa);
}

MatBuffer::~MatBuffer(){
	mxFree(dir);
	if (matClose(matFile) != 0){
		cout << "Error closing the mat file!" << endl;
	}
	for (auto &i : datamap)
		mxDestroyArray(i.second);
}