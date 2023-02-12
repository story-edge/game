#ifndef __GO__BAN__HEAD_H
#define __GO__BAN__HEAD_H

#include "whilePlayer.hpp"
#include "blackPlayer.hpp"
#include "keyHandle.hpp"
#include "judge.hpp"
#include "winLogo.hpp"

class GoBan
{
public:
    GoBan(const string &blackPlayerName,const string &whilePlayerName)
    {
        players[0] = new WhilePlayer(whilePlayerName);
        players[1] = new BlackPlayer(blackPlayerName);

        ChessBoard *chessBoard = ChessBoard::getChessBoard();
        chessBoard->show();

        keyHandle = new KeyHandle;
    }

    ~GoBan()
    {
        for (int i = 0; i < 2;i++)
        {
            delete players[i];
        }

        delete keyHandle;
    }


    void run(void)
    {
        while (true)
        {
            for (Player *player:players) {
                keyHandle->waitPlayerPlaceChess(player);
                bool ok = judge.isWin(player);
                if (ok) {
                    winLogo.showWinPlayer(player->getName(),player->getColor());
                    goto over;
                }
            }
        }

        over:
        return;
    }

private:
    Player *players[2];
    KeyHandle *keyHandle;
    Judge judge;
    WinLogo winLogo;

};

#endif