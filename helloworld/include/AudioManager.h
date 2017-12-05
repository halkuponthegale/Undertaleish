#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "GameView.h"
#include <sstream>


class AudioManager{
public:
	static void play_launch(){
		printf("playing launch\n");
		if(!buffer.loadFromFile("../include/Sounds/woohoo.wav")){
			printf("no file\n");
		}


		sound.setBuffer(buffer);
		sound.setVolume(100);
		sound.setPitch(1.4);

		sound.play();

		if(!buffer.loadFromFile("../include/Sounds/cannon.wav")){
			printf("no file\n");
		}


		sound.setBuffer(buffer);
		sound.setVolume(100);
		sound.setPitch(.8);

		sound.play();
	}

// play sound for when
	static void play_builder_box(){
		printf("playing builder\n");
		if(!buffer.loadFromFile("../include/Sounds/builder_box.wav")){
			printf("no sound file\n");
		}


		sound.setBuffer(buffer);
		sound.setVolume(30);
		sound.setPitch(0.8);
		sound.setPlayingOffset(sf::milliseconds(500));

		// sound.setPitch(0.8);
		sound.play();
		// sound.setVolume(1.2);
		// sound.setPitch(1.2);
	}

// play music during the levels
	static void play_level(int level){
		music.stop();
		std::stringstream lvlString;
		lvlString << "../include/Sounds/level" << level << ".wav";
		if(!music.openFromFile(lvlString.str())){
			printf("no sound file\n");
		}
		music.setVolume(60);
		music.setLoop(true);
		music.play();
	}

// play exciting "congratulations!" music
	static void play_end(){
		music.stop();
		if(!buffer.loadFromFile("../include/Sounds/coin_sound.wav")){
			printf("no sound file\n");
		}
		sound.setBuffer(buffer);
		sound.setPitch(1);
		sound.setVolume(20);
		sound.play();

	}

	// play a buzzer sound when player tries to do something that's not possible (ex. pick up a box thats unmovable)
		static void play_buzz(){
			if(!buffer.loadFromFile("../include/Sounds/buzzer.wav")){
				printf("no sound file\n");
			}
			sound.setBuffer(buffer);
			sound.setPitch(1);
			sound.setVolume(20);
			sound.play();

		}




};



#endif
