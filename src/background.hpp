#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP



class Background
{
    int background_transformation_step = 0;
    int counter = BACKGROUND_CHANGING_REGULARITY;
    int first = 0;
    std::string picture[4]= {"../Assets/Backgrounds/3/background.png", "../Assets/Backgrounds/2/background.png", "../Assets/Backgrounds/4/background.png", "../Assets/Backgrounds/1/background.png"};
    sf::Texture images[4];
    sf::Sprite background1;
    sf::Sprite background2;


    public:

    Background(sf::RenderWindow& window) {
        
        for (int i = 0; i < 4; ++i) {
            images[i].loadFromFile(picture[i]);
        }
        
        sf::Vector2u textureSize = images[currentLevel].getSize();
        sf::Vector2u windowSize = window.getSize();
        background1.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        background2.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);

        setImage(window, 0);
        background2.setPosition(window.getSize().x, 0);
        background1.setPosition(0, 0);
        drawIt(window);

    }
    void reset(sf::RenderWindow& window) {
        currentLevel = 0;
        counter = BACKGROUND_CHANGING_REGULARITY;
        
        background_transformation_step = 0;
        setImage(window, 0);
        background2.setPosition(window.getSize().x, 0);
        background1.setPosition(0, 0);
    }

    void update(sf::RenderWindow& window, GameMusic& music) {

        if (first == 0){
            first = 1;
            music.update();
            return;
        }
        moveIt(window);
        checkChange();
        updatePictureAndMusic(window, music);
        window.clear();
        drawIt(window);
    }

    void moveIt(sf::RenderWindow& window) {
        int window_width = window.getSize().x;
        background1.move(-speed, 0);
        background2.move(-speed, 0);
        if (background1.getPosition().x <= -window_width){
            background1.setPosition(window_width, 0);
            background2.setPosition(0, 0);}
        if (background2.getPosition().x <= -window_width){
            background2.setPosition(window_width, 0);
            background1.setPosition(0, 0);}
    }

    void checkChange() {

        int speedFactor = (int)(speed/5);
        if (speedFactor == 0) {speedFactor = 1;}
        if (counter == BACKGROUND_CHANGING_REGULARITY * speedFactor){ 
            counter = 0;
            if (background_transformation_step == 0){ 
                currentLevel++; if (currentLevel>3) currentLevel=0;
                background_transformation_step = 1; //change As Soon As Possible : when one picture perfectly fits the screen
                //UPDATE SPEED
                speedUp();
                //UPDATE MUSIC
                
            }
        }
        if (background1.getPosition().x == 0 || background2.getPosition().x == 0){
            counter ++;
        }
    }

    void updatePictureAndMusic(sf::RenderWindow& window, GameMusic& music) {
        int window_width = window.getSize().x;

        if (background_transformation_step == 0){
            return;
        }else if (background_transformation_step == 1){
            if (background1.getPosition().x == 0 && background2.getPosition().x == window_width){
                music.update();
                setImage(window, 2);
                background_transformation_step = 21;
                return;
            }else if (background2.getPosition().x == 0 && background1.getPosition().x == window_width){
                music.update();
                setImage(window, 1);
                background_transformation_step = 22;
                return;
            }else{
                return;
            }
        }else if (background_transformation_step == 21){
            if (background2.getPosition().x == 0 && background1.getPosition().x == window_width){
                setImage(window, 1);
                background_transformation_step = 0;
                
            }
        }else if (background_transformation_step == 22){
            if (background1.getPosition().x == 0 && background2.getPosition().x == window_width){
                setImage(window, 2);
                background_transformation_step = 0;
                
            }
        }
    }

    void setImage(sf::RenderWindow& window, int background_number=0){ //0 = both, 1 = back 1 and 2 = back2
        if (background_number == 1 || background_number == 0) {
            background1.setTexture(images[currentLevel]);
        }
        if (background_number == 2 || background_number == 0) {
            background2.setTexture(images[currentLevel]);
        }
    }

    void drawIt(sf::RenderWindow& window) {
        window.draw(background1);
        window.draw(background2);
    }
};

#endif // BACKGROUND_HPP
