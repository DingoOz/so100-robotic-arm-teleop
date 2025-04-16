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

// Create a wrapper for MockSerialPort that exposes the boost::asio::serial_port interface
class MockSerialPortWrapper : public boost::asio::serial_port {
public:
    MockSerialPortWrapper() : boost::asio::serial_port(boost::asio::io_service()) {
        _mock = std::make_shared<MockSerialPort>();
    }
    
    // Forward key methods to the mock
    void open(const std::string& device) override {
        _mock->open(device);
    }
    
    bool is_open() const override {
        return _mock->is_open();
    }
    
    void close() override {
        _mock->close();
    }
    
    template<typename SettableSocketOption>
    void set_option(const SettableSocketOption& option) {
        _mock->set_option(option);
    }
    
    size_t read_some(const boost::asio::mutable_buffer& buffer) override {
        return _mock->read_some(buffer);
    }
    
    size_t read_some(const boost::asio::mutable_buffer& buffer, 
                     boost::system::error_code& ec) override {
        return _mock->read_some(buffer, ec);
    }
    
    size_t write_some(const boost::asio::const_buffer& buffer) override {
        return _mock->write_some(buffer);
    }
    
    size_t write_some(const boost::asio::const_buffer& buffer, 
                      boost::system::error_code& ec) override {
        return _mock->write_some(buffer, ec);
    }
    
    native_handle_type native_handle() const override {
        return static_cast<native_handle_type>(_mock->native_handle());
    }
    
    std::shared_ptr<MockSerialPort> getMock() {
        return _mock;
    }
    
private:
    std::shared_ptr<MockSerialPort> _mock;
};

std::shared_ptr<boost::asio::serial_port> createMockSerialPort() {
    return std::make_shared<MockSerialPortWrapper>();
}

MockSerialPort& getMockFromWrapper(std::shared_ptr<boost::asio::serial_port> wrapper) {
    MockSerialPortWrapper* typed_wrapper = dynamic_cast<MockSerialPortWrapper*>(wrapper.get());
    if (!typed_wrapper) {
        throw std::runtime_error("The provided wrapper is not a MockSerialPortWrapper");
    }
    return *typed_wrapper->getMock();
}

} // namespace test_utils