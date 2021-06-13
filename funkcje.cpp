#include "klasy.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void AnimatedSprite::setText(){
    if (!texture_.loadFromFile(filename_ + ".png")) {
        std::cerr << "Could not load texture" << std::endl;
    }
    setTexture(texture_);
}

void AnimatedSprite::setPos(){
    setPosition(x_, y_);
}

void AnimatedSprite::addAnimationFrame(const sf::IntRect &rectangle, std::vector<sf::IntRect> &animated){
    animated.emplace_back(rectangle);
}

Player::Player(double x, double y, double vel_x, double vel_y, const std::string &filename){
    x_ = x;
    y_ = y;
    vel_x_ = vel_x;
    vel_y_ = vel_y;
    filename_ = filename;
    moving_right_ = true;
    frames_ = 3;
    current_frame_index_ = 0;
    sec_ = 0;
    acceleration_ = 2;
    moving_up_ = false;
    moving_down_ = false;
}

Wall::Wall(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

Enemy::Enemy(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
}

Bullet::Bullet(double x, double y, const std::string &filename){
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    frames_ = 5;
    current_frame_index_ = 0;
    sec_ = 0;
}

void Player::movingLeft(){
    moving_left_ = true;
    moving_right_ = false;
}

void Player::movingRight(){
    moving_left_ = false;
    moving_right_ = true;
}

void Bullet::movingLeft(){
    moving_left_ = true;
}

void Bullet::movingRight(){
    moving_right_ = true;
}

void Player::control(float &time, std::vector<std::unique_ptr<AnimatedSprite>> &vec){
    horizontal_collision_ = false;
    vertical_collision_ = false;
    next_pos_y_ = vel_y_ * time;
    for(const auto &rec : vec){
        if(verticalCollison(next_pos_y_, rec)){
            vertical_collision_ = true;
        }
        if(horizontalCollison(next_pos_x_, rec)){
            horizontal_collision_ = true;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        next_pos_x_ = -vel_x_ * time;
        this ->movingLeft();
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        next_pos_x_ = vel_x_ * time;
        this ->movingRight();
    }else{
        next_pos_x_ = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){
        moving_up_ = true;
    }
    if(!moving_up_){
        if(!vertical_collision_){
           move(0, next_pos_y_);
        }
    }else{
        move(0, -next_pos_y_);
        distance_jump_ += next_pos_y_;
        if(vertical_collision_ || distance_jump_ > 150){
           moving_up_ = false;
           distance_jump_ = 0;
        }
    }
    if(!horizontal_collision_){
        move(next_pos_x_, 0);
    }
}

bool Player::verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object){
    if(getGlobalBounds().top + getGlobalBounds().height + next_pos_y >= object->getGlobalBounds().top &&
            getGlobalBounds().top + next_pos_y <= object->getGlobalBounds().top + object->getGlobalBounds().height &&
            !(getGlobalBounds().left >= object->getGlobalBounds().left + object->getGlobalBounds().width ||
            getGlobalBounds().left + getGlobalBounds().width <= object->getGlobalBounds().left)){
        return true;
    }
    return false;
}

bool Player::horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object){
    if(getGlobalBounds().left + next_pos_x <= object->getGlobalBounds().left + object->getGlobalBounds().width &&
            getGlobalBounds().left + getGlobalBounds().width + next_pos_x >= object->getGlobalBounds().left &&
            !(getGlobalBounds().top >= object->getGlobalBounds().height + object->getGlobalBounds().top ||
            getGlobalBounds().top + getGlobalBounds().height <= object->getGlobalBounds().top)){
        return true;
    }
    return false;
}

void Player::shoot(std::vector<std::unique_ptr<Bullet>> &vec, sf::Event &event){
    if (event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left){
            float x, y;
            if(this->moving_right_){
                x = this->getGlobalBounds().left + this->getGlobalBounds().width;
            }else{
                x = this->getGlobalBounds().left;
            }
            y = this->getGlobalBounds().top + (this->getGlobalBounds().height/2);
            auto bullet = std::make_unique<Bullet>(x, y, "bullet");
            if(this -> moving_right_){
                bullet -> movingRight();
            }
            if(this -> moving_left_){
                bullet -> movingLeft();
            }
            bullet->setPos();
            bullet->setText();
            bullet->setFrames();
            bullet->mirror();
            vec.emplace_back(std::move(bullet));
        }
    }
}

void Bullet::fired(float &time){
    float distance = vel_x_ * time;
    if(moving_left_){
        move(-distance, 0);
    }
    if(moving_right_){
        move(distance, 0);
    }
}

void Bullet::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects){
    for(auto &bull : bullets){
        for(auto &el : objects){
            Enemy *enemy = dynamic_cast<Enemy*>(el.get());
            if(bull->getGlobalBounds().intersects(el->getGlobalBounds())){
                if(enemy != nullptr){
                    el->setPosition(10000000, 1000000);
                    bull->setPosition(10000000, 1000000);
                }else{
                    bull->setPosition(10000000, 1000000);
                }
            }
        }
    }
}

void Player::setFrames(){
    this -> addAnimationFrame(sf::IntRect(0, 0, 567, 556), animated_character_);
    this -> addAnimationFrame(sf::IntRect(567, 0, 567, 556), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(1134, 0, 567, 556), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(1701, 0, 567, 556), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(2268, 0, 567, 556), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(2835, 0, 567, 556), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(3402, 0, 567, 556), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(3969, 0, 567, 556), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(4536, 0, 567, 556), animated_walking_);
}

void Player::mirror(){
    sf::IntRect temp = animated_character_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x/2, origin_y/2);
    if(moving_right_ == true){
        setScale(0.1, 0.1);
    }
    if(moving_left_ == true){
        setScale(-0.1, 0.1);
    }
}

bool Player::moving(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
       return true;
    }
    return false;
}

void Player::step(float &time){
    sec_ += time;
    setFrames();
    mirror();
    if(!moving()){
        setTextureRect(animated_character_[0]);
    }else{
        if(sec_ >= 1.0/frames_){
            setTextureRect(animated_walking_[current_frame_index_]);
            if(current_frame_index_ >= animated_walking_.size() - 1){
               current_frame_index_ = 0;
            }else{
               current_frame_index_++;
            }
            sec_ = 0;
        }
    }
}

void Bullet::mirror(){
    sf::IntRect temp = animated_walking_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x/2, origin_y/2);
    if(moving_right_ == true){
        setScale(0.1, 0.1);
    }
    if(moving_left_ == true){
        setScale(-0.1, 0.1);
    }
}

void Bullet::setFrames(){
    this -> addAnimationFrame(sf::IntRect(0, 0, 172, 139), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(172, 0, 172, 139), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(344, 0, 172, 139), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(516, 0, 172, 139), animated_walking_);
    this -> addAnimationFrame(sf::IntRect(688, 0, 172, 139), animated_walking_);
}

void Bullet::step(float &time){
    sec_ += time;
    if(sec_ >= 1.0/frames_){
        setTextureRect(animated_walking_[current_frame_index_]);
        if(current_frame_index_ >= animated_walking_.size() - 1){
            current_frame_index_ = 0;
        }else{
            current_frame_index_++;
        }
        sec_ = 0;
    }
}
