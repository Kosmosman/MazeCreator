//
// Created by Joaquina Daeron on 10/8/23.
//

#include "window.h"

namespace s21 {
    template<typename F, typename B, typename T>
    void Window<F, B, T>::Start() {
        facade_.Init(window_);
        while (window_.isOpen()) {
            sf::Event event{};
            while (window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window_.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        facade_.MousePressed({event.mouseButton.x, event.mouseButton.y});
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    facade_.KeyboardPressed(event.key.scancode);
                }
            }
            window_.clear(sf::Color::Black);
            window_.draw(facade_.GetField());
            for (auto &i: facade_.GetButtons())
                window_.draw(i);
            for (auto &i: facade_.GetLabels())
                window_.draw(i);
            window_.display();
        }
    }


} // s21