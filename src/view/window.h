//
// Created by Joaquina Daeron on 10/8/23.
//

#ifndef MAZE_WINDOW_H
#define MAZE_WINDOW_H

#include <SFML/Graphics.hpp>

#include "facade.h"

namespace s21 {

class Window {
 public:
  explicit Window(Facade *facade)
      : window_(sf::VideoMode({width_, height_}), "Maze"), facade_(facade){};

  void Start();

 private:
  const unsigned int width_{500};
  const unsigned int height_{700};
  sf::RenderWindow window_;
  Facade *facade_{};
};

}  // namespace s21
#include "window.tpp"

#endif  // MAZE_WINDOW_H
