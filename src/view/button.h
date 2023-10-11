//
// Created by Joaquina Daeron on 10/9/23.
//

#ifndef MAZE_BUTTON_H
#define MAZE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

namespace s21 {

    class Validator {
    public:
        Validator() = default;

        static constexpr int MAX_WALL_SIZE = 50;

        static bool CheckValidCoordinate(std::string &&size) {
            try {
                return stoi(size) <= MAX_WALL_SIZE;
            } catch (std::invalid_argument&) {
                return false;
            }
        }
    };

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

        void Fill(sf::Vector2f position, sf::Vector2f size, kFunctionality functional = kFunctionality::NOTHING,
                  sf::Color text = sf::Color::Black, sf::Color rect = sf::Color::White);

        bool CheckPosition(sf::Vector2i &position);

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        sf::Text text_{font_};
        sf::Font font_{};
        sf::RectangleShape rect_{};
        // Координаты верхнего левого и нижнего правого углов
        std::vector<int> position_{0, 0, 0, 0};

    private:
        kFunctionality func_{kFunctionality::NOTHING};

    };

    class TextTables : public Button {
    public:
        enum class kValue {
            NOTHING,
            X_COORDINATE,
            Y_COORDINATE,
            FILENAME
        };

        TextTables(std::string &&font) : Button(std::move(font)) {};

        void Add(std::string ch) {
            text_.setString(text_.getString() + ch);
            std::cout << "Add new key and now fraze is << " << text_.getString().toAnsiString() << '\n';
        };

        void Remove() {
            if (text_.getString().getSize() > 0) {
                text_.setString(std::string(text_.getString().begin(), text_.getString().end() - 1));
            }
        }

        std::string GetString() { return text_.getString(); };

        const bool &CheckCondition() const noexcept { return pressed_; };

        void ChangeCondition(bool condition) noexcept { pressed_ = condition; };

        kValue &GetValue() { return func_; };

        void SetValue(kValue k) { func_ = k; };


        void Fill(sf::Vector2f position, sf::Vector2f size, kValue value = kValue::NOTHING,
                  sf::Color text = sf::Color::Black, sf::Color rect = sf::Color::White);

    private:
        bool pressed_{};
        kValue func_{kValue::NOTHING};
    };


} // s21

#endif //MAZE_BUTTON_H
