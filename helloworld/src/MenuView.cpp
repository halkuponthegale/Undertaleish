#include "MenuView.h"
#include "LvlSelectView.h"

void MenuView::Init(sf::RenderWindow *window){
	// selected option
	cur_select = 1;
	intro_return = 1;

	// load font
	font.loadFromFile("../include/Fonts/ComicSans.ttf");

	// create texts
	title.setFont(font);
	play.setFont(font);
	exit.setFont(font);

	title.setCharacterSize(80);
	play.setCharacterSize(40);
	exit.setCharacterSize(40);


	title.setString("Detention");
	play.setString("Play");
	exit.setString("Exit");

	sf::FloatRect title_bounds = title.getLocalBounds();
	sf::FloatRect play_bounds = play.getLocalBounds();
	sf::FloatRect exit_bounds = exit.getLocalBounds();

	title.setOrigin(title_bounds.width / 2, title_bounds.height / 2);
	play.setOrigin(play_bounds.width / 2, play_bounds.height / 2);
	exit.setOrigin(exit_bounds.width / 2, exit_bounds.height / 2);

	title.setPosition(window -> getSize().x / 2, window -> getSize().y / 3);
	play.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + play_bounds.height);
	exit.setPosition(window -> getSize().x / 2, window -> getSize().y / 2 + play_bounds.height * 2.5);


}

void MenuView::Update(sf::RenderWindow *window){

	// handle navigation between menu options
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && cur_select == 1){
		cur_select++;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && cur_select == 2){
		cur_select--;
	}

	// handle selected option
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if(intro_return){ return; }

		if(cur_select == 1){
			// level select screen
			game_view.setView(new LvlSelectView());
		}
		else if(cur_select == 2){
			// quit
			window -> close();
		}
	}
	else{
		intro_return = 0;
	}

}

void MenuView::Render(sf::RenderWindow *window){
	// draw all texts with selected option = Blue

	play.setFillColor(sf::Color::White);
	exit.setFillColor(sf::Color::White);

	if(cur_select == 1){
		play.setFillColor(sf::Color::Blue);
	}
	else if(cur_select == 2){
		exit.setFillColor(sf::Color::Blue);
	}


	window -> draw(title);
	window -> draw(play);
	window -> draw(exit);
}