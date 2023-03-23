#include <cstdio>
#include <stdexcept>
#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    if (width < 0 || height < 0)
        throw std::runtime_error("Invalid sizes of rectangle");
    width_ = width;
    height_ = height;
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width_, height_);
}

bool Rectangle::is_inside(int x, int y) const {
    return (x <= this->x + width_ / 2 && x >= this->x - width_ / 2) &&
           (y <= this->y + height_ / 2 && y >= this->y - height_ / 2);
}

void Rectangle::zoom(int factor) {
    if (factor < 0)
        throw std::runtime_error("Invalid label pointer");
    width_ *= factor;
    height_ *= factor;
}