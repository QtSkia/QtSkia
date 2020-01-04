#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_skiaWidget = new SkWidget;
    setCentralWidget(m_skiaWidget);

    ui->label_speed->setParent(m_skiaWidget);
    ui->pushButton_up->setParent(m_skiaWidget);
    ui->pushButton_down->setParent(m_skiaWidget);
    ui->pushButton_left->setParent(m_skiaWidget);
    ui->pushButton_right->setParent(m_skiaWidget);
    ui->horizontalSlider->setParent(m_skiaWidget);
    m_skiaWidget->setParent(this);
    m_skiaWidget->resize(this->width(), this->height());

    m_skiaWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_up_clicked()
{
    m_skiaWidget->moveUp();
}

void MainWindow::on_pushButton_down_clicked()
{
    m_skiaWidget->moveDown();
}

void MainWindow::on_pushButton_right_clicked()
{
    m_skiaWidget->moveRight();
}

void MainWindow::on_pushButton_left_clicked()
{
    m_skiaWidget->moveLeft();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    m_skiaWidget->setSpeed(value / 1000.0f);
    ui->label_speed->setText(QString::number(value));
}
