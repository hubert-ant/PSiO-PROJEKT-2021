#ifndef WALL_H
#define WALL_H

#include <string>
#include <sstream>
#include <fstream>

#include "AnimatedSprite.h"

class Wall : public AnimatedSprite {
public:
    Wall(double x, double y, const std::string &filename, float scale_x, float scale_y);
    void movingRight() {}
    void movingLeft() {}
    bool moving() {}
    void setFrames() {};
    void step(float &time) {}
    void mirror() {}
    static void setWall(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename);
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
};

Wall::Wall(double x, double y, const std::string &filename, float scale_x, float scale_y) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    scale_x_ = scale_x;
    scale_y_ = scale_y;
}

void Wall::setWall(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename){
    for(int i = -1; i < 19; i++){
        std::unique_ptr<AnimatedSprite> wall_down = std::make_unique<Wall>(i * 100, 1220.0, "wall", 4.0, 4.0);
        wall_down->setScal();
        setObject(wall_down, objects);
        std::unique_ptr<AnimatedSprite> wall_up = std::make_unique<Wall>(i * 100, -150.0, "wall", 4.0, 4.0);
        wall_up->setScal();
        setObject(wall_up, objects);
    }
    for(int i = -1; i < 13; i++){
        std::unique_ptr<AnimatedSprite> wall_left = std::make_unique<Wall>(-100, i * 100, "wall", 4.0, 4.0);
        std::unique_ptr<AnimatedSprite> wall_right = std::make_unique<Wall>(1800, i * 100, "wall", 4.0, 4.0);
        wall_left->setScal();
        wall_right->setScal();
        setObject(wall_left, objects);
        setObject(wall_right, objects);
    }
    std::fstream input(filename);
    if(input.good()){
        for(std::string line; getline(input, line);){
            if(line[0] != '$'){
                float x, y, scale_x, scale_y;
                std::string name;
                std::stringstream stream(line);
                stream >> x;
                stream >> y;
                stream >> name;
                stream >> scale_x;
                stream >> scale_y;
                std::unique_ptr<AnimatedSprite> wall = std::make_unique<Wall>(x, y, name, scale_x, scale_y);
                setObject(wall, objects);
            }
        }
        input.close();
    }else{
        std::cout << "ERROR READING POINTS FILE" << std::endl;
    }
}

#endif // WALL_H
