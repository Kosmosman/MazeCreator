#include "finder.h"
#include "gtest/gtest.h"
#include "controller.h"

struct Tester {
    using pair_type = std::pair<s21::Finder::size_t, s21::Finder::size_t>;

    std::vector<std::vector<bool>> correct_vertical_wall_4{{1, 1, 1, 1},
                                                           {0, 0, 0, 1},
                                                           {1, 1, 1, 1},
                                                           {0, 0, 0, 1}};
    std::vector<std::vector<bool>> correct_horizontal_wall_4{{0, 0, 0, 0},
                                                             {0, 0, 0, 0},
                                                             {1, 1, 1, 0},
                                                             {1, 1, 1, 1}};
    std::vector<pair_type> way_4{{3, 3},
                                 {2, 3},
                                 {1, 3},
                                 {1, 2},
                                 {1, 1},
                                 {1, 0},
                                 {0, 0}};

    std::vector<std::vector<bool>> correct_vertical_wall_10{
            {0, 1, 0, 1, 0, 0, 0, 0, 1, 1},
            {1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
            {0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
            {0, 1, 0, 0, 0, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 0, 0, 1, 1, 0, 1},
            {0, 1, 1, 0, 0, 1, 0, 0, 1, 1},
            {1, 1, 1, 0, 0, 1, 0, 1, 1, 1},
            {0, 0, 0, 0, 0, 1, 1, 1, 0, 1}};
    std::vector<std::vector<bool>> correct_horizontal_wall_10{
            {0, 1, 0, 1, 1, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
            {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
            {1, 0, 1, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

    };
    std::vector<pair_type> way_10{
            {9, 9}, {9, 8}, {8, 8}, {7, 8}, {7, 7}, {7, 6}, {6, 6}, {6, 5}, {5, 5}, {5, 4}, {5, 3}, {5, 2}, {4, 2},
            {3, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0}, {0, 0}
    };

    std::vector<pair_type> way_0{{0, 0}};
};

    Tester tester;
    s21::Finder finder;
    s21::MazeGenerator mg;
    s21::Controller controller(&finder, &mg);

TEST(finder_test, correct_finder_4) {
    finder.Init(tester.correct_horizontal_wall_4, tester.correct_vertical_wall_4);
    EXPECT_EQ(finder.FindWay({0, 0}, {3, 3}), tester.way_4);
}

TEST(finder_test, correct_finder_10) {
    finder.Init(tester.correct_horizontal_wall_10, tester.correct_vertical_wall_10);
    EXPECT_EQ(finder.FindWay({0, 0}, {9, 9}), tester.way_10);
}

TEST(finder_test, incorrect_finder) {
    controller.GenerateMaze(10, 10);
    EXPECT_EQ(controller.GetWay({0, 0}, {10, 9}), tester.way_0);
    EXPECT_EQ(controller.GetWay({0, 0}, {9, 10}), tester.way_0);
    EXPECT_EQ(controller.GetWay({-1, 0}, {9, 9}), tester.way_0);
    EXPECT_EQ(controller.GetWay({0, -1}, {0, 9}), tester.way_0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}