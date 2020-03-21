#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "optdata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    OptData opt;
    double geomx;
    double geomy;

private slots:
    void makePlot();

    void on_pushButton_Ok_clicked();

    void on_comboBox_metod_currentIndexChanged(int index);

    void on_comboBox_function_currentIndexChanged(int index);

    void on_comboBox_Stop_crit_CD_currentIndexChanged(int index);

    void on_comboBox_Stop_crit_SS_currentIndexChanged(int index);

    void on_comboBox_Area_currentIndexChanged(int index);

    void mouseClick(QMouseEvent* event);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
