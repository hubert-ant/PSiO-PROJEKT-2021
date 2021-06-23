#ifndef BULLETPLAYER_H
#define BULLETPLAYER_H

#include "AnimatedSprite.h"
#include "Bullet.h"

class Bulletplayer : public Bullet{
public:
    Bulletplayer(double x, double y, const std::string &filename);
    Bulletplayer();
    void setFrames();
    void mirror();
    void fired(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player);
};

Bulletplayer::Bulletplayer(double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    frames_ = 5;
    current_frame_index_ = 0;
    sec_walking_ = 0;
}

void Bulletplayer::mirror() {
    sf::IntRect temp = animated_walking_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x / 2, origin_y / 2);
    if (moving_right_ == true) {
        setScale(0.1, 0.1);
    }
    if (moving_left_ == true) {
        setScale(-0.1, 0.1);
    }
}

void Bulletplayer::setFrames() {
    this->addAnimationFrame(sf::IntRect(0, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(172, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(344, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(516, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(688, 0, 172, 139), animated_walking_);
}

void Bulletplayer::fired(float &time){
    float distance = vel_x_ * time;
    if (moving_left_) {
        move(-distance, 0);
    }
    if (moving_right_) {
        move(distance, 0);
    }
}

void Bulletplayer::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player) {
    for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
        for (auto object = objects.begin(); object < objects.end(); object++) {
            auto enemy = dynamic_cast<Enemy*>(object->get());
            if ((*bullet)->getGlobalBounds().intersects((*object)->getGlobalBounds())) {
                if (enemy != nullptr) {
                    objects.erase(object);
                }
                bullets.erase(bullet);
                break;
            }
        }
    }
}

#endif // BULLETPLAYER_H
