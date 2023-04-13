#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>

namespace lab_13 {

    template<typename T, std::size_t N>
    class my_array {
    private:

        std::size_t size_ = N;

        T data_[N];

    public:

        my_array() = default;

        my_array(const my_array &t) {
            for (size_t i = 0; i < N; ++i)
                data_[i] = t.data_[i];
        }

        T &at(std::size_t index) {
            if (index >= N)
                throw std::out_of_range("Invalid index ");
            return data_[index];
        }

        const T &operator[](std::size_t index) const {
            return data_[index];
        }

        T &operator[](std::size_t index) {
            return data_[index];
        }


         bool empty() const {
            return size_ == 0;
        }

         std::size_t size() const {
            return size_;
        }

        void fill(T val) {
            for (size_t i = 0; i < N; ++i)
                data_[i] = val;
        }

    };

    template<std::size_t N>
    class my_array<bool, N> {
    private:

        std::size_t size_ = N;

        uint8_t data_[N / sizeof(uint8_t) + (N % sizeof(uint8_t) == 0 ? 0 : 1)]{};

        std::size_t block_size_ = sizeof(uint8_t);

        class bool_manip {
        private:
            std::size_t step_;
            std::size_t &byte_;
        public:

            bool_manip(uint8_t &byte, uint8_t step) {
                step_ = step;
                byte_ = byte;
            }

            bool_manip &operator=(const bool &val) {
                if (val)
                    byte_ |= (1 >> step_);
                else
                    byte_ &= ~(1 >> step_);
                return *this;
            }

            bool_manip &operator=(const bool_manip &t) {
                this->operator=(t.value());
                return *this;
            }

            bool value() {
                return (byte_ >> step_) & 1;
            }

        };

    public:
        my_array() = default;

         bool at(std::size_t index) const {
            if (index >= N)
                throw std::out_of_range("Invalid index ");
            return bool_manip(index / block_size_, index % block_size_).value();
        }

        bool_manip at(std::size_t index) {
            if (index >= N)
                throw std::out_of_range("Invalid index ");
            return bool_manip(index / block_size_, index % block_size_);
        }


        bool operator[](std::size_t index) const {
            return bool_manip(index / block_size_, index % block_size_).value();
        }

        bool_manip operator[](std::size_t index) {
            return bool_manip(index / block_size_, index % block_size_);
        }


         bool empty() const {
            return size_ == 0;
        }

         std::size_t size() const {
            return size_;
        }

        void fill(bool val) {
            for (size_t i = 0; i < N; ++i)
                data_[i] = val;
        }

    };

}  // namespace lab_13

#endif  // MY_ARRAY_H_
