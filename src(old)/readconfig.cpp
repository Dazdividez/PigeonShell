#include "readconfig.hpp"

// Функция для чтения пути из конфигурационного файла
std::string readStringConfig(const std::string& filename, const std::string& section, const std::string& key) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    
    std::string line;
    bool inSection = false;
    while (std::getline(file, line)) {
        if (line == "[" + section + "]") {
            inSection = true;
            continue;
        }
        
        if (inSection) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                std::string currentKey = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                
                if (currentKey == key) {
                    return value;
                }
            }
        }
    }
    return "";
}

float readFloatConfig(const std::string& filename, const std::string& section, const std::string& key) {
    std::ifstream file(filename);
    if (!file.is_open()) return 0.0f;

    std::string line;
    bool inSection = false;
    while (std::getline(file, line)) {
        if (line == "" + section + "") {
            inSection = true;
            continue;
        }

        if (inSection) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                std::string currentKey = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                if (currentKey == key) {
                    return std::stof(value);
                }
            }
        }
    }
    return 0.0f;
}
