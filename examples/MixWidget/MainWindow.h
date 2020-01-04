#pragma once

#include <QtWidgets/QMainWindow>
#include "SkWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_left_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    SkWidget *m_skiaWidget = nullptr;
};
