#include <cstring>
#include <cstdio>
#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y) {
    radius_ = radius;
    label_ = new char[strlen(label) + 1];
    strcpy(label_, label);
}

Circle::~Circle() {
    delete[] label_;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s", id, x, y, radius_, label_);
}

bool Circle::is_inside(int x, int y) const {
    return (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= radius_;
}

void Circle::zoom(int factor) {
    radius_ *= factor;
}
