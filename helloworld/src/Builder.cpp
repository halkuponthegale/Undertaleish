#include "Builder.h"
#include "AudioManager.h"

// constructor
Builder::Builder(double xo, double yo){

    // Load mobile spritesheet from png file (in include folder)
    if(!builderTexture.loadFromFile("../include/sprites/builder.png",sf::IntRect(0, 0, 50, 150)))
    {
    }

    // create machine body rectangle
    machine_body.setSize(sf::Vector2f(50,50));
    machine_body.setOrigin(machine_body.getOrigin().x + 25, machine_body.getOrigin().y + 25);
    machine_body.setPosition(xo, yo);

    builderImage.setTexture(builderTexture);

    // initial x, y pos
    x = xo; y = yo;
    source.x = 0;
    source.y = 0;

    cur_box_idx = 0;
    cur_wall_idx = 0;
    carrybox = 0;

    // Set current sprite
    builderImage.setTextureRect(sf::IntRect(1, source.y*50, 49, 50));
    builderImage.setOrigin(builderImage.getOrigin().x + 25, builderImage.getOrigin().y + 25);

lastVelocity=0;
    active = 0;
}

// define how this machine can move (can set limitations)
void Builder::Update(){
    // W = jump
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && body->GetLinearVelocity().y == 0) {
            jump();
    }
    // A = move left
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
       if(machine_body.getPosition().x > 0) {

          // update velocity
          b2Vec2 vel = body->GetLinearVelocity();
          vel.x = -5;
          body->SetLinearVelocity( vel );

          // facing left
          facing = 0;
       }
    }
    // D = move right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(machine_body.getPosition().x < 800) {
            // update velocity
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 5;
            body->SetLinearVelocity( vel );

            // facing right
            facing = 1;
        }
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
        body->GetLinearVelocity().y == 0){
        body->SetLinearVelocity(b2Vec2(0,0));
    }

    // if you're carrying a box, move it too
    if(carrybox){
      mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 51)/30.0),0);
    }

    // Space = pick up/set down Box
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        int intersect = 0;
        int i;

        // loop through boxes until find one that is touching and on same y level
        for(i = 0; i < cur_box_idx; i++){
            if(intersects(boxlist[i]) &&  (boxlist[i] -> getBody()->GetPosition().y < (body ->GetPosition().y + 1))
                                      &&  (boxlist[i] -> getBody()->GetPosition().y > (body ->GetPosition().y - 1))){
                intersect = 1;
                break;
            }
        }

        // if you're carrying a box, not jumping, and it's not the initial space press, set it down in the direction you're facing
        if(carrybox && body->GetLinearVelocity().y == 0 && !space){
            // if facing left, place left
            if(facing == 0){
                // test to see if potential collision, if so, don't place
                sf::RectangleShape test;
                test.setSize(sf::Vector2f(50,50));
                test.setOrigin(test.getOrigin().x + 25, test.getOrigin().y + 25);
                test.setPosition(sf::Vector2f((machine_body.getPosition().x - 51), machine_body.getPosition().y - 5));
                // check out of bounds
                if (test.getPosition().x < 0 ){
                  AudioManager::play_buzz();
                      return;
                }
                // check box collisions
                for(int j = 0; j < cur_box_idx; j++){
                  if (test.getGlobalBounds().intersects(boxlist[j] -> getShape().getGlobalBounds())){
                      AudioManager::play_buzz();
                      return;
                    }
                }
                // check wall collisions
                for(int j = 0; j < cur_wall_idx; j++){
                  if (test.getGlobalBounds().intersects(walllist[j] -> getShape().getGlobalBounds())){
                      AudioManager::play_buzz();
                      return;
                    }
                }
                mybox->getBody()->SetTransform(b2Vec2((machine_body.getPosition().x - 51)/30.0, (2 + machine_body.getPosition().y)/30.0),0);
                mybox->getBody()->SetGravityScale(1);
                mybox->getBody()->SetLinearVelocity(b2Vec2(0,1));
                AudioManager::play_builder_box();
            }
            // if facing right, place right
            else{
                // test to see if potential collision, if so, don't place
                sf::RectangleShape test;
                test.setSize(sf::Vector2f(50,50));
                test.setOrigin(test.getOrigin().x + 25, test.getOrigin().y + 25);
                test.setPosition(sf::Vector2f((machine_body.getPosition().x + 51), machine_body.getPosition().y - 5));
                // check out of bounds
                if (test.getPosition().x > 800){
                  AudioManager::play_buzz();
                      return;
                }
                // check box collisions
                for(int j = 0; j < cur_box_idx; j++){
                  if (test.getGlobalBounds().intersects(boxlist[j] -> getShape().getGlobalBounds())){
                    AudioManager::play_buzz();
                    return;
                  }

                }
                // check wall collisions
                for(int j = 0; j < cur_wall_idx; j++){
                  if (test.getGlobalBounds().intersects(walllist[j] -> getShape().getGlobalBounds())){
                      AudioManager::play_buzz();
                      return;
                  }
                }
                mybox->getBody()->SetTransform(b2Vec2((machine_body.getPosition().x + 51)/30.0, (2 + machine_body.getPosition().y)/30.0),0);
                mybox->getBody()->SetGravityScale(1);
                mybox->getBody()->SetLinearVelocity(b2Vec2(0,1));
                AudioManager::play_builder_box();
            }

            // no longer carrying a box
            carrybox = 0;
        }
        // if you aren't carrying a box and you're intersecting one, pick it up
        else if(intersect && body->GetLinearVelocity().y == 0 && !space){
            // test to see if box on top, if so, don't pick up
            sf::RectangleShape test;
            test.setSize(sf::Vector2f(50,50));
            test.setOrigin(test.getOrigin().x + 25, test.getOrigin().y + 25);
            test.setPosition(sf::Vector2f((boxlist[i] -> getShape().getPosition().x), boxlist[i] ->getShape().getPosition().y - 50));
            // check box collisions
            for(int j = 0; j < cur_box_idx; j++){
              if (test.getGlobalBounds().intersects(boxlist[j] -> getShape().getGlobalBounds())){
                  AudioManager::play_buzz();
                  return;
                }
            }

            mybox = boxlist[i];
            mybox->getBody()->SetTransform(b2Vec2(machine_body.getPosition().x / 30.0, (machine_body.getPosition().y - 51)/30.0),0);
            mybox->getBody()->SetGravityScale(0);
            carrybox = 1;
            AudioManager::play_builder_box();

        }
        space = 1;

    }
    else{
        space = 0;
    }

    
     // Set variables for spritesheet
     // If active and carrying a box, choose sprite with arms up
      if (active){
      if(carrybox){
        source.y = 1;
      }
      else{ // If active and no box, choose sprite with player inside
      source.y = 2;
      }
    }
    else if (active == false) { // If inactive, choose sprite with empty machine
      source.y = 0;
    }
    // Set correct sprite to be drawn
    builderImage.setTextureRect(sf::IntRect(1, source.y*50, 49, 50));
}


void Builder::jump(){
  machine_body.move(0, -1);

  double velocity = 180;
  double theta = M_PI/2;

  b2Vec2 vel = body->GetLinearVelocity();
  double vx = cos(theta)* velocity;
  double vy = sin(theta)* velocity;
  double impx = (vel.x)*body->GetMass();
  double impy = (vel.y)*body->GetMass();

  body->ApplyLinearImpulse( b2Vec2(vx, -vy), body->GetWorldCenter(), true );
}


void Builder::setWorld(b2World& World){
  static const float SCALE = 30.f;

  b2BodyDef BodyDef2;
  BodyDef2.position = b2Vec2(x/SCALE, y/SCALE);
  BodyDef2.type = b2_dynamicBody;
  body = World.CreateBody(&BodyDef2);

  b2PolygonShape Shape2;
  Shape2.SetAsBox((50.f/2)/SCALE, (49.f/2)/SCALE);
  b2FixtureDef FixtureDef2;
  FixtureDef2.density = 10.f;
  FixtureDef2.friction = 1;
  FixtureDef2.shape = &Shape2;
  FixtureDef2.filter.maskBits = ~0x0002;
  FixtureDef2.filter.categoryBits = ~0x0007;
  FixtureDef2.filter.groupIndex = -2;

  body->CreateFixture(&FixtureDef2);
  body->SetFixedRotation(true);

}
