//
// Created by Joaquina Daeron on 10/5/23.
//

#include <window.h>

int main() {
    std::vector <s21::Button> buttons_{};
    std::vector <s21::TextTables> text_labels_{};

    s21::Field field;
    s21::Finder finder;
    s21::MazeGenerator mg;
    s21::Controller controller(&finder, &mg);

    s21::Facade facade(&controller, &buttons_, &text_labels_, &field);

    s21::Window w(&facade);

    w.Start();
    return 0;
}