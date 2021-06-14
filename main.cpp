#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "AnimatedSprite.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Wall.h"
#include "Bonus.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Zombie Game");
    sf::Clock clock;
    std::vector<std::unique_ptr<AnimatedSprite>> objects;
    std::vector<std::unique_ptr<Bullet>> bullets;

    //Player
    Player player(10.0, 520.0, 100.00, 100.0, "robot");
    player.setPos();
    player.setText();

    //Walls
    auto wall1 = std::make_unique<Wall>(0, 550, "wall");
    auto wall2 = std::make_unique<Wall>(0.0, 0.0, "wall");
    auto wall3 = std::make_unique<Wall>(250.0, 450.0, "wall");

    auto enemy1 = std::make_unique<Enemy>(500.0, 300.0, "duch");
    auto enemy2 = std::make_unique<Enemy>(600.0, 300.0, "duch");
    auto enemy3 = std::make_unique<Enemy>(700.0, 300.0, "duch");

    enemy1->setPos();
    enemy2->setPos();
    enemy3->setPos();
    enemy1->setText();
    enemy2->setText();
    enemy3->setText();
    objects.emplace_back(move(enemy1));
    objects.emplace_back(move(enemy2));
    objects.emplace_back(move(enemy3));

    wall1->setPos();
    wall2->setPos();
    wall3->setPos();
    wall1->setText();
    wall2->setText();
    wall3->setText();
    objects.emplace_back(move(wall1));
    objects.emplace_back(move(wall2));
    objects.emplace_back(move(wall3));

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
        player.control(time, objects);
        player.step(time);

        for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
            (*bullet)->fired(time);
            (*bullet)->step(time);
            (*bullet)->collision(bullets, objects);
        }

        //DRAW
        for (auto &rec : objects) {
            window.draw(*rec);
        }
        for (auto &rec : bullets) {
            window.draw(*rec);
        }
        window.draw(player);

        window.display();
    }


    return 0;
}
