#ifndef _ANIM_
#define _ANIM_

#include <SFML\Graphics.hpp>
using namespace sf;

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

#endif // DEBUG