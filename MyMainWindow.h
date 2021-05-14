#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QMenu>
#include <QMenuBar>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QListWidget>
#include <QTimer>

#include "Playlist.h"


class MyMainWindow : public QMainWindow {

public:
    MyMainWindow();

    QWidget* widget;

    QVBoxLayout* mainLayout;
    QVBoxLayout* songInfoLayout;
    QVBoxLayout* playlistLayout;
    QHBoxLayout* topLayout;
    QHBoxLayout* controlLayout;
    QHBoxLayout* controlPlaylistLayout;

    QLabel* songName;
    QLabel* frame;
    QLabel* time;

    QTimer* timer;
    QMediaPlayer* player;
    Playlist* playlist;
    QListWidget* playlistview;
    QStringList* songList;

    QPushButton* play;
    QPushButton* stop;
    QPushButton* skipforward;
    QPushButton* skipback;
    QPushButton* volumebutton;
    QPushButton* volumemute;
    QPushButton* add;
    QPushButton* remove;
    QPushButton* save;

    QSlider* volumeSlider;
    QSlider* durationSlider;

    QMenu* fileMenu;
    QMenu* helpMenu;

    QAction* fileOpen;
    QAction* filesOpen;
    QAction* saveOpen;
    QAction* helpOpen;

    void FileOpen();
    void HelpOpen();
    void keyPressEvent(QKeyEvent *event) override;

    //controls

    void onPlayClicked();
    void onStopClicked();
    void onSkipFClicked();
    void onSkipBClicked();
    void onMuteClicked();
    void callVolumeSlider();
    void changeVolumeOnSlider(int position);
    void changeDurationOnSlider(int position);
    void sliderUpdate();
    void timeUpdate();

    //playlist

    void addToPlaylist();
    void removeFromPlaylist();
    void saveHistory();
    void playFromPlaylist();
    void updatePlaylist();
    void next();
    void back();
    int getSongIndex();
};


#endif // MYMAINWINDOW_H
