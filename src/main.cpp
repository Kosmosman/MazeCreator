//
// Created by Joaquina Daeron on 10/5/23.
//

#include <window.h>

int main() {
    s21::Finder finder;
    s21::MazeGenerator mg;
    s21::Controller controller(&finder, &mg);
    s21::Facade facade(&controller);
    s21::Window w(&facade);
    w.Start();
    return 0;
}