#ifndef SPEED_HPP
#define SPEED_HPP

float speed = INITIAL_SPEED;
int counter = SPEED_INCREASE_INTERVAL;

void speedUp(){
    if (counter == 0){
        counter = SPEED_INCREASE_INTERVAL;
        if (speed < FINAL_SPEED){
            speed += SPEED_INCREASE_VALUE;
        }
    }else{
        counter--;
    }
}

void speedDown(){
    if (counter == 0){
        counter = SPEED_INCREASE_INTERVAL;
        if (speed > INITIAL_SPEED){
            speed -= SPEED_INCREASE_VALUE;
        }
    }else{
        counter--;
    }
}

void speedReset(){
    speed = INITIAL_SPEED;
    counter = SPEED_INCREASE_INTERVAL;
}

#endif // SPEED_HPP