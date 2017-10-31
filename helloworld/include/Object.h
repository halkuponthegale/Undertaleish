#pragma once
#include "Actor.h"
class Object: public Actor{
public:
  Object(double x, double y, int w, int h, bool solid) : Actor(x,y,w,h){
    this->solid = solid;
  }
  void interact(){

  }
  bool isSolid(){
    return solid;
  }
private:
  bool solid;
};
