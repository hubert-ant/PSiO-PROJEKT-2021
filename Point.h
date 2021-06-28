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
    std::unique_ptr<AnimatedSprite> point1 = std::make_unique<Point>(13.0, 410.0, "point");
    std::unique_ptr<AnimatedSprite> point2 = std::make_unique<Point>(523.0, 270.0, "point");
    std::unique_ptr<AnimatedSprite> point3 = std::make_unique<Point>(123.0, 60.0, "point");
    std::unique_ptr<AnimatedSprite> point4 = std::make_unique<Point>(531.0, 49.0, "point");
    std::unique_ptr<AnimatedSprite> point5 = std::make_unique<Point>(874.0, 40.0, "point");
    std::unique_ptr<AnimatedSprite> point6 = std::make_unique<Point>(1760.0, 139.0, "point");
    std::unique_ptr<AnimatedSprite> point7 = std::make_unique<Point>(1395.0, 280.0, "point");
    std::unique_ptr<AnimatedSprite> point8 = std::make_unique<Point>(458.0, 509.0, "point");
    std::unique_ptr<AnimatedSprite> point9 = std::make_unique<Point>(447.0, 809.0, "point");
    std::unique_ptr<AnimatedSprite> point10 = std::make_unique<Point>(731.0, 709.0, "point");
    std::unique_ptr<AnimatedSprite> point11 = std::make_unique<Point>(1260.0, 780.0, "point");
    std::unique_ptr<AnimatedSprite> point12 = std::make_unique<Point>(1307.0, 560.0, "point");
    std::unique_ptr<AnimatedSprite> point13 = std::make_unique<Point>(1660.0, 880.0, "point");
    std::unique_ptr<AnimatedSprite> point14 = std::make_unique<Point>(1310.0, 970.0, "point");
    std::unique_ptr<AnimatedSprite> point15 = std::make_unique<Point>(124.0, 1179.0, "point");
    std::unique_ptr<AnimatedSprite> point16 = std::make_unique<Point>(388.0, 935.0, "point");
    std::unique_ptr<AnimatedSprite> point17 = std::make_unique<Point>(42.0, 880.0, "point");
    std::unique_ptr<AnimatedSprite> point18 = std::make_unique<Point>(439.0, 510.0, "point");
    std::unique_ptr<AnimatedSprite> point19 = std::make_unique<Point>(1769.0, 440.0, "point");
    std::unique_ptr<AnimatedSprite> point20 = std::make_unique<Point>(1124.0, 1100.0, "point");
    setObject(point1, objects);
    setObject(point2, objects);
    setObject(point3, objects);
    setObject(point4, objects);
    setObject(point5, objects);
    setObject(point6, objects);
    setObject(point7, objects);
    setObject(point8, objects);
    setObject(point9, objects);
    setObject(point10, objects);
    setObject(point11, objects);
    setObject(point12, objects);
    setObject(point13, objects);
    setObject(point14, objects);
    setObject(point15, objects);
    setObject(point16, objects);
    setObject(point17, objects);
    setObject(point18, objects);
    setObject(point19, objects);
    setObject(point20, objects);
}
#endif // POINT_H
