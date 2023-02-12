#ifndef __WHILE__CHESS__HEAD_H
#define __WHILE__CHESS__HEAD_H

#include "chess.hpp"

class WhileChess : public Chess{

public:
    WhileChess(int x,int y) : Chess("while",x,y){}
    ~WhileChess(){}



    void show(void) const
    {
        fprintf(stderr,"\033[%d;%dH",getY(),getX());//cursor 起始定位
        fprintf(stderr,"\033[47;34m[*]\033[0m");
        fprintf(stderr,"\033[%d;%dH",getY(),getX());
    }

};

#endif