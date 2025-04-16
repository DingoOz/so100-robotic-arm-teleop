#include <catch2/catch_all.hpp>
#include "perseus-arm-teleop.hpp"
#include "servo-constants.hpp"
#include "test_utils.hpp"
#include "mock_serial_port.hpp"

using namespace perseus::servo;

// Make the private methods accessible for testing
class TestableServoReader : public ST3215ServoReader {
public:
    TestableServoReader(const std::string& port, unsigned int baud_rate, uint8_t acceleration = 30)
        : ST3215ServoReader(port, baud_rate, acceleration) {}

    // Expose private methods for testing
    std::vector<uint8_t> createReadCommand(uint8_t id, uint8_t address, uint8_t size) {
        return _createReadCommand(id, address, size);
    }

    std::vector<uint8_t> createWriteCommand(uint8_t id, uint8_t address, const std::vector<uint8_t>& data) {
        return _createWriteCommand(id, address, data);
    }
};

TEST_CASE("ST3215ServoReader Command Formation", "[st3215]") {
    // Create a reader for testing - use a mock device path
    TestableServoReader reader("/dev/null", 115200);
    
    SECTION("Read command formation") {
        uint8_t servo_id = 1;
        uint8_t address = register_addr::PRESENT_POSITION;
        uint8_t size = 2;
        
        auto command = reader.createReadCommand(servo_id, address, size);
        
        REQUIRE(command.size() == 8); // Header(2) + ID(1) + Length(1) + Instruction(1) + Address(1) + Size(1) + Checksum(1)
        REQUIRE(command[0] == protocol::HEADER1);
        REQUIRE(command[1] == protocol::HEADER2);
        REQUIRE(command[2] == servo_id);
        REQUIRE(command[3] == 4); // Length is always 4 for read command
        REQUIRE(command[4] == instruction::READ);
        REQUIRE(command[5] == address);
        REQUIRE(command[6] == size);
        
        // Verify checksum calculation
        uint8_t checksum = 0;
        for (size_t i = 2; i < command.size() - 1; i++) {
            checksum += command[i];
        }
        checksum = ~checksum;
        REQUIRE(command[7] == checksum);
    }
    
    SECTION("Write command formation") {
        uint8_t servo_id = 2;
        uint8_t address = register_addr::GOAL_POSITION;
        std::vector<uint8_t> data = {0x23, 0x01}; // Position 0x0123 (291)
        
        auto command = reader.createWriteCommand(servo_id, address, data);
        
        REQUIRE(command.size() == 9); // Header(2) + ID(1) + Length(1) + Instruction(1) + Address(1) + Data(2) + Checksum(1)
        REQUIRE(command[0] == protocol::HEADER1);
        REQUIRE(command[1] == protocol::HEADER2);
        REQUIRE(command[2] == servo_id);
        REQUIRE(command[3] == data.size() + 3); // Length = data + instruction + address + checksum
        REQUIRE(command[4] == instruction::WRITE);
        REQUIRE(command[5] == address);
        REQUIRE(command[6] == data[0]);
        REQUIRE(command[7] == data[1]);
        
        // Verify checksum calculation
        uint8_t checksum = 0;
        for (size_t i = 2; i < command.size() - 1; i++) {
            checksum += command[i];
        }
        checksum = ~checksum;
        REQUIRE(command[8] == checksum);
    }
}

// Additional basic test to ensure the test infrastructure works
TEST_CASE("ST3215ServoReader Basic Functionality", "[st3215][basic]") {
    SECTION("Test can compile and run") {
        // This is just a placeholder test to confirm the test infrastructure works
        REQUIRE(true);
    }
}