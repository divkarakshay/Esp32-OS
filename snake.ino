#define GRID 8
int sx[50], sy[50];
int len, fx, fy, dx, dy;
bool gameOver;
int score;

void initSnake() {
  len = 3;
  sx[0]=5; sy[0]=5;
  dx=1; dy=0;
  score=0;
  gameOver=false;
  fx=random(0,16); fy=random(0,8);
}

void updateSnake() {
  if (gameOver) return;

  for(int i=len;i>0;i--){ sx[i]=sx[i-1]; sy[i]=sy[i-1]; }

  sx[0]+=dx; sy[0]+=dy;

  if(sx[0]<0||sx[0]>=16||sy[0]<0||sy[0]>=8){
    gameOver=true;
    playGameOverSound();
    saveGame(0, score);

    if(score > highScore){
      highScore = score;
      prefs.putInt("high", highScore);
    }
  }

  if(sx[0]==fx && sy[0]==fy){
    len++; score++;
    playEatSound();
    fx=random(0,16); fy=random(0,8);
  }
}

void drawSnake() {
  for(int i=0;i<len;i++)
    display.fillRect(sx[i]*GRID, sy[i]*GRID+10, GRID, GRID, WHITE);

  display.drawRect(fx*GRID, fy*GRID+10, GRID, GRID, WHITE);

  display.setCursor(0,0);
  display.print("S:");
  display.print(score);
  display.print(" H:");
  display.print(highScore);
}