#pragma once

#include <QtGlobal>
#include <QString>

#include "property.hpp"

REGISTER_PROPERTY
(
    QString,
    [this](){ return this->data.toStdString(); },
    [this](const std::string& str) { *this = QString::fromStdString(str); }
)
