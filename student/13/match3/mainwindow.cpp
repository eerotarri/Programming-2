﻿#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QDebug>
#include <QPixmap>
#include <vector>
#include <set>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles
    scene_ = new QGraphicsScene(this);

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(LEFT_MARGIN, TOP_MARGIN,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);
    //

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a fruit is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // int seed = time(0); // You can change seed value for testing purposes
    int seed = 5;
    randomEng_.seed(seed);
    distr_ = std::uniform_int_distribution<int>(0, NUMBER_OF_FRUITS - 1);
    distr_(randomEng_); // Wiping out the first random number (which is almost always 0)

    init_titles();
    init_scene();

    ui->graphicsView->installEventFilter(this);

    connect(ui->upButton, &QRadioButton::clicked, this, &MainWindow::on_button_clicked);
    connect(ui->downButton, &QRadioButton::clicked, this, &MainWindow::on_button_clicked);
    connect(ui->leftButton, &QRadioButton::clicked, this, &MainWindow::on_button_clicked);
    connect(ui->rightButton, &QRadioButton::clicked, this, &MainWindow::on_button_clicked);

    // Sets button up checked by default.
    ui->upButton->setChecked(true);

    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QPoint point = ui->graphicsView->mapFromGlobal(QCursor::pos());
        int x = point.x();
        int y = point.y();
        clicked_x_ = x;
        clicked_y_ = y;
        switch_boxes();
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_timeout()
{
    switch_boxes(true);
    timer->stop();
}





void MainWindow::on_button_clicked()
{
    if (ui->upButton->isChecked()) {
        direction_ = UP;
    } else if (ui->downButton->isChecked()) {
        direction_ = DOWN;
    } else if (ui->leftButton->isChecked()) {
        direction_ = LEFT;
    } else if (ui->rightButton->isChecked()) {
        direction_ = RIGHT;
    }
    // qDebug() << direction_;
}

void MainWindow::init_titles()
{
    // Displaying column titles, starting from A
    for(int i = 0, letter = 'A'; i < COLUMNS; ++i, ++letter)
    {
        int shift = 5;
        QString letter_string = "";
        letter_string.append(letter);
        QLabel* label = new QLabel(letter_string, this);
        label->setGeometry(LEFT_MARGIN + shift + i * SQUARE_SIDE,
                           TOP_MARGIN - SQUARE_SIDE,
                           SQUARE_SIDE, SQUARE_SIDE);
    }

    // Displaying row titles, starting from A
    for(int i = 0, letter = 'A'; i < ROWS; ++i, ++letter)
    {
        QString letter_string = "";
        letter_string.append(letter);
        QLabel* label = new QLabel(letter_string, this);
        label->setGeometry(LEFT_MARGIN - SQUARE_SIDE,
                           TOP_MARGIN + i * SQUARE_SIDE,
                           SQUARE_SIDE, SQUARE_SIDE);
    }
}

void MainWindow::init_scene()
{
    int i = 0;
    while (i < ROWS) {
        fruits_.push_back({});
        int j = 0;
        while (j < COLUMNS) {
            QGraphicsRectItem* new_rect = new QGraphicsRectItem(0,0,SQUARE_SIDE, SQUARE_SIDE);
            new_rect->setPos(j * SQUARE_SIDE, i * SQUARE_SIDE);

            Fruit_kind color = static_cast<Fruit_kind>(rand() % NUMBER_OF_FRUITS);
            if (color == PLUM) {
                new_rect->setBrush(VIOLET);
            } else if (color == STRAWBERRY) {
                new_rect->setBrush(RED);
            } else if (color == APPLE) {
                new_rect->setBrush(GREEN);
            } else if (color == LEMON) {
                new_rect->setBrush(YELLOW);
            } else if (color == BLUEBERRY) {
                new_rect->setBrush(BLUE);
            } else if (color == ORANGE) {
                new_rect->setBrush(ORANGE_COLOR);
            }
            scene_->addItem(new_rect);

            fruits_.at(i).push_back(new_rect);
            ++j;
        }
        ++i;
    }

//    for (auto i : fruits_) {
//        for(auto j : i) {
//            qDebug() << j->brush();
//        }
//        qDebug() << "Rivi vaihtuu";
//    }

    // Initializes the scene until no lines of three or more exists.
    while (check_for_match()) {
        scene_->clear();
        fruits_.clear();
        init_scene();
    }

//    for (auto vector : fruits_) {
//        for (auto item : vector) {
//            item->acceptTouchEvents();
//            connect(item, &QGraphicsRectItem::isSelected, this, &MainWindow::on_mouse_press);
//        }
//    }

}

bool MainWindow::check_for_match()
{

    std::set<QGraphicsRectItem*> objects_to_remove;

    // Algorithm to search for rows of three or more fruits
    int j_index = 0;
    while (j_index < ROWS) {
        int i_index = 1;
        std::set<QGraphicsRectItem*> row_queue = {};

        while (i_index < COLUMNS) {

            row_queue.insert(fruits_[j_index][i_index-1]);

            // Looks if two consecutive objects on x-axis are the same
            // and adds them to the row queue.
            if (fruits_[j_index][i_index]->brush() ==
                    fruits_[j_index][i_index-1]->brush()) {
                row_queue.insert(fruits_[j_index][i_index]);
                if (i_index + 1 == COLUMNS) {

                    if (row_queue.size() >= 3) {
                        for (auto obj : row_queue) {
                            objects_to_remove.insert(obj);
                        }
                    }
                }
            // Adds objects to the set of items to be removed
            // if there are at least 3 in a row and resets row_queue.
            } else {
                if (row_queue.size() >= 3) {
                    for (auto obj : row_queue) {
                        objects_to_remove.insert(obj);
                    }
                }
                row_queue = {};
            }
            ++i_index;
        }
        ++j_index;
    }

    // Algorithm to search for rows of three or more fruits
    int i_index = 0;
    while (i_index < COLUMNS) {
        int j_index = 1;
        std::set<QGraphicsRectItem*> column_queue = {};

        while (j_index < ROWS) {

            column_queue.insert(fruits_[j_index-1][i_index]);

            // Looks if two consecutive objects on y-axis are the same
            // and adds them to the column queue.
            if (fruits_[j_index][i_index]->brush() ==
                    fruits_[j_index-1][i_index]->brush()) {
                column_queue.insert(fruits_[j_index][i_index]);
                if (j_index + 1 == ROWS) {

                    if (column_queue.size() >= 3) {
                        for (auto obj : column_queue) {
                            objects_to_remove.insert(obj);
                        }
                    }
                }
            // Adds objects to the set of items to be removed
            // if there are at least 3 in a row and resets column_queue.
            } else {
                if (column_queue.size() >= 3) {
                    for (auto obj : column_queue) {
                        objects_to_remove.insert(obj);
                    }
                }
                column_queue = {};
            }
            ++j_index;
        }
        ++i_index;
    }

//    qDebug() << objects_to_remove.size();

    return objects_to_remove.size() != 0;


//    for (auto item : objects_to_remove) {
//        qDebug() << item->pos();
    //    }
}

void MainWindow::switch_boxes(bool no_match)
{
    int x_of_item = clicked_x_ - clicked_x_ % SQUARE_SIDE;
    int y_of_item = clicked_y_ - clicked_y_ % SQUARE_SIDE;

    int x_index = x_of_item / SQUARE_SIDE;
    int y_index = y_of_item / SQUARE_SIDE;

    int x_dir = x_index;
    int y_dir = y_index;
    if (direction_ == UP) {
        y_dir = y_index - 1;
    } else if (direction_ == LEFT) {
        x_dir = x_index - 1;
    } else if (direction_ == DOWN) {
        y_dir = y_index + 1;
    } else if (direction_ == RIGHT) {
        x_dir = x_index + 1;
    }

    QBrush tmp = fruits_.at(y_index).at(x_index)->brush();
    if (y_dir >= 0 && x_dir >= 0 &&
        y_dir < ROWS && x_dir < COLUMNS) {
        fruits_.at(y_index).at(x_index)->setBrush(fruits_.at(y_dir).at(x_dir)->brush());
        fruits_.at(y_dir).at(x_dir)->setBrush(tmp);

    }

    if (!check_for_match() && !no_match) {
        timer->start();
    }

}

void MainWindow::draw_fruit()
{
    // Vector of fruits
    const std::vector<std::string>
            fruits = {"cherries", "strawberry", "orange", "pear", "apple",
                      "bananas", "tomato", "grapes", "eggplant"};

    // Defining where the images can be found and what kind of images they are
    const std::string PREFIX(":/");
    const std::string SUFFIX(".png");

    // Converting image (png) to a pixmap
    int i = 0; // try different values in 0 <= i < fruits.size()
    std::string filename = PREFIX + fruits.at(i) + SUFFIX;
    QPixmap image(QString::fromStdString(filename));

    // Scaling the pixmap
    image = image.scaled(SQUARE_SIDE, SQUARE_SIDE);

    // Setting the pixmap for a new label
    QLabel* label = new QLabel("test", this);
    label->setGeometry(LEFT_MARGIN + COLUMNS * SQUARE_SIDE,
                       TOP_MARGIN + ROWS * SQUARE_SIDE,
                       SQUARE_SIDE, SQUARE_SIDE);
    label->setPixmap(image);
}

