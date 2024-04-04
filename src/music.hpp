#ifndef _MUSIC_
#define _MUSIC_


class GameMusic
{   
    sf::Music music;
    std::string BG_musics[4] = {"../Assets/Musics/Hinox_Battle_BOTW_bg1.mp3", "../Assets/Musics/Dark_Owl_bg2.mp3", "../Assets/Musics/Lost_Woods_BOTW_bg3.mp3", "../Assets/Musics/SHadow_Forest_bg4.mp3"};
    std::string menu_music = "../Assets/Musics/Endless_sand.mp3";

public:
    GameMusic()
    {
        music.openFromFile(BG_musics[currentLevel]);
        music.setLoop(true);
        playMenu();
    }
    
    void update(){
        music.stop();
        music.openFromFile(BG_musics[currentLevel]);
        music.play();
    }

    void stop(){
        music.stop();
    }

    void playMenu(){
        stop();
        music.openFromFile(menu_music);
        music.play();
    }

    void reset(){
        update();
        stop();
    }

};


#endif // _MUSIC_