#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        /// дальше реализация, добавлены еще несколько своих enumerator`ов

        template<typename T>
        class enumerator {
        public:
            enumerator() = default;

            enumerator(enumerator &&) noexcept = default;

            enumerator(const enumerator &) = delete;

            enumerator &operator=(const enumerator &) = delete;

            virtual ~enumerator() = default;

            virtual T operator*() const = 0; // Получает текущий элемент.
            virtual enumerator &operator++() = 0;  // Переход к следующему элементу
            virtual explicit operator bool() const = 0;  // Возвращает true, если есть текущий элемент

            auto drop(int count) {
                return drop_enumerator(*this, count);
            }

            auto take(int count) {
                return take_enumerator(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, std::move(func));
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, std::move(func));
            }

            auto until_eq(const T &v) {
                return until([=](const T &value) { return value == v; });
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator<T, F>(*this, std::move(func));
            }

            auto where_neq(const T &v) {
                return where([=](const T &value) { return value != v; });
            }


            std::vector<T> to_vector() {
                std::vector<T> answer;
                while (*this) {
                    answer.push_back(**this);
                    ++(*this);
                }
                return answer;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    *it = **this;
                    ++it;
                    ++(*this);
                }
            }

        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

            T operator*() const override {
                return *begin_;
            }

            range_enumerator &operator++() override {
                ++begin_;
                return *this;
            }

            explicit operator bool() const override {
                return begin_ != end_;
            }

        private:
            Iter begin_;
            Iter end_;
        };

        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
                for (int i = 0; i < count && parent_; i++)
                    ++parent_;
            }

            T operator*() const override {
                return *parent_;
            }

            enumerator<T> &operator++() override {
                ++parent_;
                return *this;
            }

            explicit operator bool() const override {
                return bool(parent_);
            }

        private:
            enumerator<T> &parent_;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator(enumerator<U> &parent, F func) : func_(std::move(func)), parent_(parent) {
            }

            T operator*() const override {
                return func_(*parent_);
            }

            enumerator<T> &operator++() override {
                ++(parent_);
                return *this;
            }

            explicit operator bool() const override {
                return bool(parent_);
            }

        private:
            F func_;
            enumerator<U> &parent_;
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent),
                                                                   predicate_(std::move(predicate)),
                                                                   end_(predicate_(*parent)) {};

            T operator*() const override {
                return *parent_;
            }

            until_enumerator &operator++() override {
                ++parent_;
                end_ |= !parent_ || predicate_(*parent_);
                return *this;
            }

            explicit operator bool() const override {
                return !end_;
            }

        private:
            enumerator<T> &parent_;
            F predicate_;
            bool end_;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:

            where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent),
                                                                   predicate_(std::move(predicate)) {
                while (parent_.operator bool() && !predicate(*parent_))
                    ++parent_;
            }

            where_enumerator(where_enumerator &&)  noexcept = default;

            where_enumerator &operator++() override {
                if (parent_.operator bool()) {
                    do {
                        ++parent_;
                    } while (parent_.operator bool() && !predicate_(*parent_));
                }
                return *this;
            }

            T operator*() const override {
                return *parent_;
            }

            explicit operator bool() const override {
                return parent_.operator bool();
            }

        private:
            enumerator<T> &parent_;
            F predicate_;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : count_(count), parent_(parent) {}

            T operator*() const override {
                return *parent_;
            }

            take_enumerator &operator++() override {
                ++parent_;
                count_--;
                return *this;
            }

            explicit operator bool() const override {
                return (count_ != 0) && parent_;
            }

        private:
            int count_;
            enumerator<T> &parent_;
        };

    } // namespace impl

    template<typename T>
    auto from(T begin, T end) {
        return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
    }

} // namespace linq

#endif