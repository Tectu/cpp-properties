#pragma once

#include "archiver.hpp"

namespace tct::properties
{

    class properties;

	/**
	 * Built-in archiver for (de)serialization to/from JSON.
	 *
	 * @details This implementation uses `nlohmann::json`.
	 */
    class archiver_json :
        public archiver
    {
    public:
        [[nodiscard]]
		std::string
		save(const properties& p) const override;

        std::pair<bool, std::string>
		load(properties& p, const std::string& str) const override;

    private:
        static
        void
        write_recursively();

        static
        void
        read_recursively();
    };

}


#include <nlohmann/json.hpp>

#include "properties.hpp"

namespace tct::properties
{

    inline
    std::string
    archiver_json::save(const properties& p) const
    {
        nlohmann::json json;

        for (const auto& [key, value] : p) {
            json[key] = value->to_string();
        }

        return json.dump(4);
    }

    inline
    std::pair<bool, std::string>
    archiver_json::load(properties& p, const std::string& str) const
    {
        nlohmann::json json(str);

        return { true, "success" };
    }

}
