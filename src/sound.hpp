#ifndef _SOUND_
#define _SOUND_

#include <SFML/Audio.hpp>
#include <string.h>
#include <unistd.h>
#include <iostream>

class musicSound
{

public:
    musicSound(std::string filepath)
    {
        if(!music.openFromFile(filepath)){
            std::cout << "Error loading music file" << std::endl;
            exit(1);
        }
        music.setLoop(true);
    }
    void play()
    {
        music.play();
    }

    void stop()
    {
        music.stop();
    }

private:
    sf::Music music;
};

#endif // _SOUND__