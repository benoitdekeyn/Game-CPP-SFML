#ifndef _SOUND_
#define _SOUND_


class Music
{
    std::string musics[4] = {"../Assets/Sounds/BackgroundMusic1.wav", "../Assets/Sounds/BackgroundMusic2.wav", "../Assets/Sounds/BackgroundMusic3.wav", "../Assets/Sounds/BackgroundMusic4.wav"};

public:
    Music()
    {
        music.openFromFile("Assets/Sounds/BackgroundMusic.wav");
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
    void changeMusic(){
        music.openFromFile(musics[random]);
    }

private:
    sf::Music music;
};

#endif // _SOUND__