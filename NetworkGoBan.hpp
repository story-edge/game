#ifndef __NETWORK__GOBAN__HEAD_H
#define __NETWORK__GOBAN__HEAD_H

#include "networkPlayer.hpp"
#include "judge.hpp"
#include "keyHandle.hpp"
#include "winLogo.hpp"
#include "blackPlayer.hpp"
#include "whilePlayer.hpp"


class NetworkGoBan
{
public:
    void inputInfo(void)
    {
        cout << "Input chess color:" << endl;
        cin >> selfColor;

        cout << "Input self port:" << endl;
        cin >> selfPort;

        cout << "Input peer port:" << endl;
        cin >> peerIp;

        cout << "Input peer port:" << endl;
        cin >> peerPort;
        return;
    }

    NetworkGoBan(const string &whilePlayerName,const string &blackPlayerName)
    {
        inputInfo();

        ChessBoard *chessBoard = ChessBoard::getChessBoard();
        chessBoard->show();

        keyHandle = new KeyHandle;

        if (selfColor == "while")
        {
            whilePlayer = new NetworkPlayer(whilePlayerName,
                                            "while",keyHandle,
                                            peerIp,peerPort,
                                            true);

            blackPlayer = new NetworkPlayer(blackPlayerName,
                                            "black",keyHandle,
                                            peerIp,peerPort,
                                            false);

        } else
        {
            whilePlayer = new NetworkPlayer(whilePlayerName,
                                            "while",keyHandle,
                                            peerIp,peerPort,
                                            false);

            blackPlayer = new NetworkPlayer(blackPlayerName,
                                            "black",keyHandle,
                                            peerIp,peerPort,
                                            true);
        }
    }

    ~NetworkGoBan()
    {
        delete keyHandle;
        delete blackPlayer;
        delete whilePlayer;
    }

    void run(void)
    {
        NetworkPlayer *players[] = {whilePlayer,blackPlayer};
        while (true)
        {
            for (NetworkPlayer *player:players) {
                player->waitPlaceChess();
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
    string peerIp;
    string peerPort;
    string selfIp;
    string selfPort;
    string selfColor;

    KeyHandle *keyHandle;
    NetworkPlayer *whilePlayer;
    NetworkPlayer *blackPlayer;
    Judge judge;
    WinLogo winLogo;
};

#endif