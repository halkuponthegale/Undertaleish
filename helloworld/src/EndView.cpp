#include "EndView.h"
#include "MenuView.h"
#include "PlayView.h"


void EndView::Init(sf::RenderWindow *window){
	// load font
	font.loadFromFile("../include/Fonts/ComicSans.ttf");

	intro_return = 1;
	cur_select = 1;

	// create tmp text
	tmp.setFont(font);
	tmp2.setFont(font);
	tmp3.setFont(font);

	tmp.setCharacterSize(50);
	tmp2.setCharacterSize(30);
	tmp3.setCharacterSize(30);

	char tmptext[20];
	sprintf(tmptext, "You completed level %d", finished_lvl);
	
	tmp.setString(tmptext);
	tmp2.setString("Main Menu");
	tmp3.setString("Continue");

	sf::FloatRect tmp_bounds = tmp.getLocalBounds();
	sf::FloatRect tmp2_bounds = tmp2.getLocalBounds();
	sf::FloatRect tmp3_bounds = tmp3.getLocalBounds();

	tmp.setOrigin(tmp_bounds.width / 2, tmp_bounds.height / 2);
	tmp2.setOrigin(tmp2_bounds.width / 2, tmp2_bounds.height / 2);
	tmp3.setOrigin(tmp3_bounds.width / 2, tmp3_bounds.height / 2);

	tmp.setPosition(window -> getSize().x / 2, window -> getSize().y / 3);
	tmp2.setPosition(window -> getSize().x / 2, window -> getSize().y / 2);
	tmp3.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + tmp2_bounds.height * 2);

}


void EndView::Update(sf::RenderWindow *window){

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && cur_select == 1){
		cur_select++;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && cur_select == 2){
		cur_select--;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if(intro_return){ return; }

		if(cur_select == 1){
			// play screen
			game_view.setView(new MenuView());
		}
		else if(cur_select == 2){
			// back to lvl select
			game_view.setView(new PlayView(finished_lvl + 1));
		}
	}
	else{
		intro_return = 0;
	}

}

void EndView::Render(sf::RenderWindow *window){


	tmp2.setFillColor(sf::Color::White);
	tmp3.setFillColor(sf::Color::White);

	if(cur_select == 1){
		tmp2.setFillColor(sf::Color::Blue);
	}
	else if(cur_select == 2){
		tmp3.setFillColor(sf::Color::Blue);
	}


	window -> draw(tmp);
	window -> draw(tmp2);
	window -> draw(tmp3);

}
