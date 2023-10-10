//
// Created by Joaquina Daeron on 10/8/23.
//

#ifndef MAZE_WINDOW_H
#define MAZE_WINDOW_H

#include <SFML/Graphics.hpp>
#include "view.h"
#include "view_controller.h"

namespace s21 {

    template<typename F = Field, typename B = Button, typename T = TextTables>
    class Window {
    public:
        Window() : window_(sf::VideoMode({width_, height_}), "Maze") {};

        void Start();

        bool Status() { return window_.isOpen(); };

    private:
        const unsigned int width_{500};
        const unsigned int height_{700};
        sf::RenderWindow window_;
        ViewController<F, B, T> facade_{};
    };

} // s21
#include "window.tpp"

#endif //MAZE_WINDOW_H
