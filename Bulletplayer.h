#ifndef BULLETPLAYER_H
#define BULLETPLAYER_H

#include <AnimatedSprite.h>
#include <Bullet.h>

class Bulletplayer : public Bullet{
public:
    Bulletplayer(double x, double y, const std::string &filename);
    Bulletplayer();
    void setFrames();
    void step(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects);
};

Bulletplayer::Bulletplayer(double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    frames_ = 5;
    current_frame_index_ = 0;
    sec_walking_ = 0;
}

void Bulletplayer::setFrames() {
    this->addAnimationFrame(sf::IntRect(0, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(172, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(344, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(516, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(688, 0, 172, 139), animated_walking_);
}

void Bulletplayer::step(float &time) {
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
}

void Bulletplayer::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects) {
    for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
        for (auto object = objects.begin(); object < objects.end(); object++) {
            auto enemy = dynamic_cast<Enemy*>(object->get());
            if ((*bullet)->getGlobalBounds().intersects((*object)->getGlobalBounds())) {
                if (enemy != nullptr) {
                    objects.erase(object);
                }
                bullets.erase(bullet);
                break;
            }
        }
    }
}

#endif // BULLETPLAYER_H
