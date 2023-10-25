//
// Created by Joaquina Daeron on 10/11/23.
//

#ifndef MAZE_FINDER_H
#define MAZE_FINDER_H

#include <vector>
#include <queue>

namespace s21 {

    class Finder {
    public:
        using size_t = unsigned int;

        const std::vector<std::pair<size_t, size_t>> &
        FindWay(std::pair<size_t, size_t> &&start, const std::pair<size_t, size_t> &end);

        void Init(const std::vector<std::vector<bool>> &h, const std::vector<std::vector<bool>> &v);

    private:
        void FindEnd(size_t x_pos, size_t y_pos, size_t x_end, size_t y_end, size_t counter);

        void FindStart(const std::pair<size_t, size_t> &end);

        const std::vector<std::vector<bool>> *horizontal_{nullptr};
        const std::vector<std::vector<bool>> *vertical_{nullptr};
        std::vector<std::vector<size_t>> map_{};
        std::vector<std::pair<size_t, size_t>> way_{};
        bool was_found_{};
    };

} // s21

#endif //MAZE_FINDER_H
