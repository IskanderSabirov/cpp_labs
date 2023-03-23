#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

//с учетом, что у всех есть базовая или дефолт = 0
class Employee {
protected:
    int32_t base_salary_;
    char *name_;
private:
    virtual void print(std::ostream &ostream) const =0;
public :
    Employee(const char *name,int base_salary);
    virtual ~Employee();
    virtual int salary() = 0;

    friend std::ostream& operator<<(std::ostream& ostream, const Employee& e);
    friend std::istream& operator>>(std::istream& istream, Employee& e);
    friend std::ofstream& operator<<(std::ofstream& ofstream, const Employee& e);
    friend std::ifstream& operator>>(std::ifstream& ifstream, Employee& e);
};

///

class Developer : public Employee {
public:
    Developer(const char* name, int base_salary, int bonus);
    int salary() override;
private:
    bool has_bonus_;
    void print(std::ostream &ostream) const override;
};

///

class SalesManager :Employee {
public:
    SalesManager(const char *name, int base_salary, int sold_items, int item_price);
    int salary() override;
private:
    int32_t sold_number_;
    int32_t item_price_;
    void print(std::ostream &ostream) const override;
};

///

class EmployeesArray {
public:
    explicit EmployeesArray(int size);
    EmployeesArray();
    ~EmployeesArray();

    void add(const Employee *e);

    [[nodiscard]] int total_salary() const;

    friend std::ostream& operator<<(std::ostream& ostream, const EmployeesArray& employeesArray);

private:
    int32_t size_;
    std::vector<Employee*> employees_;
};

#endif
