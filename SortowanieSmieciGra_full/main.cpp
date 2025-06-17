
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

struct Trash {
    sf::Sprite sprite;
    std::string category;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sortowanie Śmieci");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) return -1;

    // Load bin textures
    std::vector<std::string> categories = {"szklo", "papier", "zmieszane", "plastik"};
    std::vector<sf::Texture> binTextures(4);
    std::vector<sf::Sprite> bins(4);

    for (int i = 0; i < 4; ++i) {
        binTextures[i].loadFromFile("assets/bins/" + categories[i] + ".png");
        bins[i].setTexture(binTextures[i]);
        bins[i].setPosition(100 + i * 160, 450);
    }

    // Load trash textures
    std::vector<std::pair<std::string, std::string>> trashData = {
        {"butelka.png", "plastik"}, {"gazeta.png", "papier"}, {"sloik.png", "szklo"}, {"resztki.png", "zmieszane"}
    };

    std::vector<sf::Texture> trashTextures(trashData.size());
    std::vector<Trash> trashItems;

    for (size_t i = 0; i < trashData.size(); ++i) {
        trashTextures[i].loadFromFile("assets/trash/" + trashData[i].first);
        sf::Sprite sprite(trashTextures[i]);
        sprite.setPosition(350, 100);
        trashItems.push_back({sprite, trashData[i].second});
    }

    srand(static_cast<unsigned>(time(nullptr)));
    int current = rand() % trashItems.size();
    int score = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                for (int i = 0; i < 4; ++i) {
                    if (bins[i].getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                        if (categories[i] == trashItems[current].category) {
                            score++;
                        }
                        current = rand() % trashItems.size();
                        break;
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        for (auto& bin : bins) window.draw(bin);
        window.draw(trashItems[current].sprite);

        sf::Text scoreText("Wynik: " + std::to_string(score), font, 24);
        scoreText.setPosition(10, 10);
        scoreText.setFillColor(sf::Color::Black);
        window.draw(scoreText);

        window.display();
    }

    return 0;
}
