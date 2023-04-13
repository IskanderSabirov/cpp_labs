#include <iostream>
#include <cstring>

#include "my_vector.h"

namespace product {

    class Product {
    public:
        Product() {
            price_ = 0;
            quantity_ = 0;
            name_ = new char[1];
            name_[0] = '\0';
        }

        Product(const char *name, int quantity, double price) {
            if (name == nullptr || price < 0) {
                throw std::exception();
            }
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
            quantity_ = quantity;
            price_ = price;
        }

        Product(const Product &other) {
            if (other.name_ == nullptr || other.price_ < 0) {
                throw std::exception();
            }
            name_ = new char[strlen(other.name_) + 1];
            strcpy(name_, other.name_);
            quantity_ = other.quantity_;
            price_ = other.price_;
        }

        Product &operator=(const Product &other) {
            if (this == &other)
                return *this;
            if (other.name_ == nullptr || other.price_ < 0) {
                throw std::exception();
            }
            destroy_name();
            name_ = new char[strlen(other.name_) + 1];
            strcpy(name_, other.name_);
            quantity_ = other.quantity_;
            price_ = other.price_;
            return *this;
        }

        ~Product() {
            destroy_name();
        }

        friend std::ostream &operator<<(std::ostream &ostream, const Product &p);

        friend bool operator==(const Product &p1, const Product &p2);

    private:
        void destroy_name() {
            delete[] name_;
        }

        char *name_;
        int quantity_;
        double price_;
    };

    std::ostream &operator<<(std::ostream &ostream, const Product &p) {
        ostream << p.name_ << " " << p.price_ << " " << p.quantity_;
        return ostream;
    }

    bool operator==(const Product &p1, const Product &p2) {
        return (p2.quantity_ == p1.quantity_ && p1.price_ == p2.price_ && !(strcmp(p1.name_, p2.name_)));
    }

}  // namespace product

namespace {
    template<class T>
    void test_my_vector(const T &first, const T &second) {

        {
            containers::my_vector<T> v(10);
            assert(v.size() == 10);
            assert(v.capacity() == 16);
            for (size_t i = 0; i < 10; i++)
                assert(v[i] == T());
            std::cout << v << std::endl;

            std::cout << "initialization test passed " << std::endl;
        }

        {
            containers::my_vector<T> v2(7);
            std::cout << v2 << std::endl;
            v2.push_back(first);
            assert(v2[7] == first);
            v2.push_back(second);
            assert(v2[8] == second);
            std::cout << v2 << std::endl;

            std::cout << "push_back tests passed " << std::endl;
        }

        {
            containers::my_vector<T> v1(3);
            const containers::my_vector<T> &v(v1);
            assert(v.size() == v1.size());
            assert(v.capacity() == v1.capacity());
            assert(v[2] == T());

            const containers::my_vector<T> &v2 = v1;
            assert(v1.size() == v2.size());
            assert(v2.capacity() == v1.capacity());
            assert(v2[2] == T());

            std::cout << "copy my_vector test passed " << std::endl;
        }

    }

    template<class T>
    void test_my_vector_default_constructible(const T &first, const T &second) {
        containers::my_vector<T> v(10);
        assert(v.size() == 10);
        assert(v.capacity() == 16);
        for (size_t i = 0; i < 10; i++)
            assert(v[i] == T());
        v.push_back(first);
        assert(v.capacity() == 16);
        assert(v[10] == first);
        v[0] = second;
        assert(v[0] == second);
        v.pop_back();
        assert(v.size() == 10);
        v.reserve(20);
        assert(v.capacity() == 32);
        v.clear();
        assert(v.empty());
    }

}

int main() {
    containers::my_vector<int> v;
    v.push_back(2);
    const int n{3};
    v.push_back(n);
    std::cout << v << std::endl;

    test_my_vector<int>(5, 10);
    std::cout << std::endl;
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

    test_my_vector_default_constructible<int>(5, 10);

    return 0;
}


