#include "../matrix.hpp"

#define test_condition(condition) if(condition) \
                                    std::cerr << "[FAIL] " #condition "\n"; \
                                  else \
                                    std::cout << "[OK] " #condition "\n";

int main() {
    idk::Matrix<long double> val = 
                        {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 10}};

    test_condition(val.trace() != 16)
    test_condition(val.minor(0, 0) != 2)
    test_condition(val.determinant() != -3)
    test_condition(val.transpose().determinant() != -3)

    std::cout << val << '\n';
    
    idk::Matrix<long double> val1 = 
                        {{1, 112, 3, 13},
                        {4, 5, 6, 31},
                        {7, 8, 9, 69},
                        {10, 11, 12, 155}};

    test_condition(val1.determinant() != 31680)
    
    idk::Matrix<long double> lower_triangular = {{1, 0, 0},
                                                 {2, 3, 0},
                                                 {4, 5, 6}};

    idk::Matrix<long double> upper_triangular = {{1, 2, 3},
                                                 {0, 4, 5},
                                                 {0, 0, 6}};

    idk::Matrix<long double> upper_and_lower_triangular = 
                                                {{1, 0, 0},
                                                 {0, 4, 0},
                                                 {0, 0, 6}};

    idk::Matrix<long double> lower_triangular_4x4 = 
                                                {{1, 0, 0, 0},
                                                 {2, 3, 0, 0},
                                                 {4, 5, 6, 0},
                                                 {7, 8, 9, 10}};
    
    idk::Matrix<long double> orthogonal_matrix = {{0, 1},
                                                  {1, 0}};

    test_condition(!idk::Matrix<long double>({{1, 0}, {0, 1}}).is_identity())
    test_condition(!idk::Matrix<long double>({{-5, -8, 0}, {3, 5, 0}, {1, 2, -1}}).is_involutory())
    test_condition(!idk::Matrix<long double>({{2, -2, -4}, {-1, 3, 4}, {1, -2, -3}}).is_idempotent())
    test_condition((idk::Matrix<long double>({{1, 2}}) * idk::Matrix<long double>({{3}, {4}})) != idk::Matrix<long double>({{11}}))
    test_condition((orthogonal_matrix * idk::Matrix<long double>({{1, 0}, {0, 1}})) != orthogonal_matrix)
    test_condition(!orthogonal_matrix.is_orthogonal())
    test_condition(!upper_and_lower_triangular.is_symmetric())
    test_condition(upper_and_lower_triangular.is_scalar())
    test_condition(!upper_and_lower_triangular.is_diagonal())
    test_condition(!lower_triangular.is_lower_triangular())
    test_condition(!upper_triangular.is_upper_triangular())
    test_condition(!upper_and_lower_triangular.is_upper_triangular() || !upper_and_lower_triangular.is_lower_triangular())
    test_condition(!lower_triangular_4x4.is_lower_triangular())
    
    std::cout << val.inverse() << '\n';
    std::cout << val.adjoint() << '\n';
}