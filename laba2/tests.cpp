#include <gtest/gtest.h>
#include "money.cpp"

// Constructor

TEST(constructor_test01, default_constructor)
{
    Money a = Money();
    std::string b{'0'};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 1);
}

TEST(constructor_test02, fill_constructor)
{
    Money a = Money(5,'1');
    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(),5);
}

TEST(constructor_test03, initializer_list_constructor)
{
    Money a {'1','1','1','1','1'};
    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 5);
}

TEST(constructor_test04, string_constructor)
{
    std::string str = "11111";
    Money a = Money(str);

    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 5);
}

TEST(constructor_test05, copy_constructor)
{
    Money first {'1','1','1','1','1'};
    Money second = Money(first);

    std::string b{"11111"};

    EXPECT_EQ(second.get_string_value(), b);
    EXPECT_EQ(second.get_size(), 5);
}

TEST(constructor_test06, rvalue_constructor)
{
    Money a = {"11111"};
    std::string b{"11111"};

    EXPECT_EQ(a.get_string_value(), b);
    EXPECT_EQ(a.get_size(), 5);
}

TEST(constructor_test07, error_input)
{
    try{
        Money a {"11ab4"};
    }catch(std::exception &ex){
        EXPECT_STREQ(ex.what(),"not digit input");
    }
}

// Operators testing
TEST(o_test01, basic_test_set)
{
    // 1.00 + 0.01 = 1.01
    Money a {"001"};
    Money b {'1'};
    Money c {"101"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test02, basic_test_set)
{
    // 500.00 + 500.00 = 1000.00
    Money a {"00005"};
    Money b {"00005"};
    Money c {"000001"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test03, basic_test_set)
{
    // 11.11 + 0.91 = 12.02
    Money a {"1111"};
    Money b {"19"};
    Money c {"2021"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test04, basic_test_set)
{
    // 0 + 543.21 = 543.21
    Money a {'0'};
    Money b {"12345"};
    Money c {"12345"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test05, basic_test_set)
{
    // 1000.99 + 0.01 = 1001.00
    Money a {"990001"};
    Money b {'1'};
    Money c {"001001"};
    ASSERT_TRUE(c.equals(a.add(b)));
}

TEST(o_test06, basic_test_set)
{
    // 0.01 - 5.00 = exeption
    Money a {"1"};
    Money b {"005"};
    try{
        a.remove(b);
    }catch(std::exception &ex){
        EXPECT_STREQ(ex.what(),"negative balance");
    }
}

TEST(o_test07, basic_test_set)
{
    // 115.00 - 15.00 = 100.00
    Money a {"00511"};
    Money b {"0051"};
    Money c {"00001"};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test08, basic_test_set)
{
    // 1.00 - 0.01 = 0.99
    Money a {"001"};
    Money b {'1'};
    Money c {"99"};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test09, basic_test_set)
{
    // 6543.21 - 6543.21 = 0
    Money a {"123456"};
    Money b {"123456"};
    Money c {'0'};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test10, basic_test_set)
{
    // 1000000.00 - 0.01 = 999999.99
    Money a {"000000001"};
    Money b {'1'};
    Money c {"99999999"};
    ASSERT_TRUE(c.equals(a.remove(b)));
}

TEST(o_test11, basic_test_set)
{
    // 0 + 6543.21 = 6543.21
    Money a  = Money();
    Money b {"123456"};
    Money c {"123456"};
    ASSERT_TRUE(c.equals(a.add(b)));
}