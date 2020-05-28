#include "GBlock.h"

GBlock::GBlock(){
        b[0] = Block();
        b[1] = Block();
        b[2] = Block();
        b[3] = Block();
    }
    Block GBlock::get_b1(){
        return b[0];
    }
    Block GBlock::get_b2(){
        return b[1];
    }
    Block GBlock::get_b3(){
        return b[2];
    }
    Block GBlock::get_b4(){
        return b[3];
    }
    void GBlock::down(){
        b[0].move(b[0].x, b[0].y + 1);
        b[1].move(b[1].x, b[1].y + 1);
        b[2].move(b[2].x, b[2].y + 1);
        b[3].move(b[3].x, b[3].y + 1);
    }
    void GBlock::left(){
        b[0].move(b[0].x - 1, b[0].y);
        b[1].move(b[1].x - 1, b[1].y);
        b[2].move(b[2].x - 1, b[2].y);
        b[3].move(b[3].x - 1, b[3].y);
    }
    void GBlock::right(){
        b[0].move(b[0].x + 1, b[0].y);
        b[1].move(b[1].x + 1, b[1].y);
        b[2].move(b[2].x + 1, b[2].y);
        b[3].move(b[3].x + 1, b[3].y);
    }
    void GBlock::rotate(Block _b){
        b[0].rotate(_b);
        b[1].rotate(_b);
        b[2].rotate(_b);
        b[3].rotate(_b);
    }
    void GBlock::up(){
        if(number == 2)
            rotate(b[1]);
        else if(number == 3)
            rotate(b[1]);
        else if(number == 4)
            rotate(b[1]);
        else if(number == 5)
            rotate(b[1]);
        else if(number == 6)
            rotate(b[1]);

    }
