#include <iostream>
#include <cmath>
#include "SDL.h"
#include <graphics.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL2_mixer-2.0.4/i686-w64-mingw32/include/SDL2/SDL_mixer.h"
#include <string>


enum Piece {I=0,O,T,S,Z,J,L,NONE};
int pieces[7][4][4][4] =
{
    {   //I
        {
            { 0, 0, 1, 0},
            { 0, 0, 1, 0},
            { 0, 0, 1, 0},
            { 0, 0, 1, 0}
        },{
            { 0, 0, 0, 0},
            { 1, 1, 1, 1},
            { 0, 0, 0, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 1, 0},
            { 0, 0, 1, 0},
            { 0, 0, 1, 0},
            { 0, 0, 1, 0}
        },{
            { 0, 0, 0, 0},
            { 1, 1, 1, 1},
            { 0, 0, 0, 0},
            { 0, 0, 0, 0}
        }
    },{ //O
        {
            { 0, 0, 0, 0},
            { 0, 2, 2, 0},
            { 0, 2, 2, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 2, 2, 0},
            { 0, 2, 2, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 2, 2, 0},
            { 0, 2, 2, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 2, 2, 0},
            { 0, 2, 2, 0},
            { 0, 0, 0, 0}
        }
    },{ //T
        {
            { 0, 0, 0, 0},
            { 0, 3, 3, 3},
            { 0, 0, 3, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 3, 0},
            { 0, 3, 3, 0},
            { 0, 0, 3, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 0, 3, 0},
            { 0, 3, 3, 3},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 3, 0},
            { 0, 0, 3, 3},
            { 0, 0, 3, 0},
            { 0, 0, 0, 0}
        }
    },{ //S
        {
            { 0, 0, 0, 0},
            { 0, 0, 4, 4},
            { 0, 4, 4, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 4, 0, 0},
            { 0, 4, 4, 0},
            { 0, 0, 4, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 0, 4, 4},
            { 0, 4, 4, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 4, 0, 0},
            { 0, 4, 4, 0},
            { 0, 0, 4, 0},
            { 0, 0, 0, 0}
        }
    },{ //Z
        {
            { 0, 0, 0, 0},
            { 0, 5, 5, 0},
            { 0, 0, 5, 5},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 5},
            { 0, 0, 5, 5},
            { 0, 0, 5, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 5, 5, 0},
            { 0, 0, 5, 5},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 5},
            { 0, 0, 5, 5},
            { 0, 0, 5, 0},
            { 0, 0, 0, 0}
        }
    },{ //J
        {
            { 0, 0, 0, 0},
            { 0, 6, 6, 6},
            { 0, 0, 0, 6},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 6, 0},
            { 0, 0, 6, 0},
            { 0, 6, 6, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 6, 0, 0},
            { 0, 6, 6, 6},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 6, 6},
            { 0, 0, 6, 0},
            { 0, 0, 6, 0},
            { 0, 0, 0, 0}
        }
    },{ //L
        {
            { 0, 0, 0, 0},
            { 0, 7, 7, 7},
            { 0, 7, 0, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 7, 7, 0},
            { 0, 0, 7, 0},
            { 0, 0, 7, 0},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 0, 0},
            { 0, 0, 0, 7},
            { 0, 7, 7, 7},
            { 0, 0, 0, 0}
        },{
            { 0, 0, 7, 0},
            { 0, 0, 7, 0},
            { 0, 0, 7, 7},
            { 0, 0, 0, 0}
        }
    }
};
enum GameStatus {Menu,Single,Multi,Map,Help,End1P,End2P};
GameStatus status;
int speedTable[] = {800,716,633,550,466,383,300,216,133,100};
std::string winner;
unsigned int TIME_BEGIN;
unsigned int TIME_NOW;

int selected_map = 0;
int map_list[4][28][10] =
{
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    },
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {5,4,0,0,0,0,0,0,4,5},
        {5,4,0,0,0,0,0,0,4,5},
        {5,4,7,0,0,0,0,7,4,5},
        {7,7,7,0,0,0,0,7,7,7},
        {5,5,7,5,0,0,5,7,5,5},
        {5,5,7,5,0,0,5,7,5,5},
        {5,4,7,5,0,0,5,7,4,5},
        {5,4,7,5,0,0,5,7,4,5},
        {5,4,7,5,0,0,5,7,4,5},
        {5,4,7,5,0,0,5,7,4,5},
        {5,4,7,5,0,0,5,7,4,5},
        {5,4,7,5,0,0,5,7,4,5},
        {5,4,7,5,0,0,5,7,4,5},
        {5,7,7,5,0,0,5,7,7,5},
        {5,5,5,5,0,0,5,5,5,5}
    },
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,7,0,0,0,7,0},
        {0,0,0,7,0,7,0,7,0,0},
        {0,0,0,0,0,0,7,0,0,0},
        {0,0,0,0,0,7,0,7,0,7},
        {0,0,0,0,7,0,0,0,7,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,0,0},
        {1,0,0,1,0,0,0,0,0,0},
        {1,1,1,0,0,0,0,0,0,0},
        {1,0,0,0,1,0,0,0,0,0},
        {0,1,1,1,0,0,0,0,0,0}
    },
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6},
        {1,4,1,0,0,0,0,1,2,1},
        {5,1,7,0,0,0,0,3,1,6}
    }
};

class GameMechanics{
    public:
    int board[28][10] = {};
    Piece nextPiece;
    Piece holdPiece = NONE;
    Piece currentPiece;
    int currentx,currenty,currentRotation;
    int ghosty;

    int speed;
    int sl;
    bool held;
    bool touched;
    bool gg;

    unsigned int t0, t1;

    void summon();
    bool isLegal() const;
    void ghost();
    void cRotate();
    void touch();
    void clearLine(int i);
    void checkLine();
    void hold();
    virtual bool isGG();

    void operator++();      //Left
    void operator++(int);   //Right
    void operator-();       //Down
    void operator--();      //Hard Drop
};

class Singleplayer: public GameMechanics{
    public:
    Singleplayer();
    ~Singleplayer();
    bool isGG();
};

class Multiplayer: public GameMechanics{
    public:
    int rl,kos;

    Multiplayer();
    ~Multiplayer();
    bool isGG();
    void ko();
    void recieveLine();
};

Singleplayer::Singleplayer(){
    for (int i = 0;i<28;i++){
        for (int j = 0;j<10;j++){
            board[i][j] = map_list[selected_map][i][j];
        }
    }
    sl = 0;
    held = false;
    touched = false;
    gg = false;
    speed = 0;
    srand(time(0));
    nextPiece = (Piece)(rand()%7);
    summon();
    return;
}

Singleplayer::~Singleplayer(){

}

Multiplayer::Multiplayer(){
    for (int i = 0;i<28;i++){
        for (int j = 0;j<10;j++){
            board[i][j] = map_list[selected_map][i][j];
        }
    }
    sl = 0;
    held = false;
    touched = false;
    gg = false;
    speed = 0;
    rl = 0;
    kos = 0;
    srand(time(0));
    nextPiece = (Piece)(rand()%7);
    summon();
    return;
}

Multiplayer::~Multiplayer(){

}

void GameMechanics::summon(){
    currentPiece = nextPiece;
    nextPiece = (Piece)(rand()%7);
    if ((int)currentPiece == 0){
        currenty = 5;
    }
    else currenty = 4;
    currentx = 5;
    currentRotation = 0;
    if (!isLegal()){ gg = true; return; }
    t0 = SDL_GetTicks();
    ghost();
    return;
}

bool GameMechanics::isLegal() const{
    for (int i =0;i<4;i++){
        for (int j =0;j<4;j++){
            if (pieces[(int)currentPiece][currentRotation][i][j]!=0){
                if (board[currenty-1+i][currentx-2+j]!=0){
                    return false;
                }
                if (currentx-2+j<0||currentx-2+j>=10||currenty-1+i>=28||currenty-1+i<4){
                    return false;
                }
            }
        }
    }
    return true;
}

void GameMechanics::operator-(){
    currenty++;
    if (!isLegal()){
        currenty--;
        touch();
    }
    return;
}
void GameMechanics::operator++(){
    if (currentx>0&&currentx<=9){
        currentx--;
        if (!isLegal()){
            currentx++;
        }
    }
    ghost();
    return;
}
void GameMechanics::operator++(int){
    if (currentx>=0&&currentx<9){
        currentx++;
        if (!isLegal()){
            currentx--;
        }
    }
    ghost();
    return;
}
void GameMechanics::operator--(){
    while (isLegal()){
        currenty++;
    }
    currenty--;
    touch();
    return;
}
void GameMechanics::ghost(){
    int tempy = currenty;
    while (isLegal()){
        currenty++;
    }
    currenty--;
    ghosty = currenty;
    currenty = tempy;
    return;
}
void GameMechanics::cRotate(){
    currentRotation = (currentRotation+1)%4;
    if (!isLegal()){
        currentRotation = (currentRotation+3)%4;
    } else t0 = SDL_GetTicks();
    ghost();
    return;
}

void GameMechanics::touch(){
    for (int i =0;i<4;i++){
        for (int j =0;j<4;j++){
            if (pieces[(int)currentPiece][currentRotation][i][j]!=0){
                board[currenty-1+i][currentx-2+j] = pieces[(int)currentPiece][currentRotation][i][j];
                if (board[currenty+i][currentx-2+j] == 9){
                    sl--;
                    clearLine(currenty+i);
                }
            }
        }
    }
    checkLine();
    touched = true;
    held = false;
    if (!this->isGG()){ summon(); }
}

bool Singleplayer::isGG(){
    if (gg){ return gg; }
    for (int i=0;i<10;i++){
        if (board[3][i] != 0){ return true; }
    }
    return false;
}
bool Multiplayer::isGG(){
    if (gg){ ko(); gg = false; return false;}
    for (int i=0;i<10;i++){
        if (board[3][i] != 0){ ko(); return false;}
    }
    return false;
}

void Multiplayer::ko(){
    kos++;
    for (int i = 0;i<28;i++){
        if (i == 27&&(board[i][0] != 8 && board[i][0] != 9)){
            for (int j = 0;j < 10;j++){
                sl--;
                clearLine(27);
            }
            return;
        }
        if (board[i][0] == 8 ||board[i][0] == 9){ sl--; clearLine(i);}
    }
    return;
}

void GameMechanics::clearLine(int i){
    for (int j=0;j<10;j++){
        board[i][j] = 0;
    }
    for (int k = i; k>1;k--){
        for (int j =0;j<10;j++){
            board[k][j] = board[k-1][j];
        }
    }
    sl++;
    if (sl/10>9){
        speed = 9;
    }
    else speed = (int) sl/10;
    t0 = SDL_GetTicks();
    return;
}

void GameMechanics::checkLine(){
    int lineClear = 0;
    for (int i =4;i<28;i++){
        for (int j =0;j<10;j++){
            if (board[i][j] == 0 || board[i][j] == 8){
                break;
            }
            if (j == 9){
                clearLine(i);
                lineClear++;
            }
        }
    }
    return;
}

void GameMechanics::hold(){
    if (!held){
        if (holdPiece == NONE){
            holdPiece = currentPiece;
            summon();
        } else {
            Piece temp = currentPiece;
            currentPiece = holdPiece;
            holdPiece = temp;
            if ((int)currentPiece == 0){
                currenty = 5;
            }
            else currenty = 4;
            currentx = 5;
            currentRotation = 0;
            t0 = SDL_GetTicks();
        }
        held = true;
    }
    ghost();
    return;
}

void Multiplayer::recieveLine(){
    for (int i = 0; i<27;i++){
        for (int j =0;j<10;j++){
            board[i][j] = board[i+1][j];
        }
    }
    for (int j=0;j<10;j++){
        board[27][j] = 8;
    }
    board[27][rand()%10] = 9;
    rl++;
    ghost();
    return;
}

SDL_Keycode keyList[] = {SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT,SDLK_SPACE,SDLK_LSHIFT,SDLK_RSHIFT,SDLK_RETURN,SDLK_KP_ENTER,SDLK_KP_0,SDLK_a,SDLK_s,SDLK_d,SDLK_w,SDLK_RCTRL};
SDL_Keycode lastKey = SDLK_F24;
SDL_Keycode lastKey2 = SDLK_F24;
SDL_Keycode key;

void keypress(SDL_Keycode Key, Uint32 type){
    if (status == Multi){
        if (type == SDL_KEYDOWN){
            if (Key == SDLK_DOWN || Key == SDLK_s){ key = Key; if (key == SDLK_DOWN){ lastKey2 = SDLK_DOWN; return; } lastKey = SDLK_s; return; }
            if (Key == SDLK_a || Key == SDLK_s ||Key == SDLK_d || Key == SDLK_w || Key == SDLK_SPACE || Key == SDLK_LSHIFT){
                if (lastKey != Key){ lastKey = Key; key = Key; return; }
            }
            if (Key == SDLK_LEFT || Key == SDLK_DOWN ||Key == SDLK_RIGHT || Key == SDLK_UP || Key == SDLK_LCTRL || Key == SDLK_KP_0 || Key == SDLK_RSHIFT){
                if (lastKey2 != Key){ lastKey2 = Key; key = Key; return; }
            }
        }
        if (type == SDL_KEYUP){
            if (lastKey == Key){ lastKey = SDLK_F24; key = SDLK_F23; return; }
            if (lastKey2 == Key){ lastKey2 = SDLK_F24; key = SDLK_F23; return; }
        }
        key = SDLK_F23;
        return;
    }
    if (type == SDL_KEYDOWN){
        if ((status == Single) && (Key == SDLK_DOWN || Key == SDLK_s)){ key = Key; return; }
        if (lastKey != Key){ lastKey = Key; key = Key; return; }
    }
    if (type == SDL_KEYUP){
        if (lastKey == Key){ lastKey = SDLK_F24; key = SDLK_F23; return; }
    }
    key = SDLK_F23;
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    int flags = IMG_INIT_JPG|IMG_INIT_PNG;
    if( (IMG_Init(flags)&flags) != flags ) {
        std::cout << "IMG_Init: Failed to init required jpg and png support!\n";
        std::cout << "IMG_Init: " << IMG_GetError() << std::endl;
    }

    if(TTF_Init()==-1) {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        return 3;
    }

    TTF_Font *font;
    font = TTF_OpenFont("fonts/8-Bit Madness.TTF", 300);
    if(!font) {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        return 3;
    }

    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
    Mix_Music *bgm = Mix_LoadMUS("./sound/bgm.mp3");
    Mix_PlayMusic(bgm,-1);

    window = SDL_CreateWindow("Tetris", 50, 50, 960, 540, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return 3;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Menu Background
    surface = IMG_Load("images/menuBackground_960x540.png");
    SDL_Texture *menu_background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect menu_background_rect = {0,0,960,540};
    // 1 player
    surface = TTF_RenderText_Solid(font, "1 PLAYER", {255,255,255});
    SDL_Texture *p1 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect p1_rect = {405,250,150,32};
    // 2 player
    surface = TTF_RenderText_Solid(font, "2 PLAYER", {255,255,255});
    SDL_Texture *p2 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect p2_rect = {400,300,160,32};
    // map
    surface = TTF_RenderText_Solid(font, "       MAP       ", {255,255,255});
    SDL_Texture *map_text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect map_text_rect = {395,350,160,32};
    // map
    surface = TTF_RenderText_Solid(font, "      HELP      ", {255,255,255});
    SDL_Texture *help_text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect help_text_rect = {395,400,160,32};
    // Selection
    surface = TTF_RenderText_Solid(font,">                  <", {255,255,255});
    SDL_Texture *selection = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect selection_rect = {360,250,240,32};
    // Map setting background
    surface = IMG_Load("images/mapSettings_960x540.png");
    SDL_Texture *mapSettings_background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect mapSettings_background_rect = {0,0,960,540};
    // Help background
    surface = IMG_Load("images/help_960x540.png");
    SDL_Texture *help = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect help_rect = {0,0,960,540};
    // 1 Player background
    surface = IMG_Load("images/background_960x540.png");
    SDL_Texture *p1_background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect p1_background_rect = {0,0,960,540};
    // 2 Player background
    surface = IMG_Load("images/background2P_960x540.png");
    SDL_Texture *p2_background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect p2_background_rect = {0,0,960,540};
    // sprite sheet
    surface = IMG_Load("images/tetromino_64x64.png");
    SDL_Texture *tetrimino = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    // numbers sheet
    surface = IMG_Load("images/numbers_160x32.png");
    SDL_Texture *numbers = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    // gg
    surface = TTF_RenderText_Solid(font, "GAME OVER", {255,255,255});
    SDL_Texture *gg = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect gg_rect = {405,250,150,32};

    status = Menu;
    int menuSelection = 1;
    SDL_Rect srcrect,dstrect;
    while (1) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        if (status == Menu){
            keypress(event.key.keysym.sym, event.type);
            if (event.type == SDL_KEYDOWN){
                if (key == SDLK_DOWN && selection_rect.y < 400){
                    selection_rect.y += 50;
                    menuSelection++;
                }
                if (key == SDLK_UP && selection_rect.y > 250){
                    selection_rect.y -= 50;
                    menuSelection--;
                }
                if (key == SDLK_RETURN || key == SDLK_KP_ENTER){
                    status = (GameStatus)menuSelection;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, menu_background, NULL, &menu_background_rect);\
            SDL_RenderCopy(renderer, p1, NULL, &p1_rect);
            SDL_RenderCopy(renderer, p2, NULL, &p2_rect);
            SDL_RenderCopy(renderer, map_text, NULL, &map_text_rect);
            SDL_RenderCopy(renderer, help_text, NULL, &help_text_rect);
            SDL_RenderCopy(renderer, selection, NULL, &selection_rect);
            SDL_RenderPresent(renderer);
        }
        if (status == Map){
            keypress(event.key.keysym.sym, event.type);
            if (event.type == SDL_KEYDOWN){
                if (key == SDLK_LEFT){
                    selected_map = (selected_map+3)%4;
                }
                if (key == SDLK_RIGHT){
                    selected_map = (selected_map+1)%4;
                }
                if (key == SDLK_RETURN || key == SDLK_KP_ENTER){
                    status = Menu;
                }
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, mapSettings_background, NULL, &mapSettings_background_rect);

            for (int i = 4;i<28;i++){
                for (int j = 0;j<10;j++){
                    if (map_list[selected_map][i][j]!=0){
                        srcrect = { (map_list[selected_map][i][j]%4)*16, ((int)(map_list[selected_map][i][j]/4))*16, 16, 16 };
                        dstrect = { 400 + j*16, 78 + (i-4)*16, 16, 16 };
                        SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                    }
                }
            }
            SDL_RenderPresent(renderer);

        }
        if (status == Help){
            keypress(event.key.keysym.sym, event.type);
            if (event.type == SDL_KEYDOWN){
                if (key == SDLK_ESCAPE){
                    status = Menu;
                }
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, help, NULL, &help_rect);
            SDL_RenderPresent(renderer);
        }
        if (status == Single){
            Singleplayer g;
            while (!g.isGG()){
                //Game mechanics
                g.t1 = SDL_GetTicks();
                if (g.t1-g.t0>speedTable[g.speed]){
                    g.t0 = g.t1;
                    -g;
                }
                SDL_PollEvent(&event);
                if (event.type == SDL_QUIT) {
                    break;
                }
                keypress(event.key.keysym.sym, event.type);
                if (key == SDLK_LEFT || key == SDLK_a){
                    ++g;
                }
                if (key == SDLK_RIGHT || key == SDLK_d){
                    g++;
                }
                if (key == SDLK_UP || key == SDLK_w){
                    g.cRotate();
                }
                if (key == SDLK_DOWN ||key == SDLK_s){
                    if (g.t1-g.t0>speedTable[g.speed]/2){
                        g.t0 = g.t1;
                        -g;
                    }
                }
                if (key == SDLK_SPACE){
                    --g;
                }
                if (key == SDLK_RSHIFT||key == SDLK_LSHIFT){
                    g.hold();
                }


                //Render
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, p1_background, NULL, &p1_background_rect);
                //Speed
                srcrect = { 0, 0, 16, 32 };
                dstrect = { 254, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (int)((g.speed+1)/10)*16, 0, 16, 32 };
                dstrect = { 272, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { ((g.speed+1)%10)*16, 0, 16, 32 };
                dstrect = { 290, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                //lines cleared
                srcrect = { (int)(g.sl/100)*16, 0, 16, 32 };
                dstrect = { 254, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { ((int)(g.sl/10)%10)*16, 0, 16, 32 };
                dstrect = { 272, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (g.sl%10)*16, 0, 16, 32 };
                dstrect = { 290, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);

                for (int i = 4;i<28;i++){
                    for (int j = 0;j<10;j++){
                        if (g.board[i][j]!=0){
                            srcrect = { (g.board[i][j]%4)*16, ((int)(g.board[i][j]/4))*16, 16, 16 };
                            dstrect = { 400 + j*16, 78 + (i-4)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                for (int i =0;i<4;i++){
                    for (int j =0;j<4;j++){
                        if (pieces[(int)g.currentPiece][g.currentRotation][i][j]!=0){
                            srcrect = { 3*16, 3*16, 16, 16 };
                            dstrect = { 400 + (j+g.currentx-2)*16, 78 + (i+g.ghosty-5)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                for (int i =0;i<4;i++){
                    for (int j =0;j<4;j++){
                        if (pieces[(int)g.currentPiece][g.currentRotation][i][j]!=0){
                            srcrect = { (pieces[(int)g.currentPiece][g.currentRotation][i][j]%4)*16, ((int)(pieces[(int)g.currentPiece][g.currentRotation][i][j]/4))*16, 16, 16 };
                            dstrect = { 400 + (j+g.currentx-2)*16, 78 + (i+g.currenty-5)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                for (int i =0;i<4;i++){
                    for (int j =0; j<4;j++){
                        if (pieces[(int)g.nextPiece][0][i][j]!=0){
                            srcrect = { ((g.nextPiece+1)%4)*16, ((int)((g.nextPiece+1)/4))*16, 16, 16 };
                            dstrect = { 561 + (j)*16, 80 + (i)*16, 16, 16 };
                            if (pieces[(int)g.nextPiece][0][i][j] == 2){
                                dstrect = { 569 + (j)*16, 80 + (i)*16, 16, 16 };
                            }
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                if (g.holdPiece != NONE){
                    for (int i =0;i<4;i++){
                        for (int j =0; j<4;j++){
                            if (pieces[(int)g.holdPiece][0][i][j]!=0){
                                srcrect = { ((g.holdPiece+1)%4)*16, ((int)((g.holdPiece+1)/4))*16, 16, 16 };
                                dstrect = { 561 - 242 + (j)*16, 80 + (i)*16, 16, 16 };
                                if (pieces[(int)g.holdPiece][0][i][j] == 2){
                                    dstrect = { 569 - 242 + (j)*16, 80 + (i)*16, 16, 16 };
                                }
                                SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                            }
                        }
                    }
                }

                SDL_RenderPresent(renderer);

            }
            g.~Singleplayer();
            status = End1P;

        }
        if (status == End1P){
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, gg, NULL, &gg_rect);
            SDL_RenderPresent(renderer);
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    status = Menu;
                }
            }
        }
        if (status == Multi){
            Multiplayer g1, g2;
            TIME_BEGIN = SDL_GetTicks();
            TIME_NOW = SDL_GetTicks();
            while (TIME_NOW-TIME_BEGIN<120000){
                //Game mechanics
                g1.isGG();
                g2.isGG();
                g1.t1 = SDL_GetTicks();
                g2.t1 = SDL_GetTicks();
                if (g1.t1-g1.t0>700){
                    g1.t0 = g1.t1;
                    -g1;
                }
                if (g2.t1-g2.t0>700){
                    g2.t0 = g2.t1;
                    -g2;
                }
                while (g2.touched && g1.sl != g2.rl){
                    g2.recieveLine();
                }
                while (g1.touched && g1.rl != g2.sl){
                    g1.recieveLine();
                }
                g1.touched = false;
                g2.touched = false;
                SDL_PollEvent(&event);
                if (event.type == SDL_QUIT) {
                    break;
                }
                keypress(event.key.keysym.sym, event.type);
                if (key == SDLK_a){
                    ++g1;
                }
                if (key == SDLK_LEFT){
                    ++g2;
                }
                if (key == SDLK_d){
                    g1++;
                }
                if (key == SDLK_RIGHT){
                    g2++;
                }
                if (key == SDLK_w){
                    g1.cRotate();
                }
                if (key == SDLK_UP){
                    g2.cRotate();
                }
                if (key == SDLK_s || lastKey == SDLK_s){
                    if (g1.t1-g1.t0>speedTable[g1.speed]/2){
                        g1.t0 = g1.t1;
                        -g1;
                    }
                }
                if (key == SDLK_DOWN || lastKey2 == SDLK_DOWN){
                    if (g2.t1-g2.t0>speedTable[g2.speed]/2){
                        g2.t0 = g2.t1;
                        -g2;
                    }
                }
                if (key == SDLK_SPACE){
                    --g1;
                }
                if (key == SDLK_KP_0 || key == SDLK_RCTRL){
                    --g2;
                }
                if (key == SDLK_LSHIFT){
                    g1.hold();
                }
                if (key == SDLK_RSHIFT){
                    g2.hold();
                }

                //Render
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, p2_background, NULL, &p2_background_rect);
                //Time
                srcrect = { ((int)((120000-(TIME_NOW-TIME_BEGIN))/100000))*16, 0, 16, 32 };
                dstrect = { 454, 32, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (((int)((120000-(TIME_NOW-TIME_BEGIN))/10000))%10)*16, 0, 16, 32 };
                dstrect = { 472, 32, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (((int)((120000-(TIME_NOW-TIME_BEGIN))/1000))%10)*16, 0, 16, 32 };
                dstrect = { 490, 32, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                //kos
                srcrect = { (int)(g2.kos/100)*16, 0, 16, 32 };
                dstrect = { 409, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { ((int)(g2.kos/10)%10)*16, 0, 16, 32 };
                dstrect = { 427, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (g2.kos%10)*16, 0, 16, 32 };
                dstrect = { 445, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (int)(g1.kos/100)*16, 0, 16, 32 };
                dstrect = { 500, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { ((int)(g1.kos/10)%10)*16, 0, 16, 32 };
                dstrect = { 518, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (g1.kos%10)*16, 0, 16, 32 };
                dstrect = { 536, 215, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                //lines cleared
                srcrect = { (int)(g1.sl/100)*16, 0, 16, 32 };
                dstrect = { 409, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { ((int)(g1.sl/10)%10)*16, 0, 16, 32 };
                dstrect = { 427, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (g1.sl%10)*16, 0, 16, 32 };
                dstrect = { 445, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (int)(g2.sl/100)*16, 0, 16, 32 };
                dstrect = { 500, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { ((int)(g2.sl/10)%10)*16, 0, 16, 32 };
                dstrect = { 518, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);
                srcrect = { (g2.sl%10)*16, 0, 16, 32 };
                dstrect = { 536, 299, 16, 32 };
                SDL_RenderCopy(renderer, numbers, &srcrect, &dstrect);

                for (int i = 4;i<28;i++){
                    for (int j = 0;j<10;j++){
                        if (g1.board[i][j]!=0){
                            srcrect = { (g1.board[i][j]%4)*16, ((int)(g1.board[i][j]/4))*16, 16, 16 };
                            dstrect = { 200 + j*16, 78 + (i-4)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                        if (g2.board[i][j]!=0){
                            srcrect = { (g2.board[i][j]%4)*16, ((int)(g2.board[i][j]/4))*16, 16, 16 };
                            dstrect = { 600 + j*16, 78 + (i-4)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                for (int i =0;i<4;i++){
                    for (int j =0;j<4;j++){
                        if (pieces[(int)g1.currentPiece][g1.currentRotation][i][j]!=0){
                            srcrect = { 3*16, 3*16, 16, 16 };
                            dstrect = { 200 + (j+g1.currentx-2)*16, 78 + (i+g1.ghosty-5)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                        if (pieces[(int)g2.currentPiece][g2.currentRotation][i][j]!=0){
                            srcrect = { 3*16, 3*16, 16, 16 };
                            dstrect = { 600 + (j+g2.currentx-2)*16, 78 + (i+g2.ghosty-5)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                for (int i =0;i<4;i++){
                    for (int j =0;j<4;j++){
                        if (pieces[(int)g1.currentPiece][g1.currentRotation][i][j]!=0){
                            srcrect = { (pieces[(int)g1.currentPiece][g1.currentRotation][i][j]%4)*16, ((int)(pieces[(int)g1.currentPiece][g1.currentRotation][i][j]/4))*16, 16, 16 };
                            dstrect = { 200 + (j+g1.currentx-2)*16, 78 + (i+g1.currenty-5)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                        if (pieces[(int)g2.currentPiece][g2.currentRotation][i][j]!=0){
                            srcrect = { (pieces[(int)g2.currentPiece][g2.currentRotation][i][j]%4)*16, ((int)(pieces[(int)g2.currentPiece][g2.currentRotation][i][j]/4))*16, 16, 16 };
                            dstrect = { 600 + (j+g2.currentx-2)*16, 78 + (i+g2.currenty-5)*16, 16, 16 };
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                for (int i =0;i<4;i++){
                    for (int j =0; j<4;j++){
                        if (pieces[(int)g1.nextPiece][0][i][j]!=0){
                            srcrect = { ((g1.nextPiece+1)%4)*16, ((int)((g1.nextPiece+1)/4))*16, 16, 16 };
                            dstrect = { 361 + (j)*16, 80 + (i)*16, 16, 16 };
                            if (pieces[(int)g1.nextPiece][0][i][j] == 2){
                                dstrect = { 369 + (j)*16, 80 + (i)*16, 16, 16 };
                            }
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                        if (pieces[(int)g2.nextPiece][0][i][j]!=0){
                            srcrect = { ((g2.nextPiece+1)%4)*16, ((int)((g2.nextPiece+1)/4))*16, 16, 16 };
                            dstrect = { 761 + (j)*16, 80 + (i)*16, 16, 16 };
                            if (pieces[(int)g2.nextPiece][0][i][j] == 2){
                                dstrect = { 769 + (j)*16, 80 + (i)*16, 16, 16 };
                            }
                            SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                        }
                    }
                }
                if (g1.holdPiece != NONE){
                    for (int i =0;i<4;i++){
                        for (int j =0; j<4;j++){
                            if (pieces[(int)g1.holdPiece][0][i][j]!=0){
                                srcrect = { ((g1.holdPiece+1)%4)*16, ((int)((g1.holdPiece+1)/4))*16, 16, 16 };
                                dstrect = { 361 - 242 + (j)*16, 80 + (i)*16, 16, 16 };
                                if (pieces[(int)g1.holdPiece][0][i][j] == 2){
                                    dstrect = { 369 - 242 + (j)*16, 80 + (i)*16, 16, 16 };
                                }
                                SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                            }
                        }
                    }
                }
                if (g2.holdPiece != NONE){
                    for (int i =0;i<4;i++){
                        for (int j =0; j<4;j++){
                            if (pieces[(int)g2.holdPiece][0][i][j]!=0){
                                srcrect = { ((g2.holdPiece+1)%4)*16, ((int)((g2.holdPiece+1)/4))*16, 16, 16 };
                                dstrect = { 761 - 242 + (j)*16, 80 + (i)*16, 16, 16 };
                                if (pieces[(int)g2.holdPiece][0][i][j] == 2){
                                    dstrect = { 769 - 242 + (j)*16, 80 + (i)*16, 16, 16 };
                                }
                                SDL_RenderCopy(renderer, tetrimino, &srcrect, &dstrect);
                            }
                        }
                    }
                }

                SDL_RenderPresent(renderer);
                winner = "Player 1 Wins";
                if (g1.kos > g2.kos){
                    winner = "Player 2 Wins";
                }
                else if (g1.kos == g2.kos){
                    if (g1.sl < g2.sl){
                        winner = "Player 2 Wins";
                    }
                    else if (g1.sl == g2.sl){
                        winner = "     Tie     ";
                    }
                }
                TIME_NOW = SDL_GetTicks();

            }
            g1.~Multiplayer();
            g2.~Multiplayer();
            status = End2P;

        }
        if (status == End2P){

            surface = TTF_RenderText_Solid(font, winner.c_str(), {255,255,255});
            SDL_Texture *winnerText = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_Rect winner_rect = {405,250,150,32};
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, winnerText, NULL, &winner_rect);
            SDL_RenderPresent(renderer);
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                        status = Menu;
                        delete winnerText;
                        delete &winner_rect;
                }
            }

        }

    }

    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
