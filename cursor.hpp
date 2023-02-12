#ifndef __CURSOR__HEAD_H
#define __CURSOR__HEAD_H

#include "keyHandle.hpp"
#include <iostream>
#include <functional>

using namespace std;

#define MIN_X 1
#define MIN_Y 1
#define MAX_X 57
#define MAX_Y 29
#define X_STEP 4
#define Y_STEP 2

class Cursor
{
public:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    Cursor()
    {
        x = (MAX_X - MIN_X) / 2 + 1;
        y = (MAX_Y - MIN_Y) / 2 + 1;

        show();
    }

    Cursor(int x, int y) : x(x),y(y){}

    int getX(void) const
    {
        return x;
    }

    int getY(void) const
    {
        return y;
    }

    int setX(int x)
    {
        this->x = x;
        return x;
    }

    int setY(int y)
    {
        this->y = y;
        return y;
    }

    void moveUp(void)
    {
        if (y <= MIN_Y)
            return;

        y -= Y_STEP;
    }

    void moveDown(void)
    {
        if (y >= MAX_Y)
            return;

        y += Y_STEP;
    }

    void moveRight(void)
    {
        if (x >= MAX_X)
            return;

        x += X_STEP;
    }

    void moveLeft(void)
    {
        if (x <= MIN_X)
            return;

        x -= X_STEP;
    }

    void move(Direction dir)
    {
        auto handle = function[dir];
        handle();
        show();
    }

    void setPosition(int x,int y)
    {
        this->x = x;
        this->y = y;
    }

    void show(void)
    {
        fprintf(stderr,"\033[%d;%dH",y,x);
    }

private:
    int x;
    int y;
    std::function<void(void)> function[4] ={
            std::bind(&Cursor::moveUp, this),
            std::bind(&Cursor::moveDown, this),
            std::bind(&Cursor::moveLeft, this),
            std::bind(&Cursor::moveRight, this),
    };
};

#endif