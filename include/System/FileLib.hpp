#pragma once

// Функции для упрощения работы с файловой системой

#include <vector>
#include <string>
#include <filesystem>

std::vector<std::filesystem::directory_entry> FilesList(std::string path);
