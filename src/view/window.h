//
// Created by Joaquina Daeron on 10/8/23.
//

#ifndef MAZE_WINDOW_H
#define MAZE_WINDOW_H

#include "SFML/Window.hpp"

namespace s21 {

    class Window {
    public:
        Window() : window_(sf::VideoMode({width_, height_}), "Base window") {};
        void Start();
    private:
        const unsigned int width_{1000};
        const unsigned int height_{1000};
        sf::Window window_;
    };

} // s21

#endif //MAZE_WINDOW_H
