#ifndef __WHILE__PLAYER__HEAD_H
#define __WHILE__PLAYER__HEAD_H

#include "player.hpp"
#include "chessBoard.hpp"
#include "whileChess.hpp"

class WhilePlayer : public Player
        {
public:
    WhilePlayer(const string &name) : Player(name,"while"){}

    bool placeChess(int x,int y)
    {
        ChessBoard *chessBoard = ChessBoard::getChessBoard();

        bool ok = chessBoard->isValidPosition(x,y);
        if (ok)
        {
            chessBoard->placeCHess(new WhileChess(x,y));
        }
        return ok;
    }
};

#endif