#ifndef BONUS_H
#define BONUS_H

#include "AnimatedSprite.h"

class Bonus : public AnimatedSprite {
public:
    Bonus(double x, double y, const std::string &filename);
    void movingRight() {}
    void movingLeft() {}
    bool moving() {}
    void setFrames() {}
    void step(float& time) {}
    void mirror() {}
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
    static void setBonuses(std::vector<std::unique_ptr<AnimatedSprite>> &bonuses);
};

Bonus::Bonus(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

void Bonus::setBonuses(std::vector<std::unique_ptr<AnimatedSprite>> &bonuses){
    std::unique_ptr<AnimatedSprite> bonus1 = std::make_unique<Bonus>(200.0, 400.0, "duch");
    setObject(bonus1, bonuses);
}

#endif // BONUS_H
