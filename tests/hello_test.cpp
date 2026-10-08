#include <gtest/gtest.h>
#include "person.h"

class Formula
{
public:
    static int square(int x)
    {
        return x * x;
    }
};

namespace person
{






    




TEST(HelloTest, BasicAssertions)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);

    Person p("Alice", 30);

    EXPECT_EQ(p.getName(), "Alice");
    EXPECT_EQ(p.getAge(), 30);

    EXPECT_EQ(Formula::square(5), 25);
    EXPECT_EQ(Formula::square(0), 0);

    int* n = nullptr;

    ASSERT_EQ(n, nullptr);

    Person p2("Alice", 30);

    ASSERT_EQ(Formula::square(5), 25);
    ASSERT_EQ(Formula::square(0), 0);
}

} // namespace person