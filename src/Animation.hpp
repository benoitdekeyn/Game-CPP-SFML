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
    runAnim->addFrame({sf::IntRect(0, 0, 66, 66), 0.06});
    runAnim->addFrame({sf::IntRect(80, 0, 66, 66), 0.06});
    runAnim->addFrame({sf::IntRect(160, 0, 66, 66), 0.06});
    runAnim->addFrame({sf::IntRect(240, 0, 66, 66), 0.06});
    runAnim->addFrame({sf::IntRect(320, 0, 66, 66), 0.06});
    runAnim->addFrame({sf::IntRect(400, 0, 66, 66), 0.06});
}

void addJumpFrames(Animation *jumpAnim)
{
    // Add frames to the jumping animation
    jumpAnim->addFrame({sf::IntRect(0, 50, 66, 66), 0.1});
    jumpAnim->addFrame({sf::IntRect(80, 50, 66, 66), 0.2});
    jumpAnim->addFrame({sf::IntRect(0, 50, 66, 66), 0.2});
    jumpAnim->addFrame({sf::IntRect(80, 50, 66, 66), 0.1});
}
void addFallFrames(Animation *fallAnim)
{
    // Add frames to the fall animation
    fallAnim->addFrame({sf::IntRect(160, 142, 66, 66), 0.1});
}
void addDeathFrames(Animation *deathAnim)
{
    // Add frames to the death animation
    deathAnim->addFrame({sf::IntRect(0, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(80, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(160, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(240, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(320, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(400, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(480, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(560, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(640, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(720, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(800, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(880, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(950, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1030, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1110, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1190, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1270, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1350, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1430, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1520, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1600, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1680, 142, 66, 66), 0.1});
    deathAnim->addFrame({sf::IntRect(1760, 142, 66, 66), 0.1});
}
#endif // DEBUG