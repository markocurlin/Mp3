#ifndef TRACK_H
#define TRACK_H

#include<string>

using namespace std;

class Track {
public:
    Track();
    string getName();
    string getLocation();
    void setName(string name);
    void setLocation(string location);
protected:
    string name;
    string location;
};

string getName(string name);

#endif // TRACK_H
