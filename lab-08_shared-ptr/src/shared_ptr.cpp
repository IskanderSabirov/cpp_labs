#include <algorithm>
#include "shared_ptr.hpp"

shared_ptr::shared_ptr(Matrix *obj) {
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr &other) {
    storage_ = other.storage_;
    storage_->incr();
}

shared_ptr &shared_ptr::operator=(shared_ptr other) {
    if (this == &other)
        return *this;
    // можно было бы и просто вызвать ~shared_ptr, но вдруг он наследуется от другого класса и вызовется родительский деструктор
    // по опыту прошлой лабы
    shared_ptr tmp_ptr = shared_ptr(other);
    std::swap(storage_, tmp_ptr.storage_);
    return *this;
}

shared_ptr::~shared_ptr() {
    storage_->decr();
    if (storage_->getCounter() == 0)
        delete (storage_);
}

Matrix *shared_ptr::ptr() const {
    return storage_->getObject();
}

bool shared_ptr::isNull() const {
    return (storage_->getObject() == nullptr);
}

void shared_ptr::reset(Matrix *obj) {
    shared_ptr tmp_ptr = shared_ptr(obj);
    std::swap(storage_, tmp_ptr.storage_);
}

Matrix *shared_ptr::operator->() const {
    return storage_->getObject();
}

Matrix &shared_ptr::operator*() const {
    return *storage_->getObject();
}

shared_ptr::Storage::Storage(Matrix *mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    delete (data_);
}

void shared_ptr::Storage::incr() {
    ++ref_count_;
}

void shared_ptr::Storage::decr() {
    --ref_count_;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix *shared_ptr::Storage::getObject() const {
    return data_;
}