#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

// BACKGROUND INIT
class Background
{

    String picture[4]= {"../Assets/Backgrounds/1/background.png", "../Assets/Backgrounds/2/background.png", "../Assets/Backgrounds/3/background.png", "../Assets/Backgrounds/4/background.png"};
    int n=0;
    sf::Texture Image1;
    sf::Texture Image2;
    sf::Sprite background1;
    sf::Sprite background2;

    public:

    Background(sf::RenderWindow& window) {
        
        Image1.loadFromFile(picture[n]);
        Image2.loadFromFile(picture[n]);
        background1.setTexture(Image1);
        background2.setTexture(Image2);
        sf::Vector2u textureSize = Image1.getSize();
        sf::Vector2u windowSize = window.getSize();
        background1.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        background2.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        background1.setPosition(0, 0);
        background2.setPosition(windowSize.x, 0);
        drawBackground(window);
    }

    void moveBackground(sf::RenderWindow& window) {
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

    void changeBackgroundASAP(sf::RenderWindow& window) {
        n++; if (n>3) n=0;
    }

    void changeBackground(sf::RenderWindow& window) {
        Image1.loadFromFile(picture[n]);
        background1.setTexture(Image1);
        background2.setTexture(Image2);
        sf::Vector2u textureSize = Image1.getSize();
        sf::Vector2u windowSize = window.getSize();
        background1.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        background2.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        background1.setPosition(0, 0);
        background2.setPosition(windowSize.x, 0);
    }

    void drawBackground(sf::RenderWindow& window) {
        window.draw(background1);
        window.draw(background2);
    }
};

#endif // BACKGROUND_HPP
