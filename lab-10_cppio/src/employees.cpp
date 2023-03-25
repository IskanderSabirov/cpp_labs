#include <stdexcept>
#include "employees.h"
#include "bin_manip.h"

Employee::Employee(const std::string &name, int32_t base_salary) {
    name_ = name;
    if(base_salary<0)
        throw std::runtime_error("Invalid base_salary for employee :( ");
    base_salary_ = base_salary;
}

/// Developer

[[maybe_unused]] Developer::Developer(const std::string &name, int32_t base_salary, int32_t bonus) : Employee(name, base_salary) {
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

void Developer::print(std::ofstream &ofstream) const {
    ofstream << write_le_int32(1);
    ofstream << write_string(name_);
    ofstream << write_le_int32(base_salary_) << write_bool(has_bonus_);
}

void Developer::read(std::istream &istream) {
    std::string name;
    int32_t salary, bonus;
    istream >> name >> salary >> bonus;
    if (salary < 0 || (bonus != 0 && bonus != 1))
        throw std::runtime_error("Invalid data for developer");
    name_ = name;
    base_salary_ = salary;
    has_bonus_ = (bonus == 1);
}

void Developer::read(std::ifstream &ifstream) {
    ifstream >> read_string(&name_) >> read_le_int32(&base_salary_) >> read_bool(&has_bonus_);
}

/// Sales Manager

[[maybe_unused]] SalesManager::SalesManager(const std::string &name, int32_t base_salary, int32_t s_items, int32_t i_price) : Employee(
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

void SalesManager::print(std::ofstream &ofstream) const {
    ofstream << write_le_int32(2);
    ofstream << write_string(name_);
    ofstream << write_le_int32(base_salary_) << write_le_int32(sold_number_);
    ofstream << write_le_int32(item_price_);
}

void SalesManager::read(std::istream &istream) {
    std::string name;
    int32_t salary, sold, price;
    istream >> name >> salary >> sold >> price;
    if (salary < 0 || price < 0 || sold < 0)
        throw std::runtime_error("Invalid data for sales manager");
    name_ = name;
    base_salary_ = salary;
    sold_number_ = sold;
    item_price_ = price;
}

void SalesManager::read(std::ifstream &ifstream) {
    ifstream >> read_string(&name_) >> read_le_int32(&base_salary_) >> read_le_int32(&sold_number_);
    ifstream >> read_le_int32(&item_price_);
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

void EmployeesArray::add(const Employee *e) {
    employees_.push_back((Employee *) e);
    size_++;
}

int32_t EmployeesArray::total_salary() const {
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
    e.read(istream);
    return istream;
}

std::ofstream &operator<<(std::ofstream &ofstream, const Employee &e) {
    e.print(ofstream);
    return ofstream;
}

std::ifstream &operator>>(std::ifstream &ifstream, Employee &e) {
    e.read(ifstream);
    return ifstream;
}

std::ostream &operator<<(std::ostream &ostream, const EmployeesArray &employeesArray) {
    for (int32_t i = 0; i < employeesArray.size_; i++)
        ostream << (i + 1) << ". " << *employeesArray.employees_[i];
    ostream << "== Total salary: " << employeesArray.total_salary() << std::endl;
    return ostream;
}

std::ofstream &operator<<(std::ofstream &ofstream, const EmployeesArray &employeesArray) {
    ofstream << write_le_int32(employeesArray.size_);
    for (int32_t i = 0; i < employeesArray.size_; i++)
        ofstream << *employeesArray.employees_[i];
    return ofstream;
}

std::ifstream &operator>>(std::ifstream &ifstream, EmployeesArray &employeesArray) {
    int32_t number;
    ifstream >> read_le_int32(&number);
    for (int i = 0; i < number; i++) {
        int32_t type;
        ifstream >> read_le_int32(&type);
        if (type == 1) {
            auto e = new Developer();
            ifstream >> *(Employee *) e;
            employeesArray.add((Employee *) e);
        } else if (type == 2) {
            auto e = new SalesManager();
            ifstream >> *(Employee *) e;
            employeesArray.add((Employee *) e);
        } else {
            throw std::runtime_error("Invalid type of employee");
        }
    }
    return ifstream;
}