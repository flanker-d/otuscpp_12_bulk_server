#pragma once

#include <common/communications.h>
#include <mt/command_processor.h>
#include <interpreter.h>
#include <iostream>
#include <map>

namespace async
{
  class bulk_server
  {
    public:
      bulk_server(boost::asio::io_service::strand &a_strand, const int a_port, const int a_bulk_size, const int a_file_loggers_count);
      ~bulk_server();

    private:
      boost::asio::io_service::strand &m_strand;
      common::tcp::iserver::ref m_server;
      std::map<int, interpreter::ref> m_contexts;
      mt::command_processor::ref m_command_processor;
  };
} //namespace async
