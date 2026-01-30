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
    musicTimer = new QLabel("00:00 / 00:00");

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
    mainLayout->addWidget(choseSong);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(100);
    mainLayout->addStretch();

    connect(playBtn, &QPushButton::clicked, this, &MainWindow::playPauseMusic);
    connect(tenSecUp, &QPushButton::clicked, this, &MainWindow::forward10Sec);
    connect(tenSecDown, &QPushButton::clicked, this, &MainWindow::backward10Sec);
    connect(choseSong, &QPushButton::clicked, this, &MainWindow::selectMusic);
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

void MainWindow::forward10Sec()
{
    sf::Time currentTime = music.getPlayingOffset();
    music.setPlayingOffset(currentTime + sf::seconds(10));
    updateMusicInfo();
}

void MainWindow::backward10Sec()
{
    sf::Time currentTime = music.getPlayingOffset();
    sf::Time newTime = currentTime - sf::seconds(10);

    // we don't go before the beginning
    if (newTime.asSeconds() < 0) {
        newTime = sf::seconds(0);
    }

    music.setPlayingOffset(newTime);
    updateMusicInfo();
}

void MainWindow::selectMusic()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Select Music File",
        QDir::homePath(),
        "Audio Files (*.wav *.ogg *.flac *.mp3 *.aiff *.au *.raw *.paf *.svx *.voc *.ircam *.w64)"
        ";;All Files (*.*)");

    if (!fileName.isEmpty()) {
        // stop current music if playing
        if (music.getStatus() == sf::Music::Playing) {
            music.stop();
        }

        // load new file
        if (music.openFromFile(fileName.toStdString())) {
            qDebug() << "Loaded:" << fileName;

            // extract just the filename for display
            QFileInfo fileInfo(fileName);
            musicName->setText(fileInfo.fileName());

            // Reset playback
            isPlaying = false;
            playBtn->setText("Play");
            playBtn->setEnabled(true);
        } else {
            qDebug() << "Failed to load:" << fileName;
            QMessageBox::warning(this,
                                 "Error",
                                 "Failed to load audio file!\nSupported formats: WAV, OGG, FLAC");
            musicName->setText("Failed to load music");
            playBtn->setEnabled(false);
        }
    }
}

void MainWindow::updateMusicInfo()
{
    if (music.getStatus() == sf::Music::Playing) {
        sf::Time current = music.getPlayingOffset();
        sf::Time total = music.getDuration();

        int timePerSec = static_cast<int>(current.asSeconds());
        int musicTime = static_cast<int>(total.asSeconds());

        // Prevent division by zero
        if (musicTime > 0) {
            // using floating-point division for accurate percentage
            float progress = (static_cast<float>(timePerSec) / musicTime) * 100.0f;
            musicPlace->setValue(static_cast<int>(progress));
        } else {
            musicPlace->setValue(0);
        }

        // format as MM:SS
        QString currentTime = QString("%1:%2")
                                  .arg(timePerSec / 60, 2, 10, QChar('0'))
                                  .arg(timePerSec % 60, 2, 10, QChar('0'));

        QString totalTime = QString("%1:%2")
                                .arg(musicTime / 60, 2, 10, QChar('0'))
                                .arg(musicTime % 60, 2, 10, QChar('0'));

        musicTimer->setText(currentTime + " / " + totalTime);
    }
}
