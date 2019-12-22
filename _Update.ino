void update(){
  switch(GAME_STATE){
    case GAME_MENU:
      update_menu();
      break;
    case GAME_PLAY:
      update_game();
      break;
    case GAME_PAUSE:
      update_pause();
      break;
    case GAME_OVER:
      update_gameOver();
      break;
    case GAME_WIN:
      update_win();
      break;
  }
  SFX ++;
}


void update_game(){
  if (gameOver){
    gameOverTimer--;
    if (gameOverTimer<0){
      GAME_STATE = GAME_OVER;
    }
    return;
  }
  //update cursor position
  if (gb.buttons.repeat(BUTTON_RIGHT,4)){
    cursorX = cursorX+1<GAME_W-1 ? cursorX+1 : GAME_W-1;
  }else if(gb.buttons.repeat(BUTTON_LEFT,4)){
    cursorX = cursorX>0 ? cursorX-1 : 0;
  }else if(gb.buttons.repeat(BUTTON_DOWN,4)){
    cursorY = cursorY+1<GAME_H-1 ? cursorY+1 : GAME_H-1;
  }else if(gb.buttons.repeat(BUTTON_UP,4)){
    cursorY = cursorY>0 ? cursorY-1 : 0;
  }
  //on A button press
  if(gb.buttons.pressed(BUTTON_A) && mask[cursorX][cursorY]==1 ){
    mask[cursorX][cursorY]=0;
    if(mines[cursorX][cursorY] == 10){
      gameOver = true;
      gb.sound.playCancel();
    }else{
      gb.lights.fill(WHITE);
      ledTimer=2;
      if(mines[cursorX][cursorY] == 0){
        revealEmpty(cursorX,cursorY);
      }
      gb.sound.playTick();
      if (allMinesWereFound()){
        GAME_STATE = GAME_WIN;
        if(gameTime<bestTime){
          bestTime=gameTime;
          //gb.save.set(0,bestTime);
        }
      }
    }
  }
  //on B button press
  if(gb.buttons.pressed(BUTTON_B) && mask[cursorX][cursorY]!=0){
    mask[cursorX][cursorY] = mask[cursorX][cursorY] == 1 ? 2 : 1;
  }
  //on MENU button press
  if(gb.buttons.pressed(BUTTON_MENU)){
    GAME_STATE = GAME_PAUSE;
  }

  gameTime ++;
}

void update_menu(){
  if(gb.buttons.pressed(BUTTON_UP) || gb.buttons.pressed(BUTTON_DOWN) ){
    menuSelection = menuSelection == 0 ? 1 : 0;
    gb.sound.playTick();
  }
  //on A button press
  if(gb.buttons.pressed(BUTTON_A)){
    switch (menuSelection) {
      case 0:
        GAME_STATE = GAME_PLAY;
        initLevel();
        menuSelection=0;
        break;
      case 1:
        difficulty = difficulty<3 ? difficulty+1 : 0;
        break;
    }
  }
}

void update_pause(){
  if(gb.buttons.pressed(BUTTON_UP)){
    menuSelection = menuSelection>0 ? menuSelection-1 : 2;
    gb.sound.playTick();
  }else if(gb.buttons.pressed(BUTTON_DOWN)){
    menuSelection = menuSelection<2 ? menuSelection+1 : 0;
    gb.sound.playTick();
  }
  //on MENU button press
  if(gb.buttons.pressed(BUTTON_MENU)){
    GAME_STATE = GAME_PLAY;
    menuSelection = 0;
  //on A button press
  }else if(gb.buttons.pressed(BUTTON_A)){
    switch (menuSelection) {
      case 0:
        GAME_STATE = GAME_PLAY;
        break;
      case 1:
        GAME_STATE = GAME_PLAY;
        initLevel();
        break;
      case 2:
        GAME_STATE = GAME_MENU;
        break;
    }
    menuSelection = 0;
  }
}

void update_gameOver(){
  if(gb.buttons.pressed(BUTTON_UP) || gb.buttons.pressed(BUTTON_DOWN) ){
    menuSelection = menuSelection== 0 ? 1 : 0;
  }
  //on A button press
  if(gb.buttons.pressed(BUTTON_A)){
    switch (menuSelection) {
      case 0:
        GAME_STATE = GAME_PLAY;
        initLevel();
        break;
      case 1:
        GAME_STATE = GAME_MENU;
        break;
    }
    menuSelection=0;
  }
}

void update_win(){
  if(gb.buttons.pressed(BUTTON_UP) || gb.buttons.pressed(BUTTON_DOWN) ){
    menuSelection = menuSelection== 0 ? 1 : 0;
  }
  //on A button press
  if(gb.buttons.pressed(BUTTON_A)){
    switch (menuSelection) {
      case 0:
        GAME_STATE = GAME_PLAY;
        initLevel();
        break;
      case 1:
        GAME_STATE = GAME_MENU;
        break;
    }
    menuSelection=0;
  }
}

//reveals empty spaces
void revealEmpty(int x,int y){
  if(x-1 >= 0 && mines[x-1][y] == 0 && mask[x-1][y] == 1){
    mask[x-1][y] = 0;
    revealEmpty(x-1,y);
  }
  if(x+1 < GAME_W && mines[x+1][y] == 0 && mask[x+1][y] == 1){
    mask[x+1][y] = 0;
    revealEmpty(x+1,y);
  }
  if(y-1 >= 0 && mines[x][y-1] == 0 && mask[x][y-1] == 1){
    mask[x][y-1] = 0;
    revealEmpty(x,y-1);
  }
  if(y+1 < GAME_W && mines[x][y+1] == 0 && mask[x][y+1] == 1){
    mask[x][y+1] = 0;
    revealEmpty(x,y+1);
  }
}

bool allMinesWereFound(){
  int remainingMasks = 0;
  for(int x=0; x<GAME_W; x++){
    for(int y=0; y<GAME_H; y++){
      remainingMasks = (mask[x][y] > 0) ? remainingMasks+1 : remainingMasks;
    }
  }
  SerialUSB.print(remainingMasks);
  return (remainingMasks == NB_MINES[difficulty]);
}
