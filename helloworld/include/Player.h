#ifndef PLAYER_h
#define PLAYER_h

#include <SFML/Graphics.hpp>

class player {

public:

    //Create a simple rectangle, stand in for the player
    sf::RectangleShape playerbody;

    player(); // Constructor


    // Moves the player up
    void player_up();

    // Moves the player down
    void player_down();
    
    // Moves the player left
    void player_left();

    // Moves the player right
    void player_right();

    // Puts player back in original position
    void reset();

};
#endif

