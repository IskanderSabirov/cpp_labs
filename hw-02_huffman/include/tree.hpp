#ifndef HW_02_HUFFMAN_TREE_HPP
#define HW_02_HUFFMAN_TREE_HPP

#include <vector>
#include <map>
#include "node.hpp"
#include <queue>
#include "my_exception.hpp"

namespace MyNodeTree {

    class tree {
    private:

        MyNode::node *root_{};

        std::map<char, std::vector<bool>> symbol_code_{};

    public:

        explicit tree(std::map<char, uint64_t> symbols_count_);

        tree() = default;

        ~tree();

        void code_symbols(MyNode::node *node, std::vector<bool> &code);

        [[nodiscard]] std::vector<bool> &get_code_of_symbol(char symbol);

        [[nodiscard]] uint8_t get_symbol_count() const;

        [[nodiscard]] const std::map<char, std::vector<bool>> &get_symbol_code_map() const;

    };

    struct comp {
        bool operator()(MyNode::node const *node1, MyNode::node const *node2);
    };
}

#endif //HW_02_HUFFMAN_TREE_HPP
