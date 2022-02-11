#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"

#include <QTimer>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QMainWindow>

#include <vector>

enum card_type{MUSTIKKA, MANSIKKA, BANAANI, KARVIAINEN, PIERU, LAST};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void turnCard();
    void onTimeout();

private:
    Ui::MainWindow *ui;

    QTimer* timer_;

    QGraphicsView* window_;
    QGraphicsScene* game_board_;

    std::vector<std::vector<Card *>> cards_ = {};

    Card* first_ = nullptr;
    Card* second_ = nullptr;
    unsigned short cards_turned_ = 0;

    void initialize_board();
    QColor typeToColor(card_type type);

    bool compareColors();
    void enableButtons(bool enable);
};
#endif // MAINWINDOW_HH
