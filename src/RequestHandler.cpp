/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#include "RequestHandler.h"

RequestHandler::RequestHandler(BoundedBuffer<Download*> *downloadBuffer, BoundedBuffer<Upload*> *uploadBuffer)
{
  this->downloadBuffer = downloadBuffer;
  this->uploadBuffer = uploadBuffer;
  port = 80;  
}

RequestHandler::~RequestHandler(void)
{
}

void RequestHandler::run(){
  
  boost::asio::io_service ioService;
  tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), port));

  std::cout << "File server listening on port " << port << std::endl;
	for (;;) {
		tcp::socket *socket = new tcp::socket(ioService);
		acceptor.accept(*socket);

    int requestSize = socket->receive(boost::asio::buffer(requestBuffer, 1024));
		// print the entire http request:
		std::stringstream httpRequest(std::string(requestBuffer, requestSize));
		std::cout << httpRequest.str();
		std::string method, filename;

		// extract http-request method and filename
		httpRequest >> method >> filename;
    std::cout << "Method: " << method << std::endl;
		//erase the / in the path
		filename.erase(0,1);
    
    ReaderWriterMutex* readerWriterMutex = mutexMap[filename];
    if(readerWriterMutex == NULL)
      readerWriterMutex = new ReaderWriterMutex;

    if(method == "GET"){
      downloadBuffer->put(new Download(filename, socket, readerWriterMutex));
    }
    else if(method == "POST"){
      uploadBuffer->put(new Upload(filename, socket, httpRequest.str(),readerWriterMutex));
    }
    else
    {
      std::cout << "Method not supported" << std::endl;
    }
  }
}