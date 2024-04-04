#ifndef _DEFINITIONS_
#define _DEFINITIONS_

//-------------------- DEFINITIONS --------------------

//---------- WINDOW ----------
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define COLOR_DEPTH 32
#define FPS 60

//--------- BACKGROUND -------
#define BACKGROUND_CHANGING_REGULARITY 1 // HERE NORMAL = 4 at least, TEST= 1 : number in perfect pictures at a speed between 1 and 5

//---------- SPEED -----------
#define INITIAL_SPEED 3
#define FINAL_SPEED 20
#define SPEED_INCREASE_INTERVAL 0 // skipped frames before increasing the speed by SPEED_INCREASE_VALUE (below)
#define SPEED_INCREASE_VALUE 1.0f // HERE NORMAL = 1.0f, test = 3.0f

//---------- GRAVITY ---------
#define PROPULSION_STRENGHT 2.1f
#define PROPULSION_SMOOTHER 1.0f
#define GRAVITY_STRENGHT 0.6f
#define GRAVITY_SMOOTHER 0.01f
#define SPEED_UP_MAX 7

//--------- POSITION ---------
#define INITIAL_Y_POS 450
#define RUNNER_X_POS 200
#define TOP_OFFSET 3
#define BOTTOM_OFFSET -7

//---------- HITBOX ----------
#define HITBOX_WIDTH 55
#define HITBOX_HEIGHT 60
#define HITBOX_OFFSET sf::Vector2f(40, 6)

//--------- OBSTACLE ---------
#define OBSTACLE_WIDTH 50
#define OBSTACLE_COLOR sf::Color::Red
#define OBSTACLE_INTERVAL 0.5f

//----------- SFML -----------
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace sf;
using namespace std;

//---------- HEADERS ---------
#include "speed.hpp"
#include "background.hpp"
#include "character.hpp"
#include "score.hpp"
#include "gameOver.hpp"
#include "animation.hpp"

//----------- MENU -----------
bool menuOn = true;

//----------- DEATH ----------
bool death = false;
bool animationStarted = false;

//---------- WINDOW ----------
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_DEPTH), "SFML works!");

#endif // !_DEFINITIONS_