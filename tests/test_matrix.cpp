#include "catch_amalgamated.hpp"
#include "matrix.hpp"


TEST_CASE( "MatrixND<float> operations", "[MatrixND]" ) {
    auto vdata1 = std::make_unique<VectorData<int>>(std::vector<int>{1, 2, 3});
    VectorND<int> vec1(std::move(vdata1));

    auto vdata2 = std::make_unique<VectorData<int>>(std::vector<int>{4, 5, 6});
    VectorND<int> vec2(std::move(vdata2));

    auto vdata3 = std::make_unique<VectorData<int>>(std::vector<int>{7, 8, 9});
    VectorND<int> vec3(std::move(vdata3));

    std::vector<VectorND<int>> rows = {vec1, vec2, vec3};
    MatrixND<int> m1(rows);

    MatrixND<int> m2 = m1 + 1;

    SECTION("Rows and Cols") {
        REQUIRE( m1.rows() == 3 );
        REQUIRE( m1.cols() == 3 );
    }

    SECTION("Get and Set") {
        REQUIRE( m1.get(1, 1) == 5 );
        m1.set(1, 1, 10);
        REQUIRE( m1.get(1, 1) == 10 );
    }

    SECTION("Matrix + Vector") {
        MatrixND<int> m3 = m1 + vec1;
        REQUIRE( m3.get(0, 0) == 2 );
        REQUIRE( m3.get(2, 2) == 12 );
    }

    SECTION("Matrix + Matrix") {
        MatrixND<int> m3 = m1 + m2;
        REQUIRE( m3.get(0, 0) == 3 );
        REQUIRE( m3.get(2, 2) == 19 );
    }

    SECTION("Matrix - Vector") {
        MatrixND<int> m3 = m1 - vec1;
        REQUIRE( m3.get(0, 0) == 0 );
        REQUIRE( m3.get(0, 1) == 0 );
        REQUIRE( m3.get(0, 2) == 0 );
        REQUIRE( m3.get(1, 0) == 3 );
        REQUIRE( m3.get(1, 1) == 3 );
        REQUIRE( m3.get(1, 2) == 3 );
        REQUIRE( m3.get(2, 0) == 6 );
        REQUIRE( m3.get(2, 1) == 6 );
        REQUIRE( m3.get(2, 2) == 6 );
    }

    SECTION("Matrix - Matrix") {
        MatrixND<int> m3 = m1 - m2;
        REQUIRE( m3.get(0, 0) == -1 );
        REQUIRE( m3.get(2, 2) == -1 );
    }

    SECTION("Matrix * Scalar") {
        MatrixND<int> m3 = m1 * 2;
        REQUIRE( m3.get(0, 0) == 2 );
        REQUIRE( m3.get(2, 2) == 18 );
    }

    SECTION("Matrix / Scalar") {
        MatrixND<int> m3 = m1 / 2;
        REQUIRE( m3.get(0, 0) == 0 );
        REQUIRE( m3.get(2, 2) == 4 );
    }

    SECTION("Matrix * Matrix") {
        MatrixND<int> m3 = m1 * m2;
        REQUIRE( m3.get(0, 0) == 36  );
        REQUIRE( m3.get(0, 1) == 42  );
        REQUIRE( m3.get(0, 2) == 48  );
        REQUIRE( m3.get(1, 0) == 81  );
        REQUIRE( m3.get(1, 1) == 96  );
        REQUIRE( m3.get(1, 2) == 111 );
        REQUIRE( m3.get(2, 0) == 126 );
        REQUIRE( m3.get(2, 1) == 150 );
        REQUIRE( m3.get(2, 2) == 174 );
    }

    SECTION("Transpose") {
        MatrixND<int> m3 = m1.transpose();
        for(size_t i = 0; i < m1.rows(); i++) {
            for(size_t j = 0; i < m1.rows(); i++) {
                REQUIRE( m3.get(i, j) == m1.get(j, i) );
            }
        }
    }

    SECTION("Determinant") {
        int det = m1.determinant();
        REQUIRE( det == 0 );
    }

    SECTION("Adjoint") {
        MatrixND<int> m3 = m1.adjoint();
        REQUIRE( m3.get(0, 0) == -3 );
        REQUIRE( m3.get(2, 2) == -3 );
    }

    SECTION("Trace") {
        int tr = m1.trace();
        REQUIRE( tr == 15 );
    }
}


TEST_CASE("MatrixND Operations") {
    SECTION("Creation and Basic Operations") {
        auto vdata1 = std::make_unique<VectorData<int>>(std::vector<int>{1, 2, 3});
        VectorND<int> vec1(std::move(vdata1));

        auto vdata2 = std::make_unique<VectorData<int>>(std::vector<int>{4, 5, 6});
        VectorND<int> vec2(std::move(vdata2));

        std::vector<VectorND<int>> rows = {vec1, vec2};
        MatrixND<int> mat(rows);

        REQUIRE(mat.rows() == 2);
        REQUIRE(mat.cols() == 3);
        REQUIRE(mat.get(0, 0) == 1);
        REQUIRE(mat.get(0, 1) == 2);
        REQUIRE(mat.get(0, 2) == 3);
        REQUIRE(mat.get(1, 0) == 4);
        REQUIRE(mat.get(1, 1) == 5);
        REQUIRE(mat.get(1, 2) == 6);
    }

    SECTION("Matrix Addition and Subtraction") {
        auto vdata1 = std::make_unique<VectorData<int>>(std::vector<int>{1, 2, 3});
        VectorND<int> vec1(std::move(vdata1));

        auto vdata2 = std::make_unique<VectorData<int>>(std::vector<int>{4, 5, 6});
        VectorND<int> vec2(std::move(vdata2));

        std::vector<VectorND<int>> rows = {vec1, vec2};
        MatrixND<int> mat1(rows);
        MatrixND<int> mat2(rows);

        auto res = mat1 + mat2;

        REQUIRE(res.rows() == 2);
        REQUIRE(res.cols() == 3);
        REQUIRE(res.get(0, 0) == 2);
        REQUIRE(res.get(0, 1) == 4);
        REQUIRE(res.get(0, 2) == 6);
        REQUIRE(res.get(1, 0) == 8);
        REQUIRE(res.get(1, 1) == 10);
        REQUIRE(res.get(1, 2) == 12);
    }
}

TEST_CASE("VectorND Operations") {
    SECTION("Vector Multiplication and Division") {
        auto vdata = std::make_unique<VectorData<float>>(new unsigned char[3*sizeof(float)], 3);
        vdata->set(0, 1);
        vdata->set(1, 2);
        vdata->set(2, 3);
        VectorND<float> vec(std::move(vdata));

        auto res_mul = vec * 3;
        REQUIRE(res_mul.get(0) == 3);
        REQUIRE(res_mul.get(1) == 6);
        REQUIRE(res_mul.get(2) == 9);

        auto res_div = vec / 2;
        REQUIRE(res_div.get(0) == 0.5);
        REQUIRE(res_div.get(1) == 1);
        REQUIRE(res_div.get(2) == 1.5);
    }

    SECTION("Vector Dot Product") {
        auto vdata1 = std::make_unique<VectorData<int>>(new unsigned char[3*sizeof(int)], 3);
        vdata1->set(0, 1);
        vdata1->set(1, 2);
        vdata1->set(2, 3);
        VectorND<int> vec1(std::move(vdata1));

        auto vdata2 = std::make_unique<VectorData<int>>(new unsigned char[3*sizeof(int)], 3);
        vdata2->set(0, 4);
        vdata2->set(1, 5);
        vdata2->set(2, 6);
        VectorND<int> vec2(std::move(vdata2));

        auto dot_prod = vec1.dot(vec2);
        REQUIRE(dot_prod == 32);
    }

    SECTION("Vector Cross Product") {
        Vector3D vec1(1, 2, 3);
        Vector3D vec2(4, 5, 6);

        auto cross_prod = vec1.cross(vec2);
        REQUIRE(cross_prod.x() == -3);
        REQUIRE(cross_prod.y() == 6);
        REQUIRE(cross_prod.z() == -3);
    }
}
