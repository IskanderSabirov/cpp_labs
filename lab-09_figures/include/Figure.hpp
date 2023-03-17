#pragma once

class Figure {
public:
    Figure(int id, int x, int y);

    virtual ~Figure();

    virtual void print() const = 0;

    [[nodiscard]] virtual bool is_inside(int x, int y) const = 0;

    virtual void zoom(int factor) = 0;

    [[maybe_unused]] void move(int new_x, int new_y);

    [[nodiscard]] int get_id() const;

    // ...

protected:
    int id;
    int x;
    int y;
};
