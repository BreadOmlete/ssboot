#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <boost/asio.hpp>
#include <string>
#include "itransport.h"


class SerialPort : public ITransport
{
public:
    ~SerialPort();

    static void initialize(std::string device);
    static SerialPort *serialPort();

    void send(std::string &buf) throw(std::string);
    void receive(std::string &buf) throw(std::string);
    void setTimeout(int timeout_ms);

private:
    SerialPort();
    SerialPort(std::string device);

    int recv(std::string &buf, int timeout_ms);
    void read_callback(const boost::system::error_code &error, std::size_t bytes_transferred);
    void wait_callback(const boost::system::error_code &error);

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    boost::asio::deadline_timer timeout;
    bool data_available;
    int len;
    int comm_timeout;

    static SerialPort *singleton;
};

#endif // SERIALPORT_H
