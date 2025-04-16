#include "test_utils.hpp"
#include "servo-constants.hpp"
#include <memory>
#include <stdexcept>

namespace test_utils {

std::vector<uint8_t> createServoCommandHeader(uint8_t id, uint8_t length, uint8_t instruction) {
    using namespace perseus::servo;
    std::vector<uint8_t> header = {
        protocol::HEADER1,
        protocol::HEADER2,
        id,
        length,
        instruction
    };
    return header;
}

std::vector<uint8_t> createPositionResponse(uint8_t id, uint16_t position, uint8_t error_code) {
    using namespace perseus::servo;
    
    std::vector<uint8_t> response = {
        protocol::HEADER1,
        protocol::HEADER2,
        id,
        4, // Length (error + 2 data bytes + checksum)
        error_code,
        static_cast<uint8_t>(position & 0xFF),         // Low byte
        static_cast<uint8_t>((position >> 8) & 0xFF),  // High byte
        0  // Checksum placeholder
    };
    
    // Calculate and set checksum
    response[7] = calculateChecksum(response);
    
    return response;
}

std::vector<uint8_t> createLoadResponse(uint8_t id, int16_t load, uint8_t error_code) {
    using namespace perseus::servo;
    
    std::vector<uint8_t> response = {
        protocol::HEADER1,
        protocol::HEADER2,
        id,
        4, // Length (error + 2 data bytes + checksum)
        error_code,
        static_cast<uint8_t>(load & 0xFF),         // Low byte
        static_cast<uint8_t>((load >> 8) & 0xFF),  // High byte
        0  // Checksum placeholder
    };
    
    // Calculate and set checksum
    response[7] = calculateChecksum(response);
    
    return response;
}

uint8_t calculateChecksum(const std::vector<uint8_t>& packet, size_t start_idx) {
    uint8_t checksum = 0;
    for (size_t i = start_idx; i < packet.size() - 1; i++) {
        checksum += packet[i];
    }
    return ~checksum;
}

// Simplified implementation - just create a mock and return it directly
// instead of trying to wrap boost::asio::serial_port
std::shared_ptr<MockSerialPort> createMockSerialPort() {
    return std::make_shared<MockSerialPort>();
}

// Since we're returning MockSerialPort directly, this function is no longer needed
// We'll implement it with a simple passthrough for API compatibility
MockSerialPort& getMockFromWrapper(std::shared_ptr<boost::asio::serial_port> /*wrapper*/) {
    // This function shouldn't be called in the tests with our simplified implementation
    // But implement it to avoid compilation errors
    static MockSerialPort dummy_mock;
    return dummy_mock;
}

} // namespace test_utils