#pragma once

#include <vector>

#include "common/math/transform.hpp"

class MatrixStack {
public:
    MatrixStack() = default;
    ~MatrixStack() = default;

    void push(const Transform& transform);
    void pop();
    Transform reduce() const;

private:
    std::vector<Transform> mStack;
};
