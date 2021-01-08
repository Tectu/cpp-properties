#pragma once

#include "archiver.hpp"

namespace tct::properties
{

    class properties;

    class archiver_json :
        public archiver
    {
    public:
        [[nodiscard]] std::string save(const properties& p) const override;
        std::pair<bool, std::string> load(properties& p, const std::string& str) const override;

    private:
        static void write_recursively();
        static void read_recursively();
    };

}
