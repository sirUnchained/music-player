#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include <SFML/Audio.hpp>

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

    QLabel *musicName, *musicTimer;
    QWidget *page;
    QVBoxLayout *mainLayout, *musicInfo;
    QHBoxLayout *musicOptionsLayout;
    QPushButton *playBtn, *tenSecUp, *tenSecDown, *choseSong;
    QSlider *musicPlace;

    bool isPlaying{false};
    sf::Music music;

    void playPauseMusic();
    void forward10Sec();
    void backward10Sec();
};
#endif // MAINWINDOW_H
