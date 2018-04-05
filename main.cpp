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
    params.do_read_type = common::read_func_type_e::read_until_eol;
    params.use_strand = true;

    async::bulk_server server(io_service, port, bulk_size, file_loggers_count, params);

    std::vector<std::thread> thread_group;
    //int threads_count = std::thread::hardware_concurrency();
    int threads_count = 8;
    for(int i = 0; i < threads_count; i++)
    {
      thread_group.emplace_back(std::thread([&io_service](){
        io_service.run();
      }));
    }

    for(auto& thr : thread_group)
      thr.join();
  }
  else
    std::cout << "usage: bulk_server <port> <bulk_size>" << std::endl;

  return 0;
}