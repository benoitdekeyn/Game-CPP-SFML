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
        if (!font.loadFromFile("Fonts/scoreFont.otf"))
        {
        }

        text.setFont(font);
        text.setCharacterSize(40); // in pixels
        text.setFillColor(sf::Color::Black);
        text.setPosition(WINDOW_WIDTH/1.15, WINDOW_HEIGHT/17); // top-left corner
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

    int getScore(){
        return score;
    }
};

#endif // __SCORE__