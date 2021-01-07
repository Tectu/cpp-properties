#pragma once

#include "archiver.hpp"

namespace tct::cppproperties
{
    class archiver_gpds :
        public archiver
    {
    public:
        [[nodiscard]] std::string save(const properties& p) const override;
        std::pair<bool, std::string> load(properties& p, const std::string& str) const override;
    };
}
