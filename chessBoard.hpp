#ifndef __CHESS__BOARD__HEAD_H
#define __CHESS__BOARD__HEAD_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "chess.hpp"

#define MIN_X 1
#define MIN_Y 1
#define MAX_X 57
#define MAX_Y 29

#define MAX_LINE 15
#define MAX_COLUMN 15
#define X_STEP 4
#define Y_STEP 2

#define BUF_SZ 1024

class ChessBoard{

public:
    ~ChessBoard()
    {
        //结束时光标的位置
        fprintf(stderr,"\033[%d;%dH",MAX_Y + 1,MIN_X);

        for (int i = 0; i < MAX_LINE; ++i)
        {
            for (int j = 0; j < MAX_COLUMN; ++j)
            {
                if (this->chess[i][j])
                {
                    this->chess[i][j] = nullptr;
                }
            }
        }
    }

    static ChessBoard *getChessBoard(void)
    {
        if (!chessBoard) {
            pthread_mutex_lock(&lock);//赖汉式的并发处理
            if (!chessBoard) {
                chessBoard = new ChessBoard;
            }
            pthread_mutex_unlock(&lock);
        }
            return chessBoard;

    }


    void show(void) const
    {

        FILE *fp;

        char buf[BUF_SZ] = {0};

        fp = fopen("./ChessBoard.txt","r");
        if (fp == nullptr)
        {
            perror("[ERROR] Fail to fopen ChessBoard.txt");
            return;
        }

        fprintf(stderr,"\033[%d:%dH",MIN_Y,MIN_X);

        while (fgets(buf,sizeof(buf),fp))
        {
            fprintf(stderr,"%s",buf);
        }

        fclose(fp);
    }

    //落棋 --棋盘下棋边界判定
    bool isValidPosition(int x,int y)
    {
        if (x < MIN_X || y < MIN_Y){
            return false;
        }

        if (x > MAX_X || y > MAX_Y){
            return false;
        }

        int line   = y / Y_STEP;
        int column = x / X_STEP;

        return chess[line][column] ? false : true;
    }

    //落棋
    void placeCHess(const Chess *chess) {
        int line   = chess->getY() / Y_STEP;
        int column = chess->getX() / X_STEP;

        this->chess[line][column] = chess;

        currentColumn = column;
        currentLine   = line;

        chess->show();

        return;
    }

    int getCurrentLine(void) const
    {
        return currentLine;
    }

    int getCurrentColumn(void) const
    {
        return currentColumn;
    }



    bool isSameColorChess(const string &color,int line,int column)
    {
        if (line < 0 || line >= MAX_LINE) {
            return false;
        }

        if (column < 0 || column >= MAX_COLUMN){
            return false;
        }

        auto chess = this->chess[line][column];

        if (!chess  || chess->getColor() != color) {
            return false;
        } else{
            return true;
        }

    }

    //使用内部类的方式来时释放资源--->static 修饰后函数结束时调用   第二种方法是提供一个静态成员函数
    class GC
    {
    public:
        ~GC()
        {
            if (chessBoard)
            {
                delete chessBoard;
            }
        }
    };


private:
    ChessBoard()
    {
        for (int i = 0; i < MAX_LINE; ++i) {
            for (int j = 0; j < MAX_COLUMN; ++j) {
                this->chess[i][j] = nullptr;
             }
        }
    }
    static ChessBoard *chessBoard;//使用单列模式保证棋盘的唯一
    static pthread_mutex_t lock;
    static GC gc;
    const Chess *chess[MAX_LINE][MAX_COLUMN];
    int currentLine;
    int currentColumn;
};

ChessBoard *ChessBoard::chessBoard = nullptr;
pthread_mutex_t ChessBoard::lock = PTHREAD_MUTEX_INITIALIZER;
ChessBoard::GC gc;

#endif
