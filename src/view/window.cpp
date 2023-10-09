//
// Created by Joaquina Daeron on 10/8/23.
//

#include "window.h"
#include "field.h"

namespace s21 {
    void Window::Start(const std::vector<std::vector<bool>> &vertical,
                       const std::vector<std::vector<bool>> &horizontal) {
        Field f;
        f.CreateMazeGraph(vertical, horizontal);
        while (window_.isOpen()) {
            sf::Event event{};
            while (window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window_.close();
            }
            window_.clear(sf::Color::Black);
            window_.draw(f);
            window_.display();
        }
    }
} // s21