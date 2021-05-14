#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QAction>
#include <QStyle>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QStringList>
#include <QBoxLayout>
#include "MyMainWindow.h"
#include "Track.h"
#include "HelpDialog.h"

MyMainWindow::MyMainWindow() {

    widget = new QWidget;
    setCentralWidget(widget);

    //player & playlist

    player = new QMediaPlayer(this);
    player->setVolume(50);
    playlist = new Playlist;
    playlistview = new QListWidget(this);
    songList = new QStringList;

    connect(playlistview, &QListWidget::itemPressed, this, &MyMainWindow::playFromPlaylist);
    connect(playlistview, &QListWidget::itemPressed, this, &MyMainWindow::getSongIndex);

    //labels

    songName = new QLabel(this);
    songName->setText(tr("No track"));
    songName->setStyleSheet("Font : 12pt");
    songName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    time = new QLabel(this);
    frame = new QLabel(this);
    QPixmap slika("/Users/Marko/Music/slika.png");
    frame->setPixmap(slika.scaled(300, 300, Qt::KeepAspectRatio));
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

    //controls

    play = new QPushButton(this);
    stop = new QPushButton(this);
    skipforward = new QPushButton(this);
    skipback = new QPushButton(this);
    volumebutton = new QPushButton(this);
    volumemute = new QPushButton(this);
    add = new QPushButton(this);
    remove = new QPushButton(this);
    save = new QPushButton(this);

    play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    skipforward->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    skipback->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    volumemute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    volumebutton->setIcon(style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));
    add->setText(tr("Add"));
    remove->setText(tr("Remove"));
    save->setText(tr("Save"));

    connect(play, &QPushButton::clicked, this, &MyMainWindow::onPlayClicked);
    connect(stop, &QPushButton::clicked, this, &MyMainWindow::onStopClicked);
    connect(skipforward, &QPushButton::clicked, this, &MyMainWindow::onSkipFClicked);
    connect(skipback, &QPushButton::clicked, this, &MyMainWindow::onSkipBClicked);
    connect(volumemute, &QPushButton::clicked, this, &MyMainWindow::onMuteClicked);
    connect(volumebutton, &QPushButton::clicked, this, &MyMainWindow::callVolumeSlider);
    connect(add, &QPushButton::clicked, this, &MyMainWindow::addToPlaylist);
    connect(remove, &QPushButton::clicked, this, &MyMainWindow::removeFromPlaylist);
    connect(save, &QPushButton::clicked, this, &MyMainWindow::saveHistory);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setVisible(false);
    connect(volumeSlider, &QSlider::valueChanged, this, &MyMainWindow::changeVolumeOnSlider);
    durationSlider = new QSlider(Qt::Horizontal, this);
    durationSlider->setRange(0, 1000);
    durationSlider->setValue(0);
    connect(durationSlider, &QSlider::sliderMoved, this, &MyMainWindow::changeDurationOnSlider);
    connect(player, &QMediaPlayer::positionChanged, this, &MyMainWindow::sliderUpdate);

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &MyMainWindow::timeUpdate);

    //layout

    mainLayout = new QVBoxLayout(this);
    controlLayout = new QHBoxLayout(this);
    songInfoLayout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout(this);
    playlistLayout = new QVBoxLayout(this);
    controlPlaylistLayout = new QHBoxLayout(this);

    controlLayout->addWidget(durationSlider);
    controlLayout->addWidget(time);
    controlLayout->addWidget(skipback);
    controlLayout->addWidget(play);
    controlLayout->addWidget(stop);
    controlLayout->addWidget(skipforward);
    controlLayout->addWidget(volumemute);
    controlLayout->addWidget(volumebutton);
    controlLayout->addWidget(volumeSlider);
    playlistLayout->addWidget(playlistview);
    playlistLayout->addLayout(controlPlaylistLayout);
    controlPlaylistLayout->addWidget(add);
    controlPlaylistLayout->addWidget(remove);
    controlPlaylistLayout->addWidget(save);
    songInfoLayout->addWidget(frame);
    songInfoLayout->addWidget(songName);
    songInfoLayout->setAlignment(frame, Qt::AlignHCenter);
    songInfoLayout->setAlignment(songName, Qt::AlignHCenter);
    topLayout->addLayout(songInfoLayout);
    topLayout->addLayout(playlistLayout);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(controlLayout);
    mainLayout->setMargin(40);
    widget->setLayout(mainLayout);

    setWindowTitle(tr("Music player"));
    setMinimumSize(500, 300);

    //menu

    fileOpen = new QAction(tr("&Open file..."), this);
    fileOpen->setShortcut(tr("CTRL+O"));
    filesOpen = new QAction(tr("&Open files..."), this);
    filesOpen->setShortcut(tr("CTRL+P"));
    saveOpen = new QAction(tr("&Save history..."), this);
    saveOpen->setShortcut(tr("CTRL+S"));
    helpOpen = new QAction(tr("&Controls..."), this);
    helpOpen->setShortcut(tr("CTRL+H"));

    connect(fileOpen, &QAction::triggered, this, &MyMainWindow::FileOpen);
    connect(filesOpen, &QAction::triggered, this, &MyMainWindow::addToPlaylist);
    connect(helpOpen, &QAction::triggered, this, &MyMainWindow::HelpOpen);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(fileOpen);
    fileMenu->addAction(filesOpen);
    fileMenu->addAction(saveOpen);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpOpen);
}

void MyMainWindow::FileOpen() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", "MP3 File (*.mp3)");

    if (!fileName.isEmpty()) {
        player->setMedia(QUrl::fromLocalFile(fileName));
        string temp;
        temp = getName(fileName.toStdString());
        fileName = QString::fromStdString(temp);
        songName->setText(fileName);
        songList->push_back(fileName);
    }
}

void MyMainWindow::HelpOpen() {
    HelpDialog helpDialog;
    helpDialog.setMinimumSize(200, 200);
    helpDialog.setMaximumSize(300, 300);
    helpDialog.resize(300, 300);
    helpDialog.exec();
}

void MyMainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()){
    case Qt::Key_Space: onPlayClicked();
        break;
    case Qt::Key_Enter: onStopClicked();
        break;
    case Qt::Key_M: onMuteClicked();
        break;
    case Qt::Key_Right: onSkipFClicked();
        break;
    case Qt::Key_Left: onSkipBClicked();
        break;
    }
}

//controls

void MyMainWindow::onPlayClicked() {
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else {
        player->play();
        play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MyMainWindow::onStopClicked() {
    player->stop();
    play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void MyMainWindow::onSkipFClicked() {
    if (!playlist->listOfTracks.empty()) {
        next();
        int index = getSongIndex();
        QString temp = QString::fromStdString(playlist->listOfTracks[index].getLocation());
        player->setMedia(QUrl::fromLocalFile(temp));
        songName->setText(QString::fromStdString(playlist->listOfTracks[index].getName()));
        songList->push_back(QString::fromStdString(playlist->listOfTracks[index].getName()));
        player->play();
    }
}

void MyMainWindow::onSkipBClicked() {
    if (!playlist->listOfTracks.empty()) {
        back();
        int index = getSongIndex();
        QString temp = QString::fromStdString(playlist->listOfTracks[index].getLocation());
        player->setMedia(QUrl::fromLocalFile(temp));
        songName->setText(QString::fromStdString(playlist->listOfTracks[index].getName()));
        songList->push_back(QString::fromStdString(playlist->listOfTracks[index].getName()));
        player->play();
    }
}

void MyMainWindow::onMuteClicked() {
    if (player->isMuted()) {
        player->setMuted(false);
        volumemute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        volumeSlider->setValue(50);
    }
    else {
        player->setMuted(true);
        volumemute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        volumeSlider->setValue(0);
    }
}

void MyMainWindow::callVolumeSlider() {
    if (!volumeSlider->isVisible())
        volumeSlider->setVisible(true);
    else
        volumeSlider->setVisible(false);
}

void MyMainWindow::changeVolumeOnSlider(int value) {
    player->setVolume(value);
    if (value == 0)
        volumemute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    else
        volumemute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
}

void MyMainWindow::changeDurationOnSlider(int position) {
    player->setPosition(player->duration() / 1000 * position);
}

void MyMainWindow::sliderUpdate() {
    if (!durationSlider->isSliderDown())
        durationSlider->setValue((double)player->position() / player->duration() * 1000);
}

void MyMainWindow::timeUpdate() {
    int seconds = ( player->position() / 1000 ) % 60;
    int minutes = ( player->position() / 1000 ) / 60;
    int dseconds = ( player->duration() / 1000 ) % 60;
    int dminutes = ( player->duration() / 1000 ) / 60;

    QString time1 = QString::number(minutes) + ':' + QString::number(seconds) + " / " + QString::number(dminutes) + ':' + QString::number(dseconds) ;
    time->setText(time1);
}

//playlist

void MyMainWindow::addToPlaylist() {
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select files"), "", "MP3 File (*.mp3)");
    playlistview->clear();
    playlist->addToPlaylist(files);
    playlist->checkPlaylist();
    playlistview->addItems(playlist->getPlaylist());
    playlistview->sortItems(Qt::SortOrder(Qt::AscendingOrder));
}

void MyMainWindow::removeFromPlaylist() {
    if (!playlist->listOfTracks.empty()) {
        int index = getSongIndex();
        playlist->removeFromPlaylist(index);
        player->setMedia(QUrl::fromLocalFile(""));
        songName->setText(tr("No track"));
        updatePlaylist();
    }
}

void MyMainWindow::saveHistory() {
    QString fileName = "History.txt";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        for(int i = 0; i < songList->size(); i++)
            stream << songList->operator[](i) << Qt::endl;
    }
}

void MyMainWindow::playFromPlaylist() {
    int index = getSongIndex();
    QString temp = QString::fromStdString(playlist->listOfTracks[index].getLocation());
    player->setMedia(QUrl::fromLocalFile(temp));
    songName->setText(QString::fromStdString(playlist->listOfTracks[index].getName()));
    player->play();
    play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    songList->push_back(QString::fromStdString(playlist->listOfTracks[index].getName()));
}

void MyMainWindow::updatePlaylist() {
    playlistview->clear();
    playlistview->addItems(playlist->getPlaylist());
}

void MyMainWindow::next() {
    int index = getSongIndex();
    if ((unsigned long long)index == playlist->listOfTracks.size() - 1)
        index = 0;
    else
        index++;
    playlistview->setCurrentRow(index);
}

void MyMainWindow::back() {
    int index = getSongIndex();
    if (index == 0)
        index = playlist->listOfTracks.size() - 1;
    else
        index--;
    playlistview->setCurrentRow(index);
}

int MyMainWindow::getSongIndex() {
    return playlistview->currentIndex().row();
}
