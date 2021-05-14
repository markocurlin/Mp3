#include "Playlist.h"
#include <fstream>

Playlist::Playlist()
{
    std::ifstream read("playlist");
    string location;
    while(getline(read, location)){
        Track track;
        track.setLocation(location);
        track.setName(getName(location));
        listOfTracks.push_back(track);
    }
}

void Playlist::addToPlaylist(QStringList list) {
    for(int i = 0; i < list.size(); i++) {
        Track track;
        track.setLocation(list[i].toStdString());
        track.setName(getName(list[i].toStdString()));
        listOfTracks.push_back(track);
    }
}

void Playlist::removeFromPlaylist(int index) {
    listOfTracks.erase(listOfTracks.begin() + index);
}


void Playlist::checkPlaylist() {
    for(unsigned int i = 0; i < listOfTracks.size(); i++){
        for(unsigned int j = i + 1; j < listOfTracks.size(); j++){
            if (listOfTracks[i].getName() == listOfTracks[j].getName())
                listOfTracks.erase(listOfTracks.begin() + j);
        }
    }
}

QStringList Playlist::getPlaylist()
{
    QStringList playlist;

    for(unsigned int i = 0; i < listOfTracks.size(); i++) {
        QString track = QString::fromStdString(listOfTracks[i].getName());
        playlist.push_back(track);
    }

    return playlist;
}
