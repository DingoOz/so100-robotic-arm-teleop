#include <catch2/catch_all.hpp>
#include <cstdint>

// Function to test - similar to the one in your main.cpp
uint16_t scalePosition(uint16_t pos, uint16_t srcMin, uint16_t srcMax, uint16_t destMin, uint16_t destMax) {
    // Ensure we don't divide by zero
    if (srcMax == srcMin)
        return destMin;

    // Calculate the scaling factor and apply it
    double scale = static_cast<double>(destMax - destMin) / static_cast<double>(srcMax - srcMin);
    return static_cast<uint16_t>(destMin + (pos - srcMin) * scale);
}

TEST_CASE("Position scaling", "[position][scaling]") {
    SECTION("Standard scaling") {
        // Scale from 0-4095 to 1000-2000
        REQUIRE(scalePosition(0, 0, 4095, 1000, 2000) == 1000);
        REQUIRE(scalePosition(4095, 0, 4095, 1000, 2000) == 2000);
        REQUIRE(scalePosition(2048, 0, 4095, 1000, 2000) == 1500);
    }

    SECTION("Reversed scaling") {
        // Scale from 0-4095 to 2000-1000 (reversed)
        REQUIRE(scalePosition(0, 0, 4095, 2000, 1000) == 2000);
        REQUIRE(scalePosition(4095, 0, 4095, 2000, 1000) == 1000);
        REQUIRE(scalePosition(2048, 0, 4095, 2000, 1000) == 1500);
    }

    SECTION("Different ranges") {
        // Scale from 1000-2000 to 0-4095
        REQUIRE(scalePosition(1000, 1000, 2000, 0, 4095) == 0);
        REQUIRE(scalePosition(2000, 1000, 2000, 0, 4095) == 4095);
        REQUIRE(scalePosition(1500, 1000, 2000, 0, 4095) == 2048);
    }

    SECTION("Edge cases") {
        // Handle same source min/max (avoid division by zero)
        REQUIRE(scalePosition(2000, 2000, 2000, 0, 1000) == 0);
        
        // Handle values outside source range
        REQUIRE(scalePosition(3000, 1000, 2000, 0, 4095) == 8190); // Extrapolation
        REQUIRE(scalePosition(500, 1000, 2000, 0, 4095) == -2048); // Negative result will be wrapped as unsigned
    }
}