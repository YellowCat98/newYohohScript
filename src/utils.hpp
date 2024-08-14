#pragma once
#include <deque>
#include <string>
#include <map>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>


namespace utils {
    std::deque<std::string> split(const std::string& str, const std::string& splitwith);
    template <typename T>
    bool undefined(std::map<std::string, T> map, const std::string& key) {
        return map.find(key) == map.end();
    }
    bool isInt(const std::string& str);
    bool isAlpha(const std::string& str);
    bool isSkippable(const std::string& str);

    std::string readFile(const std::string& filePath);
}