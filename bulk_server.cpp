#include <bulk_server.h>

namespace async
{
  bulk_server::bulk_server(boost::asio::io_service &a_io_service, const int a_port, const int a_bulk_size, const int a_file_loggers_count, common::tcp_server_params_t& a_params)
    : m_server(common::tcp::create_server(a_port, a_io_service, a_params))
    , m_command_processor(std::make_shared<mt::command_processor>(a_bulk_size, a_file_loggers_count))
  {
    m_server->set_on_connected([this, &a_bulk_size](auto client_id){
      m_contexts.insert(std::make_pair(client_id, std::make_shared<interpreter>(m_command_processor)));
      //std::cout << "client connected" << std::endl;
    });

    m_server->set_on_disconnected([this](auto client_id){
      auto found = m_contexts.find(client_id);
      if(found != m_contexts.end())
      {
        m_contexts.erase(found);
      }

      if(m_server->clients_count() == 0)
        m_command_processor->forced_dump();
      //std::cout << "client disconnected" << std::endl;
    });

    m_server->set_on_message([this](auto a_client_id, const char *a_data, std::size_t a_len) {
      auto found = m_contexts.find(a_client_id);
      if(found != m_contexts.end())
      {
        found->second->process_cmd({a_data, a_len});
      }
    });

    m_server->run();
  }

  bulk_server::~bulk_server()
  {
  }

} //namespace async