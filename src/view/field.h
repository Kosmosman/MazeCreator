//
// Created by Joaquina Daeron on 10/9/23.
//

#ifndef MAZE_FIELD_H
#define MAZE_FIELD_H

#include <SFML/Graphics.hpp>

namespace s21 {
    class Field : public sf::Drawable {
    public:
        using size_t = unsigned int;
        static constexpr size_t FIELD_SIDE_SIZE = 500;
        static constexpr size_t VERTEX_COUNT_MAX = 10000;

        Field() { StartInitialize(); }

        void Resize(const Field::size_t &new_height, const Field::size_t &new_width);

        void CreateMazeGraph(const std::vector<std::vector<bool>> &vertical,
                             const std::vector<std::vector<bool>> &horizontal);

    private:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        void StartInitialize();

        size_t height_{};
        size_t width_{};
        sf::VertexArray vertexes_;
        sf::VertexArray walls_;
    };
} // namespace s21

#endif //MAZE_FIELD_H
