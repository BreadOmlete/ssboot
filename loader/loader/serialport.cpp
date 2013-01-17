#include <boost/bind.hpp>
#include "serialport.h"

SerialPort *SerialPort::singleton = 0;

SerialPort::~SerialPort()
{
    serial.close();
}

void SerialPort::initialize(std::string device)
{
    if (singleton)
        delete singleton;

    singleton = new SerialPort(device);
    singleton->comm_timeout = 1000;

    singleton->mTransport = singleton;
}

SerialPort *SerialPort::serialPort()
{
    return singleton;
}

void SerialPort::send(std::string &buf) throw(std::string)
{
    try {
        boost::asio::write(serial, boost::asio::buffer(buf));
    }

    catch(boost::system::system_error err) {
        throw err.what();
    }
}

void SerialPort::receive(std::string &buf) throw(std::string)
{
    int tout = comm_timeout;

    try {
        while(1) {
            if(!recv(buf, tout))
                break;
            tout = 100;
        }
    }

    catch(boost::system::system_error err) {
        throw err.what();
    }

}

void SerialPort::setTimeout(int timeout_ms)
{
    comm_timeout = timeout_ms;
}

SerialPort::SerialPort() : ITransport(), io(), serial(io), timeout(io)
{
}

SerialPort::SerialPort(std::string device) : io(), serial(io, device), timeout(io)
{
    serial.set_option(boost::asio::serial_port::baud_rate(115200));
    serial.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
    serial.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
    serial.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
    serial.set_option(boost::asio::serial_port::character_size(8));
}

int SerialPort::recv(std::string &buf, int timeout_ms)
{
    char buffer[1];
    data_available = false;
    len = 0;

    io.reset();

    boost::asio::async_read(serial,
                            boost::asio::buffer(buffer, 1),
                            boost::bind(&SerialPort::read_callback, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));

    timeout.expires_from_now(boost::posix_time::milliseconds(timeout_ms));
    timeout.async_wait(boost::bind(&SerialPort::wait_callback, this,
                                   boost::asio::placeholders::error));

    io.run();

    if (data_available)
        buf.append(buffer, len);

    return len;
}

void SerialPort::read_callback(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (error || !bytes_transferred) {
        data_available = false;
        timeout.cancel();
        return;
    }

    timeout.cancel();
    data_available = true;
    len = bytes_transferred;
}

void SerialPort::wait_callback(const boost::system::error_code &error)
{
    if (error)
        return;

    serial.cancel();
}
