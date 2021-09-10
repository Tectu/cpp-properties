#pragma once

#include <stdexcept>

namespace tct::properties
{

	/**
	 * Exception indicating that a non-existing property was accessed.
	 */
    struct property_nonexist :
        std::runtime_error
    {
		/**
		 * Constructor.
		 *
		 * @param _property_name The name of the property that does not exist.
		 */
        explicit
		property_nonexist(const std::string& _property_name) :
            std::runtime_error("property \"" + _property_name + "\" does not exist."),
            property_name(_property_name)
        {
        }

    private:
        std::string property_name;
    };

	/**
	 * Exception indicating that a property already exists.
	 */
    struct property_exists :
        std::runtime_error
    {
		/**
		 * Constructor.
		 *
		 * @param _property_name The name of the property that exists.
		 */
        explicit
		property_exists(const std::string& _property_name) :
            std::runtime_error("property \"" + _property_name + "\" exists already."),
            property_name(_property_name)
        {
        }

    private:
        std::string property_name;
    };
}

