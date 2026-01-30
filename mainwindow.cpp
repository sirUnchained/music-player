#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , page(new QWidget(this))
{
    setWindowTitle("Music Player");
    resize(800, 600);

    setCentralWidget(page);

    mainLayout = new QVBoxLayout(page);
    musicOptionsLayout = new QHBoxLayout();
    musicInfo = new QVBoxLayout();

    playBtn = new QPushButton("play");
    tenSecUp = new QPushButton("+10");
    tenSecDown = new QPushButton("-10");
    choseSong = new QPushButton("select sound ...");

    musicName = new QLabel("Welcome !!");
    musicTimer = new QLabel("00:00");

    musicPlace = new QSlider(Qt::Horizontal);

    musicName->setAlignment(Qt::AlignCenter);
    musicName->setMargin(50);
    QFont musicNameFont = musicName->font();
    musicNameFont.setPointSize(32);
    musicNameFont.setPixelSize(64);
    musicNameFont.setBold(true);
    musicNameFont.setFamily("Arial");
    musicName->setFont(musicNameFont);

    musicTimer->setAlignment(Qt::AlignCenter);

    musicOptionsLayout->addWidget(tenSecDown);
    musicOptionsLayout->addWidget(playBtn);
    musicOptionsLayout->addWidget(tenSecUp);

    musicInfo->addWidget(musicTimer);
    musicInfo->addWidget(musicPlace);
    musicInfo->setSpacing(0);

    mainLayout->addWidget(musicName);
    mainLayout->addLayout(musicInfo);
    mainLayout->addLayout(musicOptionsLayout);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(100);
    mainLayout->addStretch();

    connect(playBtn, &QPushButton::clicked, this, &MainWindow::playPauseMusic);
    connect(tenSecUp, &QPushButton::clicked, this, &MainWindow::forward10Sec);
    connect(tenSecDown, &QPushButton::clicked, this, &MainWindow::backward10Sec);

    // sf::Music music;
    // if (!music.openFromFile("./t.ogg")) {
    //     qDebug() << "No music found!!";
    // } else {
    //     qDebug() << "music found start playing!!";
    //     music.play();
    // }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playPauseMusic()
{
    // if music is playing
    if (music.getStatus() == sf::Music::Playing) {
        music.pause(); // stop it
        playBtn->setText("Play");
        isPlaying = false;
    }
    // if music is not playing
    else {
        music.play(); // play it
        playBtn->setText("Pause");
        isPlaying = true;
    }
}

void MainWindow::forward10Sec() {}

void MainWindow::backward10Sec() {}
