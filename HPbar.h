#ifndef HPBAR_H
#define HPBAR_H

#include "AnimatedSprite.h"
#include "Player.h"
#include "Bonus.h"

class Hpbar : public AnimatedSprite{
public:
    virtual void movingLeft() {}
    virtual void movingRight() {}
    virtual bool moving() {}
    virtual void setFrames() {}
    virtual void step(float &time) {}
    virtual void mirror() {}
    virtual void control(float &time) {}
    virtual void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
    Hpbar(double x, double y, const std::string &filename);
    static void createPlayerHp(std::vector<std::unique_ptr<Hpbar>> &bar,  Player &player);
    static void subtractPlayerHp(std::vector<std::unique_ptr<Hpbar>> &bar,  Player &player);
};

Hpbar::Hpbar(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

void Hpbar::createPlayerHp(std::vector<std::unique_ptr<Hpbar>> &bar, Player &player){
    int quantity = player.checkBaseHp();
    for(int i = 0; i < quantity; i++){
        double pos_x = i * 32;
        auto hp = std::make_unique<Hpbar>(0.0 + pos_x, 600.0, "heart");
        hp -> setPos();
        hp -> setText();
        bar.emplace_back(std::move(hp));
    }
}

#endif // HPBAR_H
