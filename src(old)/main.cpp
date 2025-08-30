#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include "readconfig.hpp"
#include "taskbar.hpp"


int main() {
    // Создаем окно в полноэкранном режиме
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "Полноэкранное приложение", sf::Style::Fullscreen);
    
    // Читаем путь к фоновому изображению из конфигурационного файла
    std::string backgroundPath = readStringConfig("config.ini", "Settings", "BackgroundPath");

    // Загружаем фоновое изображение
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Ошибка загрузки фонового изображения!" << std::endl;
        return -1;
    }
    
    sf::Sprite backgroundSprite(backgroundTexture);


    std::cerr << "TaskbarInitError: " << TaskbarInit(window) << std::endl;
    
    // Главный цикл приложения
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Очищаем окно и рисуем фон
        window.clear();
        window.draw(backgroundSprite);
	Taskbar(window, new std::list<Task> {});
        window.display();
    }
    
    return 0;
}
