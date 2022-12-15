#include "3rdparty/nlohmann_json/json.hpp"

#include "archiver_json.hpp"
#include "properties.hpp"

using namespace tct::properties;

std::string
archiver_json::save(const properties& p) const
{
    nlohmann::json json;

    for (const auto& [key, value] : p) {
        json[key] = value->to_string();
    }

    return json.dump(4);
}

std::pair<bool, std::string>
archiver_json::load(properties& p, const std::string& str) const
{
    nlohmann::json json(str);

    return { true, "success" };
}
