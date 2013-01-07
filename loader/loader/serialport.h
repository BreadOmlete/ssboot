#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <boost/asio.hpp>
#include <string>


class SerialPort
{
public:
    SerialPort(std::string device);
    ~SerialPort();

    void send(std::string &buf);
    void receive(std::string &buf, int timeout_ms);

private:
    int recv(std::string &buf, int timeout_ms);
    void read_callback(const boost::system::error_code &error, std::size_t bytes_transferred);
    void wait_callback(const boost::system::error_code &error);

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    boost::asio::deadline_timer timeout;
    bool data_available;
    int len;

};

#endif // SERIALPORT_H
