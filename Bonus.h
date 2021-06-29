#ifndef BONUS_H
#define BONUS_H

#include <fstream>
#include <sstream>

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
    static void setBonuses(std::vector<std::unique_ptr<AnimatedSprite>> &bonuses, const std::string &filename);
};

Bonus::Bonus(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

void Bonus::setBonuses(std::vector<std::unique_ptr<AnimatedSprite>> &bonuses, const std::string &filename){
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
                std::unique_ptr<AnimatedSprite> bonus = std::make_unique<Bonus>(x, y, name);
                setObject(bonus, bonuses);
            }
        }
        input.close();
    }else{
        std::cout << "ERROR READING BONUSES FILE" << std::endl;
    }
    std::unique_ptr<AnimatedSprite> bonus1 = std::make_unique<Bonus>(25.0, -30.0, "bonus");
    std::unique_ptr<AnimatedSprite> bonus2 = std::make_unique<Bonus>(830.0, 280.0, "bonus");
    std::unique_ptr<AnimatedSprite> bonus3 = std::make_unique<Bonus>(1770.0, 680.0, "bonus");
    std::unique_ptr<AnimatedSprite> bonus4 = std::make_unique<Bonus>(20.0, 1030.0, "bonus");
    std::unique_ptr<AnimatedSprite> bonus5 = std::make_unique<Bonus>(780.0, 1050.0, "bonus");

}

#endif // BONUS_H
