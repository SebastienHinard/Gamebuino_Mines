//CONSTANTS

const int UNIT = 8,
          SCREEN_W = gb.display.width(),
          SCREEN_H = gb.display.height(),
          MENU_W = 2, //menu width (in units)
          GAME_W = 8, //game width and height (in units)
          GAME_H = 8;
//colors
const Color CURSOR_COLOR = WHITE, //cursor color
            MINES_COLOR = RED,  //mines color
            BLOCK_COLOR = BEIGE, //unrevealed blocks color
            HELPER_COLOR = WHITE,  //helpers color (should match block colors)
            MENU_COLOR = BEIGE,
            PLAYGROUND_COLOR = BROWN;

const int NB_MINES[] = {6,8,10,12}; //number of mines
const String difficulties[] = {"EASY","MEDIUM","HARD","CRAZY"};
const Color difficultyColors[] = {GREEN,BLUE,ORANGE,RED};
const int GAMEOVERTIMER = 50;

//Game States
const int GAME_MENU = 1,
          GAME_PLAY = 2,
          GAME_PAUSE = 3,
          GAME_OVER = 4,
          GAME_WIN = 5;


//VARIABLES - DO NOT MODIFY !

int mines[GAME_W][GAME_H];
int mask[GAME_W][GAME_W];

int cursorX,
    cursorY,
    ledTimer = 0;

int menuSelection = 0,
    difficulty = 0;

int gameTime = 0;
int bestTime = 14566;

int SFX = 0;

bool gameOver = false;
int gameOverTimer = GAMEOVERTIMER;

int GAME_STATE = GAME_MENU;
