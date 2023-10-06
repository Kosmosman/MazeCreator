//
// Created by Joaquina Daeron on 10/5/23.
//

#ifndef MAZE_RANDOMIZER_H
#define MAZE_RANDOMIZER_H

#include <random>

namespace s21 {

    class Randomizer {
    public:

        explicit Randomizer() : mt_(rd_()), dist_(0, 10) {};

        bool GenerateBool() { return dist_(mt_) % 2; };


    private:
        std::random_device rd_{};
        std::mt19937 mt_;
        std::uniform_int_distribution<int> dist_;
    };

} // s21

#endif //MAZE_RANDOMIZER_H
