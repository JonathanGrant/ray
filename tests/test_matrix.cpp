#include "catch_amalgamated.hpp"
#include "matrix.hpp"


TEST_CASE("Matrix3D class") {
    std::vector<Vector3D> data {
        Vector3D(1, 2, 3),
        Vector3D(4, 1, 7),
        Vector3D(7, -2, 9)
    };

    Matrix3D m1(data);

    SECTION("Matrix creation and basic operations") {
        REQUIRE(m1.rows() == 3);
        REQUIRE(m1.get(1, 1) == 1);
        m1.set(1, 1, 10);
        REQUIRE(m1.get(1, 1) == 10);

        Vector3D v = m1.get(2);
        REQUIRE(v.x == 7);
        REQUIRE(v.y == -2);
        REQUIRE(v.z == 9);
        
        Vector3D v_new(10, 11, 12);
        m1.set(2, v_new);
        Vector3D v_after = m1.get(2);
        REQUIRE(v_after.x == 10);
        REQUIRE(v_after.y == 11);
        REQUIRE(v_after.z == 12);
    }

    // Assuming we have a square matrix (3x3)
    SECTION("Matrix arithmetic operations") {
        Vector3D v_add(1, 1, 1);
        Matrix3D m2 = m1 + v_add;

        REQUIRE(m2.get(0, 0) == 2);
        REQUIRE(m2.get(1, 1) == 2);
        REQUIRE(m2.get(2, 2) == 10);

        Matrix3D m3 = m1 + m2;
        REQUIRE(m3.get(0, 0) == 3);
        REQUIRE(m3.get(1, 1) == 3);
        REQUIRE(m3.get(2, 2) == 19);

        Matrix3D m4 = m1 - v_add;
        REQUIRE(m4.get(0, 0) == 0);
        REQUIRE(m4.get(1, 1) == 0);
        REQUIRE(m4.get(2, 2) == 8);

        Matrix3D m5 = m1 - m2;
        REQUIRE(m5.get(0, 0) == -1);
        REQUIRE(m5.get(1, 1) == -1);
        REQUIRE(m5.get(2, 2) == -1);

        Matrix3D m6 = m1 * 2.0;
        REQUIRE(m6.get(0, 0) == 2);
        REQUIRE(m6.get(1, 1) == 2);
        REQUIRE(m6.get(2, 2) == 18);

        Matrix3D m7 = m6 / 2.0;
        REQUIRE(m7.get(0, 0) == 1);
        REQUIRE(m7.get(1, 1) == 1);
        REQUIRE(m7.get(2, 2) == 9);
    }

    SECTION("Matrix multiplication") {
        std::vector<Vector3D> data2 {
            Vector3D(2, 3, 4),
            Vector3D(5, 6, 7),
            Vector3D(8, 9, 10)
        };

        Matrix3D m2(data2);
        Matrix3D m3 = m1 * m2;

        std::vector<std::vector<float>> EXPECTED_MULTIPLICATION_VALUES {{36, 42, 48}, {69, 81, 93}, {76, 90, 104}};
        for (std::size_t row = 0; row < m1.rows(); ++row) {
            for (std::size_t col = 0; col < 3; ++col) {
                REQUIRE(m3.get(row, col) == Catch::Approx(EXPECTED_MULTIPLICATION_VALUES[row][col]));
            }
        }
    }

    SECTION("Matrix transpose") {
        Matrix3D m_transpose = m1.transpose();
        for (std::size_t row = 0; row < m1.rows(); ++row) {
            for (std::size_t col = 0; col < 3; ++col) {
                REQUIRE(m_transpose.get(row, col) == m1.get(col, row));
            }
        }
    }

    SECTION("Matrix determinant") {
        float det = m1.determinant();
        // You'll need to manually calculate the determinant for the given matrix data
        // and replace "EXPECTED_DETERMINANT_VALUE" with that value
        REQUIRE(det == Catch::Approx(4));
    }

    SECTION("Matrix trace") {
        float trace = m1.trace();
        // Trace is the sum of the elements on the main diagonal
        float expected_trace = m1.get(0, 0) + m1.get(1, 1) + m1.get(2, 2);
        REQUIRE(trace == expected_trace);
    }

}
