//
// Created by Joaquina Daeron on 10/8/23.
//

#include "window.h"

namespace s21 {
    void Window::Start() {
        while (window_.isOpen()) {
            sf::Event event{};
            while (window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window_.close();
            }

        }
    }
} // s21