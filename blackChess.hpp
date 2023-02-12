#ifndef __BLACK__CHESS_HEAD_H
#define __BLACK__CHESS_HEAD_H

#include <stdio.h>
#include "chess.hpp"

class BlackChess : public Chess{

public:
    BlackChess(int x,int y) : Chess("black",x,y){}
    ~BlackChess(){}

    void show(void) const
    {
        fprintf(stderr,"\033[%d;%dH",getY(),getX());
        fprintf(stderr,"\033[43;34m[*]\033[0m");
        fprintf(stderr,"\033[%d;%dH",getY(),getX());
    }

};

#endif