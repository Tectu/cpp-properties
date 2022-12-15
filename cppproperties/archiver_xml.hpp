#pragma once

#include "archiver.hpp"

namespace tinyxml2
{
    class XMLElement;
    class XMLDocument;
}

namespace tct::properties
{

    class properties;

	/**
	 * Built-in archiver for (de)serialization to/from XML.
	 *
	 * @details This implementation uses the tinyxml2 library.
	 */
    class archiver_xml :
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
        write_recursively(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement& root, const ::tct::properties::properties& p);

        static
        void
        read_recursively(tinyxml2::XMLElement& root, ::tct::properties::properties& p);
    };

}

