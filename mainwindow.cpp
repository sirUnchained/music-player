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
    playBtn = new QPushButton("play");
    tenSecUp = new QPushButton("+10");
    tenSecDown = new QPushButton("-10");
    choseSong = new QPushButton("select sound ...");
    musicName = new QLabel("Welcome !!");

    musicName->setAlignment(Qt::AlignCenter);
    musicName->setMargin(50);
    QFont musicNameFont = musicName->font();
    musicNameFont.setPointSize(32);
    musicNameFont.setPixelSize(64);
    musicNameFont.setBold(true);
    musicNameFont.setFamily("Arial");
    musicName->setFont(musicNameFont);

    musicOptionsLayout->addWidget(tenSecDown);
    musicOptionsLayout->addWidget(playBtn);
    musicOptionsLayout->addWidget(tenSecUp);

    mainLayout->addWidget(musicName);
    mainLayout->addLayout(musicOptionsLayout);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(100);
    mainLayout->addStretch();
}

MainWindow::~MainWindow()
{
    delete ui;
}
