#include "SDL.h"
#include <SDL_image.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
//Kich co hinh ve 1 o
#define SizeX 27
#define SizeY 27

using namespace std;

#include "Block.h"
#include "Block.cpp"
#include "Envim.h"
#include "Envim.cpp"
#include "GBlock.h"
#include "GBlock.cpp"
//Khai bao bien toan cuc
SDL_Surface* Surface;
SDL_Renderer* Renderer;
SDL_Window* Window;
SDL_Texture* TT_Background;
SDL_Texture* TT_GBlock;
SDL_Texture* Point;
TTF_Font* font;
SDL_Rect Src;
SDL_Rect Des;

//Cac phuong thuc khoi tao
bool init();
//Load anh
bool loadMedia(string path);
void close();
//Khoi cha tao nen hinh dang

//Hien thi Block con
void showBlock(int _x, int _y, int _number){
    //Set vi tri
    Des.x = _x * SizeX + 43;
    Des.y = _y * SizeY - 36;
    Src.x = _number * 18;
    Src.y = 0;
    SDL_RenderCopy(Renderer, TT_GBlock, &Src, &Des);
}
//hien thi diem
void showPoint(string point, int x_pos, int y_pos, int size){
    SDL_Rect SrcPoin;
    SDL_Rect DesPoin;
    SDL_Color color = {8, 0, 0};

    font = TTF_OpenFont("font_ttf/Lato-Black.ttf", size);
    Surface = TTF_RenderText_Solid(font, point.c_str(), color);
    Point = SDL_CreateTextureFromSurface(Renderer, Surface);
    SDL_FreeSurface(Surface);
    TTF_SizeText(font, point.c_str(), &SrcPoin.w, &SrcPoin.h);
    SrcPoin.x = 0;
    SrcPoin.y = 0;
    //Set vi tri hien thi
    DesPoin.x = x_pos;
    DesPoin.y = y_pos;
    //Set size
    DesPoin.w = SrcPoin.w;
    DesPoin.h = SrcPoin.h;
    SDL_RenderCopy(Renderer,Point,&SrcPoin,&DesPoin);
    SDL_RenderPresent(Renderer);
}
void showGBlock(int _envim[width][height], GBlock _next){
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer,TT_Background,NULL,NULL);
    //Hien thi hinh obj hien tai dang chay
    for(int i=0; i < width; i++){
        for(int j=0; j < height; j++){
            if(_envim[i][j] != 0)
                showBlock(i,j,_envim[i][j]);
        }
    }
    //hien thi hinh ke tiep ben phai
    showBlock(_next.get_b1().x + 8,_next.get_b1().y + 3,_next.number);
    showBlock(_next.get_b2().x + 8,_next.get_b2().y + 3,_next.number);
    showBlock(_next.get_b3().x + 8,_next.get_b3().y + 3,_next.number);
    showBlock(_next.get_b4().x + 8,_next.get_b4().y + 3,_next.number);
    //hien thi len man hinh

    SDL_RenderPresent(Renderer);

}
int main(int argv, char* argc[])
{
    SDL_Event Event;
    //nhac hieu hung di chuyen
    Mix_Music* music;
    Mix_Chunk *mUP ;
    Mix_Chunk *mDOWN ;
    Mix_Chunk *mLEFT ;
    Mix_Chunk *mRIGHT ;

    Src.w = 17;
    Src.h = 17;
//Set kich cơ hinh
    Des.w = SizeX;
    Des.h = SizeY;
    if(!init())
        cout << "Init failed!!!" << endl;
    else{
            if(loadMedia("image/background.bmp"))
                TT_Background = SDL_CreateTextureFromSurface(Renderer, Surface);
            SDL_FreeSurface(Surface);
            if(loadMedia("image/tiles.bmp"))
                TT_GBlock     = SDL_CreateTextureFromSurface(Renderer, Surface);
            SDL_FreeSurface(Surface);
            srand (time(NULL));
            bool quit = false;
            int start = 0;
            Envim envim;
            envim.start();
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);                                                  //load nhac
            music = Mix_LoadMUS("mp3/Kyo.mp3");
            mDOWN = Mix_LoadWAV("mp3/high.wav");
            mUP = Mix_LoadWAV("mp3/scratch.wav");
            mLEFT = Mix_LoadWAV("mp3/medium.wav");
            mRIGHT = Mix_LoadWAV("mp3/low.wav");
            //-1 lap nhac vo tan
            Mix_PlayMusic(music, -1);
            showGBlock(envim.envim, envim.next);
            while(quit != true){
                string score = to_string(envim.point);
                if(SDL_PollEvent(&Event)){
                    if(Event.type == SDL_QUIT){
                            quit = true;
                            break;
                    }
                    else if(Event.type == SDL_KEYDOWN){
                        switch(Event.key.keysym.sym){
                            case SDLK_UP:
                                envim.up();
                                showGBlock(envim.envim, envim.next);
                                Mix_PlayChannel( -1, mUP, 0 );
                                break;
                            case SDLK_RIGHT:
                                envim.right();
                                showGBlock(envim.envim, envim.next);
                                Mix_PlayChannel( -1, mRIGHT, 0 );

                                break;
                            case SDLK_LEFT:
                                envim.left();
                                showGBlock(envim.envim, envim.next);
                                Mix_PlayChannel( -1, mLEFT, 0 );
                                break;
                            case SDLK_DOWN:
                                envim.down();
                                showGBlock(envim.envim, envim.next);
                                Mix_PlayChannel( -1, mDOWN, 0 );
                                if(envim.gameover == true){
                                    showPoint("Game over", 75, 150, 40);
                                    showPoint("Score: ", 90, 200, 40);
                                    showPoint(score, 230, 195, 50);
                                    quit = true;
                                }

                                break;
                            default:
                                break;
                        }
                        showPoint("Point", 360, 400,35);
                        showPoint(score, 395, 450,45);
                    }
                 }
               //Chay tu dong
                if(SDL_GetTicks() > (start + 1000) && envim.gameover != true){
                    envim.down();
                    showGBlock(envim.envim, envim.next);
                    showPoint("Point", 360, 400,35);
                    showPoint(score, 395, 450,45);
                    if(envim.gameover == true){
                        showPoint("Game over", 75, 150, 40);
                        showPoint("Score: ", 90, 200, 40);
                        showPoint(score, 230, 195, 50);
                        quit = quit;
                    }
                    start = SDL_GetTicks();
                }
            }
    }
    SDL_Delay(10000);
    close();
    return 0;
}

//--------------------------------------------------------------------------//
bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init()){
        cout << "SDL init error!!!" << endl;
        success = false;
    }
    else{
        Window = SDL_CreateWindow("TETRIS",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320*1.5, 480*1.5, 0);      // tao cua so
        if(Window == NULL){
            cout << "Create window error!!!" << endl;
            success = false;
        }
        else
            Renderer   = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);                                  // tao renderer
    }
    return success;
}
bool loadMedia(string path){
    bool success = true;
    Surface = IMG_Load(path.c_str());                                                      // tao background
    if(Surface == NULL){
        cout << "Load img error!!!" << endl;
        success = false;
    }
    return success;
}
void close(){
    SDL_FreeSurface(Surface);
    SDL_DestroyWindow(Window);
    SDL_DestroyTexture(TT_GBlock);
    SDL_DestroyTexture(TT_Background);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
    TTF_Quit();
}
