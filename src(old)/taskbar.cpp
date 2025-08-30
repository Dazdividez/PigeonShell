#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "readconfig.hpp"
#include "taskbar.hpp"


class Task {
public:
    std::string icon;
    std::string name;
    std::string path;
    Task() {
    
    }
private:
};

int taskbarWidth, taskbarHeight, taskbarX, taskbarY;
float blurAmount, opacity;
sf::RectangleShape taskbar;

int TaskbarInit(const sf::RenderWindow &window) { 
    blurAmount = readFloatConfig("config.ini", "Taskbar", "BlurAmount");
    opacity = readFloatConfig("config.ini", "Taskbar", "Opacity");
    taskbarWidth = readFloatConfig("config.ini", "Taskbar", "PanelWidth");
    taskbarHeight = readFloatConfig("config.ini", "Taskbar", "PanelHeight");
    taskbarX = readFloatConfig("config.ini", "Taskbar", "PanelX");
    taskbarY = readFloatConfig("config.ini", "Taskbar", "PanelY");
    
    sf::Vector2u size = window.getSize();

    if (taskbarX < 0) taskbarX = size.x + taskbarX + 1;
    if (taskbarY < 0) taskbarY = size.y + taskbarX + 1;
    if (taskbarWidth < 0) taskbarWidth = size.x + taskbarWidth + 1;
    if (taskbarHeight < 0) taskbarHeight = size.y + taskbarHeight + 1;

    taskbar = sf::RectangleShape(sf::Vector2f(taskbarWidth, taskbarHeight));
    taskbar.setPosition(taskbarX, taskbarY);

    return 0;
}

int Taskbar(sf::RenderWindow &window, std::list<Task> &tasks) {
    window.draw(taskbar);

    return 0;
}
