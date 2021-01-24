#include "../test.hpp"

#include <boost/uuid/random_generator.hpp>

TEST_SUITE("boost")
{
    struct foo :
        tct::properties::properties
    {
        MAKE_PROPERTY(id, boost::uuids::uuid);
    };

    TEST_CASE("boost::uuids::uuid")
    {
        SUBCASE("raw")
        {
            foo f;
            f.id = boost::uuids::string_generator()("0ae3f611-7541-4a1a-a6a3-b0ecd2e4ab67");
            REQUIRE_EQ(f.id, boost::uuids::string_generator()("0ae3f611-7541-4a1a-a6a3-b0ecd2e4ab67"));

            const std::string& id_str = boost::uuids::to_string(f.get_property<boost::uuids::uuid>("id"));
            REQUIRE_EQ(id_str, "0ae3f611-7541-4a1a-a6a3-b0ecd2e4ab67");
        }
    }
}
