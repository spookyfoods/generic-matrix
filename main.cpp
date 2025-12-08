#include <array>
#include <iostream>
#include <type_traits>

template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <Number T, size_t Rows, size_t Columns> class Matrix {

  public:
    std::array<T, Rows * Columns> matrixArray;
    template <typename... Args>
    Matrix(Args... args) {
        static_assert(sizeof...(Args) == Rows * Columns, "Number of arguments does not match Matrix dimensions!");
        matrixArray={static_cast<T>(args)...};
}
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Columns>& ourMatrix) {
        os << "Rows: " << Rows << '\n' << "Columns: " << Columns;
        return os;
    }
    T &operator()(int row, int column) {
        return matrixArray[row * Columns + column];
    }
    const T &operator()(int row, int column) const {
        return matrixArray[row * Columns + column];
    }
    Matrix operator+(const Matrix& other) const {
        Matrix<T,Rows,Columns> result;
        for(size_t i = 0; i < Rows * Columns; ++i) {
            result.matrixArray[i] = matrixArray[i] + other.matrixArray[i];
        }
        return result;
    }
    template <size_t OtherCols>
    auto operator*(const Matrix<T,Columns, OtherCols>& other) const {
        Matrix<T, Rows,OtherCols> result;
        for(int i = 0; i < Rows; i++) {
            for(int j = 0; j < OtherCols; j++) {
                result(i,j) = 0; 
                for(int k = 0; k < Columns; k++) {
                    result(i,j) += (*this)(i,k) * other(k,j);
                }
            }
        }
        return result;
    }
};
template <typename... Args>
void func(Args... args){
    std::array<float, 4> arr = {static_cast<float>(args)...};
}


int main() {
    func(1,2,2.5,3);
    Matrix<int,3,4> m1(1,2,3,4,5,6,7,8,9,10,12);

}
