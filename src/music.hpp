#ifndef _MUSIC_
#define _MUSIC_


class GameMusic
{   
    sf::Music music;
    std::string BG_musics[4] = {"../Assets/Musics/Copacabana_Beach.mp3", "../Assets/Musics/Lost_Woods_BOTW_bg3.mp3", "../Assets/Musics/Shadow_Forest_bg4.mp3", "../Assets/Musics/Hinox_Battle_BOTW_bg1.mp3"};
    std::string menu_music = "../Assets/Musics/Endless_sand.mp3";

public:
    GameMusic()
    {
        music.openFromFile(menu_music);
        music.setLoop(true);
        music.play();
    }
    
    void update(){
        music.stop();
        music.openFromFile(BG_musics[currentLevel]);
        music.play();
        if     (currentLevel == 0){
            music.setVolume(60);
        }
        else if(currentLevel == 1){
            music.setVolume(100);
        }
        else if(currentLevel == 2){
            music.setVolume(100);
        }
        else if(currentLevel == 3){
            music.setVolume(100);
        }
    }

    void stop(){
        music.stop();
    }

    void playMenu(){
        music.stop();
        music.openFromFile(menu_music);
        music.play();
        music.setVolume(60);
    }

    void reset(){
        update();
        stop();
    }

};


#endif // _MUSIC_