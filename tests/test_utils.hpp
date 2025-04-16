#pragma once

#include <boost/asio.hpp>
#include <memory>
#include "mock_serial_port.hpp"

// Utility functions for tests
namespace test_utils {

// Creates a header for servo commands
std::vector<uint8_t> createServoCommandHeader(uint8_t id, uint8_t length, uint8_t instruction);

// Creates a valid position response for testing
std::vector<uint8_t> createPositionResponse(uint8_t id, uint16_t position, uint8_t error_code = 0);

// Creates a valid load response for testing
std::vector<uint8_t> createLoadResponse(uint8_t id, int16_t load, uint8_t error_code = 0);

// Calculates checksum for validating packets
uint8_t calculateChecksum(const std::vector<uint8_t>& packet, size_t start_idx = 2);

// Creates a mock serial port for testing
std::shared_ptr<MockSerialPort> createMockSerialPort();

// Retained for API compatibility - should not be used in tests
MockSerialPort& getMockFromWrapper(std::shared_ptr<boost::asio::serial_port> wrapper);

}