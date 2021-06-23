#ifndef BULLETENEMYGOBLIN_H
#define BULLETENEMYGOBLIN_H

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Wall.h"

class Bulletenemygoblin : public Bullet{
public:
    Bulletenemygoblin (double x, double y, const std::string &filename);
    void setFrames();
    void mirror();
    void fired(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player, float time);
    bool verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object);
    bool horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object);
protected:
    bool horizontal_collision_ = false, vertical_collision_;
    double next_pos_x_, next_pos_y_, acceleration_;
};

Bulletenemygoblin ::Bulletenemygoblin (double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    vel_y_ = -300;
    frames_ = 19;
    current_frame_index_ = 0;
    sec_walking_ = 0;
    acceleration_ = 10;
}

void Bulletenemygoblin::mirror() {
    sf::IntRect temp = animated_walking_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x / 2, origin_y / 2);
    if (moving_right_ == true) {
        setScale(-1, 1);
    }
    if (moving_left_ == true) {
        setScale(-1, 1);
    }
}


void Bulletenemygoblin::setFrames(){
    this->addAnimationFrame(sf::IntRect(40, 40, 20, 20), animated_walking_); //rzut
    this->addAnimationFrame(sf::IntRect(140, 40, 20, 20), animated_walking_); //lądowanie
    this->addAnimationFrame(sf::IntRect(240, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(340, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(440, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(540, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(640, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(740, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(840, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(940, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1040, 40, 20, 20), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1140, 40, 20, 20), animated_walking_);//wieksze tekstury
    this->addAnimationFrame(sf::IntRect(1240, 20, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1340, 20, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1430, 20, 50, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1510, 10, 60, 60), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1610, 10, 60, 70), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1710, 10, 60, 65), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1810, 10, 60, 60), animated_walking_);
}

bool Bulletenemygoblin::verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object) {
    if (getGlobalBounds().top + getGlobalBounds().height + next_pos_y >= object->getGlobalBounds().top &&
        getGlobalBounds().top + next_pos_y <= object->getGlobalBounds().top + object->getGlobalBounds().height &&
        !(getGlobalBounds().left >= object->getGlobalBounds().left + object->getGlobalBounds().width ||
          getGlobalBounds().left + getGlobalBounds().width <= object->getGlobalBounds().left)) {
        return true;
    }
    return false;
}

bool Bulletenemygoblin::horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object) {
    if (getGlobalBounds().left + next_pos_x <= object->getGlobalBounds().left + object->getGlobalBounds().width &&
        getGlobalBounds().left + getGlobalBounds().width + next_pos_x >= object->getGlobalBounds().left &&
        !(getGlobalBounds().top >= object->getGlobalBounds().height + object->getGlobalBounds().top ||
          getGlobalBounds().top + getGlobalBounds().height <= object->getGlobalBounds().top)) {
        return true;
    }
    return false;
}
void Bulletenemygoblin::fired(float &time){
    if (moving_left_) {
        direction_ = -1;
    }
    if (moving_right_) {
        direction_ = 1;
    }

    next_pos_x_ = direction_ *  vel_x_ * time;
    next_pos_y_ =    vel_y_ * time;
    vel_y_ += acceleration_ * time * 100;

    if(!vertical_collision_){
        move(0, next_pos_y_);
    }else{
        vel_y_ = 0;
    }

    if (!horizontal_collision_) {
        move(next_pos_x_, 0);
    }
}

void Bulletenemygoblin::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player, float time){
    horizontal_collision_ = false;
    vertical_collision_ = false;
    for (auto object = objects.begin(); object < objects.end(); object++) {
        auto wall = dynamic_cast<Wall*>(object->get());
        if (wall!= nullptr) {
            if (verticalCollison(next_pos_y_, *object)) {
                vertical_collision_ = true;
            }
            if (horizontalCollison(next_pos_x_, *object)) {
                horizontal_collision_ = true;
            }
        }
    }
    fired(time);
}



#endif // BULLETENEMYGOBLIN_H
