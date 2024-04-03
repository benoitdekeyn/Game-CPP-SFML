#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP


class Background
{
    int n=0;
    int background_transformation_step = 0;
    int counter = BACKGROUND_CHANGING_INTERVAL;
    std::string picture[4]= {"../Assets/Backgrounds/1/background.png", "../Assets/Backgrounds/2/background.png", "../Assets/Backgrounds/3/background.png", "../Assets/Backgrounds/4/background.png"};
    sf::Texture images[4];
    sf::Sprite background1;
    sf::Sprite background2;

    public:

    Background(sf::RenderWindow& window) {
        
        for (int i = 0; i < 4; ++i) {
            images[i].loadFromFile(picture[i]);
        }
    
        setImage(window, 0);
        background2.setPosition(window.getSize().x, 0);
        background1.setPosition(0, 0);
        drawIt(window);
    }

    void update(sf::RenderWindow& window) {
        
        if (counter == 0){ //call a picture change as soon as possible
            counter = BACKGROUND_CHANGING_INTERVAL;
            changeASAP();
        }else{counter--;}

        moveIt(window);
        updatePicture(window);
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

    void changeASAP() { //change As Soon As Possible : when one picture perfectly fits the screen
        if (background_transformation_step == 0){
            n++; if (n>3) n=0;
        background_transformation_step = 1;
        }
    }

    void updatePicture(sf::RenderWindow& window) {
        int window_width = window.getSize().x;

        if (background_transformation_step == 0){
            return;
        }else if (background_transformation_step == 1){
            if (background1.getPosition().x == 0 && background2.getPosition().x == window_width){
                setImage(window, 1);
                background_transformation_step = 22;
            }else if (background1.getPosition().x == window_width && background2.getPosition().x == 0){
                setImage(window, 2);
                background_transformation_step = 21;
            }else{
                return;
            }
        }else if (background_transformation_step == 21){
            background1.setTexture(images[n]);
            background_transformation_step = 0;
        }else if (background_transformation_step == 22){
            background2.setTexture(images[n]);
            background_transformation_step = 0;
        }
    }

    void setImage(sf::RenderWindow& window, int background_number=0){ //0 = both, 1 = back 1 and 2 = back2
        if (background_number == 1 || background_number == 0) {
            background1.setTexture(images[n]);
        }
        if (background_number == 2 || background_number == 0) {
            background2.setTexture(images[n]);
        }

        sf::Vector2u textureSize = images[n].getSize();
        sf::Vector2u windowSize = window.getSize();

        if (background_number == 1 || background_number == 0) {
            background1.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        }
        if (background_number == 2 || background_number == 0) {
            background2.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        }
    }

    void drawIt(sf::RenderWindow& window) {
        window.draw(background1);
        window.draw(background2);
    }
};

#endif // BACKGROUND_HPP
