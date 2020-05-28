#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <string>
using namespace std;
class Block
{
    public:
        Block();
        Block(int _x, int _y);
        int x,y;
        void move(int _x, int _y);
        void rotate(Block b);
};

#endif // BLOCK_H
