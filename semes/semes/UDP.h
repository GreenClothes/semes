#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <set>

using boost::asio::ip::udp;

enum { max_length = 1024 };

class UDP {
private:
    boost::asio::io_context io_context;
    unsigned short port = 9999;
    udp::socket sock;

public:
    UDP();
    void Send(std::string sendMsg, udp::endpoint client);
    udp::endpoint Receive(std::string* msg);

};