#ifndef BULLETENEMYGOBLIN_H
#define BULLETENEMYGOBLIN_H

#include <SFML/Graphics.hpp>

#include <AnimatedSprite.h>
#include <Bullet.h>

class Bulletenemygoblin : public Bullet{
public:
    Bulletenemygoblin (double x, double y, const std::string &filename);
    Bulletenemygoblin ();
    void setFrames() {}
    void step(float &time){}
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects){}
};

Bulletenemygoblin ::Bulletenemygoblin (double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    frames_ = 5;
    current_frame_index_ = 0;
    sec_walking_ = 0;
}

#endif // BULLETENEMYGOBLIN_H
