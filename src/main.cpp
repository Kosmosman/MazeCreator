//
// Created by Joaquina Daeron on 10/5/23.
//

#include <maze_generator.h>
#include <iostream>

int main() {
    s21::MazeGenerator m(5, 5);
    m.Generate();
    for (const auto& i: m.GetHorizontalWalls()) {
        for (const auto& j: i) {
            std::cout << j;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (const auto& i: m.GetVerticalWalls()) {
        for (const auto& j: i) {
            std::cout << j;
        }
        std::cout << '\n';
    }
    return 0;
}