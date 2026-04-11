#pragma once

#include <string>

class Encrypt {
private:

public:
    Encrypt();
	std::string encrypt(std::string path, std::string key);
	std::string decrypt(std::string path, std::string key);
};

