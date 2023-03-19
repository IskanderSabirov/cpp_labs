#include <cstring>
#include <cstdio>
#include <stdexcept>
#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y) {
    if (radius < 0)
        throw std::runtime_error("Invalid radius size");
    if (label != nullptr) {
        label_ = new char[strlen(label) + 1];
        strcpy(label_, label);
    } else {
        throw std::runtime_error("Invalid label pointer");
    }
    radius_ = radius;
}

Circle::~Circle() {
    delete[] label_;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius_, label_);
}

bool Circle::is_inside(int x, int y) const {
    return (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= radius_ * radius_;
}

void Circle::zoom(int factor) {
    radius_ *= factor;
}
