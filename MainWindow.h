#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CityNetwork.h"
#include <QMainWindow>
#include <QObject>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_pushButton_back_01_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_back_02_clicked();

    void on_pushButton_about_clicked();

    void on_pushButton_custom_clicked();

    void on_pushButton_default_clicked();

    void on_pushButton_selectDir01_clicked();

    void on_pushButton_addCity_clicked();

    void on_pushButton_continue_02_clicked();

    void on_pushButton_back_04_clicked();

    void on_pushButton_addCon_clicked();

    void on_pushButton_nextC_clicked();

    void on_pushButton_selectDir02_clicked();

    void on_pushButton_back_03_clicked();

    void on_lineEdit_Population_returnPressed();

    void on_lineEdit_distance_returnPressed();

private:
    Ui::MainWindow *ui;
    CityNetwork *projectNetwork;
};
#endif // MAINWINDOW_H
