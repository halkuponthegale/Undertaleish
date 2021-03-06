#include "PlayView.h"
#include "EndView.h"
#include "AudioManager.h"
#include "gameLogic.h"
#include <sys/time.h> // for clock_gettime()

// Play view handles views during level play

void PlayView::Init(sf::RenderWindow *window){
	
	// load font
	font.loadFromFile("../include/Fonts/Beyblade Metal Fight Font.ttf");

	intro_return = 1;

	// create text (font, color, position, origin, bounds) for level info
	tmp.setFont(font);
	tmp2.setFont(font);
	tmp3.setFont(font);

	tmp.setCharacterSize(20);
	tmp2.setCharacterSize(25);
	tmp3.setCharacterSize(30);

	char tmptext[10];
	sprintf(tmptext, "Level %d", play_lvl);

	tmp.setString(tmptext);
	tmp2.setString("(R)eset level");
	tmp3.setString("Press Escape to quit game");

	sf::FloatRect tmp_bounds = tmp.getLocalBounds();
	sf::FloatRect tmp2_bounds = tmp2.getLocalBounds();
	sf::FloatRect tmp3_bounds = tmp3.getLocalBounds();

	tmp.setOrigin(tmp_bounds.width / 2, tmp_bounds.height / 2);
	tmp2.setOrigin(tmp2_bounds.width / 2, tmp2_bounds.height / 2);
	tmp3.setOrigin(tmp3_bounds.width / 2, tmp3_bounds.height / 2);

	tmp.setPosition(14 * window -> getSize().x / 15, window -> getSize().y / 20);
	tmp2.setPosition(window -> getSize().x - 100, window -> getSize().y - 30);
	tmp3.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + 35);


	// Construct a world object, which will hold and simulate the rigid bodies.
	window->setFramerateLimit(60);

	// load background sprite
	if(!Bkg.loadFromFile("../include/Textures/brick2.jpg")){;}
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
		int status = GameLogic::update(boxes_list, builders_list, mobiles_list, launchers_list, walls_list, players_list, exits_list, play_lvl, top_lvl, &game_view, &ty, &vec, intro_return);
		if(status==-1)
			window->close();
		else if(status ==1)
			world.Step(1/60.f, 8, 3);
}


// Draw level (text, exits, walls, boxes, machines, and players)
void PlayView::Render(sf::RenderWindow *window){

	tmp.setFillColor(sf::Color::Black);
	tmp2.setFillColor(sf::Color::Black);

	window -> draw(bgSprite);

	if(!textures_list.empty()){
		int z;
		for(z = 0; z < textures_list.size(); z++){
			window->draw((*textures_list[z]).getShape());
		}
	}

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
			(*launchers_list[z]).dome.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).barrel.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).barrel.setRotation(90+(-1*( 180.0/3.141592653589793 )*(*launchers_list[z]).getTheta()));
			(*launchers_list[z]).powerBG.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).power.setPosition(SCALE * (*launchers_list[z]).getBody()->GetPosition().x, SCALE * (*launchers_list[z]).getBody()->GetPosition().y);
			(*launchers_list[z]).power.move(22.5,-25);
			(*launchers_list[z]).powerBG.move(22.5,-25)
			;
			window->draw((*launchers_list[z]).barrel);
			window->draw((*launchers_list[z]).dome);
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
			(*builders_list[z]).builderImage.setPosition(SCALE * (*builders_list[z]).getBody()->GetPosition().x, SCALE *  (*builders_list[z]).getBody()->GetPosition().y);
			(*builders_list[z]).builderImage.setRotation( (*builders_list[z]).getBody()->GetAngle() * 180/b2_pi);
			window->draw((*builders_list[z]).builderImage);
		}
	}

	// draw mobiles
	if(!mobiles_list.empty()){
		int z;
		for(z = 0; z < mobiles_list.size(); z++){
			(*mobiles_list[z]).mobileImage.setPosition(SCALE * (*mobiles_list[z]).getBody()->GetPosition().x, SCALE * (*mobiles_list[z]).getBody()->GetPosition().y);
			(*mobiles_list[z]).mobileImage.setRotation((*mobiles_list[z]).getBody()->GetAngle() * 180/b2_pi);
			(*mobiles_list[z]).machine_body.setPosition(SCALE * (*mobiles_list[z]).getBody()->GetPosition().x, SCALE * (*mobiles_list[z]).getBody()->GetPosition().y);
			(*mobiles_list[z]).machine_body.setRotation((*mobiles_list[z]).getBody()->GetAngle() * 180/b2_pi);
			window->draw((*mobiles_list[z]).mobileImage);
		}
	}


	// draw players
	if(!players_list.empty()){
		int z;
		for(z = 0; z < players_list.size(); z++){
			(*players_list[z]).playerImage.setPosition(SCALE * (*players_list[z]).getBody()->GetPosition().x, SCALE * (*players_list[z]).getBody()->GetPosition().y);
			(*players_list[z]).playerImage.setRotation((*players_list[z]).getBody()->GetAngle() * 180/b2_pi);
			if(!(*players_list[z]).inMachine())
				window->draw((*players_list[z]).playerImage);
		}
	}

	window -> draw(tmp);
	window -> draw(tmp2);


}
