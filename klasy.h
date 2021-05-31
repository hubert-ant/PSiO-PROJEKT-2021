#ifndef KLASY_H
#define KLASY_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class AnimatedSprite : public sf::Sprite{
public:
    virtual void movingLeft() = 0;
    virtual void movingRight() = 0;
    virtual bool moving() = 0;
    void setText();
    void setPos();
    void add_animation_frame(const sf::IntRect &rectangle, std::vector<sf::IntRect> &animated);
    virtual ~AnimatedSprite() = default;
protected:
    sf::Texture texture_;
    double x_, y_, vel_x_, vel_y_, sec_;
    std::string filename_;
    bool movingLeft_ = false, movingRight_ = false, moving_ = false;
    std::vector<sf::IntRect> animated_character_;
    std::vector<sf::IntRect> animated_walking_;
    int current_frame_index_ = 0, frames_ = 0;
};

class Bullet : public AnimatedSprite{
public:
    void movingRight();
    void movingLeft();
    bool moving(){}
    Bullet(double x, double y, const std::string &filename);
    void fired(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &vec);
private:

};

class Player : public AnimatedSprite{
public:
    Player(double x, double y, double vel_x, double vel_y, const std::string &filename);
    void control(float &time, std::vector<std::unique_ptr<AnimatedSprite>> &vec);
    bool objects_collision(std::vector<std::unique_ptr<AnimatedSprite>> &vec);
    void gravity(float &time, std::vector<std::unique_ptr<AnimatedSprite>> &vec);
    void shoot(std::vector<std::unique_ptr<Bullet>> &vec, sf::Event &event);
    void movingLeft();
    void movingRight();
    void step(float &time);
    void setFrames();
    bool moving();
    void mirror();
    void animate(float &time);
protected:
    double acceleration, distance_jump_, distance_x_, distance_y_, oldpos_y_, oldpos_x_,
            old_pos_x_gravity_, old_pos_y_gravity_;
};

class Wall : public AnimatedSprite{
public:
    Wall(double x, double y, const std::string &filename);
    void movingRight(){}
    void movingLeft(){}
    bool moving(){}
};

class Enemy : public AnimatedSprite{
public:
    Enemy(double x, double y, const std::string &filename);
    void movingRight(){}
    void movingLeft(){}
    bool moving(){}
};

#endif // KLASY_H
