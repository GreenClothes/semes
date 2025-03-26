#include "UDP.h"

UDP::UDP()
: sock(io_context, udp::endpoint(udp::v4(), port))
{}

void UDP::Send(std::string sendMsg, udp::endpoint client) {
    sock.send_to(boost::asio::buffer(sendMsg), client);
}

udp::endpoint UDP::Receive(std::string* msg) {
    char data[max_length];
    udp::endpoint sender_endpoint;

    size_t length = sock.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
    *msg = std::string{ data, length };
    return sender_endpoint;
}