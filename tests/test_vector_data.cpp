#include "vector_data.hpp"
#include "catch_amalgamated.hpp"


TEST_CASE("VectorData construction and basic functionality") {
    SECTION("Empty construction") {
        auto data = std::make_unique<unsigned char[]>(5 * sizeof(int));
        VectorData<int> vd(std::move(data), 5);
        REQUIRE(vd.length() == 5);
        REQUIRE(vd.stride() == 1);
    }

    SECTION("Copy construction") {
        auto data = std::make_unique<unsigned char[]>(5 * sizeof(int));
        VectorData<int> vd1(std::move(data), 5);
        VectorData<int> vd2(vd1);
        REQUIRE(vd2.length() == 5);
        REQUIRE(vd2.stride() == 1);
    }

    SECTION("Assignment operator") {
        auto data = std::make_unique<unsigned char[]>(5 * sizeof(int));
        VectorData<int> vd1(std::move(data), 5);
        VectorData<int> vd2 = vd1;
        REQUIRE(vd2.length() == 5);
        REQUIRE(vd2.stride() == 1);
    }
}

TEST_CASE("VectorData methods") {
    auto data = std::make_unique<unsigned char[]>(5 * sizeof(int));
    VectorData<int> vd(std::move(data), 5);

    SECTION("resize") {
        vd.resize(7);
        REQUIRE(vd.length() == 7);
    }

    SECTION("get and set") {
        vd.set(0, 10);
        REQUIRE(vd.get(0) == 10);
    }

    SECTION("Iterator functionality") {
        for (int i = 0; i < 5; ++i) {
            vd.set(i, i);
        }

        auto it = vd.begin();
        for (int i = 0; i < 5; ++i, ++it) {
            REQUIRE(*it == i);
        }
    }
}

TEST_CASE("VectorData arithmetic") {
    auto data = std::make_unique<unsigned char[]>(5 * sizeof(int));
    VectorData<int> vd(std::move(data), 5);

    for (int i = 0; i < 5; ++i) {
        vd.set(i, i);
    }

    SECTION("sum") {
        REQUIRE(vd.sum() == 10); // 0 + 1 + 2 + 3 + 4 = 10
    }

    SECTION("binary operations") {
        auto res = vd + 1;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(res.get(i) == i + 1);
        }

        res = vd - 1;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(res.get(i) == i - 1);
        }

        res = vd * 2;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(res.get(i) == i * 2);
        }

        res = vd / 2;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(res.get(i) == i / 2);
        }
    }

    SECTION("binary operations inplace") {
        vd += 1;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(vd.get(i) == i + 1);
        }

        vd -= 1;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(vd.get(i) == i);
        }

        vd *= 2;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(vd.get(i) == i * 2);
        }

        vd /= 2;
        for (int i = 0; i < 5; ++i) {
            REQUIRE(vd.get(i) == i);
        }
    }
}

TEST_CASE("VectorData out of range") {
    auto data = std::make_unique<unsigned char[]>(5 * sizeof(int));
    VectorData<int> vd(std::move(data), 5);

    SECTION("get") {
        REQUIRE_THROWS_AS(vd.get(5), std::out_of_range);
    }

    SECTION("set") {
        REQUIRE_THROWS_AS(vd.set(5, 1), std::out_of_range);
    }
}

TEST_CASE("VectorData Copy Constructor", "[vector_data]") {
    auto data = std::make_unique<unsigned char[]>(5 * sizeof(int));
    for(int i = 0; i < 5; ++i) {
        reinterpret_cast<int*>(data.get())[i] = i;  // Initialize the data
    }

    VectorData<int> original(std::move(data), 5); // Create an instance with known data

    SECTION("Copy constructor") {
        VectorData<int> copy(original);
        // Now, validate that 'copy' is indeed a copy of 'original'
        REQUIRE(copy.length() == original.length());
        for(size_t i = 0; i < original.length(); i++) {
            REQUIRE(copy.get(i) == original.get(i));
        }

        // Modify copy and check that original is not affected
        if(copy.length() > 0) {
            copy.set(0, 100);  // Or whatever modification you'd like
            REQUIRE(copy.get(0) != original.get(0));
        }
    }
}
