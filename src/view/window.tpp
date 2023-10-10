//
// Created by Joaquina Daeron on 10/8/23.
//

#include "window.h"
namespace s21 {
    template<typename F, typename B>
    void Window<F, B>::Start(const std::vector<std::vector<bool>> &vertical,
                       const std::vector<std::vector<bool>> &horizontal) {
//        Field f;
//        f.CreateMazeGraph(vertical, horizontal);
//        while (window_.isOpen()) {
//            sf::Event event{};
//            while (window_.pollEvent(event)) {
//                if (event.type == sf::Event::Closed)
//                    window_.close();
//            }
//            window_.clear(sf::Color::Black);
//            window_.draw(f);
//            window_.display();
//        }
    }

    template<typename F, typename B>
    void Window<F, B>::Start(F &field, std::vector<B> &buttons) {
        while (window_.isOpen()) {
            sf::Event event{};
            while (window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window_.close();
            }
            window_.clear(sf::Color::Black);
            window_.draw(field);
            for (auto &i: buttons)
                window_.draw(i);
            window_.display();
        }
    }



} // s21