#include <iostream>

#include "cppproperties/properties.hpp"
#include "cppproperties/archiver_xml.hpp"

struct base
{
public:
    void set_x(const int x) { m_x = x; }
    [[nodiscard]] int x() const { return m_x; }

private:
    int m_x = 0;
};

struct derived :
    base,
    tct::cppproperties::properties
{
    derived()
    {
        LINK_PROPERTY_FUNCTIONS(x, int, base::set_x, base::x)
    }
};

int main()
{
    // Create an XML archiver
    tct::cppproperties::archiver_xml ar;

    derived d1;
    d1.set_x(42);

    derived d2;
    d2.load(ar, d1.save(ar));

    std::cout << d1.save(ar) << std::endl;
    std::cout << d2.save(ar) << std::endl;
}
