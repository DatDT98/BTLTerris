#ifndef GBLOCK_H
#define GBLOCK_H
#include "Block.h"


class GBlock
{
    public:
        GBlock();
        int number;
        Block b[4];
        Block get_b1();
        Block get_b2();
        Block get_b3();
        Block get_b4();
        void down();
        void up();
        void left();
        void right();
        void rotate(Block _b);
    protected:

    private:
};
class GBlock1 : public GBlock{
public:
    GBlock1(){
        number = 1;
        b[0] = Block(5,3);
        b[1] = Block(6,3);
        b[2] = Block(5,4);
        b[3] = Block(6,4);
    }
};
//Hinh J
class GBlock2 : public GBlock{
public:
    GBlock2(){
        number = 3;
        b[0] = Block(5,3);
        b[1] = Block(5,4);
        b[2] = Block(5,5);
        b[3] = Block(4,5);
    }
};
//Hinh I
class GBlock3 : public GBlock{
public:
    GBlock3(){
        number = 2;
        b[0] = Block(5,3);
        b[1] = Block(5,4);
        b[2] = Block(5,5);
        b[3] = Block(5,6);
    }
};
//Hinh Z
class GBlock4 : public GBlock{
public:
    GBlock4(){
        number = 4;
        b[0] = Block(4,3);
        b[1] = Block(5,3);
        b[2] = Block(5,4);
        b[3] = Block(6,4);
    }
};
//Hinh T
class GBlock5 : public GBlock{
public:
    GBlock5(){
        number = 5;
        b[0] = Block(4,3);
        b[1] = Block(5,3);
        b[2] = Block(6,3);
        b[3] = Block(5,4);
    }
};
//Hinh L
class GBlock6 : public GBlock{
public:
    GBlock6(){
        number = 6;
        b[0] = Block(5,3);
        b[1] = Block(5,4);
        b[2] = Block(5,5);
        b[3] = Block(6,5);
    }
};

#endif // GBLOCK_H
