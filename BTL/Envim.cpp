#include "Envim.h"

Envim::Envim(){
        for(int i=0; i < width; i++){
            for(int j=0; j < height; j++){
                envim[i][j] = 0;
            }
        }
        next = newNext();

}
    // Bat dau chay chuong trinh
    void Envim::start(){
        push(next);
        next = newNext();
    }
    // Chon Group Block ke tiep
    GBlock Envim::newNext(){
        int rd = rand() % 6 + 1;
        switch(rd){
        case 1:
            return GBlock1();
            break;
        case 2:
            return GBlock2();
            break;
        case 3:
            return GBlock3();
            break;
        case 4:
            return GBlock4();
            break;
        case 5:
            return GBlock5();
            break;
        case 6:
            return GBlock6();
            break;
        }
    }
    // Chen Block vao moi truong thuc thi
    void Envim::push(Block b, int _number){
        envim[b.x][b.y] = _number;
    }
    // Chen Group Block vao moi truong thuc thi
    void Envim::push(GBlock _next){
        obj = _next;
        push(obj.get_b1(), obj.number);
        push(obj.get_b2(), obj.number);
        push(obj.get_b3(), obj.number);
        push(obj.get_b4(), obj.number);
    }
    void Envim::right(){
        GBlock Gb = obj;
        Gb.right();
        move(Gb);
    }
     void Envim::left(){
        GBlock Gb = obj;
        Gb.left();
        move(Gb);
    }
    void Envim::up(){
        GBlock Gb = obj;
        Gb.up();
        move(Gb);
    }
    void Envim::down(){
        GBlock tmp = obj;
        pop(obj);
        tmp.down();
        if(limit(tmp) == true){
            push(tmp);
        }
        //Neu down cham day
        else{
            push(obj);
            delRow();
            if(limit(next) == true)
               start();
            else{
                gameover = true;
            }
        }
    }
    void Envim::delRow(){
        //Kiem tra hang full?
        for(int i=0; i < height; i++){
            int cout = 0;
            for(int j=0; j < width; j++){
                if(envim[j][i] != 0)
                    cout++;
            }
            if(cout == width){
                merge(i);
                point++;
            }
        }
    }
    //Gop hang tren voi duoi
    void Envim::merge(int position){
        for(int i=position; i > 0; i--){
            for(int j=0; j < width; j++){
                envim[j][i] = envim[j][i-1];
            }

        }
    }
    void Envim::pop(Block _b){
        envim[_b.x][_b.y] = 0;
    }
    void Envim::pop(GBlock _Gb){
        pop(_Gb.get_b1());
        pop(_Gb.get_b2());
        pop(_Gb.get_b3());
        pop(_Gb.get_b4());
    }
    bool Envim::limit(Block _b){
        //Gioi han bien
        if(_b.x > width - 1 || _b.x < 0 || _b.y > height - 1 )
            return false;
        //Gioi han day
         if( envim[_b.x][_b.y] > 0)
            return false;
        return true;
    }
    bool Envim::limit(GBlock _Gb){
        if(limit((_Gb.get_b1())) == false)
            return false;
        else if(limit((_Gb.get_b2())) == false)
            return false;
        else if(limit((_Gb.get_b3())) == false)
            return false;
        else if(limit((_Gb.get_b4())) == false)
            return false;
        else
            return true;
    }
    void Envim::move(GBlock _Gb){
        pop(obj);
        if(limit(_Gb) == true)
            push(_Gb);
        else
            push(obj);

    }
