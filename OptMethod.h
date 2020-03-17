/**
* @author Elizaveta Magdich
*
* @section DESCRIPTION
*
* This program implements sequential optimization of multidimensional functions.
*/

#pragma once
#include "StopCriterion.h"
#include "Function.h"
#include "Area.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

const double goldenRatio = (1 + sqrt(5)) / 2;
const int maxIter = 30;

/**
 * The OptMethod class represents the parent class for possible optimization methods.
 * It has 2 successors:
 * <1> Coordinate descent --- CoordinateDescent
 * <2> Stohastic search --- StohasticSearch
 */

class OptMethod {
public:
	/**
	 * The function Optimize responsible for stopping optimization.
	 *
	 * @param area is the pointer to the function definition area
	 * @param func is the pointer to the function
	 * @param stopCrit is the pointer to the stop criterion
	 * @param iter is the number of iterations
	 * @returns minimum function value in this area
	 */

	virtual double Optimize(Area * area, Function * func, StopCriterion * stopCrit, int * iter) = 0;
	void SetStartPoint(vector<double> x) { StartPoint = x; }
	vector<double> GetFinalPoint() { return xFin; }
	virtual ~OptMethod() {}

    std::vector<double> xGraph;
    std::vector<double> yGraph;


protected:
	// StartPoint is the optimization start point
	vector<double>  StartPoint;
	// xFin is the optimization end point
	vector<double> xFin;
};

class CoordinateDescent : public OptMethod {
public:
	
	double Optimize(Area * area, Function * func, StopCriterion * stopCrit, int * iter) override;
	~CoordinateDescent() {}
};

class StohasticSearch : public OptMethod {
public:
	double Optimize(Area * area, Function * func, StopCriterion * stopCrit, int * iter) override;
	~StohasticSearch() {}
	double prob;
	void SetP(double x) { prob = x; }
};




