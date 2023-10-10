//
// Created by Joaquina Daeron on 10/10/23.
//

#ifndef MAZE_VIEW_CONTROLLER_H
#define MAZE_VIEW_CONTROLLER_H

#include "view.h"
#include "maze_generator.h"

#include <thread>
#include <chrono>

namespace s21 {

    template<typename F = Field, typename B = Button, typename T = TextTables>
    class ViewController {
    public:

        ViewController() = default;

        void Init(sf::Window &win) {
            window_ = &win;
            buttons_.reserve(3);
            buttons_.emplace_back("includes/Lato-Italic.ttf", "Find way");
            buttons_.back().Fill({50, 530}, {80, 32}, B::kFunctionality::FIND_WAY);

            buttons_.emplace_back("includes/Lato-Italic.ttf", "Generate maze (x, y)");
            buttons_.back().Fill({50, 580}, {132, 32}, B::kFunctionality::GENERATE_MAZE);

            buttons_.emplace_back("includes/Lato-Italic.ttf", "Load maze from file");
            buttons_.back().Fill({50, 630}, {135, 32}, B::kFunctionality::LOAD_MAZE);

            text_labels_.reserve(3);
            text_labels_.emplace_back("includes/Lato-Italic.ttf");
            text_labels_.back().Fill({200, 580}, {32, 32}, T::kValue::X_COORDINATE);

            text_labels_.emplace_back("includes/Lato-Italic.ttf");
            text_labels_.back().Fill({250, 580}, {32, 32}, T::kValue::Y_COORDINATE);

            text_labels_.emplace_back("includes/Lato-Italic.ttf");
            text_labels_.back().Fill({200, 630}, {250, 32}, T::kValue::FILENAME);

            GenerateHandler();

//            std::thread t([this]() { CheckHandler(); });
//            t.detach();
        }

        std::vector <B> &GetButtons() { return buttons_; };

        std::vector <T> &GetLabels() { return text_labels_; };

        F &GetField() { return field_; };

        void MousePressed(sf::Vector2i pos) {
            for (auto &i: text_labels_)
                i.ChangeCondition(false);
            for (auto &i: buttons_) {
                if (i.CheckPosition(pos)) {
                    switch (i.GetFunctional()) {
                        case B::kFunctionality::GENERATE_MAZE:
                            GenerateHandler();
                            break;
                        case B::kFunctionality::LOAD_MAZE:
                            LoadHandler();
                            break;
                        case B::kFunctionality::FIND_WAY:
                            FindHandler();
                            break;
                        case B::kFunctionality::NOTHING:
                            break;
                    }
                }
            }
            for (auto &i: text_labels_) {
                if (i.CheckPosition(pos))
                    LabelsHandler(pos);
            }
        }

        void KeyboardPressed(sf::Keyboard::Scan sc) {
            for (auto &i: text_labels_) {
                if (i.CheckCondition()) {
                    sc == sf::Keyboard::Scancode::Backspace ? i.Remove() : i.Add(getDescription(sc));
                    break;
                }
            }
        }

    private:

        void GenerateHandler() {
            mg_.Generate();
            field_.SetCountOfWalls(mg_.GetCountOfWalls());
            field_.CreateMazeGraph(mg_.GetVerticalWalls(), mg_.GetHorizontalWalls());
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        // NEED FIX IT
        void LoadHandler() {
            for (auto &i: text_labels_) {
                if (i.GetValue() == T::kValue::FILENAME) {
                    mg_.UploadFile(i.GetString());
                    field_.SetCountOfWalls(mg_.GetCountOfWalls());
                    field_.CreateMazeGraph(mg_.GetVerticalWalls(), mg_.GetHorizontalWalls());
                }
            }
        }

        void FindHandler() {

        }

        void LabelsHandler(sf::Vector2i &pos) {
            for (auto &i: text_labels_) {
                if (i.CheckPosition(pos)) {
                    i.ChangeCondition(true);
                } else {
                    i.ChangeCondition(false);
                }
            }
        }

        sf::Window *window_;
        std::vector <B> buttons_;
        std::vector <T> text_labels_;
        F field_{};
        MazeGenerator mg_;
    };

} // s21

#endif //MAZE_VIEW_CONTROLLER_H
