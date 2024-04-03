#ifndef _ANIM_
#define _ANIM_

#include "Character.hpp"

using namespace sf;

//-------------------- FUNCTIONS --------------------
struct Frame
{
    sf::IntRect rect;
    double duration; // in seconds
};

class Animation
{
    std::vector<Frame> frames;
    double totalLength;
    double progress;
    sf::Sprite &target;

public:
    Animation(sf::Sprite &target);
    void addFrame(Frame &&frame);
    void update(double elapsed);
    const double getLength() const { return totalLength; }
};

Animation::Animation(sf::Sprite &target) : target(target)
{
    progress = totalLength = 0.0;
}

void Animation::addFrame(Frame &&frame)
{
    totalLength += frame.duration;
    frames.push_back(std::move(frame));
}

void Animation::update(double elapsed)
{
    progress += elapsed;
    double p = progress;
    for (size_t i = 0; i < frames.size(); i++)
    {
        p -= frames[i].duration;

        if (p > 0.0 && &(frames[i]) == &(frames.back()))
        {
            i = 0;    // start over from the beginning
            continue; // break off the loop and start where i is
        }
        // if we have progressed OR if we're on the last frame, apply and stop.
        if (p <= 0.0 || &(frames[i]) == &frames.back())
        {
            target.setTextureRect(frames[i].rect);
            break; // we found our frame
        }
    }
}

//-------------------- FUNCTIONS --------------------

void selectAnimation(void);

void addRunFrames(Animation *runAnim)
{
    // Add frames to the running animation
    runAnim->addFrame({sf::IntRect(0, 105, 100, 100), 0.05});
    runAnim->addFrame({sf::IntRect(140, 105, 100, 100), 0.05});
    runAnim->addFrame({sf::IntRect(280, 105, 100, 100), 0.05});
    runAnim->addFrame({sf::IntRect(420, 105, 100, 100), 0.05});
    runAnim->addFrame({sf::IntRect(560, 105, 100, 100), 0.05});
    runAnim->addFrame({sf::IntRect(700, 105, 100, 100), 0.05});
}

void addJumpFrames(Animation *jumpAnim)
{
    // Add frames to the jumping animation
    jumpAnim->addFrame({sf::IntRect(0, 0, 100, 100), 0.1});
    jumpAnim->addFrame({sf::IntRect(140, 0, 100, 100), 0.2});
    jumpAnim->addFrame({sf::IntRect(0, 0, 100, 100), 0.2});
    jumpAnim->addFrame({sf::IntRect(140, 0, 100, 100), 0.1});
}
void addFallFrames(Animation *fallAnim)
{
    // Add frames to the fall animation
    fallAnim->addFrame({sf::IntRect(280, 210, 100, 100), 0.1});
    fallAnim->addFrame({sf::IntRect(280, 210, 100, 100), 0.1}); // I need at least two frames per animation to make it work.
}
void addDeathFrames(Animation *deathAnim)
{
    // Add frames to the death animation
    deathAnim->addFrame({sf::IntRect(0, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(140, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(280, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(420, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(560, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(700, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(840, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(980, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(1120, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(1260, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(1400, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(1540, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(1680, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(1820, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(1960, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(2100, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(2240, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(2380, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(2520, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(2660, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(2800, 210, 100, 100), 0.1});
    deathAnim->addFrame({sf::IntRect(2940, 210, 100, 100), 0.1});
}
#endif // DEBUG