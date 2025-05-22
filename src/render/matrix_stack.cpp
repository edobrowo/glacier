#include "matrix_stack.hpp"

MatrixStack::MatrixStack() : mStack() {
}

void MatrixStack::push(const Transform& transform) {
    mStack.push_back(transform);
}

void MatrixStack::pop() {
    mStack.pop_back();
}

Transform MatrixStack::reduce() const {
    Transform result;
    for (const Transform& transform : mStack)
        result *= transform;
    return result;
}
