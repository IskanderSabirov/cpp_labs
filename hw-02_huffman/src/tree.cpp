#include "tree.hpp"

namespace MyNodeTree {

    namespace {

        MyNode::node *create_tree(std::map<char, uint64_t> &data) {
            std::priority_queue<MyNode::node *, std::vector<MyNode::node *>, comp> tree{};
            try {
                for (auto [symbol, count]: data) {
                    auto n = new MyNode::node(symbol, count, nullptr, nullptr);
                    tree.push(n);
                }
                while (tree.size() > 1) {
                    MyNode::node *n1 = tree.top();
                    tree.pop();
                    MyNode::node *n2 = tree.top();
                    tree.pop();
                    tree.push(new MyNode::node(' ', n1->get_count() + n2->get_count(), n1, n2));
                }
            } catch (std::bad_alloc &e) {
                delete tree.top();
                throw MyException::my_exception("Error: can`t allocate new node in creation Huffman tree");
            };

            return (tree.empty() ? nullptr : tree.top());
        }

    }

    tree::tree(std::map<char, uint64_t> symbols_count_) {
        root_ = create_tree(symbols_count_);
        std::vector<bool> init;
        code_symbols(root_, init);
    }


    tree::~tree() {
        delete root_;
    }

    void tree::code_symbols(MyNode::node *node, std::vector<bool> &code) {

        if (node == nullptr)
            return;

        if (node->get_left() == nullptr && node->get_right() == nullptr) {
            if (code.empty())
                symbol_code_[node->get_symbol()] = std::vector<bool>{true};
            else
                symbol_code_[node->get_symbol()] = code;
        }

        std::vector<bool> left_value = code;
        std::vector<bool> right_value = code;

        left_value.push_back(false);
        right_value.push_back(true);

        code_symbols(node->get_left(), left_value);
        code_symbols(node->get_right(), right_value);

    }

    std::vector<bool> &tree::get_code_of_symbol(char symbol) {
        if (symbol_code_.find(symbol) == symbol_code_.end())
            throw MyException::my_exception("Error: can`t find requested symbol ");
        return symbol_code_[symbol];
    }

    uint8_t tree::get_symbol_count() const {
        return symbol_code_.size();
    }

    const std::map<char, std::vector<bool>> &tree::get_symbol_code_map() const {
        return symbol_code_;
    }


    bool comp::operator()(MyNode::node const *node1, MyNode::node const *node2) {
        return node1->get_count() > node2->get_count();
    }
}
