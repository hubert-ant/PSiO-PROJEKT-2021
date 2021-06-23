#ifndef BONUS_H
#define BONUS_H

#include "AnimatedSprite.h"

class Bonus : public AnimatedSprite {
public:
    Bonus(double x, double y, const std::string &filename);
    void movingRight() {}
    void movingLeft() {}
    bool moving();
    void setFrames();
    void step(float& time) {}
    void mirror() {}
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
};

#endif // BONUS_H
