#ifndef __SCO__
#define __SCO__

class Score
{
    sf::Font font;
    sf::Text text;
    int score;
public:

    Score(sf::RenderWindow &window)
    {
        score = 0;
        if (!font.loadFromFile("Arial font/arial_light.ttf"))
        {

        }

        text.setFont(font);
        text.setCharacterSize(24); // in pixels
        text.setFillColor(sf::Color::Blue);
        text.setPosition(50, 50); // top-left corner
        updateText();
    }



    void increment()
    {
        score++;
        updateText();
    }

    void updateText()
    {
        text.setString("SCORE: " + std::to_string(score));
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(text);
    }
};

#endif // __SCORE__