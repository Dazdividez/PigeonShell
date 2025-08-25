#include <string>
#include <sstream>
#include <fstream>

// Функция для чтения пути из конфигурационного файла
std::string readStringConfig(const std::string& filename, const std::string& section, const std::string& key);

float readFloatConfig(const std::string& filename, const std::string& section, const std::string& key);
