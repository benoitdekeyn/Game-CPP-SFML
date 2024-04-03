#ifndef _OVER_
#define _OVER_

class GameOver
{
    sf::Texture texture;
    sf::Sprite gameOver;

public:
    GameOver(sf::RenderWindow &window)
    {
        texture.loadFromFile("../Assets/Backgrounds/overnew.png");
        gameOver.setTexture(texture);
        gameOver.setScale(window.getSize().x / gameOver.getLocalBounds().width, window.getSize().y / gameOver.getLocalBounds().height);
    }

    void drawGameOver(sf::RenderWindow &window)
    {
        window.draw(gameOver);
    }
};

bool collisionWithObstacles(Runner player, Obstacle obstacle, sf::RenderWindow &window)
{
    if (player.hitbox.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

class Menu
{
    sf::Texture texture;
    sf::Sprite menu;

public:
    Menu(sf::RenderWindow &window)
    {
        texture.loadFromFile("../Assets/Backgrounds/menunew.png");
        menu.setTexture(texture);
        menu.setScale(window.getSize().x / menu.getLocalBounds().width, window.getSize().y / menu.getLocalBounds().height);
    }

    void drawIt(sf::RenderWindow &window)
    {
        window.draw(menu);
    }
};

#endif