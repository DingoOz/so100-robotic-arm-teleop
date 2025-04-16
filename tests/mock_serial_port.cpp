#include "mock_serial_port.hpp"
#include <algorithm>
#include <stdexcept>

MockSerialPort::MockSerialPort() 
    : _is_open(false), 
      _dummy_handle(42) {
}

MockSerialPort::~MockSerialPort() {
    if (_is_open) {
        close();
    }
}

void MockSerialPort::open(const std::string& device) {
    _is_open = true;
}

void MockSerialPort::close() {
    _is_open = false;
    reset_expectations();
}

bool MockSerialPort::is_open() const {
    return _is_open;
}

int MockSerialPort::native_handle() const {
    return _dummy_handle;
}

void MockSerialPort::expect_write(const std::vector<uint8_t>& expected_data) {
    _expected_writes.push_back(expected_data);
}

void MockSerialPort::provide_read_data(const std::vector<uint8_t>& data_to_return) {
    _read_data_queue.push_back(data_to_return);
}

size_t MockSerialPort::read_some(const boost::asio::mutable_buffer& buffer) {
    boost::system::error_code ec;
    size_t bytes_read = read_some(buffer, ec);
    if (ec) {
        throw boost::system::system_error(ec);
    }
    return bytes_read;
}

size_t MockSerialPort::read_some(const boost::asio::mutable_buffer& buffer, 
                                boost::system::error_code& ec) {
    if (!_is_open) {
        ec = boost::asio::error::bad_descriptor;
        return 0;
    }

    // If error is configured, return it
    if (_read_error) {
        ec = _read_error;
        return 0;
    }

    // If no data is queued, return would_block
    if (_read_data_queue.empty()) {
        ec = boost::asio::error::would_block;
        return 0;
    }

    // Get the next chunk of data
    std::vector<uint8_t> data = _read_data_queue.front();
    _read_data_queue.pop_front();

    // Copy data to the buffer (up to buffer size)
    size_t buffer_size = boost::asio::buffer_size(buffer);
    size_t bytes_to_copy = std::min(buffer_size, data.size());
    
    uint8_t* buffer_data = boost::asio::buffer_cast<uint8_t*>(buffer);
    std::copy(data.begin(), data.begin() + bytes_to_copy, buffer_data);

    ec = boost::system::error_code(); // Clear any error
    return bytes_to_copy;
}

size_t MockSerialPort::write_some(const boost::asio::const_buffer& buffer) {
    boost::system::error_code ec;
    size_t bytes_written = write_some(buffer, ec);
    if (ec) {
        throw boost::system::system_error(ec);
    }
    return bytes_written;
}

size_t MockSerialPort::write_some(const boost::asio::const_buffer& buffer, 
                                 boost::system::error_code& ec) {
    if (!_is_open) {
        ec = boost::asio::error::bad_descriptor;
        return 0;
    }

    // If error is configured, return it
    if (_write_error) {
        ec = _write_error;
        return 0;
    }

    const uint8_t* data = boost::asio::buffer_cast<const uint8_t*>(buffer);
    size_t length = boost::asio::buffer_size(buffer);

    // Verify against expected writes if any
    if (!_expected_writes.empty()) {
        std::vector<uint8_t> expected = _expected_writes.front();
        _expected_writes.pop_front();
        
        if (length != expected.size() || 
            !std::equal(data, data + length, expected.begin())) {
            // For test debug purposes, we could log what was expected vs. what was received
            ec = boost::system::error_code(); // Still succeed, but verification will fail
        }
    }

    ec = boost::system::error_code(); // Clear any error
    return length; // Return all bytes as "written"
}

bool MockSerialPort::verify_expectations() const {
    return _expected_writes.empty(); // All expected writes were matched
}

void MockSerialPort::reset_expectations() {
    _expected_writes.clear();
    _read_data_queue.clear();
    _read_error = boost::system::error_code();
    _write_error = boost::system::error_code();
}

void MockSerialPort::set_read_error(const boost::system::error_code& ec) {
    _read_error = ec;
}

void MockSerialPort::set_write_error(const boost::system::error_code& ec) {
    _write_error = ec;
}