//
// Created by Joaquina Daeron on 10/5/23.
//

#include "maze_generator.h"
#include <algorithm>
#include <iostream>

namespace s21 {
    MazeGenerator::MazeGenerator(const size_t &width, const size_t &height) :
            height_{height}, width_{width},
            maze_(width),
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
        for (size_t i = 0; i < width_ - 1; ++i) {
            bool choice = r_.GenerateBool();
            if (choice || maze_[i] == maze_[i + 1]) {
                vertical_walls_[row][i] = true;
            } else {
                MergeSet(i);
            }
        }
        vertical_walls_[row][width_ - 1] = true;
    }

    void MazeGenerator::CreateHorizontalWalls(const size_t &row) {
        for (size_t i = 0, space = 0, standard = maze_[0]; i <= width_; ++i) {
            if (i == width_ || maze_[i] != standard) {
                if (i != width_) standard = maze_[i];
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
        for (size_t i = 0; i < width_ - 1; ++i) {
            if (maze_[i] == maze_[i + 1]) {
                vertical_walls_[row][i] = true;
            } else {
                MergeSet(i);
            }
            horizontal_walls_[row][i] = true;
        }
        vertical_walls_[row][width_ - 1] = true;
        horizontal_walls_[row][width_ - 1] = true;
    }


    void MazeGenerator::CopyRow(const size_t &row) {
        for (size_t i = 0; i < width_; ++i)
            if (horizontal_walls_[row][i])
                maze_[i] = counter_++;
    }

    void MazeGenerator::Reset() {
        maze_.clear();
        horizontal_walls_.clear();
        vertical_walls_.clear();
        counter_ = 0;
    }

    void MazeGenerator::Init() {
        for (size_t i = 0; i < height_; ++i) {
            std::fill(maze_.begin(), maze_.end(), 0);
            std::fill(horizontal_walls_[i].begin(), horizontal_walls_[i].end(), false);
            std::fill(vertical_walls_[i].begin(), vertical_walls_[i].end(), false);
        }
        for (size_t i = 0; i < width_; ++i) {
            maze_[i] = counter_++;
        }
    }

    void MazeGenerator::MergeSet(const size_t &col) {
        size_t changeable_set = maze_[col + 1];
        for (size_t i = 0; i < width_; ++i) {
            if (maze_[i] == changeable_set)
                maze_[i] = maze_[col];
        }
    }

} // s21