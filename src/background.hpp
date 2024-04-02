#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

// BACKGROUND INIT
class Background
{


    sf::Texture backgroundTexture;
    sf::Sprite background1;
    sf::Sprite background2;

    public:

    Background(String imagePath, sf::RenderWindow& window) {
        
        backgroundTexture.loadFromFile(imagePath);
        background1.setTexture(backgroundTexture);
        background2.setTexture(backgroundTexture);
        sf::Vector2u textureSize = backgroundTexture.getSize();
        sf::Vector2u windowSize = window.getSize();
        background1.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        background2.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
        background1.setPosition(0, 0);
        background2.setPosition(windowSize.x, 0);

        drawBackground(window);
    }

    void updateBackground(sf::RenderWindow& window) {
        int window_width = window.getSize().x;
        background1.move(-speed, 0);
        background2.move(-speed, 0);
        if (background1.getPosition().x <= -window_width){
            background1.setPosition(window_width, 0);}
        if (background2.getPosition().x <= -window_width){
            background2.setPosition(window_width, 0);}
    }

    void drawBackground(sf::RenderWindow& window) {
        window.draw(background1);
        window.draw(background2);
    }
};

#endif // BACKGROUND_HPP
