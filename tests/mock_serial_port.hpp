#pragma once

#include <boost/asio.hpp>
#include <deque>
#include <functional>
#include <vector>

// Mock implementation of boost::asio::serial_port
class MockSerialPort {
public:
    MockSerialPort();
    ~MockSerialPort();

    // Simulate open/close operations
    void open(const std::string& device);
    void close();
    bool is_open() const;

    // Native handle access (returns a dummy value)
    int native_handle() const;

    // Set port options (these are no-ops in the mock)
    template<typename SettableSocketOption>
    void set_option(const SettableSocketOption& option) {
        // Store option type for verification if needed
    }

    // Mock behavior control
    void expect_write(const std::vector<uint8_t>& expected_data);
    void provide_read_data(const std::vector<uint8_t>& data_to_return);
    
    // Read/write operations
    size_t read_some(const boost::asio::mutable_buffer& buffer);
    size_t read_some(const boost::asio::mutable_buffer& buffer, 
                    boost::system::error_code& ec);
    
    size_t write_some(const boost::asio::const_buffer& buffer);
    size_t write_some(const boost::asio::const_buffer& buffer, 
                     boost::system::error_code& ec);

    // Verify expected interactions
    bool verify_expectations() const;
    void reset_expectations();

    // Simulated errors
    void set_read_error(const boost::system::error_code& ec);
    void set_write_error(const boost::system::error_code& ec);

private:
    bool _is_open;
    std::deque<std::vector<uint8_t>> _expected_writes;
    std::deque<std::vector<uint8_t>> _read_data_queue;
    boost::system::error_code _read_error;
    boost::system::error_code _write_error;
    int _dummy_handle;
};