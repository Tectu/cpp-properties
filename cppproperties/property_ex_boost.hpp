#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>

#include "property.hpp"

REGISTER_PROPERTY(
    boost::uuids::uuid,
    [this]{ return boost::uuids::to_string(this->data); },
    [this](const std::string& str){ this->data = boost::uuids::string_generator()(str); }
)
