#ifndef KEY_H
#define KEY_H

#include "AnimatedSprite.h"

class Key : public AnimatedSprite {
public:
    void movingLeft() {}
    void movingRight() {}
    bool moving() {}
    void setFrames() {}
    void step(float &time) {}
    void mirror() {}
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
    Key(double x, double y, const std::string &filename);
};

Key::Key(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

#endif // KEY_H
