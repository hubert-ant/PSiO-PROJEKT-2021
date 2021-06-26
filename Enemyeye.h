#ifndef ENEMYEYE_H
#define ENEMYEYE_H

#include "Enemy.h"
#include "Bulletenemyeye.h"

class Enemyeye : public Enemy{
public:
    Enemyeye(double x, double y, double vx, const std::string &filename);
    void setFrames();
    void step(float &time);
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets);
};

Enemyeye::Enemyeye(double x, double y, double vx, const std::string &filename) {
    x_ = x;
    y_ = y;
    vel_x_ = vx;
    filename_ = filename;
    frames_ = 6;
    current_frame_index_ = 0;
    sec_walking_ = 0;
    timer_ = 0;
}

void Enemyeye::setFrames(){
    this->addAnimationFrame(sf::IntRect(55, 50, 40, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(205, 50, 40, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(355, 50, 40, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(505, 50, 40, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(655, 50, 40, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(805, 50, 40, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(955, 50, 40, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1105, 50, 40, 40), animated_walking_);
}

void Enemyeye::setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects){
    std::unique_ptr<AnimatedSprite> enemy1 = std::make_unique<Enemyeye>(500.0, 320.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy2 = std::make_unique<Enemyeye>(600.0, 300.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy3 = std::make_unique<Enemyeye>(700.0, 300.0, 100.0, "Eye");
    setObject(enemy1, objects);
    setObject(enemy2, objects);
    setObject(enemy3, objects);
}

void Enemyeye::step(float &time){
    sec_walking_ += time;
    setFrames();
    mirror();
    if (sec_walking_ >= 1.0 / frames_) {
        setTextureRect(animated_walking_[current_frame_index_]);
        if (current_frame_index_ >= animated_walking_.size() - 1) {
            current_frame_index_ = 0;
        } else {
            current_frame_index_++;
        }
        sec_walking_ = 0;
    }
}

void Enemyeye::shoot(std::vector<std::unique_ptr<Bullet>> &bullets){
    float x, y;
    int los = (std::rand()%150)+ 1;
    if(los < 2){
        if (direction_ > 0) {
            x = this->getGlobalBounds().left + this->getGlobalBounds().width;
        } else {
            x = this->getGlobalBounds().left;
        }
        y = this->getGlobalBounds().top + (this->getGlobalBounds().height / 2);
        auto bullet = std::make_unique<Bulletenemyeye>(x, y, "bullet_enemyeye");
        if (direction_ > 0) {
            bullet->movingRight();
        }
        if (direction_ < 0) {
            bullet->movingLeft();
        }
        bullet->setPos();
        bullet->setText();
        bullet->setFrames();
        bullet->mirror();
        bullets.emplace_back(std::move(bullet));
    }
}

#endif // ENEMYEYE_H
