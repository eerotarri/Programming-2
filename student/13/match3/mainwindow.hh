/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2020                                    #
# Project3: Match3                                                          #
# File: mainwindow.hh                                                       #
# Description: Fruit flip game header file. Data-structure                  #
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

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include <deque>
#include <random>
#include <QTimer>
#include <QLabel>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Eventfilter to get access to mouse button press events.
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:

    void button_pushed_down();
    void on_timeout();
    void switch_boxes();
    void drop_boxes(bool d=true);
    void delete_boxes();
    void reinitialize();
    void quit();

private:
    Ui::MainWindow *ui;

    // Scene for the game grid
    QGraphicsScene* scene_;

    QTimer* timer;

    // The direction to examine clicked rectangle with.
    // UP by default.
    enum Direction {UP,
                   DOWN,
                   LEFT,
                   RIGHT};

    Direction direction_ = UP;

    // Margins for the drawing area (the graphicsView object)
    // You can change the values as you wish
    const int TOP_MARGIN = 150;
    const int LEFT_MARGIN = 100;

    // Size of a square containing a fruit
    const int SQUARE_SIDE = 45; // give your own value here
    // Number of vertical cells (places for fruits)
    const int ROWS = 8; // give your own value here
    // Number of horizontal cells (places for fruits)
    const int COLUMNS = 11; // give your own value here

    // Constants describing scene coordinates
    const int BORDER_UP = 0;
    const int BORDER_DOWN = SQUARE_SIDE * ROWS;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = SQUARE_SIDE * COLUMNS;

    // QColor codes for the colors
    const QColor RED = QColor(255, 0, 0);
    const QColor VIOLET = QColor(221, 160, 221);
    const QColor GREEN = QColor(0, 255, 0);
    const QColor YELLOW = QColor(255, 255, 0);
    const QColor BLUE = QColor(79, 134, 247);
    const QColor ORANGE_COLOR = QColor(255, 165, 0);

    // Data-structure to store information of rectangles
    std::vector<std::vector<QGraphicsRectItem*>> fruits_;

    // Constants for different fruits and the number of them
    // Add/remove fruits as you wish, or you can remove the whole enum type
    // Actually only the value NUMBER_OF_FRUITS is needed in the
    // template code
    enum Fruit_kind {PLUM,
                     STRAWBERRY,
                     APPLE,
                     LEMON,
                     BLUEBERRY,
                     ORANGE,
                     NUMBER_OF_FRUITS};

    // Container for items that have to be removed from the scene.
    std::set<QGraphicsRectItem*> objects_to_remove_;

    // Indexes of the x and y positions most recently clicked.
    int clicked_x_;
    int clicked_y_;

    // Boolen to determine if a rectangle has been clicked and the game is
    // still in process of deleting boxes or dropping them.
    bool already_pressed_ = false;

    // Boolean to determine if a match was found when scene was clicked.
    bool no_match_ = false;

    // Hours, minutes and seconds passed
    // since the game was started or reinitialized.
    int hours_ = 0;
    int minutes_ = 0;
    int seconds_ = 0;

    // Writes the titles for the grid rows and columns
    void init_titles();

    // Fills the board with colored rectangles
    void init_scene();

    // Checks the scene for any lines of three or more fruits.
    bool check_for_match();

    // Functions to disable or enable direction buttons.
    void disable_buttons();
    void enable_buttons();
};
#endif // MAINWINDOW_HH
