#ifndef OPTDATA_H
#define OPTDATA_H
#include <vector>


class OptData
{
public:
    int methodNumb = 0;
    int functionNumb = 0;
    int dim = 2;
    int stopCritCD = 0;
    int stopCritSS = 0;
    double rangeX1 = 0, rangeX2 = 1, rangeY1 = 0, rangeY2 = 1;
    int areaNumb = 0;
    double eps = 0.0001;
    double prob = 0.3;
    int maxIter = 1000;
    int maxIterAfterLastSuccess = 100;

    long double min;
    std::vector <double> argmin;
    int noOfIterations;
    std::vector <double>  x_0;


    OptData();
    ~OptData();
};

#endif // OPTDATA_H
