#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP


class Background
{
    int n=0;
    int currents[2] = {0, 1};
    int background_transformation_step = 0;
    int counter = BACKGROUND_CHANGING_INTERVAL;
    std::string picture[4]= {"../Assets/Backgrounds/1/background.png", "../Assets/Backgrounds/2/background.png", "../Assets/Backgrounds/3/background.png", "../Assets/Backgrounds/4/background.png"};
    sf::Texture images[4];
    sf::Sprite backgrounds[8];


    public:

    Background(sf::RenderWindow& window) {
        
        for (int i = 0; i < 4; ++i) {
            images[i].loadFromFile(picture[i]); // Load each image into a texture
        }
        for (int i,x = 0; i < 8; ++i) {
            x = int(i/2);
            backgrounds[i].setTexture(images[x]); // Set the texture of each sprite to one of the images
            backgrounds[i].setPosition(window.getSize().x, 0); // Set the position of each sprite
        }

        background12.setPosition(window.getSize().x, 0);
        background11.setPosition(0, 0);
        drawIt(window,1);
    }

    void update(sf::RenderWindow& window) {

        moveIt(window);
        checkChange();
        updatePicture(window);
        window.clear();
        drawIt(window, currents[2]/2);
    }

    void moveIt(sf::RenderWindow& window) {
        int window_width = window.getSize().x;
        backgrounds[currents[0]].move(-speed, 0);
        backgrounds[currents[1]].move(-speed, 0);
        if (backgrounds[currents[0]].getPosition().x <= -window_width){
            backgrounds[currents[1]].setPosition(window_width, 0);
            backgrounds[currents[0]].setPosition(0, 0);}
        if (backgrounds[currents[1]].getPosition().x <= -window_width){
            backgrounds[currents[0]].setPosition(window_width, 0);
            backgrounds[currents[1]].setPosition(0, 0);}
    }

    void checkChange() {
        if (counter == 0){ 
            counter = BACKGROUND_CHANGING_INTERVAL;
            if (background_transformation_step == 0){ 
                n++; if (n>3) n=0;
                background_transformation_step = 1; //change As Soon As Possible : when one picture perfectly fits the screen
            }
        }else{
            counter--;
        }
    }

    void updatePicture(sf::RenderWindow& window) {
        int window_width = window.getSize().x;

        if (background_transformation_step == 0){
            return;
        }else if (background_transformation_step == 1){
            if (backgrounds[currents[0]].getPosition().x == 0 && backgrounds[currents[1]].getPosition().x == window_width){
                currents[0] = (currents[0] + 2) % 8;
                background_transformation_step = 21;
                return;
            }else if (backgrounds[currents[1]].getPosition().x == 0 && backgrounds[currents[0]].getPosition().x == window_width){
                currents[1] = (currents[1] + 2) % 8;
                background_transformation_step = 22;
                return;
            }else{
                return;
            }
        }else if (background_transformation_step == 21){
            if (background2.getPosition().x == 0 && background1.getPosition().x == window_width){
                background1.setTexture(images[n]);
                background_transformation_step = 0;
            }
        }else if (background_transformation_step == 22){
            if (background1.getPosition().x == 0 && background2.getPosition().x == window_width){
                background2.setTexture(images[n]);
                background_transformation_step = 0;
            }
        }
    }

    void setImage(sf::RenderWindow& window, int background_number){ //0 = both, 1 = back 1 and 2 = back2
        if (background_number == 1 || background_number == 0) {
            background1.setTexture(images[n]);
        }
        if (background_number == 2 || background_number == 0) {
            background2.setTexture(images[n]);
        }
    }

    void drawIt(sf::RenderWindow& window, int background_number) {
        if (background_number == 1 || background_number == 0) {
            window.draw(backgrounds[0]);
            window.draw(backgrounds[1]);
        }
        if (background_number == 2 || background_number == 0) {
            window.draw(backgrounds[2]);
            window.draw(backgrounds[3]);
        }
        if (background_number == 3 || background_number == 0) {
            window.draw(backgrounds[4]);
            window.draw(backgrounds[5]);
        }
        if (background_number == 4 || background_number == 0) {
            window.draw(backgrounds[6]);
            window.draw(backgrounds[7]);
        }
    }
};

#endif // BACKGROUND_HPP
