#include "collisions.hpp"

class GameOver {
    sf::Texture texture;
    sf::Sprite gameOver;

public:
    GameOver(sf::RenderWindow& window) {
        texture.loadFromFile("../Assets/Backgrounds/GameOver.png");
        gameOver.setTexture(texture);
        gameOver.setScale(window.getSize().x / gameOver.getLocalBounds().width, window.getSize().y / gameOver.getLocalBounds().height);
    }

    void drawGameOver(sf::RenderWindow& window) {
        window.draw(gameOver);
    }
};

void collisionWithObstacles(Player player, Obstacle obstacle, sf::RenderWindow& window)
{
    if (player.shape.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds()))
    {
        GameOver gameOver(window);
        gameOver.drawGameOver(window);
    }
}