#include <iostream>
#include "doctest.h"
#include "tree.hpp"

using namespace MyNodeTree;

TEST_CASE("tree test - symbols count ") {
    auto map1 = std::map<char, uint64_t>{{'a', 10},
                                         {'b', 4},
                                         {'c', 1}};
    auto map2 = std::map<char, uint64_t>{};

    auto t1 = tree(map1);
    auto t2 = tree(map2);
    CHECK_EQ(t1.get_symbol_count(), 3);
    CHECK_EQ(t2.get_symbol_count(), 0);
}

TEST_CASE("tree test - get code of symbol #1") {
    auto map1 = std::map<char, uint64_t>{{'a', 10},
                                         {'b', 4},
                                         {'c', 1}};

    auto t1 = tree(map1);
    CHECK_EQ(t1.get_code_of_symbol('a'), std::vector<bool>{true});
    CHECK_EQ(t1.get_code_of_symbol('b'), std::vector<bool>{false, true});
    CHECK_EQ(t1.get_code_of_symbol('c'), std::vector<bool>{false, false});
}

TEST_CASE("tree test - get code of symbol #2") {
    auto map1 = std::map<char, uint64_t>{{'a', 5},
                                         {'b', 5},
                                         {'c', 5},
                                         {'d', 5}};

    auto t1 = tree(map1);
    CHECK_EQ(t1.get_code_of_symbol('d'), std::vector<bool>{true, true});
    CHECK_EQ(t1.get_code_of_symbol('b'), std::vector<bool>{true, false});
    CHECK_EQ(t1.get_code_of_symbol('c'), std::vector<bool>{false, true});
    CHECK_EQ(t1.get_code_of_symbol('a'), std::vector<bool>{false, false});
}


TEST_CASE("tree test - get map code of symbol ") {
    auto map = std::map<char, uint64_t>{{'a', 5},
                                        {'b', 5},
                                        {'c', 5},
                                        {'d', 5}};

    auto t1 = tree(map);

    auto answer = std::map<char, std::vector<bool>>{
            {'a', std::vector<bool>{false, false}},
            {'d', std::vector<bool>{true, true}},
            {'b', std::vector<bool>{true, false}},
            {'c', std::vector<bool>{false, true}}
    };
    CHECK_EQ(answer, t1.get_symbol_code_map());
}
