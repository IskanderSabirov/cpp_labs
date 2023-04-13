#include "Scheme.hpp"

Scheme::Scheme(int capacity) {
    if(capacity<0)
        throw std::runtime_error("Invalid capacity of scheme");
    figures_ = new Figure *[capacity];
    figures_count_ = 0;
    capacity_ = capacity;
}

Scheme::~Scheme() {
    for (int i = 0; i < figures_count_; i++)
        delete figures_[i];
    delete [] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    if(fg== nullptr)
        throw std::runtime_error("Invalid figure pointer");
    if (figures_count_ == capacity_)
        throw std::runtime_error("Invalid indices ");
    figures_[figures_count_++] = fg;
}


void Scheme::remove_figure(int id) { // элементы смещаются влево
    bool isFind = false;
    for (int i = 0; i < figures_count_; i++) {
        if (isFind)
            figures_[i - 1] = figures_[i];
        if (id == figures_[i]->get_id()) {
            isFind = true;
            delete figures_[i];
        }
    }
    figures_count_--;
    if (!isFind)
        throw std::runtime_error("Invalid id ");
}

void Scheme::print_all_figures() {
    for (int i = 0; i < figures_count_; i++) {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    // в случае если factor<0 выбросит исключение при попытке вызвать метод
    for (int i = 0; i < figures_count_; i++) {
        if (id == figures_[i]->get_id()) {
            figures_[i]->zoom(factor);
            return;
        }
    }

    throw std::runtime_error("Invalid id");
}

Figure *Scheme::is_inside_figure(int x, int y) { // если внутри нескольких фигур, то возвращается любая из них
    for (int i = 0; i < figures_count_; i++) {
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    }
    return nullptr;
}

[[maybe_unused]] void Scheme::move(int id, int new_x, int new_y) {
    for (int i = 0; i < figures_count_; i++) {
        if (id == figures_[i]->get_id()) {
            figures_[i]->move(new_x, new_y);
            return;
        }
    }

    throw std::runtime_error("Invalid id");
}