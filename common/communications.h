#pragma once

#include <common/interface.h>
#include <boost/asio.hpp>
#include <boost/asio/socket_base.hpp>
#include <array>
#include <functional>

namespace common
{
  namespace tcp
  {
    const int BUF_LENGTH = 32768;
    using buf_t = std::array<char, BUF_LENGTH>;
    using pbuf_t = std::unique_ptr<buf_t>;

    class iserver
      : public interface<iserver>
    {
      public:
        virtual void run() = 0;
        virtual void remove_client(const int a_client_id) = 0;
        virtual void set_on_connected(std::function<void(const int)> a_on_connected) = 0;
        virtual void set_on_disconnected(std::function<void(const int)> a_on_disconnected) = 0;
        virtual void set_on_message(std::function<void(const int, const char *, std::size_t)> a_on_message) = 0;
        virtual void on_connected(const int a_client_id) = 0;
        virtual void on_disconnected(const int a_client_id) = 0;
        virtual void on_message(const int a_client_id, const char *a_data, std::size_t a_len) = 0;
        virtual std::size_t clients_count() = 0;

      protected:
        virtual void do_accept() = 0;
    };

    iserver::ref create_server(const int a_port, boost::asio::io_service::strand& a_strand);

    class iclient_session
      : public interface<iclient_session>
    {
      public:
        virtual void start() = 0;
        virtual void shutdown() = 0;

      protected:
        virtual void do_receive() = 0;
    };

    iclient_session::ref create_client_session(boost::asio::ip::tcp::socket& a_sock, boost::asio::io_service::strand& a_strand, iserver::ref a_server);
  } //namespace tcp
} //namespace common