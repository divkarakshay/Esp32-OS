int py=20, bx=64, by=32, dxp=1, dyp=1;

void initPong(){}

void updatePong() {
  int y=analogRead(VRY_PIN);
  if(y<1000) py-=3;
  if(y>3000) py+=3;

  bx+=dxp; by+=dyp;

  if(by<=10||by>=63) dyp*=-1;
  if(bx<=5 && by>=py && by<=py+15) dxp*=-1;
}

void drawPong() {
  display.fillRect(0,py,3,15,WHITE);
  display.fillRect(bx,by,3,3,WHITE);
}