#ifndef _SOUND_
#define _SOUND_

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <string.h>
#include <unistd.h>


class musicSound{

public:
    musicSound(std::string filepath){
        if(music.openFromFile(filepath)){
            std::cout << "Error loading sound" << std::endl;
        }
    }
    void play(){
        music.play();
    }

    void stop(){
        music.stop();
    }

private:
    sf::Music music;
};

#endif // _SOUND__