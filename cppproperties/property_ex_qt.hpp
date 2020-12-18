#pragma once

#include <charconv>
#include <QtGlobal>
#include <QString>
#include <QPoint>

#include "property.hpp"

REGISTER_PROPERTY
(
    QString,
    [this](){ return this->data.toStdString(); },
    [this](const std::string& str) { *this = QString::fromStdString(str); }
)

REGISTER_PROPERTY
(
    QPoint,
    [this]()
    {
        return std::to_string(data.x()) + ";" + std::to_string(data.y());
    },
    [this](const std::string& str)
    {
        std::string::size_type separator_pos = str.find_first_of(';');
        if (separator_pos == std::string::npos)
            throw std::runtime_error("Could not find separation character.");

        // Parse X
        if (const auto [p, ec] = std::from_chars(str.data(), str.data()+separator_pos, data.rx()); ec != std::errc())
            throw std::runtime_error("could not parse string \"" + str + "\" into QPoint.");

        // Parse Y
        if (const auto [p, ec] = std::from_chars(str.data()+separator_pos+1, str.data()+str.size(), data.ry()); ec != std::errc())
            throw std::runtime_error("could not parse string \"" + str + "\" into QPoint.");
    }
)
