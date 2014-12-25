#include <iostream>
#include <cmath>
#include <random>
#include <complex>
#include <typeinfo>

#include "gif.hpp"

using namespace std;

const int size = 512;

class Pixel
{
public:
    void red(uint8_t color)
    {
        px &= 0xFFFFFF00;
        px |= static_cast<uint32_t>(color);
    }
    void green(uint8_t color)
    {
        px &= 0xFFFF00FF;
        px |= static_cast<uint32_t>(color) << 8;
    }
    void blue(uint8_t color)
    {
        px &= 0xFF00FFFF;
        px |= static_cast<uint32_t>(color) << 16;
    }
    Pixel& operator=(uint32_t color)
    {
        px=color;
        return *this;
    }
private:
    uint32_t px {0};
};


class Frame
{
    using FrameRow = Pixel(&)[size];
public:
    FrameRow operator[](int idx)
    {
        return arr[idx];
    }
    operator void*()
    {
        return arr;
    }
private:
    Pixel arr[size][size];
};

class Shape
{
    int x1,y1, x2,y2;
public:
    Shape(int xx1,int yy1,int xx2,int yy2)
    {
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
    }
    void paint(Frame &f){
        for(int y=y1; y<=y2; y++) // по строчкам
            for(int x=x1; x<=x2; x++) // по столбцам
            {
                double w = x2-x1;
                double h = y2-y1;
                if( (x-x1)/w + (y-y1)/h < 1.0 )
                    f[y][x].green(40);

            }

    }
};


int main()
{
    // Массив пикселей
    Frame frame;
    for(int i=0; i<size; i++) // по строчкам
        for(int j=0; j<size; j++) // по столбцам
            frame[i][j].blue(1);

    // создание объекта (gif-файла) с заданным именем и размерами
    GifWriter gw("checking.gif",size,size,250);

    Shape t(20,20, 100, 100);
    t.paint(frame);

    Shape k(40,40, 160, 160);
    k.paint(frame);

    Shape r(80,80, 220, 220);
    r.paint(frame);

    Shape e(120,120, 280, 280);
    e.paint(frame);

    Shape p(160,160, 340, 340);
    p.paint(frame);

    Shape n(200,200, 380, 380);
    n.paint(frame);

    for(int i=70; i<90; i++)
        for(int j=60; j<80; j++)
            frame[i][j].red(250);

    for(int i=90; i<110; i++)
        for(int j=150; j<170; j++)
            frame[j][i].blue(250);

    for(int i=200; i<210; i++)
        for(int j=200; j<210; j++)
            frame[j][i].blue(100), frame[j][i].red(100);

    for(int i=200; i<210; i++)
        for(int j=200; j<210; j++)
            frame[j][i].blue(40), frame[j][i].red(250);


     for(int i=280; i<290; i++)
        for(int j=190; j<200; j++)
            frame[j][i].blue(200),frame[j][i].blue(100);


      for(int i= 180; i<200; i++)
        for(int j=150; j<170; j++)
            frame[j][i].blue(200),frame[j][i].red(100);


            for(int i= 150; i<160; i++)
        for(int j=120; j<130; j++)
            frame[j][i].blue(200),frame[j][i].blue(100);

             for(int i= 120; i<130; i++)
        for(int j=120; j<130; j++)
            frame[j][i].blue(200),frame[j][i].red(250);

            for(int i= 190; i<200; i++)
        for(int j=130; j<140; j++)
            frame[j][i].blue(200),frame[j][i].blue(250);

            for(int i=200; i<220; i++)
        for(int j=280; j<300; j++)
            frame[j][i]=250;
/*
    for(int i=237; i<300; i++) // по строчкам
        for(int j=237; j<300; j++) // по столбцам
            frame[i][j].red(255), frame[i][j].blue(255);
*/

    gw.write(frame);

    return 0;
}
