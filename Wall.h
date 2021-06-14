#ifndef WALL_H
#define WALL_H

#include <string>

#include <AnimatedSprite.h>

class Wall : public AnimatedSprite {
public:
    Wall(double x, double y, const std::string &filename);
    void movingRight() {}
    void movingLeft() {}
    bool moving() {}
    void setFrames() {};
    void step(float &time) {}
    void mirror() {}
};

Wall::Wall(double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
}



#endif // WALL_H
