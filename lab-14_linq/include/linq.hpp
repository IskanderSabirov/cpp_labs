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
            enumerator(enumerator &&) = default;
            enumerator(const enumerator &) = delete;
            enumerator &operator=(const enumerator &) = delete;
            virtual ~enumerator() = default;

            virtual const T &operator*() = 0;// Получает текущий элемент.
            virtual enumerator &operator++() = 0;// Переход к следующему элементу
            virtual explicit operator bool() const = 0;// Возвращает true, если есть текущий элемент

            std::vector <T> to_vector() {
                std::vector <T> answer;
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
                    it++;
                    ++(*this);
                }
            }

            auto take(int number) {
                return take_enumerator<T>(*this, number);
            }

            auto drop(int number) {
                return drop_enumerator<T>(*this, number);
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator<T, F>(*this, std::move(func));
            }

            auto where_neq(T t) {
                return where([t](T cur) { return cur != t; });
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, std::move(func));
            }

            auto until_eq(T t) {
                return until([t](T cur) { return cur == t; });
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, std::move(func));
            }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

            const T &operator*() override {
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

            const T &operator*() override {
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
            select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(std::move(func)) {
                cur_ = func_(*parent);
            }

            select_enumerator(select_enumerator &&) noexcept = default;

            virtual explicit operator bool() const {
                return parent_.operator bool();
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                if (parent_.operator bool())
                    cur_ = func_(*parent_);
                return *this;
            }

            virtual const T &operator*() {
                return cur_;
            }

        private:
            enumerator<U> &parent_;
            F func_;
            T cur_;
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {}

            until_enumerator(until_enumerator &&) noexcept = default;

            virtual explicit operator bool() const {
                return parent_.operator bool() && !func_(*parent_);
            }

            virtual enumerator<T> &operator++() {
                if (parent_.operator bool() && !func_(*parent_))
                    ++parent_;
                return *this;
            }

            virtual const T &operator*() {
                return *parent_;
            }

        private:
            enumerator<T> &parent_;
            F func_;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
                while ((bool) parent && !func_(*parent))
                    ++parent;
            }
            where_enumerator(where_enumerator &&)  noexcept = default;

            virtual explicit operator bool() const {
                return (bool) parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                while ((bool) parent_ && !func_(*parent_))
                    ++parent_;
                return *this;
            }

            virtual const T &operator*() {
                return *parent_;
            }

        private:
            enumerator<T> &parent_;
            F func_;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : count_(count), parent_(parent) {}

            const T &operator*() override {
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