#include "Machine.h"

class Mobile: public Machine{
public:
  Mobile(double xo, double yo){

      machine_body.setSize(sf::Vector2f(50,50));
      machine_body.setPosition(0,0);
      machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
      machine_body.setFillColor(sf::Color::Magenta);

      x = xo; y = yo;

      machine_body.setPosition(xo, yo);

  }

  void rotate(double dTheta){
    theta += dTheta;
  }
  double getTheta(){
    return theta;
  }
  void setBody(b2Body& bod){
    body = &bod;
  }

  void setWorld(b2World& World);


  // define how this machine can move (can set limitations)
  void Update(){
      // move up

      // if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      //     if(machine_body.getPosition().y > 0) {
      //         machine_body.move(0, -1);
      //
      //         // if you have a box, move it as well
      //
      //     }
      // }

      // move left
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(machine_body.getPosition().x < 750) {  // check
            // machine_body.move(1, 0);
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = -5;
            body->SetLinearVelocity( vel );
        }
      }
      // // move down
      // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      //     if(machine_body.getPosition().y < 550) {  // check
      //         machine_body.move(0, 1);
      //
      //
      //     }
      // }
      // move right
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(machine_body.getPosition().x < 750) {  // check
            // machine_body.move(1, 0);
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );
      }
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      body->SetLinearVelocity(b2Vec2(0,0));
    }
  }

  void getOut(){
    // b2Vec2 vel = body->GetLinearVelocity();
    // vel.x = 0;
    // vel.y = -1;
    // body->SetLinearVelocity(vel);
    printf("getting out\n");
    body->SetGravityScale(1);
    body->SetLinearVelocity(b2Vec2(0,1));
  }

private:
  double theta;
};
