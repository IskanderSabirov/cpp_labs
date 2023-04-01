#include <iostream>
#include <cstring>

#include "my_vector.hpp"

namespace product {

    class Product {
    public:
        Product(const char *name, int quantity, double price) {
            if (name == nullptr || quantity < 0 || price < 0) {
                throw std::exception();
            }
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
            quantity_ = quantity;
            price_ = price;
        }

        Product(Product &other) {
            if (other.name_ == nullptr || other.quantity_ < 0 || other.price_ < 0) {
                throw std::exception();
            }
            name_ = new char[strlen(other.name_) + 1];
            strcpy(name_, other.name_);
            quantity_ = other.quantity_;
            price_ = other.price_;
        }

        Product &operator=(Product &other) {
            if (this == &other)
                return *this;
            if (other.name_ == nullptr || other.quantity_ < 0 || other.price_ < 0) {
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

    private:
        void destroy_name(){
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

}  // namespace product

int main() {
    containers::my_vector<int> v;
    v.push_back(2);
    const int n{3};
    v.push_back(n);
    std::cout << v << std::endl;

    //test_my_vector<int>(5, 10);
    //test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}
