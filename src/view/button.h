//
// Created by Joaquina Daeron on 10/9/23.
//

#ifndef MAZE_BUTTON_H
#define MAZE_BUTTON_H

#include <SFML/Graphics.hpp>

namespace s21 {

    class Button : public sf::Drawable {
    public:
        enum class kFunctionality {
            NOTHING,
            LOAD_MAZE,
            GENERATE_MAZE,
            FIND_WAY
        };

        Button() : text_{font_} {};

        Button(std::string &&text);

        Button(std::string &&place, std::string &&text);

        void SetPosition(sf::Vector2f pos);

        void SetSize(sf::Vector2f size);

        void SetColor(sf::Color text = sf::Color::Black, sf::Color rect = sf::Color::White);

        void SetFunctional(kFunctionality k) { func_ = k; };

        kFunctionality &GetFunctional() { return func_; };

        void FillButton(sf::Vector2f position, sf::Vector2f size, kFunctionality functional,
                        sf::Color text = sf::Color::Black, sf::Color rect = sf::Color::White);

        bool CheckPosition(sf::Vector2i &position);

    private:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Font font_{};
        sf::Text text_{font_};
        sf::RectangleShape rect_{};
        // Координаты верхнего левого и нижнего правого углов
        std::vector<int> position_{0, 0, 0, 0};
        kFunctionality func_{kFunctionality::NOTHING};
    };

} // s21

#endif //MAZE_BUTTON_H
