#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Bulletplayer.h"
#include "Bulletenemyeye.h"
#include "Bulletenemygoblin.h"
#include "Enemy.h"
#include "Enemyeye.h"
#include "Enemygoblin.h"
#include "Player.h"
#include "Wall.h"
#include "Bonus.h"
#include "HPbar.h"
#include "Point.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(1400, 1000), "Zombie Game");
    sf::Clock clock;
    std::vector<std::unique_ptr<AnimatedSprite>> objects;
    std::vector<std::unique_ptr<AnimatedSprite>> bonuses;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Bullet>> bullets_enemy_eye;
    std::vector<std::unique_ptr<Bullet>> bullets_enemy_goblin;
    std::vector<std::unique_ptr<Hpbar>> hp_bar;
    srand(time(NULL));

    //Player
    Player player(10.0, 520.0, 100.00, 0.0, "gunner");
    player.setPos();
    player.setText();

    //Walls & enemies
    Wall::setWall(objects);
    Enemyeye::setEnemies(objects);
    Enemygoblin::setEnemies(objects);
    Bonus::setBonuses(bonuses);
    Point::setPoints(objects);
    Hpbar::createPlayerHp(hp_bar, player);

    //loop
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        //EVENTS
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                player.shoot(bullets);
        }
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        window.clear(sf::Color::Black);

        //LOGIC
        player.checkCollision(objects);
        player.checkCollisionBonus(bonuses);
        player.control(time);
        player.step(time);

        //Hpbar::subtractPlayerHp(hp_bar, player);

        //tworzenie pociskow przeciwnikow
        for (auto object = objects.begin(); object < objects.end(); object++) {
            auto enemyeye = dynamic_cast<Enemyeye*>(object->get());
            auto enemygoblin = dynamic_cast<Enemygoblin*>(object->get());
            if (enemyeye != nullptr) {
                (*object)->shoot(bullets_enemy_eye);
            }
            if (enemygoblin != nullptr) {
                (*object)->shoot(bullets_enemy_goblin);
            }
            (*object)->step(time);
            (*object)->control(time);
        }
        //obsluga pociskow przeciwnikow
        for (auto bullet_en_eye = bullets_enemy_eye.begin(); bullet_en_eye < bullets_enemy_eye.end(); ++bullet_en_eye) {
            (*bullet_en_eye)->fired(time);
            (*bullet_en_eye)->step(time);
            (*bullet_en_eye)->collision(bullets_enemy_eye, objects, player, time);
        }
        for (auto bullet_en_goblin = bullets_enemy_goblin.begin(); bullet_en_goblin < bullets_enemy_goblin.end(); ++bullet_en_goblin) {
            (*bullet_en_goblin)->step(time);
            (*bullet_en_goblin)->collision(bullets_enemy_goblin, objects, player, time);
        }

        for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
            (*bullet)->fired(time);
            (*bullet)->step(time);
            (*bullet)->collision(bullets, objects, player, time);
        }

        //DRAW
        for (auto &rec : objects) {
            window.draw(*rec);
        }
        for (auto &rec : bullets) {
            window.draw(*rec);
        }
        for (auto &rec : bullets_enemy_eye) {
            window.draw(*rec);
        }
        for (auto &rec : bullets_enemy_goblin) {
            window.draw(*rec);
        }
        for (auto &rec : bonuses) {
            window.draw(*rec);
        }
        for (auto it = hp_bar.begin(); it < hp_bar.begin() + player.checkHp() ; it++) {
            window.draw(**it);
        }
        window.draw(player);

        window.display();
    }


    return 0;
}
