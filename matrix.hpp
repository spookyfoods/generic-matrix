#pragma once
#include <array>
#include <iostream>
#include <type_traits>

template <typename Derived>
class MatrixBase{
    const Derived& self() const { 
        return *static_cast<const Derived*>(this); 
    }
    friend std::ostream& operator<<(std::ostream& os, const MatrixBase<Derived>& ourMatrixBase) {
        const Derived& ourMatrixChild=ourMatrixBase.self();
        for (size_t i = 0; i < ourMatrixChild.rows(); ++i) {
            os << "[ ";
            for (size_t j = 0; j < ourMatrixChild.cols(); ++j) {
                os << ourMatrixChild(i, j) << " ";
            }
            os << "]\n";
        }
        return os;
    }
};

template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <Number T, size_t Rows, size_t Columns> 
class MatrixDense : public MatrixBase<MatrixDense<T,Rows,Columns>> {
  private:
    std::array<T, Rows * Columns> matrixArray;
  public:
    MatrixDense() : matrixArray{} {}
    
    template <typename... Args>
    MatrixDense(Args... args) {
        static_assert(sizeof...(Args) == Rows * Columns, "Number of arguments does not match Matrix dimensions!");
        matrixArray={static_cast<T>(args)...};
    }
    constexpr size_t rows() const { return Rows; }
    constexpr size_t cols() const { return Columns; }
    T &operator()(size_t row, size_t column) {
        return matrixArray[row * Columns + column];
    }
    const T &operator()(size_t row, size_t column) const {
        return matrixArray[row * Columns + column];
    }
    MatrixDense operator+(const MatrixDense& other) const {
        MatrixDense<T,Rows,Columns> result;
        for(size_t i = 0; i < Rows * Columns; ++i) {
            result.matrixArray[i] = matrixArray[i] + other.matrixArray[i];
        }
        return result;
    }
    template <size_t OtherCols>
    auto operator*(const MatrixDense<T,Columns, OtherCols>& other) const {
        MatrixDense<T, Rows,OtherCols> result;
        for(size_t i{0}; i < Rows; i++) {
            for(size_t j{0}; j < OtherCols; j++) {
                result(i,j) = 0;
                for(size_t k {0}; k < Columns; k++) {
                    result(i,j) += (*this)(i,k) * other(k,j);
                }
            }
        }
        return result;
    }
    const T* data() const {
        return matrixArray.data();
    }
};
