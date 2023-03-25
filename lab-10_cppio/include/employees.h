#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include "bin_manip.h"


class Employee {
protected:
    int32_t base_salary_{};
    std::string name_;
    virtual void print(std::ostream &ostream) const =0;
    virtual void print(std::ofstream &ofstream) const =0;
    virtual void read(std::istream &istream) =0;
    virtual void read(std::ifstream &ifstream) =0;
public :
    Employee(const std::string& name, int32_t base_salary);
    Employee() = default;
    virtual ~Employee() = default;
    [[nodiscard]] virtual int32_t salary() const = 0;

    friend std::ostream& operator<<(std::ostream& ostream, const Employee& e);
    friend std::istream& operator>>(std::istream& istream, Employee& e);
    friend std::ofstream& operator<<(std::ofstream& ofstream, const Employee& e);
    friend std::ifstream& operator>>(std::ifstream& ifstream, Employee& e);
};

///

class Developer : public Employee {
public:
    Developer(const std::string& name, int32_t base_salary, int32_t bonus);
    Developer() = default;
    [[nodiscard]] int32_t salary() const override;
private:
    bool has_bonus_{};
    void print(std::ostream &ostream) const override;
    void print(std::ofstream &ofstream) const override;
    void read(std::istream &istream) override;
    void read(std::ifstream &ifstream) override;
};

///

class SalesManager :Employee {
public:
    SalesManager(const std::string& name, int32_t base_salary, int32_t sold_items, int32_t item_price);
    SalesManager() = default;
    [[nodiscard]] int32_t salary() const override;
private:
    int32_t sold_number_{};
    int32_t item_price_{};
    void print(std::ostream &ostream) const override;
    void print(std::ofstream &ofstream) const override;
    void read(std::istream &istream) override;
    void read(std::ifstream &ifstream) override;
};

///

class EmployeesArray {
public:
    explicit EmployeesArray(int32_t size);
    EmployeesArray();
    ~EmployeesArray();

    void add(const Employee *e);

    [[nodiscard]] int32_t total_salary() const;

    friend std::ostream& operator<<(std::ostream& ostream, const EmployeesArray& employeesArray);

    friend std::ofstream &operator<<(std::ofstream &ofstream, const EmployeesArray &employeesArray);

    friend std::ifstream &operator>>(std::ifstream &ifstream, EmployeesArray &employeesArray);
private:
    int32_t size_;
    std::vector<Employee*> employees_;
};

///
std::ostream &operator<<(std::ostream &ostream, const Employee &e);

std::istream &operator>>(std::istream &istream, Employee &e);

std::ofstream &operator<<(std::ofstream &ofstream, const Employee &e);

std::ifstream &operator>>(std::ifstream &ifstream, Employee &e);

std::ostream &operator<<(std::ostream &ostream, const EmployeesArray &employeesArray);

std::ofstream &operator<<(std::ofstream &ofstream, const EmployeesArray &employeesArray);

std::ifstream &operator>>(std::ifstream &ifstream, EmployeesArray &employeesArray);

#endif
