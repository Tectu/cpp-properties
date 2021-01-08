#pragma once

namespace gpds
{
    class container;
}

namespace tct::properties
{
    class properties;

    class archiver_gpds
    {
    public:
        [[nodiscard]] gpds::container save(const properties& p) const;
        std::pair<bool, std::string> load(properties&p, const gpds::container& c) const;

    private:
        static void write_recursively(gpds::container& root, const ::tct::properties::properties& p);
        static void read_recursively(const gpds::container& root, ::tct::properties::properties& p);
    };
}
