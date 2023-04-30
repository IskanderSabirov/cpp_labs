#include "node.hpp"

namespace MyNode {

    node::~node() {
        delete right_;
        delete left_;
    }

    node::node(char symbol, uint32_t count, node *left, node *right) {
        symbol_ = symbol;
        count_ = count;
        left_ = left;
        right_ = right;
    }

    node::node(node *left, node *right) {
        left_ = left;
        right_ = right;
    }

    node *node::get_right() const {
        return right_;
    }

    node *node::get_left() const {
        return left_;
    }

    char node::get_symbol() const {
        return symbol_;
    }

    int32_t node::get_count() const {
        return count_;
    }

}