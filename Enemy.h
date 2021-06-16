#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "AnimatedSprite.h"

class Enemy : public AnimatedSprite {
public:
    Enemy(double x, double y, const std::string &filename);
    void movingRight() {}
    void movingLeft() {}
    bool moving() {}
    void setFrames() {}
    void step(float& time) {}
    void mirror() {}
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
};

Enemy::Enemy(double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
}

void Enemy::setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects){
    std::unique_ptr<AnimatedSprite> enemy1 = std::make_unique<Enemy>(500.0, 300.0, "duch");
    std::unique_ptr<AnimatedSprite> enemy2 = std::make_unique<Enemy>(600.0, 300.0, "duch");
    std::unique_ptr<AnimatedSprite> enemy3 = std::make_unique<Enemy>(700.0, 300.0, "duch");
    setObject(enemy1, objects);
    setObject(enemy2, objects);
    setObject(enemy3, objects);
}

#endif // ENEMY_H
