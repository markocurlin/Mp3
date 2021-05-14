#include "Track.h"

Track::Track() {
    name = "";
    location = "";
}

string Track::getName() {
    return name;
}

string Track::getLocation() {
    return location;
}

void Track::setName(string name) {
    this->name = name;
}

void Track::setLocation(string location) {
    this->location = location;
}

string getName(string name) {
    string temp = " ";
    string::reverse_iterator pos;

    for(pos = name.rbegin(); *pos != '/'; pos++) {
        temp.push_back(*pos);
    }

    name.clear();

    for(pos = temp.rbegin(); *pos != '.'; pos++) {
        name.push_back(*pos);
    }

    return name;
}
