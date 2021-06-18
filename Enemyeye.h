#ifndef ENEMYEYE_H
#define ENEMYEYE_H

#include <Enemy.h>

class Enemyeye : public Enemy{
public:
    Enemyeye(double x, double y, double vx, const std::string &filename);
    void setFrames();
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
};

Enemyeye::Enemyeye(double x, double y, double vx, const std::string &filename) {
    x_ = x;
    y_ = y;
    vel_x_ = vx;
    filename_ = filename;
    frames_ = 6;
    current_frame_index_ = 0;
    sec_walking_ = 0;
    direction_ = (std::rand()%2)+ -1;
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
    std::unique_ptr<AnimatedSprite> enemy1 = std::make_unique<Enemyeye>(500.0, 320.0, 100.0, "Flight");
    std::unique_ptr<AnimatedSprite> enemy2 = std::make_unique<Enemyeye>(600.0, 300.0, 100.0, "Flight");
    std::unique_ptr<AnimatedSprite> enemy3 = std::make_unique<Enemyeye>(700.0, 300.0, 100.0, "Flight");
    setObject(enemy1, objects);
    setObject(enemy2, objects);
    setObject(enemy3, objects);
}



#endif // ENEMYEYE_H
