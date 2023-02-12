#ifndef __CHESS__HEAD_H
#define __CHESS__HEAD_H

#include <iostream>

using namespace std;

class Chess{
public:


    Chess(const string &color,int x,int y):color(color),x(x),y(y){}

    int getX(void) const
    {
        return x;
    }

    int getY(void) const
    {
        return y;
    }

    string getColor(void) const
    {
        return color;
    }

    //作为基类的纯虚函数其实现方法由其派生系实现
    virtual void show(void) const = 0;

    //虚析构和纯虚析构是用来解决基类指针释放派生系的对象
    virtual ~Chess() {}

private:
    string color;
    int x;
    int y;
};

#endif