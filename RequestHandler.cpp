/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#include "RequestHandler.h"


RequestHandler::RequestHandler(BoundedBuffer* buffer) : socketBuffer(buffer)
{
  port = 80;
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::run(){
  
  for(;;){
    boost::asio::io_service ioService;
    tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), port));

    std::cout << "File server listening on port " << port << std::endl;
	  for (;;) {
		  tcp::socket *socket = new tcp::socket(ioService);
		  acceptor.accept(*socket);

      socketBuffer->put(socket);
    }
  }
}