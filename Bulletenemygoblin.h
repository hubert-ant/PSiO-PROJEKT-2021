#ifndef BULLETENEMYGOBLIN_H
#define BULLETENEMYGOBLIN_H

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Wall.h"
#include "Player.h"

class Bulletenemygoblin : public Bullet{
public:
    Bulletenemygoblin (double x, double y, const std::string &filename);
    void setFrames();
    void mirror();
    void fired(float &time);
    void step(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player, float time);
    bool verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object);
    bool horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object);
    void del(std::vector<std::unique_ptr<Bullet>> &bullets, Player &player);
    double getPosx();
    double getPosy();
    sf::FloatRect getCollisionBound();
protected:
    bool horizontal_collision_ = false, vertical_collision_;
    double next_pos_x_, next_pos_y_, acceleration_;
    int to_delete_;
};

Bulletenemygoblin ::Bulletenemygoblin (double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    vel_y_ = -300;
    frames_ = 18;
    current_frame_index_ = 0;
    sec_walking_ = 0;
    acceleration_ = 10;
    to_delete_ = 0;
}

double Bulletenemygoblin::getPosx(){
    return getPosition().x;
}

double Bulletenemygoblin::getPosy(){
    return getPosition().y;
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
    this->addAnimationFrame(sf::IntRect(0, 0, 100, 100), animated_character_);
    this->addAnimationFrame(sf::IntRect(100, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(200, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(300, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(400, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(500, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(600, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(700, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(800, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(900, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1000, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1100, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1200, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1300, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1400, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1500, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1600, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1700, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1800, 0, 100, 100), animated_walking_);

//    this->addAnimationFrame(sf::IntRect(48, 42, 10, 16), animated_character_); //rzut
//    this->addAnimationFrame(sf::IntRect(148, 42, 10, 16), animated_walking_); //lądowanie
//    this->addAnimationFrame(sf::IntRect(248, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(348, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(448, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(548, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(648, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(748, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(848, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(948, 42, 10, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(1044, 44, 16, 16), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(1144, 44, 16, 16), animated_walking_);//wieksze tekstury
//    this->addAnimationFrame(sf::IntRect(1235, 33, 35, 35), animated_walking_);//tu jest git
//    this->addAnimationFrame(sf::IntRect(1331, 27, 35, 40), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(1430, 20, 50, 50), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(1500, 0, 100, 100), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(1600, 0, 100, 100), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(1700, 0, 100, 100), animated_walking_);
//    this->addAnimationFrame(sf::IntRect(1800, 0, 100, 100), animated_walking_);

}

sf::FloatRect Bulletenemygoblin::getCollisionBound(){
    sf::FloatRect collisonbox = getGlobalBounds();
    collisonbox.left += 48;
    collisonbox.top += 48;
    collisonbox.width = 9;
    collisonbox.height = 9;
    return collisonbox;
}

bool Bulletenemygoblin::verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object) {
    if (getCollisionBound().top + getCollisionBound().height + next_pos_y >= object->getGlobalBounds().top &&
        getCollisionBound().top + next_pos_y <= object->getGlobalBounds().top + object->getGlobalBounds().height &&
        !(getCollisionBound().left >= object->getGlobalBounds().left + object->getGlobalBounds().width ||
          getCollisionBound().left + getCollisionBound().width <= object->getGlobalBounds().left)) {
        return true;
    }
    return false;
}

bool Bulletenemygoblin::horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object) {
    if (getCollisionBound().left + next_pos_x <= object->getGlobalBounds().left + object->getGlobalBounds().width &&
        getCollisionBound().left + getCollisionBound().width + next_pos_x >= object->getGlobalBounds().left &&
        !(getCollisionBound().top >= object->getGlobalBounds().height + object->getGlobalBounds().top ||
          getCollisionBound().top + getCollisionBound().height <= object->getGlobalBounds().top)) {
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

void Bulletenemygoblin::del(std::vector<std::unique_ptr<Bullet>> &bullets, Player &player){
    for (auto bullet = bullets.begin(); bullet < bullets.end(); bullet++){
        if(to_delete_ == 1){
            if((player.getPosition().x > getPosx() - 50 && player.getPosition().y <= getPosy() - 30) ||
                    (player.getPosition().x < getPosx() + 50 && player.getPosition().y <= getPosy() - 30) ){//nie do konca dziala
                player.subtractHp(0);
            }
            bullets.erase(bullet);
            break;
        }
    }
}

void Bulletenemygoblin::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player, float time){
    horizontal_collision_ = false;
    vertical_collision_ = false;
    for (auto object = objects.begin(); object < objects.end(); object++) {
        auto wall = dynamic_cast<Wall*>(object->get());
        if (wall != nullptr) {
            if (verticalCollison(next_pos_y_, *object)) {
                vertical_collision_ = true;
            }
            if (horizontalCollison(next_pos_x_, *object)) {
                horizontal_collision_ = true;
            }
        }      
    }
    fired(time);
    del(bullets, player);
}

void Bulletenemygoblin::step(float &time){
    if(!vertical_collision_){
        setTextureRect(animated_character_[0]);
    }else{
        if (sec_walking_ == 0) {
            setTextureRect(animated_walking_[current_frame_index_]);
            if (current_frame_index_ >= animated_walking_.size() - 1) {
                to_delete_ = 1;
            } else {
                current_frame_index_++;
            }
        }
        sec_walking_ += time;
        if (sec_walking_ >= 1.0 / frames_) {
            sec_walking_ = 0;
        }
    }
}

#endif // BULLETENEMYGOBLIN_H
