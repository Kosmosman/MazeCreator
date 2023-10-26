//
// Created by Joaquina Daeron on 10/5/23.
//

#ifndef MAZE_MAZE_GENERATOR_H
#define MAZE_MAZE_GENERATOR_H

#include <vector>
#include <random>
#include "randomizer.h"

namespace s21 {

    class MazeGenerator {
    public:
        using size_t = unsigned int;
        using matrix_bool = std::vector<std::vector<bool>>;
        static constexpr size_t DEFAULT_VALUE = 10;

        MazeGenerator();

        explicit MazeGenerator(const size_t &width, const size_t &height);

        void Generate();

        const matrix_bool &GetVerticalWalls() { return vertical_walls_; };

        const matrix_bool &GetHorizontalWalls() { return horizontal_walls_; };

        const size_t &GetCountOfWalls() { return count_of_walls_; };

        void Resize(const size_t &new_height, const size_t &new_width);

        void UploadFile(std::string&&);


    private:
        void Init();

        void Reset();

        void CreateVerticalWalls(const size_t &);

        void CreateHorizontalWalls(const size_t &);

        void CreateLastRow();

        void MergeSet(const size_t &col);

        void CopyRow(const size_t &);

        size_t height_{};
        size_t width_{};
        size_t counter_{};
        size_t count_of_walls_{};
        std::vector<size_t> maze_{};
        matrix_bool horizontal_walls_{};
        matrix_bool vertical_walls_{};
        Randomizer r_{};
    };

} // s21

#endif //MAZE_MAZE_GENERATOR_H
