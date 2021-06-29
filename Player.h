#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include "AnimatedSprite.h"
#include "Bulletplayer.h"
#include "Point.h"
#include "HPbar.h"
#include "Key.h"

class Player : public AnimatedSprite {
public:
    Player(double x, double y, double vel_x, double vel_y, const std::string &filename);
    void control(float &time);
    void shoot(std::vector<std::unique_ptr<Bullet>> &vec);
    void movingLeft();
    void movingRight();
    void step(float &time);
    void setFrames();
    bool moving();
    void mirror();
    void animate(float &time);
    bool verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object);
    bool horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object);
    void checkCollision(std::vector<std::unique_ptr<AnimatedSprite>> &vec);
    void collisionEnemy(std::vector<std::unique_ptr<AnimatedSprite>> &vec);
    void checkCollisionBonus(std::vector<std::unique_ptr<AnimatedSprite>> &bonuses);
    void collectPoints(std::vector<std::unique_ptr<AnimatedSprite>> &points);
    int checkHp();
    void subtractHp(int how_many);
    void addHp(int how_many);
    int checkBaseHp();
    void subtractLifes();
    void addPoints();
    void moveView(sf::View &view, sf::RenderWindow &window, std::vector<std::unique_ptr<Hpbar>> &bar, Key &key, sf::Text &text, Point &point);
    void collectKey(Key &key);
    bool checkKey();
    void checkCollisonDoors(sf::Event &event); //wygranie gry
    void checkLifes(); // przegranie gry
    int checkPoints();
protected:
    double acceleration_, distance_jump_, next_pos_x_, next_pos_y_;
    bool horizontal_collision_, vertical_collision_, moving_up_, got_key_;
    std::vector<sf::IntRect> animated_jumping_;
    int base_hp_, hp_, how_many_to_delete_, how_many_to_add_, lifes_, delete_life_, points_;
};

void Player::moveView(sf::View &view, sf::RenderWindow &window, std::vector<std::unique_ptr<Hpbar>> &bar, Key &key, sf::Text &text, Point &point){
    float player_x = getPosition().x;
    float player_y = getPosition().y;
    float window_x = window.getSize().x/2;
    float window_y = window.getSize().y/2;
    std::stringstream stream;
    stream << checkPoints();
    text.setString(stream.str());
    if(player_x > window_x && player_x < 2 * window_x){
        if(!horizontal_collision_){
            if(moving()){
                for(auto &rec : bar){
                    rec->move(next_pos_x_, 0);
                }
                view.move(next_pos_x_, 0);
                key.move(next_pos_x_, 0);
                text.move(next_pos_x_, 0);
                point.move(next_pos_x_, 0);
            }
        }
    }
    if(player_y > window_y && player_y < 2 * window_y){
        if(!vertical_collision_){
            for(auto &rec : bar){
                rec->move(0, next_pos_y_);
            }
            view.move(0, next_pos_y_);
            key.move(0, next_pos_y_);
            text.move(0, next_pos_y_);
            point.move(0, next_pos_y_);
        }
    }

}

Player::Player(double x, double y, double vel_x, double vel_y, const std::string &filename) {
    x_ = x;
    y_ = y;
    vel_x_ = vel_x;
    vel_y_ = vel_y;
    filename_ = filename;
    moving_right_ = true;
    frames_ = 6;
    frames_staying_ = 5;
    current_frame_index_ = 0;
    current_frame_index_staying_ = 0;
    sec_walking_ = 0;
    sec_staying_ = 0;
    acceleration_ = 10;
    moving_up_ = false;
    base_hp_ = 10;
    hp_ = base_hp_;
    lifes_ = 3;
    points_ = 0;
    got_key_ = false;
}

void Player::movingLeft() {
    moving_left_ = true;
    moving_right_ = false;
}

void Player::movingRight() {
    moving_left_ = false;
    moving_right_ = true;
}

void Player::checkCollision(std::vector<std::unique_ptr<AnimatedSprite>> &vec){
    horizontal_collision_ = false;
    vertical_collision_ = false;
    for (auto it = vec.begin(); it < vec.end(); it++) {
        if (verticalCollison(next_pos_y_, *it)) {
            vertical_collision_ = true;
        }
        if (horizontalCollison(next_pos_x_, *it)) {
            horizontal_collision_ = true;
        }
    }
}

void Player::collisionEnemy(std::vector<std::unique_ptr<AnimatedSprite>> &vec){
    for (auto it = vec.begin(); it < vec.end(); it++){
        auto enemy = dynamic_cast<Enemy*>(it->get());
        if(enemy != nullptr){
            if(this->getGlobalBounds().intersects(enemy->getGlobalBounds())){
                subtractLifes();
                break;
            }
        }
    }
}

void Player::collectPoints(std::vector<std::unique_ptr<AnimatedSprite>> &points){
    for (auto it = points.begin(); it < points.end(); it++){
        if(this->getGlobalBounds().intersects((*it)->getGlobalBounds())){
            points.erase(it);
            addPoints();
            break;
        }
    }
}

void Player::control(float &time) {
    vel_y_ += acceleration_ * time * 100;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        next_pos_x_ = -vel_x_ * time;
        this->movingLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        next_pos_x_ = vel_x_ * time;
        this->movingRight();
    } else {
        next_pos_x_ = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !moving_up_) {
        moving_up_ = true;
        vel_y_ = -500;
    }
    next_pos_y_ = vel_y_ * time;
    if(!vertical_collision_){
        move(0, next_pos_y_);
    }else{
        vel_y_ = 0;
    }

    if(vertical_collision_ && vel_y_ >= 0){
        moving_up_ = false;
    }

    if (!horizontal_collision_) {
        move(next_pos_x_, 0);
    }
}

bool Player::verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object) {
    if (getGlobalBounds().top + getGlobalBounds().height + next_pos_y >= object->getGlobalBounds().top &&
        getGlobalBounds().top + next_pos_y <= object->getGlobalBounds().top + object->getGlobalBounds().height &&
        !(getGlobalBounds().left >= object->getGlobalBounds().left + object->getGlobalBounds().width ||
          getGlobalBounds().left + getGlobalBounds().width <= object->getGlobalBounds().left)) {
        return true;
    }
    return false;
}

bool Player::horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object) {
    if (getGlobalBounds().left + next_pos_x <= object->getGlobalBounds().left + object->getGlobalBounds().width &&
        getGlobalBounds().left + getGlobalBounds().width + next_pos_x >= object->getGlobalBounds().left &&
        !(getGlobalBounds().top >= object->getGlobalBounds().height + object->getGlobalBounds().top ||
          getGlobalBounds().top + getGlobalBounds().height <= object->getGlobalBounds().top)) {
        return true;
    }
    return false;
}

void Player::shoot(std::vector<std::unique_ptr<Bullet>> &vec) {
    float x, y;
    if (this->moving_right_) {
        x = this->getGlobalBounds().left + this->getGlobalBounds().width;
    } else {
        x = this->getGlobalBounds().left;
    }
    y = this->getGlobalBounds().top + (this->getGlobalBounds().height / 2);
    auto bullet = std::make_unique<Bulletplayer>(x, y, "bullet");
    if (this->moving_right_) {
        bullet->movingRight();
    }
    if (this->moving_left_) {
        bullet->movingLeft();
    }
    bullet->setPos();
    bullet->setText();
    bullet->setFrames();
    bullet->mirror();
    vec.emplace_back(std::move(bullet));
}

void Player::setFrames() {
    this->addAnimationFrame(sf::IntRect(0, 0, 48, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(48, 0, 48, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(96, 0, 48, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(144, 0, 48, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(192, 0, 48, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(240, 0, 48, 40), animated_walking_);
    this->addAnimationFrame(sf::IntRect(288, 0, 48, 40), animated_character_);
    this->addAnimationFrame(sf::IntRect(336, 0, 48, 40), animated_character_);
    this->addAnimationFrame(sf::IntRect(384, 0, 48, 40), animated_character_);
    this->addAnimationFrame(sf::IntRect(432, 0, 48, 40), animated_character_);
    this->addAnimationFrame(sf::IntRect(480, 0, 48, 40), animated_character_);
    this->addAnimationFrame(sf::IntRect(576, 0, 48, 40), animated_jumping_);
}

void Player::mirror() {
    sf::IntRect temp = animated_character_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x / 2, origin_y / 2);
    if (moving_right_ == true) {
        setScale(1, 1);
    }
    if (moving_left_ == true) {
        setScale(-1, 1);
    }
}

bool Player::moving() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return true;
    }
    return false;
}

void Player::step(float &time) {
    setFrames();
    mirror();
    if(vertical_collision_){
        if (!moving()) {
            if (sec_staying_ == 0) {
                setTextureRect(animated_character_[current_frame_index_staying_]);
                if (current_frame_index_staying_ >= animated_character_.size() - 1) {
                    current_frame_index_staying_ = 0;
                } else {
                    current_frame_index_staying_++;
                }
            }
            sec_staying_ += time;
            if (sec_staying_ >= 1.0 / frames_staying_) {
                sec_staying_ = 0;
            }
            sec_walking_ = 0;
        }else {
            if (sec_walking_ == 0) {
                setTextureRect(animated_walking_[current_frame_index_]);
                if (current_frame_index_ >= animated_walking_.size() - 1) {
                    current_frame_index_ = 0;
                } else {
                    current_frame_index_++;
                }
            }
            sec_walking_ += time;
            if (sec_walking_ >= 1.0 / frames_) {
                sec_walking_ = 0;
            }
            sec_staying_ = 0;
        }
    }else{
        setTextureRect(animated_jumping_[0]);
        sec_staying_ = 0;
        sec_walking_ = 0;
    }
    //std::cout << points_ <<  std::endl;
}

int Player::checkBaseHp(){
    return base_hp_;
}

int Player::checkHp(){
    if(hp_ <= 0){
        subtractLifes();
    }
    return hp_;
}

void Player::subtractHp(int how_many){
    hp_ -= how_many;
}

void Player::addHp(int how_many){
    if(hp_ < 10){
        hp_ += how_many;
    }
}

void Player::subtractLifes(){
    setPosition(x_, y_);
    vel_y_ = 0;
    lifes_ -= 1;
    hp_ = base_hp_;
}

void Player::checkCollisionBonus(std::vector<std::unique_ptr<AnimatedSprite>> &bonuses){
    for(auto it = bonuses.begin(); it < bonuses.end(); it++){
        if(this->getGlobalBounds().intersects((*it)->getGlobalBounds())){
            addHp(1);
            bonuses.erase(it);
            break;
        }
    }
}

void Player::addPoints(){
    points_ += 1;
}

void Player::collectKey(Key &key){
    if(this->getGlobalBounds().intersects(key.getGlobalBounds())){
        key.setCollected();
        got_key_ = true;
    }
}

bool Player::checkKey(){
    return got_key_;
}

void Player::checkLifes(){
    if(lifes_ <=0){
        //przegrana
    }
}

int Player::checkPoints(){
    return points_;
}

#endif // PLAYER_H
