#include <bulk_server.h>
#include <boost/thread.hpp>

int main(int argc, char **argv)
{
  if(argc == 3)
  {
    boost::asio::io_service io_service;
    boost::asio::io_service::strand strand(io_service);

    int port = std::stoi(argv[1]);
    int bulk_size = std::stoi(argv[2]);

    int file_loggers_count = 2;

    async::bulk_server server(strand, port, bulk_size, file_loggers_count);

    boost::thread_group thread_group;
    //int threads_count = boost::thread::hardware_concurrency();
    int threads_count = 2;
    for(int i = 0; i < threads_count; i++)
    {
      thread_group.create_thread([&io_service](){
        io_service.run();
      });
    }

    thread_group.join_all();
  }
  else
    std::cout << "usage: bulk_server <port> <bulk_size>" << std::endl;

  return 0;
}