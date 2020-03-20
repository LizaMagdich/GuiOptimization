#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>

#include "Area.h"
#include "Function.h"
#include "OptMethod.h"
#include "StopCriterion.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mousePos(QMouseEvent*)));
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mouseClick(QMouseEvent*)));

    opt.functionNumb = ui->comboBox_function->currentIndex();
    opt.areaNumb = ui->comboBox_Area->currentIndex();
    opt.methodNumb = ui->comboBox_metod->currentIndex();
    opt.stopCritCD = ui->comboBox_Stop_crit_CD->currentIndex();
    opt.stopCritSS = ui->comboBox_Stop_crit_SS->currentIndex();
    opt.eps = ui->eps->value();
    opt.prob = ui->prob->value();
    opt.maxIter = ui->max_iter->value();

    Area * area = nullptr;
    switch(opt.areaNumb){
           case 0:{
               area = new Area_1_F_1;
               break;
           }
           case 1:{
               area = new Area_2_F_1;
               break;
           }
           case 2:{
               area = new Area_3_F_1;
               break;
           }
       }


    opt.rangeX1 = area->GetBorderI(0);
    opt.rangeX2 = area->GetBorderI(1);
    opt.rangeY1 = area->GetBorderI(2);
    opt.rangeY2 = area->GetBorderI(3);

    delete area;

    opt.x_0.clear();
    opt.x_0.push_back(ui->x_0->value());
    opt.x_0.push_back( ui->y_0->value());

    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot(){
    ui->customPlot->clearPlottables();
    ui->customPlot->axisRect()->setupFullAxesBox(true);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
    int nx = 200;
    int ny = 200;

    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(opt.rangeX1, opt.rangeX2), QCPRange(opt.rangeY1, opt.rangeY2)); // and span the coordinate range
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);

        Function * func = nullptr;

        switch(opt.functionNumb){
               case 0:{
                     z=(x- 2)*(x - 2)*(x - 2)*(x - 2) + (x - 2*y)*(x - 2 *y);
                   break;
               }
               case 1:{
                  z=0.1*cos(10*(x*x + y*y));
                   break;
               }
               case 2:{
                   z=x*x + y*y;
                   break;
               }
           }
        vector<double> vec;
        vec.push_back(x);
        vec.push_back(y);
        delete func;
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    //colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}


void MainWindow::on_pushButton_Ok_clicked()
{
    opt.functionNumb = ui->comboBox_function->currentIndex();
    opt.areaNumb = ui->comboBox_Area->currentIndex();
    opt.methodNumb = ui->comboBox_metod->currentIndex();
    opt.stopCritCD = ui->comboBox_Stop_crit_CD->currentIndex();
    opt.stopCritSS = ui->comboBox_Stop_crit_SS->currentIndex();
    opt.eps = ui->eps->value();
    opt.prob = ui->prob->value();
    opt.maxIter = ui->max_iter->value();

    Area * area = nullptr;
    switch(opt.areaNumb){
           case 0:{
               area = new Area_1_F_1;
               break;
           }
           case 1:{
               area = new Area_2_F_1;
               break;
           }
           case 2:{
               area = new Area_3_F_1;
               break;
           }
       }


    opt.rangeX1 = area->GetBorderI(0);
    opt.rangeX2 = area->GetBorderI(1);
    opt.rangeY1 = area->GetBorderI(2);
    opt.rangeY2 = area->GetBorderI(3);



    opt.x_0.push_back(ui->x_0->value());
    opt.x_0.push_back( ui->y_0->value());


    Function * func = nullptr;

    switch(opt.functionNumb){
           case 0:{
               func = new F_1;
               break;
           }
           case 1:{
               func = new F_2;
               break;
           }
           case 2:{
               func = new F_3;
               break;
           }
       }


    OptMethod * method = nullptr;
    StopCriterion* stopCrit = nullptr;


    switch(opt.methodNumb){
           case 0:{
               method = new CoordinateDescent;
               switch(opt.stopCritCD){
                      case 0:{
                          stopCrit = new NormDifOfNodes;
                          break;
                      }
                      case 1:{
                          stopCrit = new NormDifOfValFunc;
                          break;
                      }
                      case 2:{
                          stopCrit = new NormGrad;
                          break;
                      }
                  }
               break;
           }
           case 1:{
               method = new StohasticSearch;
               switch(opt.stopCritSS){
                      case 0:{
                          stopCrit = new ModDifOfNodes;
                          break;
                      }
                      case 1:{
                          stopCrit = new LatestImprov;;
                          break;
                      }
                  }
               break;
           }
       }

    area->SetDim(func->GetDimension());
    stopCrit->SetEps(opt.eps);
    method->SetStartPoint(opt.x_0);
    stopCrit->SetNumberMaxIter(opt.maxIter);

    int iter = 0;
    opt.min = method->Optimize(area, func, stopCrit, &iter);
    opt.argmin = method->GetFinalPoint();
    opt.noOfIterations = iter;

    //ploting

    QVector<double> xGraph = QVector<double>(method->xGraph.begin(), method->xGraph.end());
    QVector<double> yGraph = QVector<double>(method->yGraph.begin(), method->yGraph.end());
    xGraph.push_front(opt.x_0[0]);
    yGraph.push_front(opt.x_0[1]);

    QCPCurve *pathGraph = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
    pathGraph->setData(xGraph, yGraph);
    pathGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 0), QBrush(Qt::red), 5));
    pathGraph->setPen(QPen(Qt::gray, 2));
    QCPCurve *finalPoint = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QVector<double> argx, argy;
    argx.push_back(opt.argmin[0]);
    argy.push_back(opt.argmin[1]);
    finalPoint->setData(argx, argy);
    finalPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, QPen(Qt::yellow, 3), QBrush(Qt::yellow), 12));
    finalPoint->setPen(QPen(QColor(120, 120, 120), 2));

    ui->customPlot->replot();

    ui->textBrowser->insertPlainText("min: ");
    QString num;
    num = QString::number(double(opt.min));
    ui->textBrowser->insertPlainText(num);

    ui->textBrowser->insertPlainText("\nargmin: (");
    num = QString::number(double(opt.argmin[0]));
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText(" ; ");
    num = QString::number(double(opt.argmin[1]));
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText(")");
    ui->textBrowser->insertPlainText("\nIterations:");
    num = QString::number(double(opt.noOfIterations));
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText("\n");

    ui->customPlot->QCustomPlot::removePlottable(pathGraph);
    ui->customPlot->QCustomPlot::removePlottable(finalPoint);



    delete area;
    delete func;
    delete method;
    delete stopCrit;
}



void MainWindow::mousePos(QMouseEvent* event)
{

}

void MainWindow::mouseClick(QMouseEvent* event)
{

    ui->textBrowser->clear();


    ui->textBrowser->insertPlainText("\n");
    ui->textBrowser->insertPlainText("Start point: (");
    QString num;


    ui->customPlot->mouseMove(event);


    geomx = opt.rangeX1 + (opt.rangeX2-opt.rangeX1)*(double((event->x()) - 50.)/401);
    geomy = opt.rangeY1 + (opt.rangeX2-opt.rangeX1)*(1 - double((event->y())  - 14.)/619);

    if(geomx < opt.rangeX1 || geomx > opt.rangeX2 || geomy < opt.rangeY1 || geomy > opt.rangeY2){
       ui->textBrowser->clear();
       ui->textBrowser->insertPlainText("Сlick on the plot.");
    }else{

    num = QString::number(geomx);
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText(" ; ");
    num = QString::number(geomy);
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText(")");
    ui->textBrowser->insertPlainText("\n");


    ui->x_0->setValue(geomx);
    ui->y_0->setValue(geomy);

    opt.x_0.clear();

    opt.x_0.push_back(ui->x_0->value());
    opt.x_0.push_back(ui->y_0->value());

    MainWindow::on_pushButton_Ok_clicked();

    }
}




void MainWindow::on_comboBox_metod_currentIndexChanged(int index)
{
    opt.methodNumb = index;

    MainWindow::makePlot();
}

void MainWindow::on_comboBox_function_currentIndexChanged(int index)
{
    opt.functionNumb = index;

    MainWindow::makePlot();
}

void MainWindow::on_comboBox_Stop_crit_CD_currentIndexChanged(int index)
{
    opt.stopCritCD = index;

    MainWindow::makePlot();
}

void MainWindow::on_comboBox_Stop_crit_SS_currentIndexChanged(int index)
{
    opt.stopCritSS = index;

    MainWindow::makePlot();
}

void MainWindow::on_comboBox_Area_currentIndexChanged(int index)
{
    opt.areaNumb = index;

    Area * area = nullptr;
    switch(opt.areaNumb){
           case 0:{
               area = new Area_1_F_1;
               break;
           }
           case 1:{
               area = new Area_2_F_1;
               break;
           }
           case 2:{
               area = new Area_3_F_1;
               break;
           }
       }

    opt.rangeX1 = area->GetBorderI(0);
    opt.rangeX2 = area->GetBorderI(1);
    opt.rangeY1 = area->GetBorderI(2);
    opt.rangeY2 = area->GetBorderI(3);

    delete area;
     MainWindow::makePlot();

}
