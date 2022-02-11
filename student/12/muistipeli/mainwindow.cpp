#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QDebug>

const int CARD_WIDHT = 70; // kortin leveys
const int CARD_HEIGHT = 100; // kortin korkeus

const int PADDING_X = 10;
const int PADDING_Y = 10;

const int X_AMOUNT = 8;
const int Y_AMOUNT = 5;

const int SIDE_PADDING = 50;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, this, &MainWindow::onTimeout);

    this->resize((CARD_WIDHT + PADDING_X) * X_AMOUNT + 2 * SIDE_PADDING,  (CARD_HEIGHT + PADDING_Y) * Y_AMOUNT + 2 * SIDE_PADDING);

    window_ = new QGraphicsView(this);
    window_->setGeometry(SIDE_PADDING, SIDE_PADDING, (CARD_WIDHT + PADDING_X) * X_AMOUNT,  (CARD_HEIGHT + PADDING_Y) * Y_AMOUNT);

    game_board_ = new QGraphicsScene();



    window_->setScene(game_board_);


    initialize_board();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::turnCard()
{
    auto button = qobject_cast<Card*>(sender());
    button->setAutoFillBackground(true);
    QPalette palette = button->palette();
    palette.setColor(QPalette::Button, button->getColor());
    button->setPalette(palette);
    button->update();

    cards_turned_++;
    if (cards_turned_ == 1) {
        first_ = button;
    } else if (cards_turned_ == 2) {
        second_ = button;
        enableButtons(false);
        compareColors();
    }
}

void MainWindow::onTimeout()
{
    first_->hideColor();
    second_->hideColor();

    cards_turned_ = 0;

    enableButtons(true);

    timer_->stop();
}

void MainWindow::initialize_board()
{
    int j = 0;
    while (j < Y_AMOUNT) {
        cards_.push_back({});

        int i = 0;
        while (i < X_AMOUNT) {
            card_type type = static_cast<card_type>(rand() % LAST);
            QColor color = typeToColor(type);


            Card* button = new Card(color);
            connect(button, &QAbstractButton::clicked, this, &MainWindow::turnCard);
            button->setGeometry((CARD_WIDHT + PADDING_X) * i,
                                (CARD_HEIGHT + PADDING_Y) * j,
                                CARD_WIDHT, CARD_HEIGHT);
            game_board_->addWidget(button);

            cards_.at(j).push_back(button);

            ++i;
        }
        ++j;
    }
}

QColor MainWindow::typeToColor(card_type type)
{
    switch (type) {
    case MUSTIKKA:
        return QColor(0,0,255);
        break;
    case MANSIKKA:
        return QColor(255,0,0);
        break;
    case KARVIAINEN:
        return QColor(255,0,0);
        break;
    case BANAANI:
        return QColor(255,255,0);
        break;
    case PIERU:
        return QColor(150,75,0);
        break;
    default:
        return QColor(0,0,0);
    }
}

bool MainWindow::compareColors()
{
    if (first_->getColor() == second_->getColor()) {
        qDebug() << "on sama väri";
        return true;
    }
    qDebug() << "on eri väri";
    timer_->start(2000);

    return false;
}

void MainWindow::enableButtons(bool enable)
{
    for (auto row : cards_) {
        for (auto card : row) {
            if (card != nullptr) {
                if (enable) {
                    card->setEnabled(true);
                } else {
                    card->setEnabled(false);
                }
            }
        }
    }
}

