#include "Character.hpp"
#include "Collisions.hpp"

int main()
{

    Runner player{"../Assets/Character/NightBorne.png", Vector2f(00, 00)};
    // Character obstacle{"../Assets/Character/NightBorne.png", Vector2f(00, 00)};

    // INIT
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);
    int speed = 5; // number of pixels per frame
    // int width = window.width;
    // int height = window.height;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("data/backgrounds/background.png");
    sf::Sprite background1(backgroundTexture);
    sf::Sprite background2(backgroundTexture);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    background1.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
    background2.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
    background2.setPosition(windowSize.x, 0);
    int x_width_window = windowSize.x;

    // MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        // BACKGROUND INIT
        background1.move(-speed, 0);
        background2.move(-speed, 0);
        if (background1.getPosition().x <= -x_width_window)
        {
            background1.setPosition(x_width_window, 0);
        }
        if (background2.getPosition().x <= -x_width_window)
        {
            background2.setPosition(x_width_window, 0);
        }
        window.clear();
        window.draw(background1);
        window.draw(background2);

        // collisionWithObstacles(player, obstacle);

        // player.update();
        // player.draw();

        // obstacle.update();
        // obstacle.draw();

        window.display();
    }
    return 0;
}
