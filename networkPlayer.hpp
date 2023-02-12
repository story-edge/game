#ifndef __NETWORK__PLAYER__HEAD_H
#define __NETWORK__pLAYER__HEAD_H

#include <stdio.h>
#include  "player.hpp"
#include "keyHandle.hpp"
#include "blackChess.hpp"
#include "whileChess.hpp"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Point
{
public:
    Point(){}
    Point(int x,int y):x(x),y(y){}
    int getX(void) const
    {
        return x;
    }

    int getY(void) const
    {
        return y;
    }

private:
    int x;
    int y;
};

class NetworkPlayer : public Player
{
public:
    NetworkPlayer(const string &name,
                  const string &color,
                  KeyHandle *keyHandle,
                  const string &ip,
                  const string &port,
                  bool localUser = false
                  ):
                  Player(name,color),
                  keyHandle(keyHandle),
                  localUser(localUser)
                  {
                        sfd = socket(AF_INET,SOCK_DGRAM,0);
                        if (sfd < 0)
                        {
                            perror("[ERROR] Fail to socket");
                            return;
                        }

                        if (localUser)
                        {
                            this->peerIp   = ip;
                            this->peerPort = port;
                        } else
                        {
                            struct sockaddr_in peerAddr;
                            peerAddr.sin_family = AF_INET;
                            peerAddr.sin_port   = htons(atoi(port.c_str()));
                            peerAddr.sin_addr.s_addr = inet_addr(ip.c_str());

                            int ret = bind(sfd,(struct sockaddr *)&peerAddr,sizeof(peerAddr));
                            if (ret < 0)
                            {
                                perror("[ERROR] Fail to bind");
                                return;
                            }
                        }
                  }

                  bool recvPointFromPeer(Point &point)
                  {
                        int ret = recvfrom(sfd,(void *)&point,sizeof(point),0,NULL,NULL);
                        if (ret <= 0)
                        {
                            perror("[ERROR] Fail to recvfrom");
                            return false;
                        }

                      return true;
                  };

                  bool transferToPeer(const Point &point,const string &ip,const string &port)
                  {
                      struct sockaddr_in peerAddr;
                      peerAddr.sin_family = AF_INET;
                      peerAddr.sin_port   = htons(atoi(port.c_str()));
                      peerAddr.sin_addr.s_addr = inet_addr(ip.c_str());

                      int ret = sendto(sfd,(void *)&point,sizeof(point),0,(struct sockaddr *)&peerAddr,sizeof(peerAddr));
                      if (ret < 0)
                      {
                          perror("[ERROR] Fail to sendto");
                          return false;
                      }

                      return true;
                  }

                  bool placeChess(int x,int y)
                  {
                      ChessBoard *chessBoard = ChessBoard::getChessBoard();
                      bool ok = chessBoard->isValidPosition(x,y);

                      if (ok)
                      {
                          Chess *chess = nullptr;
                          string color = getColor();
                          if (color == "black")
                          {
                              new BlackChess(x,y);
                          } else
                          {
                              new WhileChess(x,y);
                          }
                      }

                      return ok;
                  }

                  void waitPlaceChess(void)
                  {
                      if (!localUser)
                      {
                          Point point;
                          bool ok = recvPointFromPeer(point);
                          if (ok)
                          {
                              keyHandle->setCursorPosition(point.getX(),point.getY());
                              this->placeChess(point.getX(),point.getY());
                          } else
                          {
                              keyHandle->waitPlayerPlaceChess(this);
                              Point point(keyHandle->getCursorX(),keyHandle->getCursorY());
                              this->transferToPeer(point,peerIp,peerPort);
                          }
                      }
                  }

    ~NetworkPlayer()
    {
        close(sfd);
    }



private:
    int sfd;
    int localUser;
    string peerIp;
    string peerPort;
    KeyHandle *keyHandle;

};

#endif