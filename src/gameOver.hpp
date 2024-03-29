#ifndef _OVER_
#define _OVER_
#include "Character.hpp"

class GameOver
{
    sf::Texture texture;
    sf::Sprite gameOver;

public:
    GameOver(sf::RenderWindow &window)
    {
        texture.loadFromFile("../Assets/Backgrounds/GameOver.png");
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
#endif