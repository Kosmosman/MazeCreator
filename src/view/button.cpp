//
// Created by Joaquina Daeron on 10/9/23.
//

#include "button.h"
#include <iostream>

namespace s21 {

Button::Button(std::string &&place, std::string &&text) {
  if (!font_.loadFromFile(place)) {
    std::cout << "Error!";
  } else {
    text_.setFont(font_);
    text_.setString(text);
  }
}

Button::Button(std::string &&font) {
  if (!font_.loadFromFile(font))
    std::cout << "Error!";
  text_.setFont(font_);
}

void Button::SetPosition(sf::Vector2f pos) {
  rect_.setPosition(pos);
  text_.setPosition(pos);
  position_[0] += static_cast<int>(pos.x);
  position_[1] += static_cast<int>(pos.y);
  position_[2] += position_[0];
  position_[3] += position_[1];
}

void Button::SetSize(sf::Vector2f size) {
  rect_.setSize(size);
  text_.setCharacterSize(static_cast<unsigned int>(size.y) / 2);
  position_[2] += static_cast<int>(size.x);
  position_[3] += static_cast<int>(size.y);
}

void Button::SetColor(sf::Color text, sf::Color rect) {
  rect_.setFillColor(rect);
  text_.setFillColor(text);
}

void Button::draw(sf::RenderTarget &target,
                  const sf::RenderStates &states) const {
  target.draw(rect_, states);
  target.draw(text_, states);
}

void Button::Fill(sf::Vector2f position, sf::Vector2f size,
                  Button::kFunctionality functional, sf::Color text,
                  sf::Color rect) {
  SetPosition(position);
  SetSize(size);
  SetColor(text, rect);
  SetFunctional(functional);
}

bool Button::CheckPosition(sf::Vector2i &position) {
  return position.x >= position_[0] && position.x <= position_[2] &&
         position.y >= position_[1] && position.y <= position_[3];
}

void TextTables::Fill(sf::Vector2f position, sf::Vector2f size,
                      TextTables::kValue value, sf::Color text,
                      sf::Color rect) {
  SetPosition(position);
  SetSize(size);
  SetColor(text, rect);
  SetValue(value);
}
} // namespace s21