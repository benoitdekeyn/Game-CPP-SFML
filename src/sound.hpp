#ifndef _SOUND_
#define _SOUND_

#include <SFML/Audio.hpp>
#include <string.h>
#include <unistd.h>

class musicSound
{

public:
    musicSound(std::string filepath)
    {
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