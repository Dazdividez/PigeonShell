#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

class DockIcon {
public:
    sf::RectangleShape shape;
    std::string name;
    
    DockIcon(float x, float y, float size, const std::string& iconName) 
        : name(iconName) {
        shape.setSize(sf::Vector2f(size, size));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(100, 100, 100, 220));
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2);
    }
    
    bool contains(float mouseX, float mouseY) const {
        return shape.getGlobalBounds().contains(mouseX, mouseY);
    }
};

class Dock {
private:
    std::vector<DockIcon> icons;
    sf::RectangleShape background;
    float totalWidth = 0;
    
public:
    Dock() {
        background.setFillColor(sf::Color(50, 50, 50, 220));
        background.setOutlineColor(sf::Color::White);
        background.setOutlineThickness(2);
    }
    
    void addIcon(const std::string& name) {
        float iconSize = 60;
        float spacing = 20;
        
        icons.emplace_back(0, 0, iconSize, name);
        totalWidth = icons.size() * iconSize + (icons.size() - 1) * spacing;
        background.setSize(sf::Vector2f(totalWidth + 40, 80));
    }
    
    void updatePosition() {
        background.setPosition(0, 0);
        
        float iconSize = 60;
        float spacing = 20;
        float startX = 20;
        
        for (size_t i = 0; i < icons.size(); ++i) {
            float x = startX + i * (iconSize + spacing);
            float y = 10;
            icons[i].shape.setPosition(x, y);
        }
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(background);
        for (auto& icon : icons) {
            window.draw(icon.shape);
        }
    }
    
    std::string getClickedIcon(float mouseX, float mouseY) {
        for (auto& icon : icons) {
            if (icon.contains(mouseX, mouseY)) {
                return icon.name;
            }
        }
        return "";
    }
    
    sf::Vector2f getSize() const {
        return background.getSize();
    }
};

// Функция для установки поверх всех окон
void setWindowAlwaysOnTop(sf::Window& window) {
#ifdef _WIN32
    // Для Windows
    HWND hwnd = window.getSystemHandle();
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#elif defined(__linux__)
    // Для Linux (требует xdotool или xprop)
    system(("xdotool windowactivate " + std::to_string(window.getSystemHandle())).c_str());
#endif
}

// Функция для отключения фокуса у окна
void setWindowNoFocus(sf::Window& window) {
#ifdef _WIN32
    HWND hwnd = window.getSystemHandle();
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_NOACTIVATE);
#endif
}

int main() {
    // Получаем реальные размеры экрана
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.width;
    unsigned int screenHeight = desktop.height;
    
    std::cout << "Screen size: " << screenWidth << "x" << screenHeight << std::endl;
    
    // Создаем док
    Dock dock;
    dock.addIcon("Browser");
    dock.addIcon("Editor");
    dock.addIcon("Terminal");
    dock.addIcon("Settings");
    dock.updatePosition();
    
    // Получаем размер дока
    sf::Vector2f dockSize = dock.getSize();
    
    // Рассчитываем позицию для нижнего края экрана
    int windowX = (screenWidth - dockSize.x) / 2;
    int windowY = screenHeight - dockSize.y - 10;
    
    // Настройки для прозрачного окна
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    // Создаем окно с флагом AlwaysOnTop
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(dockSize.x), 
                                        static_cast<unsigned int>(dockSize.y)), 
                          "Dock", 
                          sf::Style::None | sf::Style::AlwaysOnTop, // Важно!
                          settings);
    
    // Устанавливаем позицию
    window.setPosition(sf::Vector2i(windowX, windowY));
    window.setFramerateLimit(60);
    
    // Дополнительные настройки для "поверх всех"
    setWindowAlwaysOnTop(window);
    setWindowNoFocus(window);
    
    std::cout << "Dock is always on top!" << std::endl;
    
    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                std::string clicked = dock.getClickedIcon(
                    static_cast<float>(mousePos.x), 
                    static_cast<float>(mousePos.y)
                );
                if (!clicked.empty()) {
                    std::cout << "Clicked: " << clicked << std::endl;
                }
            }
            
            // Игнорируем события фокуса
            if (event.type == sf::Event::GainedFocus || event.type == sf::Event::LostFocus) {
                // Ничего не делаем, окно всегда должно быть поверх
            }
        }
        
        // Периодически обновляем позицию поверх всех
        static sf::Clock refreshClock;
        if (refreshClock.getElapsedTime().asSeconds() > 1.0f) {
            setWindowAlwaysOnTop(window);
            refreshClock.restart();
        }
        
        window.clear(sf::Color::Transparent);
        dock.draw(window);
        window.display();
    }
    
    return 0;
}
