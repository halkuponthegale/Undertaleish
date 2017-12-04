#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "GameView.h"


class AudioManager{
public:
	static void play_launch(){
		printf("playing launch\n");
		// sf::SoundBuffer buffer;
		if(!buffer.loadFromFile("../include/Sounds/woohoo.wav")){
			printf("no file\n");
		}

		sound.setBuffer(buffer);
		sound.play();
	}

	static void play_builder_box(){
		printf("playing builder\n");
		if(!buffer.loadFromFile("../include/Sounds/builder_box.wav")){
			printf("no file\n");
		}

		sound.setBuffer(buffer);
		sound.play();
	}
};



#endif