#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QLabel *musicName;
    QWidget *page;
    QVBoxLayout *mainLayout;
    QHBoxLayout *musicOptionsLayout;
    QPushButton *playBtn, *tenSecUp, *tenSecDown, *choseSong;
};
#endif // MAINWINDOW_H
