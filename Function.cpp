#include "Function.h"


void Function::PrintName() { std::cout << "I am a function " << Name(); std::cout << std::endl; }

const char * F_1::Name() { return "(x1 - 2)^4 + (x1 - 2*x2)^2.\0"; }

const char * F_2::Name() { return "0.1*cos(10*(x^2 + y^2)).\0"; }

const char * F_3::Name() { return "(x1)^2 + (x2)^2.\0"; }

double F_1::eval( vector<double> x) {
	return ((x[0] - 2)*(x[0] - 2)*(x[0] - 2)*(x[0] - 2) + (x[0] - 2 * x[1])*(x[0] - 2 * x[1]));
}

double F_2::eval(vector<double> x) {
    return  0.1*cos(10*(x[0]*x[0] + x[1]*x[1]));
}


double F_3::eval(vector<double> x) {
    return x[0] * x[0] + x[1]* x[1];
}
