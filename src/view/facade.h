//
// Created by Joaquina Daeron on 10/26/23.
//

#ifndef MAZE_FACADE_H
#define MAZE_FACADE_H

#include "controller.h"
#include "view.h"
#include <vector>

namespace s21 {

class Facade {
public:
  explicit Facade(Controller *controller) : controller_{controller} { Init(); };

  void MousePressed(sf::Vector2i pos) {
    for (auto &i : text_labels_)
      i.ChangeCondition(false);
    for (auto &i : buttons_) {
      if (i.CheckPosition(pos)) {
        switch (i.GetFunctional()) {
        case Button::kFunctionality::GENERATE_MAZE:
          GenerateHandler();
          break;
        case Button::kFunctionality::LOAD_MAZE:
          LoadHandler();
          break;
        case Button::kFunctionality::FIND_WAY:
          FindHandler();
          break;
        case Button::kFunctionality::NOTHING:
          break;
        }
      }
    }
    for (auto &i : text_labels_) {
      if (i.CheckPosition(pos))
        LabelsHandler(pos);
    }
  }

  void KeyboardPressed(sf::Keyboard::Scan sc) {
    for (auto &i : text_labels_) {
      if (i.CheckCondition()) {
        if (sc == sf::Keyboard::Scancode::Backspace)
          i.Remove();
        else if (i.GetString().size() < 2 ||
                 i.GetValue() == TextTables::kValue::FILENAME)
          i.Add(getDescription(sc));
        break;
      }
    }
  }

  const std::vector<Button> &GetButtons() { return buttons_; };

  const std::vector<TextTables> &GetLabels() { return text_labels_; };

  Field &GetField() { return field_; };

private:
  void Init() {
    buttons_.reserve(3);
    buttons_.emplace_back("../view/font/Lato-Italic.ttf",
                          "Find way (x, y) (x, y)");
    buttons_.back().Fill({50, 530}, {132, 32},
                         Button::kFunctionality::FIND_WAY);

    buttons_.emplace_back("../view/font/Lato-Italic.ttf",
                          "Generate maze (x, y)");
    buttons_.back().Fill({50, 580}, {132, 32},
                         Button::kFunctionality::GENERATE_MAZE);

    buttons_.emplace_back("../view/font/Lato-Italic.ttf",
                          "Load maze from file");
    buttons_.back().Fill({50, 630}, {135, 32},
                         Button::kFunctionality::LOAD_MAZE);

    text_labels_.reserve(7);
    text_labels_.emplace_back("../view/font/Lato-Italic.ttf");
    text_labels_.back().Fill({200, 580}, {32, 32},
                             TextTables::kValue::X_COORDINATE);

    text_labels_.emplace_back("../view/font/Lato-Italic.ttf");
    text_labels_.back().Fill({250, 580}, {32, 32},
                             TextTables::kValue::Y_COORDINATE);

    text_labels_.emplace_back("../view/font/Lato-Italic.ttf");
    text_labels_.back().Fill({200, 630}, {250, 32},
                             TextTables::kValue::FILENAME);

    text_labels_.emplace_back("../view/font/Lato-Italic.ttf");
    text_labels_.back().Fill({200, 530}, {32, 32}, TextTables::kValue::X_START);

    text_labels_.emplace_back("../view/font/Lato-Italic.ttf");
    text_labels_.back().Fill({250, 530}, {32, 32}, TextTables::kValue::Y_START);

    text_labels_.emplace_back("../view/font/Lato-Italic.ttf");
    text_labels_.back().Fill({300, 530}, {32, 32}, TextTables::kValue::X_END);

    text_labels_.emplace_back("../view/font/Lato-Italic.ttf");
    text_labels_.back().Fill({350, 530}, {32, 32}, TextTables::kValue::Y_END);

    GenerateHandler();
  }

  void GenerateHandler() {
    int x{}, y{};
    try {
      for (auto &i : text_labels_) {
        if (i.GetValue() == TextTables::kValue::X_COORDINATE)
          x = std::stoi(i.GetString());
        else if (i.GetValue() == TextTables::kValue::Y_COORDINATE)
          y = std::stoi(i.GetString());
      }
    } catch (std::invalid_argument &e) {
      x = y = 10;
    }
    controller_->GenerateMaze(y, x);
    field_.SetCountOfWalls(controller_->GetCountOfWalls());
    field_.CreateMazeGraph(controller_->GetVerticalWalls(),
                           controller_->GetHorizontalWalls());
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  void LoadHandler() {
    for (auto &i : text_labels_) {
      if (i.GetValue() == TextTables::kValue::FILENAME) {
        controller_->UploadFile(i.GetString());
        field_.SetCountOfWalls(controller_->GetCountOfWalls());
        field_.CreateMazeGraph(controller_->GetVerticalWalls(),
                               controller_->GetHorizontalWalls());
      }
    }
  }

  void FindHandler() {
    int x_start{}, y_start{}, x_end{}, y_end{};
    try {
      for (auto &i : text_labels_) {
        switch (i.GetValue()) {
        case TextTables::kValue::X_START:
          x_start = std::stoi(i.GetString());
          break;
        case TextTables::kValue::Y_START:
          y_start = std::stoi(i.GetString());
          break;
        case TextTables::kValue::X_END:
          x_end = std::stoi(i.GetString());
          break;
        case TextTables::kValue::Y_END:
          y_end = std::stoi(i.GetString());
          break;
        }
      }
    } catch (std::invalid_argument &e) {
      return;
    }
    auto path = controller_->GetWay({y_start, x_start}, {y_end, x_end});
    field_.CreatePath(path);
  }

  void LabelsHandler(sf::Vector2i &pos) {
    for (auto &i : text_labels_) {
      if (i.CheckPosition(pos)) {
        i.ChangeCondition(true);
      } else {
        i.ChangeCondition(false);
      }
    }
  }

  std::vector<Button> buttons_{};
  std::vector<TextTables> text_labels_{};
  Field field_{};
  Controller *controller_{};
};

} // namespace s21

#endif // MAZE_FACADE_H
