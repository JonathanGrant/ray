#include "catch_amalgamated.hpp"
#include "vector.hpp"


TEST_CASE( "Vector3D Tests", "[vector3d]" ) {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    
    SECTION( "Vector addition" ) {
        Vector3D v3 = v1 + v2;
        REQUIRE( v3.x == 5.0 );
        REQUIRE( v3.y == 7.0 );
        REQUIRE( v3.z == 9.0 );
    }

    SECTION( "Vector subtraction" ) {
        Vector3D v3 = v1 - v2;
        REQUIRE( v3.x == -3.0 );
        REQUIRE( v3.y == -3.0 );
        REQUIRE( v3.z == -3.0 );
    }

    SECTION( "Dot product" ) {
        float dot_product = v1.dot(v2);
        REQUIRE( dot_product == Catch::Approx(32.0) );
    }
    
    SECTION( "Magnitude of Vector" ) {
        float magnitude = v1.magnitude();
        REQUIRE( magnitude == Catch::Approx(sqrt(14.0)) );  // sqrt(1^2 + 2^2 + 3^2)
    }
}

TEST_CASE( "More Vector3D Tests", "[vector3d]" ) {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);

    SECTION( "Cross product" ) {
        Vector3D v_cross = v1.cross(v2);
        // The cross product of <1, 2, 3> and <4, 5, 6> is <-3, 6, -3>
        REQUIRE( v_cross.x == Catch::Approx(-3.0) );
        REQUIRE( v_cross.y == Catch::Approx(6.0) );
        REQUIRE( v_cross.z == Catch::Approx(-3.0) );
    }

    SECTION( "Angle between vectors" ) {
        float angle = v1.angle(v2);
        // The angle can be calculated using the dot product and magnitude of both vectors.
        float dot_product = v1.dot(v2);
        float magnitude_v1 = v1.magnitude();
        float magnitude_v2 = v2.magnitude();
        float expected_angle = acos(dot_product / (magnitude_v1 * magnitude_v2));
        REQUIRE( angle == Catch::Approx(expected_angle) );
    }
}

TEST_CASE("Vector3D class") {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);

    SECTION("Default constructor") {
        Vector3D v;
        REQUIRE(v.x == 0);
        REQUIRE(v.y == 0);
        REQUIRE(v.z == 0);
    }

    SECTION("Constructor with parameters") {
        REQUIRE(v1.x == 1.0);
        REQUIRE(v1.y == 2.0);
        REQUIRE(v1.z == 3.0);
    }

    SECTION("Get and Set operations") {
        REQUIRE(v1.get(0) == 1.0);
        v1.set(0, 7.0);
        REQUIRE(v1.get(0) == 7.0);
    }

    SECTION("Distance between vectors") {
        REQUIRE(v1.distance(v2) == Catch::Approx(5.19615));
    }

    SECTION("Magnitude of a vector") {
        REQUIRE(v1.magnitude() == Catch::Approx(3.74165));
    }

    SECTION("Addition of vectors") {
        Vector3D v3 = v1 + v2;
        REQUIRE(v3.x == 5.0);
        REQUIRE(v3.y == 7.0);
        REQUIRE(v3.z == 9.0);
    }

    SECTION("Subtraction of vectors") {
        Vector3D v4 = v2 - v1;
        REQUIRE(v4.x == 3.0);
        REQUIRE(v4.y == 3.0);
        REQUIRE(v4.z == 3.0);
    }

    SECTION("Multiplication and Division by scalar") {
        Vector3D v5 = v1 * 2.0;
        REQUIRE(v5.x == 2.0);
        REQUIRE(v5.y == 4.0);
        REQUIRE(v5.z == 6.0);

        Vector3D v6 = v5 / 2.0;
        REQUIRE(v6.x == 1.0);
        REQUIRE(v6.y == 2.0);
        REQUIRE(v6.z == 3.0);
    }

    SECTION("Dot product of vectors") {
        REQUIRE(v1.dot(v2) == 32.0);
    }

    SECTION("Angle between vectors") {
        REQUIRE(v1.angle(v2) == Catch::Approx(0.225726));
    }

    SECTION("Cross product of vectors") {
        Vector3D v7 = v1.cross(v2);
        REQUIRE(v7.x == -3.0);
        REQUIRE(v7.y == 6.0);
        REQUIRE(v7.z == -3.0);
    }

    SECTION("Norms of a vector") {
        REQUIRE(v1.l1Norm() == 6.0);
        REQUIRE(v1.l2Norm() == Catch::Approx(3.74165));
        REQUIRE(v1.linfNorm() == 3.0);
        REQUIRE(v1.norm() == Catch::Approx(6.0));
    }
}
