/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#include "RequestHandler.h"


RequestHandler::RequestHandler(BoundedBuffer<tcp::socket>* buffer) : socketBuffer(buffer)
{
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
		socketBuffer->put(socket);

		tcp::socket* socket = buffer->get();

		int requestSize = socket->receive(boost::asio::buffer(requestBuffer, 1024));
		// print the entire http request:
		std::stringstream httpRequest(std::string(requestBuffer, requestSize));
		std::cout << httpRequest.str();
		std::string method, filename;

		// extract http-request method and filename
		httpRequest >> method >> filename;
		//erase the / in the path
		filename.erase(0,1); 
		std::cout << "Requested file: " << filename << std::endl;

		if(method == "POST"){
			Upload *upload = new Upload(filename, socket);
			uploadBuffer->put(upload);

			  Upload upload(&buffer);
			  boost::thread uploadThread(boost::bind(&Upload::run, &upload));
   

		}
		else if(method == "GET"){
			Download download = new Download(filename, socket);
			downloadBuffer->put(download);

			  Download download(&buffer);
			  boost::thread downladThread(boost::bind(&Download::run, &download));
			
			
		}
		else{
			std::cout<< method << " wird nicht unterstützt." << std::endl;
		}
  }
}