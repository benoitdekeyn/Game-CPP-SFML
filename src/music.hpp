#ifndef _MUSIC_
#define _MUSIC_


class GameMusic
{   
    sf::Music music;
    std::string musics[4] = {"../Assets/Musics/BackgroundMusic1.mp3", "../Assets/Musics/BackgroundMusic2.mp3", "../Assets/Musics/BackgroundMusic3.mp3", "../Assets/Musics/BackgroundMusic4.mp3"};

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