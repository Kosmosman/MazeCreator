//
// Created by Joaquina Daeron on 10/5/23.
//

#include "maze_generator.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace s21 {
MazeGenerator::MazeGenerator()
    : height_{DEFAULT_VALUE},
      width_{DEFAULT_VALUE},
      maze_(DEFAULT_VALUE),
      horizontal_walls_(DEFAULT_VALUE, std::vector<bool>(DEFAULT_VALUE)),
      vertical_walls_(DEFAULT_VALUE, std::vector<bool>(DEFAULT_VALUE)) {}

MazeGenerator::MazeGenerator(const size_t &width, const size_t &height)
    : height_{height},
      width_{width},
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
      ++count_of_walls_;
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
          ++count_of_walls_;
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
      ++count_of_walls_;
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
    if (horizontal_walls_[row][i]) maze_[i] = counter_++;
}

void MazeGenerator::Reset() {
  maze_.clear();
  horizontal_walls_.clear();
  vertical_walls_.clear();
  counter_ = 0;
  count_of_walls_ = 0;
}

void MazeGenerator::Init() {
  counter_ = 0;
  for (size_t i = 0; i < height_; ++i) {
    std::fill(maze_.begin(), maze_.end(), 0);
    std::fill(horizontal_walls_[i].begin(), horizontal_walls_[i].end(), false);
    std::fill(vertical_walls_[i].begin(), vertical_walls_[i].end(), false);
  }
  for (size_t i = 0; i < width_; ++i) {
    maze_[i] = counter_++;
  }
  count_of_walls_ = height_ + width_;
}

void MazeGenerator::MergeSet(const size_t &col) {
  size_t changeable_set = maze_[col + 1];
  for (size_t i = 0; i < width_; ++i) {
    if (maze_[i] == changeable_set) maze_[i] = maze_[col];
  }
}

void MazeGenerator::Resize(const size_t &new_height, const size_t &new_width) {
  vertical_walls_.resize(new_height);
  horizontal_walls_.resize(new_height);
  height_ = new_height;
  for (auto &i : vertical_walls_) i.resize(new_width);
  for (auto &i : horizontal_walls_) i.resize(new_width);
  maze_.resize(new_width);
  width_ = new_width;
}

void MazeGenerator::UploadFile(std::string &&filename) {
  std::ifstream f;
  f.open(filename);
  counter_ = 0;
  if (f.is_open()) {
    std::cout << "find a file!\n";
    int N, M;
    f >> N >> M;
    Resize(N, M);
    bool tmp{};
    for (int i = 0; i < N && f.good(); ++i) {
      for (int j = 0; j < M; ++j) {
        f >> tmp;
        vertical_walls_[i][j] = tmp;
        counter_ += tmp;
      }
    }
    for (int i = 0; i < N && f.good(); ++i) {
      for (int j = 0; j < M; ++j) {
        f >> tmp;
        horizontal_walls_[i][j] = tmp;
        counter_ += tmp;
      }
    }
    f.close();
  }
}

}  // namespace s21