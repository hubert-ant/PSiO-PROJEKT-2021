#ifndef ENEMYGOBLIN_H
#define ENEMYGOBLIN_H

#include "Enemy.h"
#include "Bulletenemygoblin.h"

class Enemygoblin : public Enemy{
public:
    Enemygoblin(double x, double y, double vx, const std::string &filename);
    void setFrames();
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
    void step(float &time);
    void shoot( std::vector<std::unique_ptr<Bullet>> &bullets);
};

Enemygoblin::Enemygoblin(double x, double y, double vx, const std::string &filename) {
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
}

void Enemygoblin::setFrames(){
    this->addAnimationFrame(sf::IntRect(55, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(205, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(355, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(505, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(655, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(805, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(955, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1105, 50, 40, 50), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1255, 50, 40, 50), animated_character_);
    this->addAnimationFrame(sf::IntRect(1405, 50, 40, 50), animated_character_);
    this->addAnimationFrame(sf::IntRect(1555, 50, 40, 50), animated_character_);
    this->addAnimationFrame(sf::IntRect(1705, 50, 40, 50), animated_character_);
}
void Enemygoblin::setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects){
    std::unique_ptr<AnimatedSprite> enemy1 = std::make_unique<Enemygoblin>(435.0, 525.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy2 = std::make_unique<Enemygoblin>(235.0, 355.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy3 = std::make_unique<Enemygoblin>(120.0, 75.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy4 = std::make_unique<Enemygoblin>(888.0, 155.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy5 = std::make_unique<Enemygoblin>(1290.0, 54.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy6 = std::make_unique<Enemygoblin>(802.0, 404.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy7 = std::make_unique<Enemygoblin>(450.0, 824.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy8 = std::make_unique<Enemygoblin>(768.0, 725.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy9 = std::make_unique<Enemygoblin>(886.0, 879.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy10 = std::make_unique<Enemygoblin>(1296.0, 980.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy11 = std::make_unique<Enemygoblin>(1192.0, 1194.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy12 = std::make_unique<Enemygoblin>(665.0, 1194.0, 100.0, "goblin");
    std::unique_ptr<AnimatedSprite> enemy13 = std::make_unique<Enemygoblin>(1219.0, 614.0, 100.0, "goblin");
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
}

void Enemygoblin::step(float &time){
    setFrames();
    mirror();
    if (!moving()) {
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

void Enemygoblin::shoot(std::vector<std::unique_ptr<Bullet>> &bullets){
    float x, y;
    int los = (std::rand()%200)+ 1;
    if(los < 2){
        if (direction_ > 0) {
            x = this->getGlobalBounds().left + this->getGlobalBounds().width;
        } else {
            x = this->getGlobalBounds().left;
        }
        y = this->getGlobalBounds().top + (this->getGlobalBounds().height / 2);
        auto bullet = std::make_unique<Bulletenemygoblin>(x, y, "bullet_enemygoblin");
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


#endif // ENEMYGOBLIN_H
