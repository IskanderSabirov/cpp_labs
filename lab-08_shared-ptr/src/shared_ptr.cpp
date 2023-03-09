#include "shared_ptr.cpp"

shared_ptr::shared_ptr(Matrix *obj) {
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr &other) {
    storage_ = other.storage_;
    storage_.incr();
}

shared_ptr::shared_ptr &operator=(shared_ptr other) {
    // можно было бы и просто вызвать ~shared_ptr, но вдруг он наследуется от другого класса и вызовется родительский деструктор
    // по опыту прошлой лабы
    shared_ptr tmp_ptr = shared_ptr(other);
    std::swap(storage_, tmp_ptr.storage_);
    return *this;
}

shared_ptr::~shared_ptr() {
    storage_.decr();
    if (storage_.getCounter() == 0)
        delete (storage_);
}

shared_ptr::Matrix *ptr() const {
    return storage_.getObject();
}

shared_ptr:: bool isNull() const {
    return (storage_.getObject() == nullptr)
}

shared_ptr:: void reset(Matrix *obj) {
    shared_ptr tmp_ptr = shared_ptr(obj);
    std::swap(storage_, tmp_ptr.storage_);
    return *this;
}

shared_ptr::Matrix *operator->() const {
    return storage_.getObject();
}

shared_ptr::Matrix &operator*() const {
    return *storage_.getObject();
}

Storage::Storage(Matrix *mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

Storage::~Storage() {
    delete (data_);
}

Storage:: void incr() {
    ++ref_count_;
}

Storage:: void decr() {
    --ref_count_;
}

Storage:: int getCounter() const {
    return ref_count_;
}

Storage::Matrix *getObject() {
    return data_;
}

