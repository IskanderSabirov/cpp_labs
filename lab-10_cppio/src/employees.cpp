#include <stdexcept>
#include "employees.h"

Employee::Employee(const std::string &name, int32_t base_salary) {
    name_ = name;
    base_salary_ = base_salary;
}

/// Developer

Developer::Developer(const std::string &name, int32_t base_salary, int32_t bonus) : Employee(name, base_salary) {
    if (bonus != 0 && bonus != 1)
        throw std::runtime_error("Invalid bonus for developer");
    has_bonus_ = (bonus == 1);
}

int32_t Developer::salary() const {
    int32_t salary = base_salary_;
    if (has_bonus_) {
        salary += 1000;
    }
    return salary;
}

void Developer::print(std::ostream &ostream) const {
    ostream << "Developer" << std::endl;
    ostream << "Name: " << name_ << std::endl;
    ostream << "Base Salary: " << base_salary_ << std::endl;
    ostream << "Has bonus: " << (has_bonus_ ? '+' : '-') << std::endl;
}

/// Sales Manager

SalesManager::SalesManager(const std::string &name, int32_t base_salary, int32_t s_items, int32_t i_price) : Employee(
        name, base_salary) {
    if (s_items < 0 || i_price < 0)
        throw std::runtime_error("Invalid data for Sales Manager");
    item_price_ = i_price;
    sold_number_ = s_items;
}

int32_t SalesManager::salary() const {
    return base_salary_ + sold_number_ * item_price_ / 100;
}

void SalesManager::print(std::ostream &ostream) const {
    ostream << "Sales Manager" << std::endl;
    ostream << "Name: " << name_ << std::endl;
    ostream << "Base Salary: " << base_salary_ << std::endl;
    ostream << "Sold items: " << sold_number_ << std::endl;
    ostream << "Item price: " << item_price_ << std::endl;
}

/// EmployeesArray

[[maybe_unused]] EmployeesArray::EmployeesArray(int32_t size) {
    if (size < 0)
        throw std::runtime_error("Invalid size for employees array");
    employees_ = std::vector<Employee *>(size);
    size_ = size;
}

EmployeesArray::EmployeesArray() {
    employees_ = std::vector<Employee *>(0);
    size_ = 0;
}


EmployeesArray::~EmployeesArray() {
    for (int32_t i = 0; i < size_; i++)
        delete employees_[i];
}

[[maybe_unused]] void EmployeesArray::add(const Employee *e) {
    employees_.push_back((Employee *) e);
    size_++;
}

[[maybe_unused]] int32_t EmployeesArray::total_salary() const {
    int32_t total = 0;
    for (auto e: employees_)
        total += e->salary();
    return total;
}

/// friend functions

std::ostream &operator<<(std::ostream &ostream, const Employee &e) {
    e.print(ostream);
    return ostream;
}

std::istream &operator>>(std::istream &istream, Employee &e) {
    return istream;
}

std::ofstream &operator<<(std::ofstream &ofstream, const Employee &e) {
    return ofstream;
}

std::ifstream &operator>>(std::ifstream &ifstream, Employee &e) {
    return ifstream;
}

std::ostream &operator<<(std::ostream &ostream, const EmployeesArray &employeesArray) {
    for (int32_t i = 0; i < employeesArray.size_; i++)
        ostream << (i + 1) << ". " << *employeesArray.employees_[i];
    ostream << "== Total salary: " << employeesArray.total_salary() << std::endl;
    return ostream;
}