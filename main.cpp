#include <fstream>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
	int port = 80;

	try {
		boost::asio::io_service ioService;
		tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), port));

		std::cout << "File server listening on port " << port << std::endl;
		for (;;) {
			tcp::socket socket(ioService);
			acceptor.accept(socket);

			std::cout << "Connection accepted from " << socket.remote_endpoint() << std::endl;

			char requestBuffer[1024];
			int requestSize = socket.receive(boost::asio::buffer(requestBuffer, 1024));
			// print the entire http request:
			std::stringstream httpRequest(std::string(requestBuffer, requestSize));
			std::cout << httpRequest.str();
			std::string method, filename;

			// extract http-request method and filename
			httpRequest >> method >> filename;
			//erase the / in the path
			filename.erase(0,1); 
			std::cout << "Requested file: " << filename << std::endl;
			boost::filesystem::path path(filename.c_str());

			if(boost::filesystem::is_regular_file(path)){

				std::ifstream file(filename.c_str(), std::ios::binary); //we open this file
				unsigned int buff_size = 1024;//boost::filesystem::file_size(path);
				char* buff = new char[buff_size]; //creating the buffer
				unsigned int count = 0; //counter
				std::cout << "Sending" << std::endl;
				std::cout << "length: " << boost::filesystem::file_size(path) << std::endl;

				std::stringstream httpResponse;

				httpResponse << "HTTP/1.0 200 OK\n";
				httpResponse << "Server: FileServer/0.0.1\n";
				httpResponse << "Content-Type: application/octet-stream\n";
				httpResponse << "Content-Length: " << boost::filesystem::file_size(path) << "\n\n";
				// send the http-response header
				socket.send(boost::asio::buffer(httpResponse.str().c_str(), httpResponse.str().length()));

				while( !file.eof() ) { //loop until there is no more data to send
					memset(buff,0,buff_size); //cleanup the buffer
					file.read(buff,buff_size); //read some data 
					//boost::system::error_code ignored_error;
					unsigned int len = file.gcount(); //get the effective number of bytes read
					count+=len; //increment counter
					socket.send(boost::asio::buffer(buff, buff_size));
				}
				socket.shutdown(tcp::socket::shutdown_both);
				socket.close();
				//
				file.close(); //close file
				delete(buff);  //delete buffer
				std::cout << "Finished" << std::endl;
				std::cout << "Sent "  << count << " bytes" << std::endl;
			}
			else{
				std::cout << "No such file: " << filename << std::endl;

				std::string payload("The file " + filename + " does not exist!");
				int payloadSize = payload.length();
				// create http-response
				std::stringstream httpResponse;
				httpResponse << "HTTP/1.0 200 OK\n";
				httpResponse << "Server: FileServer/0.0.1\n";
				httpResponse << "Content-Type: text/html\n";
				httpResponse << "Content-Length: " << payloadSize << "\n\n";
				// send the http-response header
				socket.send(boost::asio::buffer(httpResponse.str().c_str(), httpResponse.str().length()));
				// send the http-response payload
				socket.send(boost::asio::buffer(payload.c_str(), payloadSize));
				socket.shutdown(tcp::socket::shutdown_both);
				socket.close();
			}
		}
	} catch (std::exception &cause) {
		std::cout<<"Fail! check if port 80 is available..."<<std::endl;
		system("pause");
		std::cerr << cause.what() << std::endl;
	}

	return 0;
}
