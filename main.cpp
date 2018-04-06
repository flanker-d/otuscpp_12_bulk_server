#include <bulk_server.h>

int main(int argc, char **argv)
{
  if(argc == 3)
  {
    boost::asio::io_service io_service;

    int port = std::stoi(argv[1]);
    int bulk_size = std::stoi(argv[2]);

    int file_loggers_count = 2;

    common::tcp_server_params_t params;
    params.do_read_type = common::read_func_type_e::async_read_some_eol;
    params.use_strand = false;

    async::bulk_server server(io_service, port, bulk_size, file_loggers_count, params);
    io_service.run();
  }
  else
    std::cout << "usage: bulk_server <port> <bulk_size>" << std::endl;

  return 0;
}