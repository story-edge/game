#ifndef __WIN__LOGO__HEAD_H
#define __WIN__LOGO__HEAD_H

#include <stdio.h>
#include <iostream>

#define CHESSBOARD_WIDTH 57
#define CHESSBOARD_HEIGHT 29
#define X_OFFSET 3

using namespace std;

class WinLogo
{
public:
    WinLogo(int x = 0,int y = 0,int width = 25,int height = 15)
    {
        this->width  = width;
        this->height = height;

        if (!x)
        {
            this->x = CHESSBOARD_WIDTH + X_OFFSET;
        } else{
            this->x = x;
        }

        if (!y)
        {
            this->y = (CHESSBOARD_HEIGHT - height) / 2;
        } else{
            this->y = y;
        }
    }

    void drawRectangle(int x,int y,int width,int height,int color)
    {
        fprintf(stderr,"\033[%d;%dH",y,x);

        for (int i = 0;i < height;i++)
        {
            for (int j = 0;j < width;j++)
            {
                fprintf(stderr,"\033[%dm \033[0m",color);
            }

            fprintf(stderr,"\033[%d;%dH",y + i,x);
        }
    }

    void drawTest(int x,int y,const char *test,int background,int fontColor)
    {
        fprintf(stderr,"\033[%d;%dH\033[%d;%dm%s\033[0m",y,x,background,fontColor,test);
    }

    void showWinPlayer(const string &name,const string &color)
    {
        drawRectangle(x,y,width + 2,height,42);
        drawRectangle(x + 2,y + 1,width + 2,height,47);

        string test1 = "This colors is :";
        test1 += color;
        drawTest(x + 3,y + 1 + height / 2 - 2,test1.c_str(),47,33);

        string test2 = "The winner is :";
        test2 += name;
        drawTest(x + 3,y + 2 + height / 2 - 2,test2.c_str(),47,33);

        drawTest(x + 3,y + 3 + height / 2 - 2,"The deveoper is :",47,34);
        drawTest(x + 3 + 3,y + 4 + height / 2 - 2,"Mir Luo.",47,35);


    }

private:
    int x;
    int y;
    int width;
    int height;
};
#endif