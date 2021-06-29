#ifndef ENEMYGOBLIN_H
#define ENEMYGOBLIN_H

#include "Enemy.h"
#include "Bulletenemygoblin.h"

class Enemygoblin : public Enemy{
public:
    Enemygoblin(double x, double y, double vx, const std::string &filename);
    void setFrames();
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename);
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
void Enemygoblin::setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects, const std::string &filename){
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
                std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Enemygoblin>(x, y, vel_x, name);
                setObject(enemy, objects);
            }
        }
        input.close();
    }else{
        std::cout << "ERROR READING GOBLIN FILE" << std::endl;
    }
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
