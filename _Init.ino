void initLevel(){
  gameTime = 0;
  gameOver = false;
  gameOverTimer = GAMEOVERTIMER;
  cursorX=0;
  cursorY=0;
  //mask init
  for(int x=0; x<GAME_W; x++){
    for (int y=0; y<GAME_H; y++){
      mask[x][y]=1;
    }
  }
  //clear mines
  for(int x=0; x<GAME_W; x++){
    for(int y=0; y<GAME_H; y++){
      mines[x][y]=0;
    }
  }
  //add mines
  int added_mines = 0;
  while (added_mines < NB_MINES[difficulty]){
    int x = random(GAME_W);
    int y = random(GAME_H);
    if(mines[x][y] == 0){
      mines[x][y] = 10;
      added_mines ++;
    }
  }
  //add helpers
  for(int x=0; x<GAME_W; x++){
    for(int y=0; y<GAME_H; y++){
      if(mines[x][y]==0){
        int helper = 0;
        helper = (mines[x-1][y]==10 && x>0) ? helper+1 : helper ;
        helper = (mines[x-1][y-1]==10 && x>0 && y>0) ? helper+1 : helper ;
        helper = (mines[x][y-1]==10 && y>0) ? helper+1 : helper ;
        helper = (mines[x+1][y-1]==10 && x<GAME_W-1 && y>0) ? helper+1 : helper ;
        helper = (mines[x+1][y]==10 && x<GAME_W-1) ? helper+1 : helper ;
        helper = (mines[x+1][y+1]==10 && x<GAME_W-1 && y<GAME_H-1) ? helper+1 : helper ;
        helper = (mines[x][y+1]==10 && y<GAME_H-1) ? helper+1 : helper ;
        helper = (mines[x-1][y+1]==10 && x>0 && y<GAME_H-1) ? helper+1 : helper ;
        mines[x][y] = helper;
      }
    }
  }
}
