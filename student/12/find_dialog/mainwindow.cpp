#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileLineEdit_textEdited(const QString &arg1)
{
    file_ = arg1.toStdString();
    //qDebug() << "on_fileLineEdit_textEdited";
}

void MainWindow::on_keyLineEdit_textEdited(const QString &arg1)
{
    line_ = arg1.toStdString();
    //qDebug() << "on_fileLineEdit_textEdited";
}

void MainWindow::on_findPushButton_clicked()
{
    std::ifstream File(file_);
    if (not File) {
        browser_ = "File not found";
    } else {
        std::string rivi;
        bool isFound = false;
        while ( getline(File, rivi) ) {
            if (ui->matchCheckBox->isChecked()) {
                std::transform(line_.begin(), line_.end(), line_.begin(), ::toupper);
                std::transform(rivi.begin(), rivi.end(), rivi.begin(), ::toupper);
            }
            size_t found = rivi.find(line_);
            if (found != std::string::npos) {
                isFound = true;
            }
        }

        if (line_ == "") {
            browser_ = "File found";
        } else if (!isFound) {
            browser_ = "Word not found";
        } else {
            browser_ = "Word found";
        }
    }
    ui->textBrowser->setHtml(QString::fromStdString(browser_));
}
