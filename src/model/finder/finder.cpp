//
// Created by Joaquina Daeron on 10/11/23.
//

#include "finder.h"

namespace s21 {

const std::vector<std::pair<Finder::size_t, Finder::size_t>> &Finder::FindWay(
    std::pair<size_t, size_t> &&start, const std::pair<size_t, size_t> &end) {
  FindEnd(start.first, start.second, end.first, end.second, 1);
  FindStart(end);
  return way_;
}

void Finder::FindEnd(size_t x_pos, size_t y_pos, size_t x_end, size_t y_end,
                     size_t counter) {  // y, x
  map_[y_pos][x_pos] = counter++;
  if (x_pos == x_end && y_pos == y_end) was_found_ = true;
  if (was_found_) return;

  if (x_pos > 0 && !map_[y_pos][x_pos - 1] && !(*vertical_)[y_pos][x_pos - 1])
    FindEnd(x_pos - 1, y_pos, x_end, y_end, counter);

  if (x_pos < map_[0].size() - 1 && !map_[y_pos][x_pos + 1] &&
      !(*vertical_)[y_pos][x_pos])
    FindEnd(x_pos + 1, y_pos, x_end, y_end, counter);

  if (y_pos > 0 && !map_[y_pos - 1][x_pos] && !(*horizontal_)[y_pos - 1][x_pos])
    FindEnd(x_pos, y_pos - 1, x_end, y_end, counter);

  if (y_pos < map_.size() - 1 && !map_[y_pos + 1][x_pos] &&
      !(*horizontal_)[y_pos][x_pos])
    FindEnd(x_pos, y_pos + 1, x_end, y_end, counter);
}

void Finder::Init(const std::vector<std::vector<bool>> &h,
                  const std::vector<std::vector<bool>> &v) {
  horizontal_ = &h;
  vertical_ = &v;
  map_.resize(horizontal_->size());
  way_.resize(0);
  was_found_ = false;
  for (auto &i : map_) {
    i.resize(vertical_[0].size());
    std::fill(i.begin(), i.end(), 0);
  }
}

void Finder::FindStart(const std::pair<size_t, size_t> &end) {
  size_t x{end.second}, y{end.first};
  auto pos = map_[y][x] - 1;
  way_.reserve(map_[y][x]);
  way_.emplace_back(y, x);
  while (map_[y][x] != 1) {
    if (x > 0 && map_[y][x - 1] == pos && !(*vertical_)[y][x - 1])
      --x;
    else if (x < map_[0].size() - 1 && map_[y][x + 1] == pos &&
             !(*vertical_)[y][x])
      ++x;
    else if (y > 0 && map_[y - 1][x] == pos && !(*horizontal_)[y - 1][x])
      --y;
    else if (y < map_.size() - 1 && map_[y + 1][x] == pos &&
             !(*horizontal_)[y][x])
      ++y;
    else
      break;
    --pos, way_.emplace_back(y, x);
  }
}

}  // namespace s21