#include "matrix.hpp"
int main() {
    // Usage: MatrixDense, not Matrix
    MatrixDense<int, 2, 2> m1(1, 2, 3, 4);
    
    // This calls operator<< from MatrixBase!
    std::cout << m1; 
}
