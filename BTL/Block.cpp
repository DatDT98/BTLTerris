#include "Block.h"


    Block::Block(){
        x = 0;
        y = 0;
    }
    Block::Block(int _x , int _y){
        x = _x;
        y = _y;
    }
    void Block::move(int _x, int _y){
        x = _x;
        y = _y;
    }
    void Block::rotate(Block b){
        int _x, _y, tmp;
        _x = b.x - x;
        _y = b.y - y;
        //swap _x, _y
        tmp = _x;
        _x = _y;
        _y = -tmp;
        x = b.x + _x;
        y = b.y + _y;
    }

