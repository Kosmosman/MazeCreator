//
// Created by Joaquina Daeron on 10/8/23.
//

#ifndef MAZE_WINDOW_H
#define MAZE_WINDOW_H

#include <SFML/Graphics.hpp>

namespace s21 {

    class Window {
    public:
        Window() : window_(sf::VideoMode({width_, height_}), "Base window") {};
        void Start(const std::vector<std::vector<bool>> &vertical,
                   const std::vector<std::vector<bool>> &horizontal);
    private:
        const unsigned int width_{500};
        const unsigned int height_{700};
        sf::RenderWindow window_;
    };

} // s21

#endif //MAZE_WINDOW_H
