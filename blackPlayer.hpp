#ifndef __BLACK__PLAYER__HEAD_H
#define __BLACK__PLAYER__HEAD_H

#include "player.hpp"
#include "chessBoard.hpp"
#include "blackChess.hpp"

class BlackPlayer : public Player
{
public:
    BlackPlayer(const string &name) : Player(name,"black"){}

    bool placeChess(int x,int y) {
        ChessBoard *chessBoard = ChessBoard::getChessBoard();

        bool ok = chessBoard->isValidPosition(x, y);
        if (ok) {
            chessBoard->placeCHess(new BlackChess(x, y));
        }
        return ok;
    }
};

#endif