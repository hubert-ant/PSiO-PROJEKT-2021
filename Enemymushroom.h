#ifndef ENEMYMUSHROOM_H
#define ENEMYMUSHROOM_H

#include <fstream>

#include "Enemy.h"
#include "Player.h"
#include "Key.h"
#include "Wall.h"
class Enemymushroom : public Enemy{
public:
    Enemymushroom(double x, double y, double vx, const std::string &filename);
    void setFrames();
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename);
    void step(float &time);
    void shoot( std::vector<std::unique_ptr<Bullet>> &bullets) {}
    void checkKeyCollected(Key &key);
    void chasingPlayer(Player &player, float &time);
    bool verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object);
    void checkCollision(std::vector<std::unique_ptr<AnimatedSprite>> &vec);
protected:
    bool move_ = false, vertical_collision_ = false;
    float next_pos_x_mushroom_, next_pos_y_mushroom_, acceleration_;
};

Enemymushroom::Enemymushroom(double x, double y, double vx, const std::string &filename) {
    x_ = x;
    y_ = y;
    vel_x_ = vx;
    filename_ = filename;
    frames_ = 8;
    frames_staying_ = 4;
    current_frame_index_ = 0;
    current_frame_index_staying_ = 0;
    sec_walking_ = 0;
    sec_staying_ = 0;
    direction_ = (std::rand()%2)+ -1;
    timer_ = 0;
    acceleration_ = 9;
    setFrames();
}

void Enemymushroom::setFrames(){
    this->addAnimationFrame(sf::IntRect(64, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(214, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(364, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(514, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(664, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(814, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(964, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1114, 64, 22, 37), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1264, 64, 22, 37), animated_character_);
    this->addAnimationFrame(sf::IntRect(1414, 64, 22, 37), animated_character_);
    this->addAnimationFrame(sf::IntRect(1564, 64, 22, 37), animated_character_);
    this->addAnimationFrame(sf::IntRect(1714, 64, 22, 37), animated_character_);
}
void Enemymushroom::setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename){
    std::fstream input(filename);
    if(input.good()){
        for(std::string line; getline(input, line);){
            if(line[0] != '$'){
                float x, y, vel_x;
                std::string name;
                std::stringstream stream(line);
                stream >> x;
                stream >> y;
                stream >> vel_x;
                stream >> name;
                std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Enemymushroom>(x, y, vel_x, name);
                setObject(enemy, objects);
            }
        }
        input.close();
    }else{
        std::cout << "ERROR READING MUSHROOMS FILE" << std::endl;
    }
}

void Enemymushroom::checkKeyCollected(Key &key){
    if(key.checkCollected()){
        move_ = true;
    }
}

bool Enemymushroom::verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object) {
    if (getGlobalBounds().top + getGlobalBounds().height + next_pos_y >= object->getGlobalBounds().top &&
        getGlobalBounds().top + next_pos_y <= object->getGlobalBounds().top + object->getGlobalBounds().height &&
        !(getGlobalBounds().left >= object->getGlobalBounds().left + object->getGlobalBounds().width ||
          getGlobalBounds().left + getGlobalBounds().width <= object->getGlobalBounds().left)) {
        return true;
    }
    return false;
}

void Enemymushroom::checkCollision(std::vector<std::unique_ptr<AnimatedSprite>> &vec){//??
    vertical_collision_ = false;
    for (auto it = vec.begin(); it < vec.end(); it++) {
        auto wall = dynamic_cast<Wall*>(it->get());
        if(wall != nullptr){
            if (verticalCollison(next_pos_y_mushroom_, *it)) {
                vertical_collision_ = true;
            }
        }
    }
}

void Enemymushroom::chasingPlayer(Player &player, float &time){
    if(move_){
        if(player.getPosition().x > this -> getPosition().x){
            direction_ = 1;
        }else{
            direction_ = -1;
        }
        vel_y_ += acceleration_ * time * 100;
        next_pos_y_mushroom_ = vel_y_ * time;
        next_pos_x_mushroom_ = direction_ * vel_x_ * time;
        if((fabs(player.getPosition().x - this->getPosition().x) > 0) || (fabs(player.getPosition().y - this->getPosition().y) > 0) ){
            if(this->getPosition().x > 0 && this->getPosition().x < 1800){
                move(next_pos_x_mushroom_, 0);
            }
        }

        if(!vertical_collision_){
            move(0, next_pos_y_mushroom_);
        }else{
            vel_y_ = 0;
        }
    }
}

void Enemymushroom::step(float &time){
    mirror();
    if (!move_) {
        if (sec_staying_ == 0) {
            setTextureRect(animated_character_[current_frame_index_staying_]);
            if (current_frame_index_staying_ >= animated_character_.size() - 1) {
                current_frame_index_staying_ = 0;
            } else {
                current_frame_index_staying_++;
            }
        }
        sec_staying_ += time;
        if (sec_staying_ >= 1.0 / frames_staying_) {
            sec_staying_ = 0;
        }
        sec_walking_ = 0;
    }else {
        if (sec_walking_ == 0) {
            setTextureRect(animated_walking_[current_frame_index_]);
            if (current_frame_index_ >= animated_walking_.size() - 1) {
                current_frame_index_ = 0;
            } else {
                current_frame_index_++;
            }
        }
        sec_walking_ += time;
        if (sec_walking_ >= 1.0 / frames_) {
            sec_walking_ = 0;
        }
        sec_staying_ = 0;
    }
}

#endif // ENEMYMUSHROOM_H
