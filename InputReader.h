/***************************************************
	DO NOT MODIFY THIS FILE
	Data Structure & Algorithm Assignment 3
	InputReader.h
	Purpose: Helper file for reading input

	@author Kien Huynh
	@version 1.0 05-10-2016
***************************************************/
#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool ReadArrayInput(string filename, int*& arr, int& count);

bool ReadArrayInputOfGraph(string filename, int*& vertexDataArr, int& vertexCount, int**& edgeDataArr, int& edgeCount);

bool ReadAdjacencyMat(string filename, int**& mat, int& count);

#endif
