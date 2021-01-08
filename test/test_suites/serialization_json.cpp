#include "../test.hpp"

#include "cppproperties/archiver_json.hpp"

#include <iostream>

TEST_SUITE("serialization - json")
{
    tct::properties::archiver_json ar;

    TEST_CASE("serialize")
    {
        test_shape dut;

        const std::string& json_str = ar.save(dut);

        //std::cout << json_str << std::endl;
    }
}
