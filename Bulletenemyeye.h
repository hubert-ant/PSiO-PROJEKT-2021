#ifndef BULLETENEMYEYE_H
#define BULLETENEMYEYE_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include <AnimatedSprite.h>
#include <Bullet.h>

class Bulletenemy : public Bullet{
public:
    Bulletenemy(double x, double y, const std::string &filename);
};

Bulletenemy::Bulletenemy(double x, double y, const std::string &filename){
    vel_x_ = 200;
    frames_ = 5;
    current_frame_index_ = 0;
    sec_walking_ = 0;
}

#endif // BULLETENEMYEYE_H
