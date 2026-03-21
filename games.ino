int currentGame=0;

void startGame(int g){
  currentGame=g;
  if(g==0) initSnake();
  if(g==1) initPong();
  if(g==2) initFlappy();
}

void runGame(){
  display.clearDisplay();

  if(currentGame==0){updateSnake();drawSnake();}
  if(currentGame==1){updatePong();drawPong();}
  if(currentGame==2){updateFlappy();drawFlappy();}

  display.display();
}