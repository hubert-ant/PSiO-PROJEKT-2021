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
    virtual void setFrames() = 0;
    virtual void step(float &time) = 0;
    virtual void mirror() = 0;
    void setText();
    void setPos();
    void addAnimationFrame(const sf::IntRect &rectangle, std::vector<sf::IntRect> &animated);
    virtual ~AnimatedSprite() = default;
protected:
    sf::Texture texture_;
    double x_, y_, vel_x_, vel_y_, sec_, timer_;
    std::string filename_;
    bool moving_left_ = false, moving_right_ = false, moving_ = false;
    std::vector<sf::IntRect> animated_character_;
    std::vector<sf::IntRect> animated_walking_;
    int current_frame_index_ = 0, frames_ = 0;
};

class Bullet : public AnimatedSprite{
public:
    void movingRight();
    void movingLeft();
    bool moving(){}
    void setFrames();
    void mirror();
    void step(float &time);
    Bullet(double x, double y, const std::string &filename);
    void fired(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &vec);
private:

};

class Player : public AnimatedSprite{
public:
    Player(double x, double y, double vel_x, double vel_y, const std::string &filename);
    void control(float &time, std::vector<std::unique_ptr<AnimatedSprite>> &vec);
    void shoot(std::vector<std::unique_ptr<Bullet>> &vec, sf::Event &event);
    void movingLeft();
    void movingRight();
    void step(float &time);
    void setFrames();
    bool moving();
    void mirror();
    void animate(float &time);
    bool verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object);
    bool horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object);
protected:
    double acceleration_, distance_jump_, next_pos_x_, next_pos_y_;
    bool horizontal_collision_, vertical_collision_, moving_up_, moving_down_;
};

class Wall : public AnimatedSprite{
public:
    Wall(double x, double y, const std::string &filename);
    void movingRight(){}
    void movingLeft(){}
    bool moving(){}
    void setFrames(){};
    void step(float &time){}
    void mirror(){}
};

class Enemy : public AnimatedSprite{
public:
    Enemy(double x, double y, const std::string &filename);
    void movingRight(){}
    void movingLeft(){}
    bool moving(){}
    void setFrames(){}
    void step(float &time){}
    void mirror(){}
};

class Bonus : public AnimatedSprite{
public:
    Bonus(double x, double y, const std::string &filename);
    void movingRight(){}
    void movingLeft(){}
    bool moving();
    void setFrames();
    void step(float &time){}
    void mirror(){}
};

#endif // KLASY_H
