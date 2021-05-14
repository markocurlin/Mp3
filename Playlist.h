#ifndef PLAYLIST_H
#define PLAYLIST_H

#include<QStringList>
#include<vector>

#include "Track.h"

using namespace std;

class Playlist {
public:
    Playlist();
    void addToPlaylist(QStringList list);
    void removeFromPlaylist(int index);
    void checkPlaylist();
    QStringList getPlaylist();

    vector<Track> listOfTracks;
};

#endif // PLAYLIST_H
