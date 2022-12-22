//
// Created by Dan on 4/12/2022.
//

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <fstream>
#include "mixer.h"
#include "testfiles.h"

void printvec(std::vector<int64_t> & vec);


TEST(mixtest, FirstTest) {
   ASSERT_TRUE(1==1);
}

TEST(mixtest, firstmove)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final = {2,1,-3,3,-2,0,4};

    mixer sut(a);
    sut.mix(0); //mix the first element
    ASSERT_THAT(a, ::testing::ContainerEq(final));
}

TEST(mixtest, secondmove)
{
    std::vector<int64_t> ref = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final = {1,-3,2,3,-2,0,4};

    mixer sut(a);
    sut.mix(0); //mix the first element
    sut.mix(1); //mix the first element
    ASSERT_THAT(a, ::testing::ContainerEq(final));
}

TEST(mixtest, thirdmove)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final = {1,2,3,-2,-3,0,4};

    mixer sut(a);
    sut.mix(0);
    sut.mix(1);
    sut.mix(2);
    ASSERT_THAT(a, ::testing::ContainerEq(final));
}
TEST(mixtest, fourthdmove)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final = {1,2,-2,-3,0,3,4};

    mixer sut(a);
    sut.mix(0);
    sut.mix(1);
    sut.mix(2);
    sut.mix(3);
    ASSERT_THAT(a, ::testing::ContainerEq(final));
}

TEST(mixtest, fifthmove)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final = {1,2,-3,0,3,4,-2};

    mixer sut(a);
    sut.mix(0);
    sut.mix(1);
    sut.mix(2);
    sut.mix(3);
    sut.mix(4);
    ASSERT_THAT(a, ::testing::ContainerEq(final));
}

TEST(mixtest, sixthmove)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final = {1,2,-3,0,3,4,-2};

    mixer sut(a);
    sut.mix(0);
    sut.mix(1);
    sut.mix(2);
    sut.mix(3);
    sut.mix(4);
    sut.mix(5);
    ASSERT_THAT(a, ::testing::ContainerEq(final));
}

TEST(mixtest, seventhmove)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final = {1,2,-3,4,0,3,-2};

    mixer sut(a);
    sut.mix(0);
    sut.mix(1);
    sut.mix(2);
    sut.mix(3);
    sut.mix(4);
    sut.mix(5);
    sut.mix(6);
    ASSERT_THAT(a, ::testing::ContainerEq(final));
}

TEST(mixtest, findsum)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    mixer sut(a);
    for(int i=0; i<a.size(); i++)
        sut.mix(i);

    auto wherezero = std::find(a.begin(), a.end(), 0);
    int index = wherezero - a.begin();
    auto first = a[(index + 1000) % a.size()];
    auto second = a[(index + 2000) % a.size()];
    auto third = a[(index + 3000) % a.size()];
    ASSERT_TRUE(first == 4);
    ASSERT_TRUE(second == -3);
    ASSERT_TRUE(third == 2);
    ASSERT_TRUE(first+second+third == 3);
}

TEST(mixtest, bigfile)
{

    std::ifstream inputFile(inputFileName);
    std::vector<int64_t> a;

    int64_t i;
    while(inputFile >> i)
        a.push_back(i);

    std::cout << a.size() << std::endl;
    ASSERT_TRUE(a.size() == 5000);

    mixer sut(a);
    for(int i=0; i<a.size(); i++)
        sut.mix(i);

    auto wherezero = std::find(a.begin(), a.end(), 0);
    int index = wherezero - a.begin();
    auto first = a[(index + 1000) % a.size()];
    auto second = a[(index + 2000) % a.size()];
    auto third = a[(index + 3000) % a.size()];
    std::cout << first << ' ' << second << ' ' << third << ' ' << std::endl;
    std::cout << first + second + third << std::endl;
    ASSERT_TRUE(first+second+third == 19559);
}

TEST(mixtest, firstmove_bignumbers)
{
    std::vector<int64_t> a = {1,2,-3,3,-2,0,4};
    std::vector<int64_t> final1 = {0,-2434767459,1623178306,3246356612,-1623178306,2434767459,811589153};
    std::for_each(a.begin(), a.end(), [](int64_t &el){el *= 811589153; });

    mixer sut(a);
    for(int j=0; j<10; j++)
    {
        for(int i=0; i<a.size(); i++)
        {
            sut.mix(i);
        }
    }
    ASSERT_THAT(a, ::testing::ContainerEq(final1));

    auto wherezero = std::find(a.begin(), a.end(), 0);
    int index = wherezero - a.begin();
    auto first = a[(index + 1000) % a.size()];
    auto second = a[(index + 2000) % a.size()];
    auto third = a[(index + 3000) % a.size()];
    ASSERT_TRUE(first == 811589153);
    ASSERT_TRUE(second == 2434767459);
    ASSERT_TRUE(third == -1623178306);
    ASSERT_TRUE(first+second+third == 1623178306);
}

TEST(mixtest, bigfile_bignumbers)
{

    std::ifstream inputFile(inputFileName);
    std::vector<int64_t> a;

    int64_t i;
    while(inputFile >> i)
        a.push_back(i);
    std::for_each(a.begin(), a.end(), [](int64_t &el){el *= 811589153; });


    std::cout << a.size() << std::endl;
    ASSERT_TRUE(a.size() == 5000);

    mixer sut(a);
    for(int j=0; j<10; j++)
    {
        for(int i=0; i<a.size(); i++)
        {
            sut.mix(i);
        }
    }

    auto wherezero = std::find(a.begin(), a.end(), 0);
    int index = wherezero - a.begin();
    auto first = a[(index + 1000) % a.size()];
    auto second = a[(index + 2000) % a.size()];
    auto third = a[(index + 3000) % a.size()];
    std::cout << first << ' ' << second << ' ' << third << ' ' << std::endl;
    std::cout << first + second + third << std::endl;
    ASSERT_TRUE(first+second+third == 912226207972);
}

void printvec(std::vector<int64_t> & vec)
{
        std::cout << "vec: ";
        for(auto i: vec)
            std::cout << i << ' ';
        std::cout << std::endl;

}