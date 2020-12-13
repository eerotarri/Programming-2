/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QRadioButton *leftButton;
    QRadioButton *rightButton;
    QRadioButton *upButton;
    QRadioButton *downButton;
    QLabel *timeText;
    QLabel *pointText;
    QLCDNumber *pointNumber;
    QLabel *timeLabel;
    QPushButton *restartButton;
    QPushButton *quitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(160, 220, 97, 131));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        graphicsView->setFont(font);
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        leftButton = new QRadioButton(centralwidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setGeometry(QRect(80, 50, 106, 26));
        rightButton = new QRadioButton(centralwidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setGeometry(QRect(200, 50, 106, 26));
        upButton = new QRadioButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(140, 20, 106, 26));
        downButton = new QRadioButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setGeometry(QRect(140, 80, 106, 26));
        timeText = new QLabel(centralwidget);
        timeText->setObjectName(QString::fromUtf8("timeText"));
        timeText->setGeometry(QRect(310, 20, 63, 20));
        pointText = new QLabel(centralwidget);
        pointText->setObjectName(QString::fromUtf8("pointText"));
        pointText->setGeometry(QRect(390, 20, 63, 20));
        pointNumber = new QLCDNumber(centralwidget);
        pointNumber->setObjectName(QString::fromUtf8("pointNumber"));
        pointNumber->setGeometry(QRect(380, 40, 64, 23));
        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setGeometry(QRect(300, 40, 63, 20));
        restartButton = new QPushButton(centralwidget);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));
        restartButton->setGeometry(QRect(680, 30, 84, 28));
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));
        quitButton->setGeometry(QRect(680, 70, 84, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        leftButton->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        rightButton->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        upButton->setText(QCoreApplication::translate("MainWindow", "Up", nullptr));
        downButton->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        timeText->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        pointText->setText(QCoreApplication::translate("MainWindow", "Points", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        restartButton->setText(QCoreApplication::translate("MainWindow", "RESTART", nullptr));
        quitButton->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
