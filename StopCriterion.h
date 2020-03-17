#pragma once
#include "Function.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
const double step = 1e-9;

double Norm(vector<double> x);
vector<double> Gradient(Function * func, vector<double> x);


/**
 * The StopCriterion class represents the parent class for possible stopping criteria.
 * It has 2 successors:
 * <1> NormDifOfNodes --- stop criterion according to the norm of the difference between last two points
 * <2> NormDifOfValFunc --- stop criterion according to the norm of the difference between values at last two points
 * <3> NormGrad --- stop criterion according to the norm of the gradient value at last point
 *
 * All criteria contain a stop criterion by the number of iterations
 */

class StopCriterion {
public:
	virtual ~StopCriterion() {}
	double eps;
	int numberMaxIter;
	int numbMaxIterAfterLastImp;
	/**
	 * The function Stop responsible for stopping optimization.
	 *
	 * @param iter is a number of iterations
	 * @param x1 is a current point
	 * @param x2 is a previous point
	 * @param f1 is a value of the function at current point
	 * @param f2 is a value of the function at previous point
	 * @param func is function pointer
	 * @returns bool value: true --- stop of the optimization, false --- continue the optimization
	 */
	void SetEps(double x) { eps = x; }
	double GetEps() { return eps; }
	void SetNumberMaxIter(int x) { numberMaxIter = x; }
	void SetNumbMaxIterAfterLastImp(int x) { numbMaxIterAfterLastImp = x; }

	virtual bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) = 0;
};


class NormDifOfNodes : public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) override;
};

class NormDifOfValFunc : public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) override;
};

class NormGrad : public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) override;
};

class ModDifOfNodes : public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) override;
};

class LatestImprov: public StopCriterion {
public:
	bool Stop(int iter, vector<double> x1, vector<double> x2, double  f1, double  f2, Function * func, int iterLatestImprov) override;
};
