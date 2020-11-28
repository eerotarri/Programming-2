#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileLineEdit_textEdited(const QString &arg1);

    void on_keyLineEdit_textEdited(const QString &arg1);

    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::string file_ = "";
    std::string line_ = "";
    std::string browser_;
};
#endif // MAINWINDOW_HH
