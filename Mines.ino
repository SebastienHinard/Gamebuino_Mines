#include <Gamebuino-Meta.h>
#include "_ConstsAndVars.h"

void setup(){
  gb.begin();
}

void loop(){
  while(!gb.update());
  update();
  draw();
}
