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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:

    void on_button_clicked();
    void on_timeout();

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
    const int SQUARE_SIDE = 35; // give your own value here
    // Number of vertical cells (places for fruits)
    const int ROWS = 10; // give your own value here
    // Number of horizontal cells (places for fruits)
    const int COLUMNS = 12; // give your own value here

    // Constants describing scene coordinates
    const int BORDER_UP = 0;
    const int BORDER_DOWN = SQUARE_SIDE * ROWS;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = SQUARE_SIDE * COLUMNS;

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

    // For randomly selecting fruits for the grid
    std::default_random_engine randomEng_;
    std::uniform_int_distribution<int> distr_;

    int clicked_x_;
    int clicked_y_;

    // Writes the titles for the grid rows and columns
    void init_titles();

    // Fills the board with colored rectangles
    void init_scene();

    // Checks the scene for any lines of three or more fruits.
    bool check_for_match();

    void switch_boxes(bool no_match=false);

    // Draws a single fruit near the right bottom corner of the grid
    // At the moment, this function is not called in the template,
    // but try to do so, if you want to use real fruits instead of rectangles.
    void draw_fruit();
};
#endif // MAINWINDOW_HH
