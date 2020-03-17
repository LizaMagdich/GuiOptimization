#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

/**
 * The Function class represents the parent class for all possible functions.
 * It has 3 successors --- 3 functions
 *
 */

class Function {
protected:
	virtual const char * Name() { return "\0"; }
	int dimension;
public:
	int GetDimension() { return dimension; }
	/**
	 * The function eval returns the value of the function at a given point.
	 *
	 * @param x is a point
	 * @returns value of the function at a given point
	 */
	virtual  double eval(vector<double> x) { return 0; };
	void PrintName();
	virtual ~Function() {}
};


class F_1 : public Function {
protected:
	const char * Name() override;
public:
	double eval(vector<double> x) override;
	F_1() { dimension = 2; }
};

class F_2 : public Function {
protected:
	const char * Name() override;
public:
	double eval(vector<double> x) override;
    F_2() { dimension = 2; }
};

class F_3 : public Function {
protected:
	const char * Name() override;
public:
	double eval(vector<double> x) override;
    F_3() { dimension = 2; }

};
