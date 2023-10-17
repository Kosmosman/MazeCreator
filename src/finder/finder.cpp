//
// Created by Joaquina Daeron on 10/11/23.
//

#include "finder.h"

namespace s21 {

    void Finder::FindWay(std::pair<size_t, size_t> &&start, const std::pair<size_t, size_t> &end, int counter) {
        FindEnd(std::move(start), end, 1);
        FindStart(end);
    }

    void Finder::FindEnd(std::pair<size_t, size_t> &&start, const std::pair<size_t, size_t> &end, int counter) {
        map_[start.first][start.second] = counter++;
        if (start == end) was_found_ = true;
        if (was_found_) return;
        if (start.first > 0 && !(*horizontal_)[start.first - 1][start.second])
            FindEnd({start.first - 1, start.second}, end, counter);
        if (start.first < horizontal_->size() - 1 && !(*horizontal_)[start.first][start.second])
            FindEnd({start.first + 1, start.second}, end, counter);
        if (start.second > 0 && (*vertical_)[start.first][start.second - 1])
            FindEnd({start.first, start.second - 1}, end, counter);
        if (start.second > vertical_[0].size() - 1 && !(*vertical_)[start.first][start.second])
            FindEnd({start.first, start.second + 1}, end, counter);
    }

    void Finder::Init(const std::vector<std::vector<bool>> &h, const std::vector<std::vector<bool>> &v) {
        horizontal_ = &h;
        vertical_ = &v;
        map_.resize(horizontal_->size());
        for (auto &i: map_)
            i.resize(vertical_[0].size());
    }

    void Finder::FindStart(const std::pair<size_t, size_t> &end) {
        size_t x{end.second}, y{end.first};
        auto pos = map_[y][x] - 1;
        way_.resize(map_[y][x]);
        way_.emplace_back(y, x);
        while (map_[y][x] != 1) {
            if (x > 0 && map_[y][x - 1] == pos) --x;
            else if (x < map_[0].size() - 1 && map_[y][x + 1] == pos) ++x;
            else if (y > 0 && map_[y - 1][x] == pos) --y;
            else if (y < map_.size() - 1 && map_[y + 1][x] == pos) ++y;
            --pos, way_.emplace_back(y, x);
        }
    }

} // s21