#ifndef POINT_H
#define POINT_H

#include <fstream>
#include <sstream>

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
    static void setPoints(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename);
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
};

Point::Point(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

void Point::setPoints(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename){
    std::fstream input(filename);
    if(input.good()){
        for(std::string line; getline(input, line);){
            if(line[0] != '$'){
                float x, y;
                std::string name;
                std::stringstream stream(line);
                stream >> x;
                stream >> y;
                stream >> name;
                std::unique_ptr<AnimatedSprite> point = std::make_unique<Point>(x, y, name);
                setObject(point, objects);
            }
        }
        input.close();
    }else{
        std::cout << "ERROR READING POINTS FILE" << std::endl;
    }
}
#endif // POINT_H
