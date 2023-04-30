#ifndef LAB_13_ARRAY_NODE_HPP
#define LAB_13_ARRAY_NODE_HPP

#include <stdexcept>

namespace MyNode {

    class node {
    private:
        char symbol_{};
        uint32_t count_{};
        node *left_{};
        node *right_{};

    public:

        node() = default;

        node(node *left, node *right);

        node(char symbol, uint32_t count, node *left, node *right);

        [[nodiscard]] node *get_right() const;

        [[nodiscard]] node *get_left() const;

        [[nodiscard]] char get_symbol() const;

        [[nodiscard]] int32_t get_count() const;

        ~node();

    };

}

#endif //LAB_13_ARRAY_NODE_HPP
