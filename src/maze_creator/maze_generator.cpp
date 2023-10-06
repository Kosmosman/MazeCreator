//
// Created by Joaquina Daeron on 10/5/23.
//

#include "maze_generator.h"
#include <algorithm>
#include <iostream>

namespace s21 {
    MazeGenerator::MazeGenerator(const size_t &width, const size_t &height) :
            height_{height}, width_{width},
            maze_(height, std::vector<size_t>(width)),
            horizontal_walls_(height, std::vector<bool>(width)),
            vertical_walls_(height, std::vector<bool>(width)) {}

    void MazeGenerator::Generate() {
        Init();
        for (size_t i = 0; i < height_ - 1; ++i) {
            CreateVerticalWalls(i);
            CreateHorizontalWalls(i);
            CopyRow(i);
        }
        CreateLastRow();
    }

    void MazeGenerator::CreateVerticalWalls(const size_t &row) {
        for (size_t i = 0; i < width_ - 1; ++i)
            if (maze_[row][i] == maze_[row][i + 1])
                vertical_walls_[row][i] = true;
        for (size_t i = 1; i < width_; ++i) {
            if (!vertical_walls_[row][i - 1]) {
                if (r_.GenerateBool()) {
                    vertical_walls_[row][i - 1] = true;
                } else {
                    maze_[row][i] = maze_[row][i - 1];
                }
            }
        }
    }

    void MazeGenerator::CreateHorizontalWalls(const size_t &row) {
        for (size_t i = 0, space = 0, standard = maze_[row][0]; i <= width_; ++i) {
            if (i == width_ || maze_[row][i] != standard) {
                if (i != width_) standard = maze_[row][i];
                auto pos = space;
                while (space > 1 && pos > 0) {
                    if (r_.GenerateBool()) {
                        horizontal_walls_[row][i - pos] = true;
                        --space;
                    }
                    --pos;
                }
                space = 1;
            } else {
                ++space;
            }
        }
    }

    void MazeGenerator::CreateLastRow() {
        auto row = height_ - 1;
        for (size_t i = 1; i < width_; ++i)
            vertical_walls_[height_ - 1][i - 1] = maze_[row][i] == maze_[row][i - 1];
    }


    void MazeGenerator::CopyRow(const size_t &row) {
        std::copy(maze_[row].begin(), maze_[row].begin() + static_cast<long>(width_), maze_[row + 1].begin());
        for (size_t i = 0; i < width_; ++i)
            if (horizontal_walls_[row][i])
                maze_[row + 1][i] = counter_++;
    }

    void MazeGenerator::Reset() {
        maze_.clear();
        horizontal_walls_.clear();
        vertical_walls_.clear();
        counter_ = 0;
    }

    void MazeGenerator::Init() {
        for (size_t i = 0; i < height_; ++i) {
            std::fill(maze_[i].begin(), maze_[i].end(), 0);
            std::fill(horizontal_walls_[i].begin(), horizontal_walls_[i].end(), false);
            std::fill(vertical_walls_[i].begin(), vertical_walls_[i].end(), false);
        }
        for (size_t i = 0; i < width_; ++i) {
            maze_[0][i] = counter_++;
            horizontal_walls_[height_ - 1][i] = true;
        }
        for (size_t i = 0; i < height_; ++i)
            vertical_walls_[i][width_ - 1] = true;
    }

} // s21