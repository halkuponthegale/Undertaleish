#include "PlayView.h"
#include "EndView.h"

void PlayView::Init(sf::RenderWindow *window){
	// load font
	font.loadFromFile("../include/Fonts/Beyblade Metal Fight Font.ttf");

	intro_return = 1;

	// create tmp text
	tmp.setFont(font);
	tmp2.setFont(font);
	tmp3.setFont(font);

	tmp.setCharacterSize(50);
	tmp2.setCharacterSize(30);
	tmp3.setCharacterSize(30);

	char tmptext[16];
	sprintf(tmptext, "Playing Level %d", play_lvl);

	tmp.setString(tmptext);
	tmp2.setString("Press Return to go to finish (win level)");
	tmp3.setString("Press Escape to quit game");

	sf::FloatRect tmp_bounds = tmp.getLocalBounds();
	sf::FloatRect tmp2_bounds = tmp2.getLocalBounds();
	sf::FloatRect tmp3_bounds = tmp3.getLocalBounds();

	tmp.setOrigin(tmp_bounds.width / 2, tmp_bounds.height / 2);
	tmp2.setOrigin(tmp2_bounds.width / 2, tmp2_bounds.height / 2);
	tmp3.setOrigin(tmp3_bounds.width / 2, tmp3_bounds.height / 2);

	tmp.setPosition(window -> getSize().x / 2, window -> getSize().y / 3);
	tmp2.setPosition(window -> getSize().x / 2, window -> getSize().y / 2);
	tmp3.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + 30);


	// Construct a world object, which will hold and simulate the rigid bodies.
	window->setFramerateLimit(60);

	// load background sprite
	if(!Bkg.loadFromFile("../include/Textures/brick.jpg"));
	Bkg.setRepeated(true);
	bgSprite.setTexture(Bkg);
	bgSprite.setTextureRect(sf::IntRect(0,0,800,600));

	// push builders onto vector
	if(!builders_list.empty()){
		int z;
		for(z = 0; z < builders_list.size(); z++){
			vec.push_back(&(*builders_list[z]));
			ty.push_back(0);
		}
	}

	// push launchers onto vector
	if(!launchers_list.empty()){
		int z;
		for(z = 0; z < launchers_list.size(); z++){
			vec.push_back(&(*launchers_list[z]));
			ty.push_back(1);
		}
	}

	// push mobiles onto vector
	if(!mobiles_list.empty()){
		int z;
		for(z = 0; z < mobiles_list.size(); z++){
			vec.push_back(&(*mobiles_list[z]));
			ty.push_back(2);
		}
	}

}

void PlayView::Update(sf::RenderWindow *window){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if(intro_return){ return; }

		// increase top level if completed level is top level
		if(play_lvl == top_lvl && top_lvl < MAX_LVL){
			top_lvl++;
		}

		game_view.setView(new EndView(play_lvl));
	}
	else{
		intro_return = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
		window -> close();
	}

	// if last level, check if two player bodies are touching
	// if so, end level
	if(players_list.size() > 1){
		if(!(players_list[0] -> inMachine()) && !(players_list[1] -> inMachine()) &&
		   players_list[0] -> getShape().getGlobalBounds().intersects(players_list[1] -> getShape().getGlobalBounds()) ){
			if(play_lvl == top_lvl && top_lvl < MAX_LVL){
				top_lvl++;
			}

			game_view.setView(new EndView(play_lvl));
		}
	}

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			//builder = 0, launcher = 1, mobile = 2;
			if(!players_list.empty()){
				int z;
				for(z = 0; z < players_list.size(); z++){
					if(!(*players_list[z]).inMachine()){
						// if player is at exit, leave
						if(!exits_list.empty() && (*players_list[z]).isAtExit((*exits_list[0]).getShape())){
							if(play_lvl == top_lvl && top_lvl < MAX_LVL){
								top_lvl++;
							}

							game_view.setView(new EndView(play_lvl));
						}
						// otherwise, check if in machine
						else
							 (*players_list[z]).intersects(vec,ty);

					}
				}



			}
  }

	if(!players_list.empty()){
		int z;
		for(z = 0; z < players_list.size(); z++){
			(*players_list[z]).Update();
		}
	}
	world.Step(1/60.f, 8, 3);


}

void PlayView::Render(sf::RenderWindow *window){
	window -> draw(bgSprite);
	window -> draw(tmp);
	window -> draw(tmp2);
	window -> draw(tmp3);

	// draw exit(s)
	if(!exits_list.empty()){
		int z;
		for(z = 0; z < exits_list.size(); z++){
			(*exits_list[z]).bounds.setPosition(SCALE * (*exits_list[z]).getBody()->GetPosition().x, SCALE * (*exits_list[z]).getBody()->GetPosition().y);
			(*exits_list[z]).bounds.setRotation((*exits_list[z]).getBody()->GetAngle() * 180/b2_pi);
			window->draw((*exits_list[z]).getShape());
		}
	}



	// draw walls
	if(!walls_list.empty()){
		int z;
		for(z = 0; z < walls_list.size(); z++){
			window->draw((*walls_list[z]).getShape());
		}
	}

	// draw boxes
	if(!boxes_list.empty()){
		int j;
		for(j = 0; j < boxes_list.size(); j++){
			(*boxes_list[j]).setPos(SCALE* (*boxes_list[j]).getBody()->GetPosition().x,SCALE*(*boxes_list[j]).getBody()->GetPosition().y);
			window->draw((*boxes_list[j]).getShape());
		}
	}


  // draw launchers
	if(!launchers_list.empty()){
		int z;
		for(z = 0; z < launchers_list.size(); z++){
			(*launchers_list[z]).machine_body.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).machine_body.setRotation((*launchers_list[z]).getBody()->GetAngle() * 180/b2_pi);
			(*launchers_list[z]).barrel.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).barrel.setRotation(90+(-1*( 180.0/3.141592653589793 )*(*launchers_list[z]).getTheta()));
			(*launchers_list[z]).powerBG.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).power.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
				(*launchers_list[z]).power.move(22.5,-25);
				(*launchers_list[z]).powerBG.move(22.5,-25);
			window->draw((*launchers_list[z]).barrel);
			window->draw((*launchers_list[z]).machine_body);
			window->draw((*launchers_list[z]).powerBG);
			window->draw((*launchers_list[z]).power);
		}
	}

	// draw builders
	if(!builders_list.empty()){
		int z;
		for(z = 0; z < builders_list.size(); z++){
			(*builders_list[z]).machine_body.setPosition(SCALE * (*builders_list[z]).getBody()->GetPosition().x, SCALE *  (*builders_list[z]).getBody()->GetPosition().y);
			(*builders_list[z]).machine_body.setRotation( (*builders_list[z]).getBody()->GetAngle() * 180/b2_pi);
			window->draw((*builders_list[z]).machine_body);
		}
	}

	// draw mobiles
	if(!mobiles_list.empty()){
		int z;
		for(z = 0; z < mobiles_list.size(); z++){
			(*mobiles_list[z]).machine_body.setPosition(SCALE * (*mobiles_list[z]).getBody()->GetPosition().x, SCALE * (*mobiles_list[z]).getBody()->GetPosition().y);
			(*mobiles_list[z]).machine_body.setRotation((*mobiles_list[z]).getBody()->GetAngle() * 180/b2_pi);
			window->draw((*mobiles_list[z]).machine_body);
		}
	}


	// draw plauers
	if(!players_list.empty()){
		int z;
		for(z = 0; z < players_list.size(); z++){
			(*players_list[z]).playerbody.setPosition(SCALE * (*players_list[z]).getBody()->GetPosition().x, SCALE * (*players_list[z]).getBody()->GetPosition().y);
			(*players_list[z]).playerbody.setRotation((*players_list[z]).getBody()->GetAngle() * 180/b2_pi);
			if(!(*players_list[z]).inMachine())
				window->draw((*players_list[z]).playerbody);
		}
	}
	//
	// // draw player
	// (*player).playerbody.setPosition(SCALE * (*player).getBody()->GetPosition().x, SCALE * (*player).getBody()->GetPosition().y);
	// (*player).playerbody.setRotation((*player).getBody()->GetAngle() * 180/b2_pi);
	// if(!(*player).inMachine())
	// 	window->draw((*player).playerbody);

}
