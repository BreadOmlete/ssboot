#include <fstream>
#include <iostream>
#include <ios>
#include <string>
#include "serialport.h"

std::string SSBOOT_WELCOME_MSG = ":SSBOOT";
std::string SSBOOT_ENTER_MSG = "i";

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Missing parameters!" << std::endl;
        std::cout << argv[0] << " tty binary_file" << std::endl;
        return 1;
    }

    std::cout << "Waiting for device (you may need to reset target)..." << std::endl;

    //    ifstream program(argv[2], ios::binary);

    SerialPort *serial;

    try {
        serial = new SerialPort(argv[1]);
    }

    catch(boost::system::system_error err) {
        std::cout << "Can't open serial port! Error: " << err.what() << std::endl;
        return 1;
    }

    std::string buf;

    serial->receive(buf, 10000);
    if (buf.find(SSBOOT_WELCOME_MSG, 0) == std::string::npos) {
        std::cout << "Please enable SSBOOT mode!" << std::endl;
        delete serial;
        return 1;
    }

    // send bootloader enter string
    serial->send(SSBOOT_ENTER_MSG);
    buf.clear();
    serial->receive(buf, 500);
    if (buf.find("NOK", 0) != std::string::npos)
    {
        std::cout << "Please enable SSBOOT mode!" << std::endl;
        delete serial;
        return 1;
    } else if (buf.find("OK", 0) != std::string::npos) {
        std::cout << "SSBOOT mode on" << std::endl;
    } else {
        std::cout << "Please enable SSBOOT mode!" << std::endl;
        delete serial;
        return 1;
   }

    delete serial;

    return 0;
}

