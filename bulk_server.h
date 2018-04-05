#pragma once

#include <common/communications/communications.h>
#include <mt/command_processor.h>
#include <interpreter.h>
#include <iostream>
#include <map>

namespace async
{
  class bulk_server
  {
    public:
      bulk_server(boost::asio::io_service &a_io_service, const int a_port, const int a_bulk_size, const int a_file_loggers_count, common::tcp_server_params_t& a_params);
      ~bulk_server();

    private:
      common::tcp::iserver::ref m_server;
      std::map<int, interpreter::ref> m_contexts;
      mt::command_processor::ref m_command_processor;
  };
} //namespace async
