#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class AnimatedSprite : public sf::Sprite {
public:
    virtual void movingLeft() = 0;
    virtual void movingRight() = 0;
    virtual bool moving() = 0;
    virtual void setFrames() = 0;
    virtual void step(float& time) = 0;
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

void AnimatedSprite::setText() {
    if (!texture_.loadFromFile(filename_ + ".png")) {
        std::cerr << "Could not load texture" << std::endl;
    }
    setTexture(texture_);
}

void AnimatedSprite::setPos() {
    setPosition(x_, y_);
}

void AnimatedSprite::addAnimationFrame(const sf::IntRect& rectangle, std::vector<sf::IntRect>& animated) {
    animated.emplace_back(rectangle);
}

#endif // ANIMATEDSPRITE_H
