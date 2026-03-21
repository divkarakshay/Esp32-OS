int byy, vel, pipeX, gapY, fscore;
bool fOver;

void initFlappy(){
  byy=30; vel=0; pipeX=128; gapY=random(10,40);
  fscore=0; fOver=false;
}

void updateFlappy(){
  if(fOver) return;

  if(digitalRead(BTN_SELECT)==LOW) vel=-6;

  vel+=1; byy+=vel;
  pipeX-=3;

  if(pipeX<0){ pipeX=128; gapY=random(10,40); fscore++; }

  if(byy<10||byy>63) fOver=true;
}

void drawFlappy(){
  display.fillCircle(10,byy,3,WHITE);
  display.fillRect(pipeX,10,10,gapY,WHITE);
  display.fillRect(pipeX,gapY+20,10,64,WHITE);

  display.setCursor(0,0);
  display.print(fscore);
}