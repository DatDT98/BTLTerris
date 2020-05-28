#include <SDL.h>
#include <SDL_image.h>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <ctime>
//Kich co hinh ve 1 o
#define X_SizeBlock 27
#define Y_SizeBlock 27

using namespace std;

//#include "Block.h"
#include "Block.cpp"
//#include "Envim.h"
#include "Envim.cpp"
//#include "GBlock.h"
#include "GBlock.cpp"

//Khai bao bien toan cuc
SDL_Surface* Surface = NULL;
SDL_Renderer* Renderer = NULL;
SDL_Window* Window = NULL;
SDL_Texture* TT_Background = NULL;
SDL_Texture* TT_GBlock = NULL;
SDL_Texture* Point = NULL;
TTF_Font* font = NULL;
//Hinh ve hien thi
SDL_Rect Src;
SDL_Rect Des;

//Cac phuong thuc khoi tao
bool init();
//Load anh
bool loadMedia(string path);
//Hien thi Block con
void showBlock(int _x, int _y, int _number);
//Hien thi khoi cha tao nen hinh dang
void showGBlock(int _envim[col][row], GBlock _next);
//Hien thi chu
void showScore(string point, int x_pos, int y_pos, int size);
//Destroy all
void close();

int main(int argv, char* argc[])
{
    bool quit = false;
    int start = 0;
    //nhac hieu hung di chuyen
    SDL_Event event;
    Mix_Music* music = NULL;
    Mix_Chunk *mUP  = NULL;
    Mix_Chunk *mDOWN  = NULL;
    Mix_Chunk *mLEFT = NULL;
    Mix_Chunk *mRIGHT = NULL;

    Src.w = 17;
    Src.h = 17;
//Set kich cơ hinh

    if(!init())
        cout << "Init failed!!!" << endl;
    else{
        if(loadMedia("image/background.bmp"))
        {
            TT_Background = SDL_CreateTextureFromSurface(Renderer, Surface);
            SDL_FreeSurface(Surface);
        }
        if(loadMedia("image/tiles.bmp"))
        {
            TT_GBlock     = SDL_CreateTextureFromSurface(Renderer, Surface);
            SDL_FreeSurface(Surface);
        }
        srand (time(NULL));
        //Tao moi truong chay
        Envim envim;
        //Bat dau chay
        envim.start();
        //Chen nhac nen
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);                                                  //load nhac
        music = Mix_LoadMUS("music/Kyo.mp3");
        mDOWN = Mix_LoadWAV("music/high.wav");
        mUP = Mix_LoadWAV("music/scratch.wav");
        mLEFT = Mix_LoadWAV("music/medium.wav");
        mRIGHT = Mix_LoadWAV("music/low.wav");
        //-1 lap nhac vo tan
        Mix_PlayMusic(music, -1);
        //Hien khoi
        showGBlock(envim.envim, envim.next);
        while(quit != true){
            string score = to_string(envim.score);
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                        quit = true;
                        break;
                }
                else if(event.type == SDL_KEYDOWN){
                    switch(event.key.keysym.sym){
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
                                showScore("Game over", 75, 150, 40);
                                showScore("Score: ", 90, 200, 40);
                                showScore(score, 230, 195, 50);
                                quit = true;
                            }
                            break;
                        default:
                            break;
                    }
                    //Moi lan di chuyen cap nhat diem
                    showScore("Score", 360, 400,35);
                    showScore(score, 395, 450,45);
                }
             }
           //Chay tu dong
            int lever = envim.score / 2;
            if(SDL_GetTicks() > (start + (1000 - (lever*200)))){
                envim.down();
                showGBlock(envim.envim, envim.next);
                showScore("Score", 360, 400,35);
                showScore(score, 395, 450,45);
                if(envim.gameover == true){
                    showScore("Game over", 75, 150, 40);
                    showScore("Score: ", 90, 200, 40);
                    showScore(score, 230, 195, 50);
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
void showBlock(int _x, int _y, int _number){
    //Set vi tri bat dau lay hinh
    Src.x = _number * 18;
    Src.y = 0;
    //Set vi tri
    Des.x = _x * X_SizeBlock + 42;
    Des.y = _y * Y_SizeBlock + 45 ;
    Des.w = X_SizeBlock;
    Des.h = Y_SizeBlock;
    SDL_RenderCopy(Renderer, TT_GBlock, &Src, &Des);
}
//hien thi diem
void showScore(string score, int x_pos, int y_pos, int size){
    SDL_Rect SrcScore;
    SDL_Rect DesScore;
    SDL_Color color = {8, 0, 0};

    font = TTF_OpenFont("font/Lato-Black.ttf", size);
    Surface = TTF_RenderText_Solid(font, score.c_str(), color);
    SDL_Texture* Score = SDL_CreateTextureFromSurface(Renderer, Surface);
    SDL_FreeSurface(Surface);
    TTF_SizeText(font, score.c_str(), &SrcScore.w, &SrcScore.h);
    SrcScore.x = 0;
    SrcScore.y = 0;
    //Set vi tri hien thi
    DesScore.x = x_pos;
    DesScore.y = y_pos;
    //Set size
    DesScore.w = SrcScore.w;
    DesScore.h = SrcScore.h;
    SDL_RenderCopy(Renderer,Score,&SrcScore,&DesScore);
    SDL_RenderPresent(Renderer);
}
void showGBlock(int _envim[col][row], GBlock _next){
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer,TT_Background,NULL,NULL);
    //Hien thi hinh obj hien tai dang chay
    for(int i=0; i < col; i++){
        for(int j=0; j < row; j++){
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
void close(){
    SDL_FreeSurface(Surface);
    SDL_DestroyWindow(Window);
    SDL_DestroyTexture(TT_GBlock);
    SDL_DestroyTexture(TT_Background);
    SDL_DestroyRenderer(Renderer);
    Mix_CloseAudio();
    SDL_Quit();
    TTF_Quit();
}
