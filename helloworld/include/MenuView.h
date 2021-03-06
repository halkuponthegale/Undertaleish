#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "GameView.h"

/*
	MenuView handles the text and selection in the main menu
	Also handles transition to LvlSelectView
*/

class MenuView : public MiniView{
	public:
		void Init(sf::RenderWindow *window);
		void Update(sf::RenderWindow *window);
		void Render(sf::RenderWindow *window);
		~MenuView(){
			title.setString("");
			play.setString("");
			exit.setString("");
		}
	private:
		sf::Font font;

		sf::Text title;
		sf::Text play;
		sf::Text exit;

		int cur_select;
		int intro_return;

};

#endif
