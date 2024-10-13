#include <gtest/gtest.h>
#include "solution.cpp"

TEST(test01, basic_test_set)
{
    int length = 32, width = 16, height = 64; 
    int box = box_capacity(length, width, height);
    ASSERT_TRUE(box==13824);
}

TEST(test02, basic_test_set)
{
    int length = 1, width = 1, height = 64; 
    int box = box_capacity(length, width, height);
    ASSERT_TRUE(box==0);
}

TEST(test03, basic_test_set)
{
    int length = 100, width = 3, height = 2048; 
    int box = box_capacity(length, width, height);
    ASSERT_TRUE(box==230400);
}


TEST(test04, basic_test_set)
{
    int length = 1, width = 1, height = 1; 
    int box = box_capacity(length, width, height);
    ASSERT_TRUE(box==0);
}

TEST(test05, basic_test_set)
{
    int length = 16, width = 16, height = 16; 
    int box = box_capacity(length, width, height);
    ASSERT_TRUE(box==1728);
}

TEST(test06, basic_test_set)
{
    int length = 32000, width = 2, height = 2; 
    int box = box_capacity(length, width, height);
    ASSERT_TRUE(box==24000);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}