#ifndef WALL_H
#define WALL_H

#include <string>

#include "AnimatedSprite.h"

class Wall : public AnimatedSprite {
public:
    Wall(double x, double y, const std::string &filename);
    void movingRight() {}
    void movingLeft() {}
    bool moving() {}
    void setFrames() {};
    void step(float &time) {}
    void mirror() {}
    static void setWall(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
};

Wall::Wall(double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
}

void Wall::setWall(std::vector<std::unique_ptr<AnimatedSprite>> &objects){
    std::unique_ptr<AnimatedSprite> wall1 = std::make_unique<Wall>(0, 550, "wall");
    std::unique_ptr<AnimatedSprite> wall2 = std::make_unique<Wall>(0.0, 200.0, "wall");
    std::unique_ptr<AnimatedSprite> wall3 = std::make_unique<Wall>(200.0, 450.0, "wall");
    setObject(wall1, objects);
    setObject(wall2, objects);
    setObject(wall3, objects);
}

#endif // WALL_H
