/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2020                                    #
# Project3: Match3                                                          #
# File: mainwindow.cpp                                                      #
# Description: Fruit flip game implementation file. Data-structure          #
#        consists of QGraphicsRectItem pointers that have respective        #
#        positions in the scene                                             #
#                                                                           #
# Program author                                                            #
# Name: Eero Tarri                                                          #
# Student number: 283568                                                    #
# UserID: tarri                                                             #
# E-Mail: eero.tarri@tuni.fi                                                #
#############################################################################
*/

#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QDebug>
#include <QPixmap>
#include <vector>

// Constructor for MainWindow
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

    init_titles();
    init_scene();

    ui->graphicsView->installEventFilter(this);

    connect(ui->upButton, &QRadioButton::clicked, this, &MainWindow::button_pushed_down);
    connect(ui->downButton, &QRadioButton::clicked, this, &MainWindow::button_pushed_down);
    connect(ui->leftButton, &QRadioButton::clicked, this, &MainWindow::button_pushed_down);
    connect(ui->rightButton, &QRadioButton::clicked, this, &MainWindow::button_pushed_down);

    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::reinitialize);

    // Sets button up checked by default.
    ui->upButton->setChecked(true);

    // Timer for the clock with 1 second interval.
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);
    timer->start();

}

// Destructor for MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Eventfilter to get position of the clicked rectangle.
// When the scene is clicked position of cursor is saved in
// attributes clicked_x_ and clicked_y_.
// Disables clicking rectangles and direction buttons until
// dropping boxes is done or the rectangle has been switched back.
// If rectangle is clicked eventfilter will call for switch_boxes.
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (!already_pressed_) {
        if (event->type() == QEvent::MouseButtonPress) {
            already_pressed_ = true;
            disable_buttons();
            clicked_x_ = ui->graphicsView->mapFromGlobal(QCursor::pos()).x();
            clicked_y_ = ui->graphicsView->mapFromGlobal(QCursor::pos()).y();
            no_match_ = false;
            switch_boxes();
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

// Timeout slot for updating the timeLabel. Gets current time from attributes
// and updates it. Time is converted into a string type variable time that is
// given to the timeLabel object.
void MainWindow::on_timeout()
{
    seconds_ += 1;
    if (seconds_ > 59) {
        seconds_ = 0;
        minutes_ += 1;
    }
    if (minutes_ > 59) {
        minutes_ = 0;
        hours_ += 1;
    }

    std::string time;
    if (hours_ < 10) {
        time.append("0");
        time.append(std::to_string(hours_));
    } else {
        time.append(std::to_string(hours_));
    }
    time.append(":");
    if (minutes_ < 10) {
        time.append("0");
        time.append(std::to_string(minutes_));
    } else {
        time.append(std::to_string(minutes_));
    }
    time.append(":");
    if (seconds_ < 10) {
        time.append("0");
        time.append(std::to_string(seconds_));
    } else {
        time.append(std::to_string(seconds_));
    }
    ui->timeLabel->setText(QString::fromStdString(time));

}

// Slot for clicking the direction buttons. Finds out which button is activated
// and changes attribute direction_ to corresponding DIRECTION type direction.
void MainWindow::button_pushed_down()
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
}

// Initializes the titles around scene.
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

// Initializes the scene and fills it with colored rectangles.
// Also fills the container fruits_ with pointers to the rectangles
// in the same order as in the scene. At the start of the game or
// when reinitialized this will repeat until no matches are found.
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

    // Initializes the scene until no lines of three or more exists.
    while (check_for_match()) {
        objects_to_remove_.clear();
        scene_->clear();
        fruits_.clear();
        init_scene();
    }
}

// Function that finds the pointers to all the rectangles that make a match
// of three or more. Algorithm iterates trough the objects and checks if to
// consecutive objects have the same color. When the current rectangle no
// longer has the same color as the previous or when the row or column has
// no more objects to iterate trough the algorithm checks if the queue
// container has three or more pointers in it and adds them to the container
// objects_to_remove_.
// Returns true if matches of three or more were found and false otherwise.
bool MainWindow::check_for_match()
{
    // Algorithm to search for rows of three or more fruits
    int j_index = 0;
    while (j_index < ROWS) {
        int i_index = 1;
        std::set<QGraphicsRectItem*> row_queue = {};

        while (i_index < COLUMNS) {

            if (!(fruits_[j_index][i_index] == nullptr || fruits_[j_index][i_index-1] == nullptr)) {
                row_queue.insert(fruits_[j_index][i_index-1]);

                // Looks if two consecutive objects on x-axis are the same
                // and adds them to the row queue.
                if (fruits_[j_index][i_index]->brush() ==
                        fruits_[j_index][i_index-1]->brush()) {
                    row_queue.insert(fruits_[j_index][i_index]);
                    if (i_index + 1 == COLUMNS) {

                        if (row_queue.size() >= 3) {
                            for (auto obj : row_queue) {
                                objects_to_remove_.insert(obj);
                            }
                        }
                    }
                // Adds objects to the set of items to be removed
                // if there are at least 3 in a row and resets row_queue.
                } else {
                    if (row_queue.size() >= 3) {
                        for (auto obj : row_queue) {
                            objects_to_remove_.insert(obj);
                        }
                    }
                    row_queue = {};
                }
            } else {
                if (row_queue.size() >= 3) {
                    for (auto obj : row_queue) {
                        objects_to_remove_.insert(obj);
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

            if (!(fruits_[j_index][i_index] == nullptr || fruits_[j_index-1][i_index] == nullptr)) {
                column_queue.insert(fruits_[j_index-1][i_index]);

                // Looks if two consecutive objects on y-axis are the same
                // and adds them to the column queue.
                if (fruits_[j_index][i_index]->brush() ==
                        fruits_[j_index-1][i_index]->brush()) {
                    column_queue.insert(fruits_[j_index][i_index]);
                    if (j_index + 1 == ROWS) {

                        if (column_queue.size() >= 3) {
                            for (auto obj : column_queue) {
                                objects_to_remove_.insert(obj);
                            }
                        }
                    }
                // Adds objects to the set of items to be removed
                // if there are at least 3 in a row and resets column_queue.
                } else {
                    if (column_queue.size() >= 3) {
                        for (auto obj : column_queue) {
                            objects_to_remove_.insert(obj);
                        }
                    }
                    column_queue = {};
                }
            } else {
                if (column_queue.size() >= 3) {
                    for (auto obj : column_queue) {
                        objects_to_remove_.insert(obj);
                    }
                }
                column_queue = {};
            }
            ++j_index;
        }
        ++i_index;
    }

    return objects_to_remove_.size() != 0;
}

// Function to disable all the direction buttons.
void MainWindow::disable_buttons()
{
    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
}

// Function to enable all the direction buttons.
void MainWindow::enable_buttons()
{
    ui->upButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
}

// Function to remove the objects on the container objects_to_remove_.
// Iterates trough pointers in fruits_ and cross references them with
// pointers in objects_to_remove_ and makes that pointer in fruits_ to
// point at nullptr. Then deletes items in objects to remove.
// Calls drop_boxes with 1 second delay and empties objects_to_remove_.
void MainWindow::delete_boxes()
{
    int j_index = 0;
    for (auto row : fruits_) {
        int i_index = 0;
        for (auto fruit : row) {
            auto found = objects_to_remove_.find(fruit);
            if (found != objects_to_remove_.end()) {
                fruits_.at(j_index).at(i_index) = nullptr;
            }
            ++i_index;
        }
        ++j_index;
    }
    for (QGraphicsRectItem* rec : objects_to_remove_) {
        delete rec;
    }

    // This adds the amount of removed objects to the pointNumber lcd.
    int value = ui->pointNumber->intValue();
    value += objects_to_remove_.size();
    ui->pointNumber->display(QString::number(value));

    objects_to_remove_ = {};
    QTimer::singleShot(1000, this, SLOT(drop_boxes()));
}

// Resets the scene with new colors.
// Resets the clock and points.
void MainWindow::reinitialize()
{
    objects_to_remove_.clear();
    scene_->clear();
    fruits_.clear();
    init_scene();

    seconds_ = 0;
    minutes_ = 0;
    hours_ = 0;

    ui->pointNumber->display(QString::number(0));
}

// Function to drop the boxes as low as they can go.
// Iterates trought fruits_ and whenever rectangle that has nullptr
// underneath it the rectangle is moved to the lower spot and previous position
// is set to point at nullptr. When at least 1 box has been dropped the value
// dropped is set to true. If dropped = true the function will call itself
// recursively.
// If more matches are found after dropping delete_boxes will be called.
// Otherwise buttons and clicking rectangles will be enabled again.
void MainWindow::drop_boxes(bool d)
{
    bool dropped = false;
    int j_index = 0;
    while (j_index < ROWS - 1) {
        int i_index = 0;
        while (i_index < COLUMNS) {
            if (fruits_[j_index][i_index] != nullptr) {
                if (fruits_[j_index + 1][i_index] == nullptr) {
                    // Move rectangle down by one
                    fruits_[j_index][i_index]->setPos(i_index * SQUARE_SIDE,
                                                      (j_index + 1) * SQUARE_SIDE);
                    fruits_[j_index + 1][i_index] = fruits_[j_index][i_index];
                    fruits_[j_index][i_index] = nullptr;
                    dropped = true;
                }
            }
            ++i_index;
        }
        ++j_index;
    }
    if (d == true) {
        drop_boxes(dropped);
    }
    if (check_for_match()) {
        QTimer::singleShot(1000, this, SLOT(delete_boxes()));
    } else {
        already_pressed_ = false;
        enable_buttons();
    }
}

// Function to switch places with two chosen adjacent boxes.
// Indexes are calculated from the position most recently clicked.
// y_dir and x_dir save the position in fruits_ of the object that is switched
// with the clicked object.
// Function wont chance the positions of objects only their colours.
// If no match is found when a rectangle is clicked the function will
// call itself with 1 second delay. Attribute no_match_ tells the function
// that it has called itself previously so it wont loop indefinitely.
// If matches are found delete_boxes will be called.
void MainWindow::switch_boxes()
{
    int x_index = (clicked_x_ - clicked_x_ % SQUARE_SIDE) / SQUARE_SIDE;
    int y_index = (clicked_y_ - clicked_y_ % SQUARE_SIDE) / SQUARE_SIDE;

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
        if (fruits_.at(y_index).at(x_index) != nullptr && fruits_.at(y_dir).at(x_dir) != nullptr) {
            fruits_.at(y_index).at(x_index)->setBrush(fruits_.at(y_dir).at(x_dir)->brush());
            fruits_.at(y_dir).at(x_dir)->setBrush(tmp);
        }
    }

    if (!check_for_match() && !no_match_) {
        no_match_ = true;
        QTimer::singleShot(1000, this, SLOT(switch_boxes()));
        already_pressed_ = false;
    } else {
        QTimer::singleShot(1000, this, SLOT(delete_boxes()));
    }

}
