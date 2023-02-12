#ifndef __JUDGE__HEAD_H
#define __JUDGE__HEAD_H

#include "player.hpp"
#include "chessBoard.hpp"

class Judge
{
public:
    bool isWin(Player *player)
    {
        bool ok;

        ok = isHorizontalWin(player->getColor());
        if (ok){
            return true;
        }

        ok = isVerticalWin(player->getColor());
        if (ok){
            return true;
        }

        ok = isUpHillWin(player->getColor());
        if (ok){
            return true;
        }

        ok = isDownHillWin(player->getColor());
        if (ok){
            return true;
        }

        return false;
    }

    bool isHorizontalWin(const string &chessColor)
    {
        int count = 0;
        ChessBoard *chessBoard = ChessBoard::getChessBoard();

        int curLine   = chessBoard->getCurrentLine();
        int curColumn = chessBoard->getCurrentColumn();

        //right
        for (int i = 0;i < 5 ;i++)
        {
            if (chessBoard->isSameColorChess(chessColor,curLine,curColumn + i)){
                count++;
            } else {
                break;
            }

        }

        if (count >= 5)
        {
            return true;
        }

        //left
        for (int i = 0;i < 5;i++)
        {
            if (chessBoard->isSameColorChess(chessColor, curLine, curColumn - i)) {
                count++;
            } else {
                break;
            }
        }

        return count - 1 >= 5 ? true : false;

    }

    bool isVerticalWin(const string &chessColor)
    {
        int count = 0;
        ChessBoard *chessBoard = ChessBoard::getChessBoard();

        int curLine   = chessBoard->getCurrentLine();
        int curColumn = chessBoard->getCurrentColumn();

        //up
        for (int i = 0;i < 5 ;i++)
        {
            if (chessBoard->isSameColorChess(chessColor,curLine - i,curColumn)){
                count++;
            } else {
                break;
            }

        }

        if (count >= 5)
        {
            return true;
        }

        //down
        for (int i = 0;i < 5;i++)
        {
            if (chessBoard->isSameColorChess(chessColor, curLine + i, curColumn )) {
                count++;
            } else {
                break;
            }
        }

        return count - 1 >= 5 ? true : false;

    }

    bool isUpHillWin(const string &chessColor)
    {
        int count = 0;
        ChessBoard *chessBoard = ChessBoard::getChessBoard();

        int curLine   = chessBoard->getCurrentLine();
        int curColumn = chessBoard->getCurrentColumn();


        for (int i = 0;i < 5 ;i++)
        {
            if (chessBoard->isSameColorChess(chessColor,curLine + i,curColumn - i)){
                count++;
            } else {
                break;
            }

        }

        if (count >= 5)
        {
            return true;
        }


        for (int i = 0;i < 5;i++)
        {
            if (chessBoard->isSameColorChess(chessColor, curLine - i, curColumn + i)) {
                count++;
            } else {
                break;
            }
        }

        return count - 1 >= 5 ? true : false;

    }

    bool isDownHillWin(const string &chessColor)
    {
        int count = 0;
        ChessBoard *chessBoard = ChessBoard::getChessBoard();

        int curLine   = chessBoard->getCurrentLine();
        int curColumn = chessBoard->getCurrentColumn();

        for (int i = 0;i < 5 ;i++)
        {
            if (chessBoard->isSameColorChess(chessColor,curLine - i,curColumn - i)){
                count++;
            } else {
                break;
            }

        }

        if (count >= 5)
        {
            return true;
        }


        for (int i = 0;i < 5;i++)
        {
            if (chessBoard->isSameColorChess(chessColor, curLine + i, curColumn + i)) {
                count++;
            } else {
                break;
            }
        }

        return count - 1 >= 5 ? true : false;

    }
};

#endif