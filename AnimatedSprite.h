#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bullet;

class AnimatedSprite : public sf::Sprite {
public:
    virtual void movingLeft() = 0;
    virtual void movingRight() = 0;
    virtual bool moving() = 0;
    virtual void setFrames() = 0;
    virtual void step(float &time) = 0;
    virtual void mirror() = 0;
    virtual void control(float &time) = 0;
    virtual void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) = 0;
    void setText();
    void setPos();
    void setDirection();
    void addAnimationFrame(const sf::IntRect &rectangle, std::vector<sf::IntRect> &animated);
    static void setObject(std::unique_ptr<AnimatedSprite> &object, std::vector<std::unique_ptr<AnimatedSprite>> &objects);
    virtual ~AnimatedSprite() = default;
protected:
    sf::Texture texture_;
    double x_, y_, vel_x_, vel_y_, sec_walking_, timer_, sec_staying_;
    std::string filename_;
    bool moving_left_ = false, moving_right_ = false, moving_ = false;
    std::vector<sf::IntRect> animated_character_;
    std::vector<sf::IntRect> animated_walking_;
    int current_frame_index_ = 0, current_frame_index_staying_ = 0, frames_ = 0, frames_staying_ = 0, direction_;
};

void AnimatedSprite::setText() {
    if (!texture_.loadFromFile(filename_ + ".png")) {
        std::cerr << "Could not load texture" << std::endl;
    }
    setTexture(texture_);
}

void AnimatedSprite::setPos() {
    setPosition(x_, y_);
}

void AnimatedSprite::setDirection() {
    int temp = (std::rand()%10)+ 1;
    if(temp > 5){
        direction_ = 1;
    }else{
        direction_ = -1;
    }
}

void AnimatedSprite::addAnimationFrame(const sf::IntRect& rectangle, std::vector<sf::IntRect>& animated) {
    animated.emplace_back(rectangle);
}

void AnimatedSprite::setObject(std::unique_ptr<AnimatedSprite> &object, std::vector<std::unique_ptr<AnimatedSprite>> &objects){
    object->setPos();
    object->setText();
    object->setDirection();
    objects.emplace_back(std::move(object));
}

#endif // ANIMATEDSPRITE_H
