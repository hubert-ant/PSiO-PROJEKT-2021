#ifndef POINT_H
#define POINT_H

#include "AnimatedSprite.h"

class Point : public AnimatedSprite {
public:
    Point(double x, double y, const std::string &filename);
    void movingRight() {}
    void movingLeft() {}
    bool moving() {}
    void setFrames() {};
    void step(float &time) {}
    void mirror() {}
    static void setPoints(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
};

Point::Point(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

void Point::setPoints(std::vector<std::unique_ptr<AnimatedSprite>> &objects){
    std::unique_ptr<AnimatedSprite> point1 = std::make_unique<Point>(700.0, 300.0, "point");
    setObject(point1, objects);
}
#endif // POINT_H
