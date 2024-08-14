#include "utils.hpp"

std::deque<std::string> utils::split(const std::string& str, const std::string& splitwith) {
    std::deque<std::string> vec;

    if (splitwith.empty()) {
        for (char c : str) {
            vec.push_back(std::string(1, c));
        }
    } else {
        std::string token;
        size_t start = 0;
        size_t end = str.find(splitwith);
        
        while (end != std::string::npos) {
            token = str.substr(start, end - start);
            vec.push_back(token);
            start = end + splitwith.length();
            end = str.find(splitwith, start);
        }

        // Add the last token
        token = str.substr(start);
        vec.push_back(token);
    }

    return vec;
}

// definition of utils::undefined is in utils.hpp

bool utils::isInt(const std::string& str) {
    try {
        auto idk = std::stoi(str);
        return true;
    } catch (std::invalid_argument&) {
        return false;
    } catch (std::out_of_range&) {
        return false;
    }
}

bool utils::isAlpha(const std::string& str) {
    for (char ch : str) {
        if (!std::isalpha(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

bool utils::isSkippable(const std::string& str) {
    return str == " " || str == "\n" || str == "\t";
}

std::string utils::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}