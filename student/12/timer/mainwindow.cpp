#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));

    ui->lcdNumberSec->setPalette(palette);
    ui->lcdNumberSec->setAutoFillBackground(true);

    ui->lcdNumberMin->setPalette(palette);
    ui->lcdNumberMin->setAutoFillBackground(true);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::on_stop);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_reset);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::on_close);

    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timeout()
{
    int current_mins = ui->lcdNumberMin->intValue();
    int current_secs = ui->lcdNumberSec->intValue();

    if (current_secs == 59) {
        update_display(current_mins + 1, 0);
    } else {
        update_display(current_mins, current_secs + 1);
    }
}

void MainWindow::on_start()
{
    timer->start();
}

void MainWindow::on_stop()
{
    timer->stop();
}

void MainWindow::on_reset()
{
    update_display(0, 0);
}

void MainWindow::on_close()
{
    close();
}

void MainWindow::update_display(int mins, int secs)
{
    ui->lcdNumberMin->display(mins);
    ui->lcdNumberSec->display(secs);
}
