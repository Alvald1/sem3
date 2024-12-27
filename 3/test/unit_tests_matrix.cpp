#include <gtest/gtest.h>
#include "map/matrix/matrix.hpp"

// Test default constructor
TEST(MatrixTest, default_constructor) {
    Matrix<int> m;
    EXPECT_EQ(m.get_rows(), 0);
    EXPECT_EQ(m.get_cols(), 0);
}

// Test parameterized constructor
TEST(MatrixTest, parameterized_constructor) {
    Matrix<int> m(3, 4);
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 4);
}

// Test copy constructor
TEST(MatrixTest, copy_constructor) {
    Matrix<int> m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    Matrix<int> m2(m1);
    EXPECT_EQ(m2.get_rows(), 2);
    EXPECT_EQ(m2.get_cols(), 2);
    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 1), 2);
}

// Test copy constructor with empty matrix
TEST(MatrixTest, copy_constructor_empty) {
    Matrix<int> m1;
    Matrix<int> m2(m1);
    EXPECT_EQ(m2.get_rows(), 0);
    EXPECT_EQ(m2.get_cols(), 0);
}

// Test move constructor
TEST(MatrixTest, move_constructor) {
    Matrix<int> m1(2, 2);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    Matrix<int> m2(std::move(m1));
    EXPECT_EQ(m2.get_rows(), 2);
    EXPECT_EQ(m2.get_cols(), 2);
    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 1), 2);
    EXPECT_EQ(m1.get_rows(), 0);
    EXPECT_EQ(m1.get_cols(), 0);
}

// Test copy assignment
TEST(MatrixTest, copy_assignment) {
    Matrix<int> m1(2, 3);
    m1(0, 0) = 5;
    Matrix<int> m2;
    m2 = m1;
    EXPECT_EQ(m2.get_rows(), 2);
    EXPECT_EQ(m2.get_cols(), 3);
    EXPECT_EQ(m2(0, 0), 5);
}

// Test copy assignment with empty matrix
TEST(MatrixTest, copy_assignment_empty) {
    Matrix<int> m1;
    Matrix<int> m2(2, 2);
    m2 = m1;
    EXPECT_EQ(m2.get_rows(), 0);
    EXPECT_EQ(m2.get_cols(), 0);
}

// Test move assignment self-assignment
TEST(MatrixTest, move_assignment_self) {
    Matrix<int> m(2, 3);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    m = m; // Self-assignment
    EXPECT_EQ(m.get_rows(), 2);
    EXPECT_EQ(m.get_cols(), 3);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(1, 0), 3);
    EXPECT_EQ(m(1, 1), 4);
}

// Test move assignment
TEST(MatrixTest, move_assignment) {
    Matrix<int> m1(2, 3);
    m1(0, 0) = 7;
    Matrix<int> m2;
    m2 = std::move(m1);
    EXPECT_EQ(m2.get_rows(), 2);
    EXPECT_EQ(m2.get_cols(), 3);
    EXPECT_EQ(m2(0, 0), 7);
    EXPECT_EQ(m1.get_rows(), 0);
    EXPECT_EQ(m1.get_cols(), 0);
}

// Test move assignment with empty matrix
TEST(MatrixTest, move_assignment_empty) {
    Matrix<int> m1;
    Matrix<int> m2(2, 2);
    m2 = std::move(m1);
    EXPECT_EQ(m2.get_rows(), 0);
    EXPECT_EQ(m2.get_cols(), 0);
    EXPECT_EQ(m1.get_rows(), 0);
    EXPECT_EQ(m1.get_cols(), 0);
}

// Test move assignment self-assignment
TEST(MatrixTest, move_assignment_self2) {
    Matrix<int> m(2, 2);
    m(0, 0) = 5;
    m(0, 1) = 6;
    m(1, 0) = 7;
    m(1, 1) = 8;
    m = std::move(m); // Self-move assignment
    EXPECT_EQ(m.get_rows(), 2);
    EXPECT_EQ(m.get_cols(), 2);
    EXPECT_EQ(m(0, 0), 5);
    EXPECT_EQ(m(0, 1), 6);
    EXPECT_EQ(m(1, 0), 7);
    EXPECT_EQ(m(1, 1), 8);
}

// Test resize increasing size
TEST(MatrixTest, resize_increase) {
    Matrix<int> m(2, 2);
    m(0, 0) = 1;
    m.resize(3, 3);
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 3);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(2, 2), 0); // Default initialized
}

// Test resize decreasing size
TEST(MatrixTest, resize_decrease) {
    Matrix<int> m(3, 3);
    m(2, 2) = 9;
    m.resize(2, 2);
    EXPECT_EQ(m.get_rows(), 2);
    EXPECT_EQ(m.get_cols(), 2);
    // Accessing (2,2) should now be out of range
    EXPECT_THROW(m(2, 2), std::out_of_range);
}

// Test resize to zero rows and zero columns
TEST(MatrixTest, resize_to_zero) {
    Matrix<int> m(3, 3);
    m.resize(0, 0);
    EXPECT_EQ(m.get_rows(), 0);
    EXPECT_EQ(m.get_cols(), 0);
    EXPECT_THROW(m(0, 0), std::out_of_range);
}

// Test resize with one dimension zero
TEST(MatrixTest, resize_one_dimension_zero) {
    Matrix<int> m(2, 2);
    m.resize(0, 3);
    EXPECT_EQ(m.get_rows(), 0);
    EXPECT_EQ(m.get_cols(), 3);
    EXPECT_THROW(m(0, 0), std::out_of_range);

    m.resize(3, 0);
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 0);
    EXPECT_THROW(m(0, 0), std::out_of_range);
}

// Test add_row
TEST(MatrixTest, add_row) {
    Matrix<int> m(2, 2);
    m.add_row(1);
    EXPECT_EQ(m.get_rows(), 3);
    // New row initialized to 0
    EXPECT_EQ(m(1, 0), 0);
    EXPECT_EQ(m(1, 1), 0);
}

// Test adding a row at the end
TEST(MatrixTest, add_row_at_end) {
    Matrix<int> m(2, 2);
    m.add_row(2);
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m(2, 0), 0);
    EXPECT_EQ(m(2, 1), 0);
}

// Test add_column
TEST(MatrixTest, add_column) {
    Matrix<int> m(2, 2);
    m.add_column(1);
    EXPECT_EQ(m.get_cols(), 3);
    // New column initialized to 0
    EXPECT_EQ(m(0, 1), 0);
    EXPECT_EQ(m(1, 1), 0);
}

// Test adding a column at the end
TEST(MatrixTest, add_column_at_end) {
    Matrix<int> m(2, 2);
    m.add_column(2);
    EXPECT_EQ(m.get_cols(), 3);
    EXPECT_EQ(m(0, 2), 0);
    EXPECT_EQ(m(1, 2), 0);
}

// Test delete_row
TEST(MatrixTest, delete_row) {
    Matrix<int> m(3, 2);
    m.delete_row(1);
    EXPECT_EQ(m.get_rows(), 2);
    // Ensure the correct rows remain
    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(1, 0), 0);
}

// Test deleting the last row
TEST(MatrixTest, delete_last_row) {
    Matrix<int> m(3, 2);
    m.delete_row(2);
    EXPECT_EQ(m.get_rows(), 2);
    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(1, 0), 0);
}

// Test delete_column
TEST(MatrixTest, delete_column) {
    Matrix<int> m(2, 3);
    m.delete_column(1);
    EXPECT_EQ(m.get_cols(), 2);
    // Ensure the correct columns remain
    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(0, 1), 0);
}

// Test deleting the last column
TEST(MatrixTest, delete_last_column) {
    Matrix<int> m(2, 3);
    m.delete_column(2);
    EXPECT_EQ(m.get_cols(), 2);
    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(0, 1), 0);
}

// Test operator()
TEST(MatrixTest, access_operator) {
    Matrix<int> m(2, 2);
    m(0, 0) = 10;
    m(1, 1) = 20;
    EXPECT_EQ(m(0, 0), 10);
    EXPECT_EQ(m(1, 1), 20);
    // Test out of range
    EXPECT_THROW(m(2, 2), std::out_of_range);
}

// Test operator() on empty matrix
TEST(MatrixTest, access_operator_empty) {
    Matrix<int> m;
    EXPECT_THROW(m(0, 0), std::out_of_range);
}

// Test iterator
TEST(MatrixIteratorTest, iteration) {
    Matrix<int> m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    int sum = 0;
    for (auto it = m.begin(); it != m.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 10);
}

// Test const iterator
TEST(MatrixIteratorTest, const_iteration) {
    Matrix<int> m(2, 2);
    m(0, 0) = 5;
    m(0, 1) = 6;
    m(1, 0) = 7;
    m(1, 1) = 8;
    const Matrix<int>& cm = m;
    int sum = 0;
    for (auto it = cm.cbegin(); it != cm.cend(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 26);
}

// Test iterator operators
TEST(MatrixIteratorTest, iterator_operators) {
    Matrix<int> m(1, 3);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(0, 2) = 3;
    auto it = m.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    --it;
    // Test copy assignment self-assignment
    EXPECT_EQ(*it, 2);
    it--;
    EXPECT_EQ(*it, 1);
    EXPECT_TRUE(it < m.end());
    EXPECT_TRUE(m.end() > it);
    EXPECT_EQ(it[1], 2);
}

// Test exception on invalid add_row
TEST(MatrixTest, add_row_out_of_range) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.add_row(3), std::out_of_range);
}

// Test exception on invalid add_column
TEST(MatrixTest, add_column_out_of_range) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.add_column(3), std::out_of_range);
}

// Test exception on invalid delete_row
TEST(MatrixTest, delete_row_out_of_range) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.delete_row(2), std::out_of_range);
}

// Test exception on invalid delete_column
TEST(MatrixTest, delete_column_out_of_range) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.delete_column(2), std::out_of_range);
}

TEST(MatrixTest, copy_assignment_self) {
    Matrix<int> m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    m = m; // Self-assignment
    EXPECT_EQ(m.get_rows(), 2);
    EXPECT_EQ(m.get_cols(), 2);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(1, 0), 3);
    EXPECT_EQ(m(1, 1), 4);
}
