#include <SFML/Graphics.hpp>
#include <iostream>

#include "classes/afTools.h"
#include "classes/Orbusoid.h"
#include "classes/Line.h"

using namespace std;

unsigned int width = 900;
unsigned int height = 600;
int ms_time = 1000/30;
bool clicked = false;

const unsigned int max_enemy = 20;
const unsigned int damage = 10;
const unsigned int bonus = 5;
unsigned int enemy_killed = 0;
unsigned int max_live = 300; 
unsigned int min_live = 150;

unsigned int cycle = min_live / 2;
unsigned int cycle_count = 0;

int max_player_life = 100;
int player_life = 100;

// mouse
float mx = -1;
float my = -1;

vector<Orbusoid> enemies;
sf::RenderStates filter;
sf::Font font;

Orbusoid getRandomEnemy() {
    int offset = 100;
    float x = offset + rand() % (width - offset);
    float y = offset + rand() % (height - offset);
    Orbusoid enemy(x, y);
    return enemy;
}
void initGame() {
    // globals
    player_life = max_player_life;

    // init enemies
    for (size_t i = 0; i < max_enemy; i++) {
        Orbusoid enemy = getRandomEnemy();
        enemy.life = min_live + rand() % (max_live - min_live);
        enemies.push_back(enemy);
    }
    
    // font
    font.loadFromFile("files/sansation.af");
}

void refreshValues() {
    player_life = player_life <= 0 ? 0 : player_life;
    player_life = player_life >= max_player_life ? max_player_life : player_life;
    // removes enemies
    bool enemy_destruction_in_progress = false;
    vector<Orbusoid> new_set;
    for (size_t i = 0; i < enemies.size(); i++) {
        if( ! enemies[i].endedExploding() ) {
            new_set.push_back(enemies[i]);
            if( enemies[i].life <= 0) {
                cout << "IN PROGRESS" << endl;
                enemy_destruction_in_progress = true;
            }
        }
    }
    if(enemies.size() != new_set.size()) {
        cout << new_set.size() << endl;
    }
    enemies = new_set;

    if(cycle_count >= cycle) {
        // add new enemies only when everyone exploded correctly
        if(!enemy_destruction_in_progress) {
            cycle_count = 0;
            enemies.push_back(getRandomEnemy());
            enemies.push_back(getRandomEnemy());
            enemies.push_back(getRandomEnemy());
            enemies.push_back(getRandomEnemy());
        }
    } else {
        cycle_count++;
    }
}

void printStatusInside(sf::RenderWindow &window) {
    // life bar
    sf::Vector2f anchor(10, 10);
    sf::Color color(100, 20, 240);

    float pr = 200 * ( (float)player_life / (float)max_player_life );
    sf::Vector2f life_rect_size(pr, 20);
    sf::RectangleShape rect;
    rect.setFillColor(color);
    rect.setPosition(anchor);
    rect.setSize(life_rect_size);
    window.draw(rect);

    string str(doubleToStr(enemy_killed));
    sf::Text text;
    text.setFont(font);
    text.setPosition(anchor + sf::Vector2f(10, 30));
    text.setString("Killed " + str);
    text.setFillColor(color);
    window.draw(text);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "SpaceMiner by afmika", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture background_texture;
    sf::Sprite background;
    if(background_texture.loadFromFile("images/background/space.jpg")) {
        sf::Vector2f size = (sf::Vector2f) background_texture.getSize();
        float scaleFactorX = ((float) width) / size.x;
        float scaleFactorY = ((float) height) / size.y;
        background.setScale( scaleFactorX, scaleFactorY );
        background.setTexture(background_texture);
    }

    sf::Vector2u size = window.getSize();
    width = size.x; height = size.y;

    initGame();

    Line line;
    while(window.isOpen()) {
        sf::Event e;
        mx = static_cast<float>(sf::Mouse::getPosition(window).x);
        my = static_cast<float>(sf::Mouse::getPosition(window).y);
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            if(e.type == sf::Event::MouseButtonPressed) {
               clicked = true;
            }
            if(e.type == sf::Event::MouseButtonReleased) {
               clicked = false;
               line.points.clear();
            }
            if(e.key.code == sf::Keyboard::Escape) {
                window.close();
                return 0;
            }
            if (e.type == sf::Event::Resized) {
                std::cout << "new width: " << e.size.width << std::endl;
                std::cout << "new height: " << e.size.height << std::endl;
            }
            if(e.type == sf::Event::MouseMoved) {
                // printf("%i, %i\n", x, y);
                if(clicked)
                    line.add(sf::Vector2f(mx, my));
            }
        }
        // window.draw(background);

        refreshValues();
        
        for (size_t i = 0; i < enemies.size(); i++) {
            Orbusoid *enemy = &enemies[i];
            if(enemy->life > 0)
                enemy->life--;
            bool is_killed = line.captures(*enemy) && enemy->life > 0;
            bool dead_alone = !line.captures(*enemy) && enemy->life <= 0;
            if( is_killed ) {
                enemy->destroy();
                enemy->setKilled(true);    
                player_life += bonus;
                enemy_killed++;
            }
            if( dead_alone && !enemy->is_killed ) {
                if(!enemy->is_exploding) {
                    player_life -= damage;
                }
                enemy->destroy();
                enemy->setKilled(false);
            }

            enemy->drawInside(window);
        }

        line.drawInside(window);
        printStatusInside(window);

        window.display();
        window.clear();
		sf::sleep(sf::milliseconds(ms_time));
    }

    return 0;
}
