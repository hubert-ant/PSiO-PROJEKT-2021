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
    for(int i = -1; i < 19; i++){
        std::unique_ptr<AnimatedSprite> wall_down = std::make_unique<Wall>(i * 100, 1220.0, "wall");
        wall_down->setScale(4, 4);
        setObject(wall_down, objects);
        std::unique_ptr<AnimatedSprite> wall_up = std::make_unique<Wall>(i * 100, -150.0, "wall");
        wall_up->setScale(4, 4);
        setObject(wall_up, objects);
    }
    for(int i = -1; i < 13; i++){
        std::unique_ptr<AnimatedSprite> wall_left = std::make_unique<Wall>(-100, i * 100, "wall");
        std::unique_ptr<AnimatedSprite> wall_right = std::make_unique<Wall>(1800, i * 100, "wall");
        wall_left->setScale(4, 4);
        wall_right->setScale(4, 4);
        setObject(wall_left, objects);
        setObject(wall_right, objects);
    }
    std::unique_ptr<AnimatedSprite> wall1 = std::make_unique<Wall>(0, 550, "wall");
    wall1->setScale(6, 2);
    setObject(wall1, objects);
    std::unique_ptr<AnimatedSprite> wall2 = std::make_unique<Wall>(150, 650, "wall");
    wall2->setScale(3, 2);
    setObject(wall2, objects);
    std::unique_ptr<AnimatedSprite> wall3 = std::make_unique<Wall>(250, 550, "wall");
    wall3->setScale(16, 2);
    setObject(wall3, objects);
    std::unique_ptr<AnimatedSprite> wall4 = std::make_unique<Wall>(0, 450, "wall");
    wall4->setScale(2, 2);
    setObject(wall4, objects);
    std::unique_ptr<AnimatedSprite> wall5 = std::make_unique<Wall>(100, 380, "wall");
    wall5->setScale(12, 2);
    setObject(wall5, objects);
    std::unique_ptr<AnimatedSprite> wall6 = std::make_unique<Wall>(0, 750, "wall");
    wall6->setScale(12, 2);
    setObject(wall6, objects);
    std::unique_ptr<AnimatedSprite> wall7 = std::make_unique<Wall>(300, 850, "wall");
    wall7->setScale(12, 2);
    setObject(wall7, objects);
    std::unique_ptr<AnimatedSprite> wall8 = std::make_unique<Wall>(600, 750, "wall");
    wall8->setScale(15, 2);
    setObject(wall8, objects);
    std::unique_ptr<AnimatedSprite> wall9 = std::make_unique<Wall>(720, 650, "wall");
    wall9->setScale(2, 2);
    setObject(wall9, objects);
    std::unique_ptr<AnimatedSprite> wall10 = std::make_unique<Wall>(650, 430, "wall");
    wall10->setScale(13, 2);
    setObject(wall10, objects);
    std::unique_ptr<AnimatedSprite> wall11 = std::make_unique<Wall>(430, 310, "wall");
    wall11->setScale(8, 2);
    setObject(wall11, objects);
    std::unique_ptr<AnimatedSprite> wall12 = std::make_unique<Wall>(0, 250, "wall");
    wall12->setScale(10, 2);
    setObject(wall12, objects);
    std::unique_ptr<AnimatedSprite> wall13 = std::make_unique<Wall>(320, 200, "wall");
    wall13->setScale(2, 2);
    setObject(wall13, objects);
    std::unique_ptr<AnimatedSprite> wall14 = std::make_unique<Wall>(0, 100, "wall");
    wall14->setScale(10, 2);
    setObject(wall14, objects);
    std::unique_ptr<AnimatedSprite> wall15 = std::make_unique<Wall>(400, 90, "wall");
    wall15->setScale(10, 2);
    setObject(wall15, objects);
    std::unique_ptr<AnimatedSprite> wall16 = std::make_unique<Wall>(700, 180, "wall");
    wall16->setScale(15, 2);
    setObject(wall16, objects);
    std::unique_ptr<AnimatedSprite> wall17 = std::make_unique<Wall>(1100, 80, "wall");
    wall17->setScale(15, 2);
    setObject(wall17, objects);
    std::unique_ptr<AnimatedSprite> wall18 = std::make_unique<Wall>(1500, 180, "wall");
    wall18->setScale(12, 2);
    setObject(wall18, objects);
    std::unique_ptr<AnimatedSprite> wall19 = std::make_unique<Wall>(1750, 60, "wall");
    wall19->setScale(2, 2);
    setObject(wall19, objects);
    std::unique_ptr<AnimatedSprite> wall20 = std::make_unique<Wall>(1050, 350, "wall");
    wall20->setScale(8, 2);
    setObject(wall20, objects);
    std::unique_ptr<AnimatedSprite> wall21 = std::make_unique<Wall>(1320, 420, "wall");
    wall21->setScale(8, 2);
    setObject(wall21, objects);
    std::unique_ptr<AnimatedSprite> wall22 = std::make_unique<Wall>(1020, 640, "wall");
    wall22->setScale(16, 2);
    setObject(wall22, objects);
    std::unique_ptr<AnimatedSprite> wall23 = std::make_unique<Wall>(1500, 720, "wall");
    wall23->setScale(12, 2);
    setObject(wall23, objects);
    std::unique_ptr<AnimatedSprite> wall24 = std::make_unique<Wall>(1750, 600, "wall");
    wall24->setScale(2, 2);
    setObject(wall24, objects);
    std::unique_ptr<AnimatedSprite> wall25 = std::make_unique<Wall>(1600, 500, "wall");
    wall25->setScale(2, 2);
    setObject(wall25, objects);
    std::unique_ptr<AnimatedSprite> wall26 = std::make_unique<Wall>(300, 1100, "wall");
    wall26->setScale(8, 2);
    setObject(wall26, objects);
    std::unique_ptr<AnimatedSprite> wall27 = std::make_unique<Wall>(500, 1000, "wall");
    wall27->setScale(8, 2);
    setObject(wall27, objects);
    std::unique_ptr<AnimatedSprite> wall28 = std::make_unique<Wall>(700, 900, "wall");
    wall28->setScale(16, 2);
    setObject(wall28, objects);
    std::unique_ptr<AnimatedSprite> wall29 = std::make_unique<Wall>(1150, 820, "wall");
    wall29->setScale(10, 2);
    setObject(wall29, objects);
    std::unique_ptr<AnimatedSprite> wall30 = std::make_unique<Wall>(1450, 780, "wall");
    wall30->setScale(2, 2);
    setObject(wall30, objects);
    std::unique_ptr<AnimatedSprite> wall31 = std::make_unique<Wall>(0, 950, "wall");
    wall31->setScale(8, 2);
    setObject(wall31, objects);
    std::unique_ptr<AnimatedSprite> wall32 = std::make_unique<Wall>(1100, 1000, "wall");
    wall32->setScale(16, 2);
    setObject(wall32, objects);
    std::unique_ptr<AnimatedSprite> wall33 = std::make_unique<Wall>(1500, 1110, "wall");
    wall33->setScale(12, 2);
    setObject(wall33, objects);
    std::unique_ptr<AnimatedSprite> wall34 = std::make_unique<Wall>(0, 1090, "wall");
    wall34->setScale(6, 2);
    setObject(wall34, objects);
    std::unique_ptr<AnimatedSprite> wall35 = std::make_unique<Wall>(900, 1070, "wall");
    wall35->setScale(6, 2);
    setObject(wall35, objects);
}

#endif // WALL_H
