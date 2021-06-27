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
    std::unique_ptr<AnimatedSprite> wall1 = std::make_unique<Wall>(0.0, 900, "wall");
    std::unique_ptr<AnimatedSprite> wall2 = std::make_unique<Wall>(200.0, 900.0, "wall");
    std::unique_ptr<AnimatedSprite> wall3 = std::make_unique<Wall>(400.0, 900.0, "wall");
    std::unique_ptr<AnimatedSprite> wall4 = std::make_unique<Wall>(400.0, 900.0, "wall");
    std::unique_ptr<AnimatedSprite> wall5 = std::make_unique<Wall>(600.0, 900.0, "wall");
    std::unique_ptr<AnimatedSprite> wall6 = std::make_unique<Wall>(800.0, 900.0, "wall");
    std::unique_ptr<AnimatedSprite> wall7 = std::make_unique<Wall>(1000.0, 900.0, "wall");
    std::unique_ptr<AnimatedSprite> wall8 = std::make_unique<Wall>(1200.0, 900.0, "wall");
    setObject(wall1, objects);
    setObject(wall2, objects);
    setObject(wall3, objects);
    setObject(wall4, objects);
    setObject(wall5, objects);
    setObject(wall6, objects);
    setObject(wall7, objects);
    setObject(wall8, objects);
}

#endif // WALL_H
