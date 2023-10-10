//
// Created by Joaquina Daeron on 10/8/23.
//

#ifndef MAZE_WINDOW_H
#define MAZE_WINDOW_H

#include <SFML/Graphics.hpp>
#include "view.h"

namespace s21 {

    template<typename F = Field, typename B = Button>
    class Window {
    public:
        Window() : window_(sf::VideoMode({width_, height_}), "Maze") {};

        void Start(F &field, std::vector<B> &buttons);

        bool Status() { return window_.isOpen(); };

        sf::RenderWindow &GetWindow() { return window_; };

    private:
        const unsigned int width_{500};
        const unsigned int height_{700};
        sf::RenderWindow window_;
        typename B::kFunctionality BUTTON_EVENT{B::kFunctionality::NOTHING};
    };

} // s21
#include "window.tpp"

#endif //MAZE_WINDOW_H
