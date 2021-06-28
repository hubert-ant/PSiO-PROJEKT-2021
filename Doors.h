#ifndef DOORS_H
#define DOORS_H

#include "AnimatedSprite.h"

class Doors: public AnimatedSprite {
public:
    void movingLeft() {}
    void movingRight() {}
    bool moving() {}
    void setFrames() {}
    void step(float &time) {}
    void mirror() {}
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
    Doors(double x, double y, const std::string &filename);
};

Doors::Doors(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

#endif // DOORS_H
