//
// Created by Joaquina Daeron on 10/10/23.
//

#ifndef MAZE_VIEW_CONTROLLER_H
#define MAZE_VIEW_CONTROLLER_H

#include "window.h"
#include "button.h"
#include "field.h"
#include "maze_generator.h"

#include <thread>
#include <chrono>

namespace s21 {

    template<typename F = Field, typename B = Button>
    class ViewController {
    public:

        ViewController() = default;

        void Start() {
            buttons_.reserve(3);
            buttons_.emplace_back("includes/Lato-Italic.ttf", "Find way");
            buttons_.back().FillButton({50, 530}, {80, 32}, B::kFunctionality::FIND_WAY);

            buttons_.emplace_back("includes/Lato-Italic.ttf", "Generate maze");
            buttons_.back().FillButton({50, 580}, {100, 32}, B::kFunctionality::GENERATE_MAZE);

            buttons_.emplace_back("includes/Lato-Italic.ttf", "Load maze from file");
            buttons_.back().FillButton({50, 630}, {130, 32}, B::kFunctionality::LOAD_MAZE);

            mg_.Generate();
            field_.SetCountOfWalls(mg_.GetCountOfWalls());
            field_.CreateMazeGraph(mg_.GetVerticalWalls(), mg_.GetHorizontalWalls());
            std::thread t([this]() { CheckHandler(); });
            window_.Start(field_, buttons_);
            t.join();
        }

    private:
        void CheckHandler() {
            sf::Vector2i pos{0, 0};
            while (!window_.Status())
                continue;
            while (window_.Status()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    pos = sf::Mouse::getPosition(window_.GetWindow());
                    for (auto &i: buttons_) {
                        if (i.CheckPosition(pos)) {
                            switch (i.GetFunctional()) {
                                case B::kFunctionality::GENERATE_MAZE:
                                    mg_.Generate();
                                    field_.CreateMazeGraph(mg_.GetVerticalWalls(), mg_.GetHorizontalWalls());
                                    std::this_thread::sleep_for(std::chrono::milliseconds (200));
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
        }

        Window<F, B> window_{};
        std::vector<B> buttons_;
        F field_{};
        MazeGenerator mg_;
    };

} // s21

#endif //MAZE_VIEW_CONTROLLER_H
