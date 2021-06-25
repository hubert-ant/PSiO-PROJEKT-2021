#ifndef BULLETENEMYEYE_H
#define BULLETENEMYEYE_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Player.h"
#include "Wall.h"

class Bulletenemyeye : public Bullet{
public:
    Bulletenemyeye(double x, double y, const std::string &filename);
    void setFrames();
    void mirror();
    void fired(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player, float time);
};

Bulletenemyeye::Bulletenemyeye(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    frames_ = 3;
    current_frame_index_ = 0;
    sec_walking_ = 0;
}

void Bulletenemyeye::mirror() {
    sf::IntRect temp = animated_walking_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x / 2, origin_y / 2);
    if (moving_right_ == true) {
        setScale(1, 1);
    }
    if (moving_left_ == true) {
        setScale(-1, 1);
    }
}

void Bulletenemyeye::setFrames(){
    this->addAnimationFrame(sf::IntRect(0, 0, 48, 48), animated_walking_);
    this->addAnimationFrame(sf::IntRect(48, 0, 48, 48), animated_walking_);
    this->addAnimationFrame(sf::IntRect(96, 0, 48, 48), animated_walking_);
}

void Bulletenemyeye::fired(float &time){
    float distance = vel_x_ * time;
    if (moving_left_) {
        move(-distance, 0);
    }
    if (moving_right_) {
        move(distance, 0);
    }
}

void Bulletenemyeye::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player, float time){
    for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
        for (auto object = objects.begin(); object < objects.end(); object++) {
            auto wall = dynamic_cast<Wall*>(object->get());
            if ((*bullet)->getGlobalBounds().intersects(player.getGlobalBounds())){
                bullets.erase(bullet);
                player.subtractHp(1);
                break;
            }
            if ((*bullet)->getGlobalBounds().intersects((*object)->getGlobalBounds())) {
                if (wall != nullptr) {
                    bullets.erase(bullet);
                    break;
                }
            }

        }
    }
}


#endif // BULLETENEMYEYE_H
