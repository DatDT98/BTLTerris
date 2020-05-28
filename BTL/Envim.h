#ifndef ENVIM_H
#define ENVIM_H
#include "GBlock.h"
#include "Block.h"
#define width 10
#define height 23
class Envim
{
    public:
        Envim();
        int envim[width][height];
        bool gameover = false;
        GBlock obj, next;
        int point = 0;
        void start();
        GBlock newNext();
        void push(Block b, int _number);
        void push(GBlock _next);
        void right();
        void left();
        void up();
        void down();
        void delRow();
        void merge(int position);
        void pop(Block _b);
        void pop(GBlock _Gb);
        bool limit(Block _b);
        bool limit(GBlock _Gb);
        void move(GBlock _Gb);
    protected:

    private:
};

#endif // ENVIM_H
