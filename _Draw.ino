void draw(){
  switch(GAME_STATE){
    case GAME_MENU:
      clearScreenAndLight();
      drawMenu();
      break;
    case GAME_PLAY:
      clearScreenAndLight();
      drawGrid();
      drawTilesAndMask();
      drawCursor();
      drawUI();
      break;
    case GAME_PAUSE:
      clearScreenAndLight();
      drawPause();
      break;
    case GAME_OVER:
      clearScreenAndLight();
      drawGameOver();
      break;
    case GAME_WIN:
      clearScreenAndLight();
      drawGrid();
      drawTilesAndMask();
      drawUI();
      drawWin();
      break;
  }

}

void clearScreenAndLight(){
  gb.display.clear();
  if( ledTimer<1 ){
    gb.lights.clear();
  } else {
    ledTimer--;
  }
}

void drawMenu(){
  gb.display.setColor(DARKBLUE);
  gb.display.fillRect(0,15,80,16);
  printXY(22,18,"MINES",WHITE,2);
  printXY(30,32,"start",WHITE,1);
  printXY(30,40,"level",WHITE,1);
  printXY(40,49,difficulties[difficulty],difficultyColors[difficulty],1);
  drawMenuCursor(22,32+menuSelection*8);
}

void drawWin(){
  gb.display.setColor(BLACK);
  gb.display.fillRect(11,13,59,36);
  printXY(13,16,"YOU WIN",GREEN,2);
  printXY(13,18,"YOU WIN",WHITE,2);
  printXY(30,32,"restart",WHITE,1);
  printXY(30,40,"quit",WHITE,1);
  drawMenuCursor(22,32+menuSelection*8);
}

void drawPause(){
  printXY(22,18,"PAUSE",WHITE,2);
  printXY(30,32,"continue",WHITE,1);
  printXY(30,40,"restart",WHITE,1);
  printXY(30,48,"quit",WHITE,1);
  drawMenuCursor(22,32+menuSelection*8);
}

void drawGameOver(){
  printXY(24,16,"GAME",RED,2);
  printXY(24,28,"OVER",RED,2);
  printXY(24,18,"GAME",WHITE,2);
  printXY(24,30,"OVER",WHITE,2);
  printXY(28,44,"restart",WHITE,1);
  printXY(28,52,"quit",WHITE,1);
  drawMenuCursor(20,44+menuSelection*8);
  gb.lights.fill(RED);
}

void drawGrid(){
  gb.display.setColor(PLAYGROUND_COLOR);
  gb.display.fillRect(MENU_W*UNIT,0,GAME_W*UNIT,GAME_H*UNIT);
}

void drawTilesAndMask(){
  for (int x=0; x<GAME_W; x++){
    for (int y=0; y<GAME_H; y++){
      if(mask[x][y] != 0){
        gb.display.setColor(BLACK);
        gb.display.drawRect(MENU_W*UNIT+x*UNIT+1,y*UNIT+1,UNIT-2,UNIT-2);
        gb.display.setColor(BLOCK_COLOR);
        gb.display.fillRect(MENU_W*UNIT+x*UNIT+1,y*UNIT+1,UNIT-3,UNIT-3);
        if(mask[x][y] == 2){
          printXY(MENU_W*UNIT+x*UNIT+2,y*UNIT+1,"X",HELPER_COLOR,1);
        }
      }else{
        if(mines[x][y]==10){
          gb.display.setColor(BLACK);
          gb.display.drawRect(MENU_W*UNIT+x*UNIT+2,y*UNIT+2,UNIT-4,UNIT-4);
          gb.display.setColor(MINES_COLOR);
          gb.display.fillRect(MENU_W*UNIT+x*UNIT+2,y*UNIT+2,UNIT-5,UNIT-5);
        }else if(mines[x][y]!=0){
          printXY(MENU_W*UNIT+x*UNIT+2,y*UNIT+1,(String)mines[x][y],WHITE,1);
        }
      }
    }
  }
}

void drawCursor(){
  gameOver ? gb.display.setColor(RED) : gb.display.setColor(CURSOR_COLOR);
  gb.display.drawRect(MENU_W*UNIT+cursorX*UNIT,cursorY*UNIT,UNIT,UNIT);
}

void drawMenuCursor(int x, int y){
  gb.display.setColor(WHITE);
  gb.display.drawTriangle(x, y, x +4, y+2, x, y+4);
}

void drawUI(){
  if(gameOver){
    gb.lights.fill(RED);
  }
  gb.display.setColor(MENU_COLOR);
  gb.display.fillRect(0,0,MENU_W*UNIT,GAME_H*UNIT);
  //actual time
  int minutes = gameTime/25/60;
  int seconds = gameTime/25 - minutes*60;
  String sMinutes = minutes < 10 ? "0"+(String)minutes : minutes;
  String sSeconds = seconds < 10 ? "0"+(String)seconds : seconds;
  printXY(1,2,"MIN",PLAYGROUND_COLOR,1);
  printXY(1,8,sMinutes,BLACK,2);
  printXY(1,9,sMinutes,PLAYGROUND_COLOR,2);
  printXY(1,20,"SEC",PLAYGROUND_COLOR,1);
  printXY(1,26,sSeconds,BLACK,2);
  printXY(1,27,sSeconds,PLAYGROUND_COLOR,2);
  //best time
  minutes = bestTime/25/60;
  seconds = bestTime/25 - minutes*60;
  sMinutes = (String)minutes;
  sSeconds = seconds < 10 ? "0"+(String)seconds : seconds;
  printXY(0,42,"Best",PLAYGROUND_COLOR,1);
  printXY(0,48,sMinutes+":"+sSeconds,PLAYGROUND_COLOR,1);
  //nb of mines
  gb.display.setColor(BLACK);
  gb.display.drawRect(2,58,4,4);
  gb.display.setColor(MINES_COLOR);
  gb.display.fillRect(3,59,3,3);
  String nbMines = NB_MINES[difficulty]<10 ? "0"+(String)NB_MINES[difficulty] : (String)NB_MINES[difficulty];
  printXY(7,57,nbMines,WHITE,1);
}

void printXY(int x,int y, String text, Color color, int size){
  gb.display.setColor(color);
  gb.display.setCursor(x,y);
  gb.display.setFontSize(size);
  gb.display.print(text);
}
