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
    std::unique_ptr<AnimatedSprite> enemy1 = std::make_unique<Enemyeye>(200.0, 10.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy2 = std::make_unique<Enemyeye>(500.0, 20.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy3 = std::make_unique<Enemyeye>(1300.0, 15.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy4 = std::make_unique<Enemyeye>(1150.0, 30.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy5 = std::make_unique<Enemyeye>(900.0, 15.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy6 = std::make_unique<Enemyeye>(700.0, 250.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy7 = std::make_unique<Enemyeye>(1200.0, 250.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy8 = std::make_unique<Enemyeye>(1400.0, 350.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy9 = std::make_unique<Enemyeye>(800.0, 540.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy10 = std::make_unique<Enemyeye>(1100.0, 520.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy11 = std::make_unique<Enemyeye>(435.0, 720.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy12 = std::make_unique<Enemyeye>(1260.0, 750.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy13 = std::make_unique<Enemyeye>(375.0, 940.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy14 = std::make_unique<Enemyeye>(850.0, 970.0, 100.0, "Eye");
    std::unique_ptr<AnimatedSprite> enemy15 = std::make_unique<Enemyeye>(1050.0, 900.0, 100.0, "Eye");
    setObject(enemy1, objects);
    setObject(enemy2, objects);
    setObject(enemy3, objects);
    setObject(enemy4, objects);
    setObject(enemy5, objects);
    setObject(enemy6, objects);
    setObject(enemy7, objects);
    setObject(enemy8, objects);
    setObject(enemy9, objects);
    setObject(enemy10, objects);
    setObject(enemy11, objects);
    setObject(enemy12, objects);
    setObject(enemy13, objects);
    setObject(enemy14, objects);
    setObject(enemy15, objects);
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
