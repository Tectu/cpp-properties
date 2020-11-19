#pragma once

#include <filesystem>

#include "property.hpp"

/**
 * std::filesystem::path
 */
REGISTER_PROPERTY
(
    std::filesystem::path,
    [this](){ return this->data.string(); },
    [this](const std::string& str) { *this = str; }
)