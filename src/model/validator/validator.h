//
// Created by Joaquina Daeron on 10/26/23.
//

#ifndef MAZE_VALIDATOR_H
#define MAZE_VALIDATOR_H

#include <string>

namespace s21 {

class Validator {
 public:
  Validator() = default;

  static constexpr int MAX_WALL_SIZE = 50;

  static void CheckValidCoordinate(int x, int y) {
    if (x < 0 | y < 0) throw std::out_of_range("Less then zero");
    if (x > MAX_WALL_SIZE | y > MAX_WALL_SIZE)
      throw std::out_of_range("Over then max size");
  }

  static void CheckValidBorders(std::vector<int> &&positions, int x_border,
                                int y_border) {
    if (positions[0] < 0 | positions[1] < 0 | positions[2] < 0 |
        positions[3] < 0)
      throw std::out_of_range("Less then zero");
    if (positions[0] >= x_border | positions[1] >= y_border |
        positions[2] >= x_border | positions[3] >= y_border)
      throw std::out_of_range("Position bigger then max size");
  }
};

}  // namespace s21

#endif  // MAZE_VALIDATOR_H
