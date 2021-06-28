#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <sstream>

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
#include "Key.h"
#include "Doors.h"

int main() {

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Dungeon Escape");
    sf::Clock clock;
    std::vector<std::unique_ptr<AnimatedSprite>> objects;
    std::vector<std::unique_ptr<AnimatedSprite>> bonuses;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Bullet>> bullets_enemy_eye;
    std::vector<std::unique_ptr<Bullet>> bullets_enemy_goblin;
    std::vector<std::unique_ptr<Hpbar>> hp_bar;
    sf::Text score;//score
    sf::Font font;
    font.loadFromFile("AGENCYB.ttf");
    score.setPosition(window.getSize().x - 100, window.getSize().y - 40);
    score.setFont(font);
    score.setFillColor(sf::Color::Red);
    score.setCharacterSize(32);

    Point point_show(window.getSize().x - 70, window.getSize().y - 30, "point");
    point_show.setPos();
    point_show.setText();

    sf::View view( sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Vector2f(window.getSize().x, window.getSize().y));
    //view.zoom(3);

    //Player
    Player player(100.0, 520.0, 100.0, 0.0, "gunner");
    player.setPos();
    player.setText();

    //Walls & enemies
    Wall::setWall(objects);
//    Enemyeye::setEnemies(objects);
//    Enemygoblin::setEnemies(objects);
    Bonus::setBonuses(bonuses);
    Point::setPoints(objects);
    Hpbar::createPlayerHp(hp_bar, player.checkBaseHp());

    Key key_collect(1760, 1180, "key");
    key_collect.setPos();
    key_collect.setText();

    Key key_show(window.getSize().x - 30, window.getSize().y - 30, "key");
    key_show.setPos();
    key_show.setText();

    Doors doors(1750, 15, "doors");
    doors.setPos();
    doors.setText();
    doors.setScale(2.0, 2.0);

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
        window.setView(view);

        //LOGIC
        player.checkCollision(objects);
        player.checkCollisionBonus(bonuses);
        player.control(time);
        player.step(time);
        player.moveView(view, window, hp_bar, key_show, score, point_show);
        player.collectKey(key_collect);

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
        if(!player.checkKey()){
            window.draw(key_collect);
        }else{
            window.draw(key_show);
        }
        window.draw(doors);
        window.draw(player);
        window.draw(score);
        window.draw(point_show);

        window.display();
    }


    return 0;
}
