#ifndef __KEY__HANDLE__HEAD_H
#define __KEY__HANDLE__HEAD_H

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "cursor.hpp"
#include <map>
#include "player.hpp"
#include <functional>

#define PLACE_CHESS_KEY ' '

using namespace std;

class KeyHandle{

public:
    KeyHandle(){

        struct termios attr;

        tcgetattr(0,&attr);
        attr.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(0,TCSANOW,&attr);

        auto handleUp = std::bind(&Cursor::move,&cursor,Cursor::UP);
        keyMap.insert(pair<char,function<void(void)>>('w',handleUp));
        keyMap.insert(pair<char,function<void(void)>>('W',handleUp));

        auto handleDown = std::bind(&Cursor::move,&cursor,Cursor::DOWN);
        keyMap.insert(pair<char,function<void(void)>>('s',handleDown));
        keyMap.insert(pair<char,function<void(void)>>('S',handleDown));

        auto handleLeft = std::bind(&Cursor::move,&cursor,Cursor::LEFT);
        keyMap.insert(pair<char,function<void(void)>>('a',handleLeft));
        keyMap.insert(pair<char,function<void(void)>>('A',handleLeft));

        auto handleRight = std::bind(&Cursor::move,&cursor,Cursor::RIGHT);
        keyMap.insert(pair<char,function<void(void)>>('d',handleRight));
        keyMap.insert(pair<char,function<void(void)>>('D',handleRight));

    }

    ~KeyHandle(){

        struct termios attr;

        tcgetattr(0,&attr);
        attr.c_lflag |= (ECHO | ICANON);
        tcsetattr(0,TCSANOW,&attr);
    }

    void  waitPlayerPlaceChess(Player *player){
        bool ok = false;
        do{
            tcflush(0,TCIFLUSH);
            int ch = getchar();
            if(ch == PLACE_CHESS_KEY){
                ok = player->placeChess(cursor.getX(),cursor.getY());
            }else{
                auto it = keyMap.find(ch);
                if(it != keyMap.end()){
                    auto handle = it->second;
                    handle();
                }

            }
        }while(!ok);

        return;
    }

    int getCursorX(void) const
    {
        return cursor.getX();
    }

    int getCursorY(void) const
    {
        return cursor.getY();
    }

    void setCursorPosition(int x,int y)
    {
        cursor.setPosition(x,y);
    }

private:
    Cursor cursor;
    map<char,function<void(void)>> keyMap;
};

#endif