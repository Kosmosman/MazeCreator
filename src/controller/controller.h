//
// Created by Joaquina Daeron on 10/10/23.
//

#ifndef MAZE_CONTROLLER_H
#define MAZE_CONTROLLER_H

#include "finder.h"
#include "maze_generator.h"
#include "validator.h"

#include <chrono>
#include <thread>

namespace s21 {

class Controller {
public:
  using size_t = unsigned int;

  Controller(Finder *finder, MazeGenerator *mg) : finder_{finder}, mg_{mg} {};

  size_t GetHeight() { return mg_->GetHorizontalWalls().size(); };

  size_t GetWidth() { return mg_->GetHorizontalWalls()[0].size(); };

  size_t GetCountOfWalls() { return mg_->GetCountOfWalls(); };

  const std::vector<std::vector<bool>> &GetVerticalWalls() {
    return mg_->GetVerticalWalls();
  };

  const std::vector<std::vector<bool>> &GetHorizontalWalls() {
    return mg_->GetHorizontalWalls();
  };

  const std::vector<std::pair<size_t, size_t>> &
  GetWay(std::pair<size_t, size_t> &&start, std::pair<size_t, size_t> &&end) {
    try {
      IsValidPositions(
          {static_cast<int>(start.first), static_cast<int>(start.second),
           static_cast<int>(end.first), static_cast<int>(end.second)});
    } catch (std::out_of_range &) {
      start = end = {0, 0};
    }
    finder_->Init(mg_->GetHorizontalWalls(), mg_->GetVerticalWalls());
    return finder_->FindWay(std::move(start), end);
  }

  void GenerateMaze(size_t y, size_t x) {
    try {
      IsValidSize(static_cast<int>(x), static_cast<int>(y));
    } catch (std::out_of_range &) {
      x = y = 10;
    }
    mg_->Resize(y, x);
    mg_->Generate();
  }

  void UploadFile(std::string &&s) { mg_->UploadFile(std::move(s)); };

private:
  void IsValidPositions(std::vector<int> &&positions) {
    try {
      Validator::CheckValidBorders(std::move(positions),
                                   static_cast<int>(GetWidth()),
                                   static_cast<int>(GetHeight()));
    } catch (std::out_of_range &) {
      throw;
    }
  }

  void IsValidSize(int x, int y) {
    try {
      Validator::CheckValidCoordinate(x, y);
    } catch (std::out_of_range &) {
      throw;
    }
  }

  Finder *finder_{};
  MazeGenerator *mg_{};
};

} // namespace s21

#endif // MAZE_CONTROLLER_H
