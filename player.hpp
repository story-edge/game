#ifndef __PLAYER__HEAD_H
#define __PLAYER__HEAD_H

#include <iostream>

using namespace std;

class Player
{
public:
    Player(const string &name,const string &color) : name(name),color(color){}

    string getName(void) const
    {
        return name;
    }

    string getColor(void) const
    {
        return color;
    }

    virtual bool placeChess(int x,int y) = 0;


private:
    string name;
    string color;
};

#endif