#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <unistd.h>
#include <iostream>

using namespace sf;
// using namespace std;


void collisionWithObstacles(character player, character obstacle)
{
    if(player.hitbox.getGlobalBounds().intersects(obstacle.hitbox.getGlobalBounds()))
    {
        exit(0);
    }
}

// bool topBottomCollision(Player player)
// {
    
//     if(player.position.y < 0)
//     {
//         player.position.y = 0;
//     }

//     if(player.position.y > window.getSize().y - player.shape.getSize().y)
//     {
//         player.position.y = window.getSize().y - player.shape.getSize().y;
//     }
// }

// int main()
// {
//     Player player;
//     Obstacle obstacle;
    
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // topBottomCollision(player);
//         collisionWithObstacles(player, obstacle);

//         window.clear(); // Clear the window before drawing anything

//         player.update();
//         player.draw();

//         obstacle.update();
//         obstacle.draw();

//         window.display();
        
//         usleep(100);
//     }
// }
