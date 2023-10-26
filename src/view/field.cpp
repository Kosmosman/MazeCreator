//
// Created by Joaquina Daeron on 10/9/23.
//

#include "field.h"

namespace s21 {
    void Field::CreateField(const Field::size_t &new_height, const Field::size_t &new_width) {
        if (height_ != new_height || width_ != new_width) {
            height_ = new_height;
            width_ = new_width;
            vertexes_.resize(height_ * width_ * 4);
            float cell_h{static_cast<float>(FIELD_SIDE_SIZE) / static_cast<float>(height_)};
            float cell_w{static_cast<float>(FIELD_SIDE_SIZE) / static_cast<float>(width_)};
            for (size_t i = 0; i < height_; ++i) {
                for (size_t j = 0; j < width_; ++j) {
                    auto start_pos = i * width_ * 4 + j * 4;

                    vertexes_[start_pos].position = {j * cell_w, i * cell_h};
                    vertexes_[start_pos + 1].position = {(j + 1) * cell_w, i * cell_h};
                    vertexes_[start_pos + 2].position = {(j + 1) * cell_w, (i + 1) * cell_h};
                    vertexes_[start_pos + 3].position = {j * cell_w, (i + 1) * cell_h};

                    vertexes_[start_pos].color = sf::Color::Black;
                    vertexes_[start_pos + 1].color = sf::Color::Black;
                    vertexes_[start_pos + 2].color = sf::Color::Black;
                    vertexes_[start_pos + 3].color = sf::Color::Black;
                }
            }
        }
    }

    void Field::CreateMazeGraph(const std::vector<std::vector<bool>> &vertical,
                                const std::vector<std::vector<bool>> &horizontal) {
        CreateField(vertical.size(), vertical[0].size());
        walls_.resize(count_of_walls_ * 6);
        path_vertexes_.resize(0);
        size_t pos{0};
        for (size_t i = 0; i < height_; ++i) {
            for (size_t j = 0; j < width_; ++j) {
                if (vertical[i][j]) {
                    auto start_pos = i * width_ * 4 + j * 4;
                    walls_[pos++].position = vertexes_[start_pos + 1].position;
                    walls_[pos++].position = vertexes_[start_pos + 2].position;
                    walls_[pos++].position = {vertexes_[start_pos + 1].position.x - 2,
                                              vertexes_[start_pos + 1].position.y};

                    walls_[pos++].position = vertexes_[start_pos + 2].position;
                    walls_[pos++].position = {vertexes_[start_pos + 1].position.x - 2,
                                              vertexes_[start_pos + 1].position.y};
                    walls_[pos++].position = {vertexes_[start_pos + 2].position.x - 2,
                                              vertexes_[start_pos + 2].position.y};
                }
                if (horizontal[i][j]) {
                    auto start_pos = i * width_ * 4 + j * 4;
                    walls_[pos++].position = vertexes_[start_pos + 2].position;
                    walls_[pos++].position = vertexes_[start_pos + 3].position;
                    walls_[pos++].position = {vertexes_[start_pos + 2].position.x,
                                              vertexes_[start_pos + 2].position.y - 2};

                    walls_[pos++].position = vertexes_[start_pos + 3].position;
                    walls_[pos++].position = {vertexes_[start_pos + 2].position.x,
                                              vertexes_[start_pos + 2].position.y - 2};
                    walls_[pos++].position = {vertexes_[start_pos + 3].position.x,
                                              vertexes_[start_pos + 3].position.y - 2};
                }
            }
        }
        walls_.resize(pos);
    }

    void Field::CreatePath(const std::vector<std::pair<size_t, size_t>>& path) {
        path_vertexes_.resize((path.size() - 1) * 6);
        for (size_t i = 0, pos = 0; i < path.size() - 1; ++i) {
            auto start_pos = path[i].first * width_ * 4 + path[i].second * 4;
            auto end_pos = path[i + 1].first * width_ * 4 + path[i + 1].second * 4;
            auto left_x{(vertexes_[start_pos].position.x + vertexes_[start_pos + 1].position.x) / 2};
            auto right_x{(vertexes_[end_pos].position.x + vertexes_[end_pos + 1].position.x) / 2};
            auto top_y{(vertexes_[start_pos + 1].position.y + vertexes_[start_pos + 2].position.y) / 2};
            auto down_y{(vertexes_[end_pos + 1].position.y + vertexes_[end_pos + 2].position.y) / 2};

            path_vertexes_[pos].color = sf::Color::Red;
            path_vertexes_[pos++].position = {left_x - 1, top_y + 1};
            path_vertexes_[pos].color = sf::Color::Red;
            path_vertexes_[pos++].position = {right_x + 1, top_y + 1};
            path_vertexes_[pos].color = sf::Color::Red;
            path_vertexes_[pos++].position = {right_x + 1, down_y - 1};

            path_vertexes_[pos].color = sf::Color::Red;
            path_vertexes_[pos++].position = {right_x + 1, down_y - 1};
            path_vertexes_[pos].color = sf::Color::Red;
            path_vertexes_[pos++].position = {left_x - 1, down_y - 1};
            path_vertexes_[pos].color = sf::Color::Red;
            path_vertexes_[pos++].position = {left_x - 1, top_y + 1};
        }
    }

    void Field::StartInitialize() {
        vertexes_.setPrimitiveType(sf::PrimitiveType::LineStrip);
        walls_.setPrimitiveType(sf::PrimitiveType::Triangles);
        path_vertexes_.setPrimitiveType(sf::PrimitiveType::Triangles);
    }

    void Field::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
        target.draw(vertexes_, states);
        target.draw(walls_, states);
        target.draw(path_vertexes_, states);
    }
} // namespace s21