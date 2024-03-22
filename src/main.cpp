#include <SFML/Graphics.hpp>

sf::VideoMode mode(1600, 900, 32);
sf::RenderWindow window(mode, "My window");



int main(){    

    //INIT
    int speed = 5; //number of pixels per frame
    int width = mode.width;
    int height = mode.height;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("data/backgrounds/background.png");
    sf::Sprite background1(backgroundTexture);
    sf::Sprite background2(backgroundTexture);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    background1.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    background2.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    background2.setPosition(windowSize.x, 0);
    
    //MAIN LOOP
    while (window.isOpen()){sf::Event event;while (window.pollEvent(event)){if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))window.close();}

        //BACKGROUND INIT
        background1.move(-speed, 0);
        background2.move(-speed, 0);
        if (background1.getPosition().x <= -width) {
            background1.setPosition(width, 0);
        }
        if (background2.getPosition().x <= -width) {
            background2.setPosition(width, 0);
        }
        window.clear();
        window.draw(background1);
        window.draw(background2);
        


        //HERE THE MAIN LOOP CODE



        //Don't touch below :
        window.display();
    }return 0;
}

