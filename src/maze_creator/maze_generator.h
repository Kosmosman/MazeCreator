//
// Created by Joaquina Daeron on 10/5/23.
//

#ifndef MAZE_MAZE_GENERATOR_H
#define MAZE_MAZE_GENERATOR_H

#include <vector>
#include <random>
#include "../randomizer/randomizer.h"

namespace s21 {

    class MazeGenerator {
    public:
        using size_t = unsigned int;
        using matrix_size_t = std::vector<std::vector<size_t>>;
        using matirx_bool = std::vector<std::vector<bool>>;

        explicit MazeGenerator(const size_t &width, const size_t &height);

        void Generate();

        const matirx_bool &GetVerticalWalls() { return vertical_walls_; };

        const matirx_bool &GetHorizontalWalls() { return horizontal_walls_; };

        const matrix_size_t &GetMaze() {return maze_;};


    private:
        void Init();

        void Reset();

        void CreateVerticalWalls(const size_t &);

        void CreateHorizontalWalls(const size_t &);

        void CreateLastRow();

        void MergeSet(const size_t& col, const size_t& row);

        void CopyRow(const size_t &);

        size_t height_;
        size_t width_;
        size_t counter_{};
        matrix_size_t maze_;
        matirx_bool horizontal_walls_;
        matirx_bool vertical_walls_;
        Randomizer r_{};
    };

} // s21

#endif //MAZE_MAZE_GENERATOR_H
