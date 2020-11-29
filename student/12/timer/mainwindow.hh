#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer;

private slots:
    // Add your slots here
    void on_timeout();
    void on_start();
    void on_stop();
    void on_reset();
    void on_close();

private:
    void update_display(int mins, int secs);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HH
