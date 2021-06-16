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

    sf::RenderWindow window(sf::VideoMode(1400, 1000), "Zombie Game");
    sf::Clock clock;
    std::vector<std::unique_ptr<AnimatedSprite>> objects;
    std::vector<std::unique_ptr<Bullet>> bullets;

    //Player
    Player player(10.0, 520.0, 100.00, 100.0, "gunner");
    player.setPos();
    player.setText();

    //Walls & enemies
    Wall::setWall(objects);
    Enemy::setEnemies(objects);

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
