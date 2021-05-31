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

void AnimatedSprite::add_animation_frame(const sf::IntRect &rectangle, std::vector<sf::IntRect> &animated){
    animated.emplace_back(rectangle);
}

Player::Player(double x, double y, double vel_x, double vel_y, const std::string &filename){
    x_ = x;
    y_ = y;
    vel_x_ = vel_x;
    vel_y_ = vel_y;
    filename_ = filename;
    movingRight_ = true;
    frames_ = 3;
    current_frame_index_ = 0;
    sec_ = 0;
    acceleration = 2.0;
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
}

void Player::movingLeft(){
    movingLeft_ = true;
    movingRight_ = false;
}

void Player::movingRight(){
    movingLeft_ = false;
    movingRight_ = true;
}

void Bullet::movingLeft(){
    movingLeft_ = true;
}

void Bullet::movingRight(){
    movingRight_ = true;
}


void Player::control(float &time, std::vector<std::unique_ptr<AnimatedSprite>> &vec){
    if(objects_collision(vec)){
        setPosition(oldpos_x_, oldpos_y_);
    }else{
        oldpos_x_ = getPosition().x;
        oldpos_y_ = getPosition().y;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            distance_y_ = -vel_y_ * time;
            move(0, distance_y_);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            distance_x_ = -vel_x_ * time;
            this ->movingLeft();
            move(distance_x_, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            distance_y_ = vel_y_ * time;
            move(0, distance_y_);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            distance_x_ = vel_x_ * time;
            this ->movingRight();
            move(distance_x_, 0);
        }
    }
}

bool Player::objects_collision(std::vector<std::unique_ptr<AnimatedSprite>> &vec){
    for(auto &el : vec){
        if(this -> getGlobalBounds().intersects(el -> getGlobalBounds())){
            std::cout<<"CCCCCCCCCCC"<<std::endl;
            return true;
        }
    }
    std::cout<<"AAAAAAAAAAA"<<std::endl;
    return false;
}

void Player::shoot(std::vector<std::unique_ptr<Bullet>> &vec, sf::Event &event){
    if (event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left){
            float right = this->getGlobalBounds().left + this->getGlobalBounds().width;
            float y = this->getGlobalBounds().top + (this->getGlobalBounds().height/2);
            auto bullet = std::make_unique<Bullet>(right, y, "owoc");
            if(this -> movingRight_){
                bullet -> movingRight();
            }
            if(this -> movingLeft_){
                bullet -> movingLeft();
            }
            bullet->setPos();
            bullet->setText();
            vec.emplace_back(std::move(bullet));
        }
    }
}

void Bullet::fired(float &time){
    float distance = vel_x_ * time;
    if(movingLeft_){
        move(-distance, 0);
    }
    if(movingRight_){
        move(distance, 0);
    }
}

void Bullet::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &vec){
    for(auto &bull : bullets){
        for(auto &el : vec){
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
    this -> add_animation_frame(sf::IntRect(0, 0, 37, 37), animated_character_);
    //this -> add_animation_frame(sf::IntRect(50, 0, 37, 37));
    //this -> add_animation_frame(sf::IntRect(100, 0, 37, 37));
    //this -> add_animation_frame(sf::IntRect(150, 0, 37, 37));
    this -> add_animation_frame(sf::IntRect(250, 0, 37, 37), animated_walking_);
    this -> add_animation_frame(sf::IntRect(300, 0, 37, 37), animated_walking_);
    this -> add_animation_frame(sf::IntRect(350, 0, 37, 37), animated_walking_);
}

void Player::mirror(){
    sf::IntRect temp = animated_character_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x/2, origin_y/2);
    if(movingRight_ == true){
        setScale(1, 1);
    }
    if(movingLeft_ == true){
        setScale(-1, 1);
    }
}

bool Player::moving(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
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

void Player::gravity(float &time, std::vector<std::unique_ptr<AnimatedSprite>> &vec){
    for(auto &el : vec){
        Wall *wall = dynamic_cast<Wall*>(el.get());
        if(wall != nullptr){
            if(this->getGlobalBounds().intersects(wall->getGlobalBounds())){
                //this -> control(time, vec);
                //break;
            }else{
                old_pos_x_gravity_ = getPosition().x;
                old_pos_y_gravity_ = getPosition().y;
                if(objects_collision(vec)){
                    setPosition(old_pos_x_gravity_, old_pos_y_gravity_);
                }
                float distance_y = acceleration * vel_y_;
                move(0, distance_y);
                //break;
            }
        }
    }
}
