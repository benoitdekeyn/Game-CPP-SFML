#ifndef _MUSIC_
#define _MUSIC_


class GameMusic
{   
    sf::Music music;
    std::string musics[4] = {"../Assets/Sounds/BackgroundMusic1.mp3", "../Assets/Sounds/BackgroundMusic2.mp3", "../Assets/Sounds/BackgroundMusic3.mp3", "../Assets/Sounds/BackgroundMusic4.mp3"};

public:
    GameMusic()
    {
        music.openFromFile(musics[currentLevel]);
        music.setLoop(true);
        music.play();
    }
    
    void update(){
        music.stop();
        music.openFromFile(musics[currentLevel]);
        music.play();
    }

    void stop(){
        music.stop();
    }

    void reset(){
        update();
        stop();
    }

};

#endif // _MUSIC_