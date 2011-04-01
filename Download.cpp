/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#include "Download.h"

using boost::asio::ip::tcp;

Download::Download(std::string filename, tcp::socket socket)
{
  this->socket = socket;
  this->filename = filename;
}

Download::~Download(void)
{
}

static enum ContentType{
  html,
  application
 };

std::string getHtmlHeader(int contentType, unsigned int contentSize){
  std::stringstream header;
  header << "HTTP/1.0 200 OK\n";
	header << "Server: FileServer/0.0.1\n";
	header << "Content-Type: ";
  switch(contentType){
    case ContentType::html:
      header << "text/html";
      break;
    case ContentType::application: 
      header << "application/octet-stream";
      break;
  }  
  header << "\n";
	header << "Content-Length: " << contentSize << "\n\n";
  return header.str();
}

void Download::run(){
  for(;;){					
			std::cout << "Requested file: " << filename << std::endl;      
			  boost::filesystem::path path(("Files/"+ filename).c_str());
			  std::cout << "testpath: " << path.directory_string() << std::endl;

			if(boost::filesystem::is_regular_file(path)){
				std::ifstream file(("Files/"+ filename).c_str(), std::ios::binary); //we open this file
				unsigned int buff_size = 1024;
				char* buff = new char[buff_size]; //creating the buffer
				unsigned int count = 0; //counter
				std::cout << "Sending" << std::endl;
				std::cout << "length: " << boost::filesystem::file_size(path) << std::endl;        

        std::string httpResponse = getHtmlHeader(ContentType::application, boost::filesystem::file_size(path));
				// send the http-response header        
				socket->send(boost::asio::buffer(httpResponse.c_str(), httpResponse.length()));

				while( !file.eof() ) { //loop until there is no more data to send
					memset(buff,0,buff_size); //cleanup the buffer
					file.read(buff,buff_size); //read some data 					
					unsigned int len = file.gcount(); //get the effective number of bytes read
					count+=len; //increment counter
					socket->send(boost::asio::buffer(buff, buff_size));
				}
				//
				file.close(); //close file
				delete(buff);  //delete buffer
				std::cout << "Finished" << std::endl;
				std::cout << "Sent "  << count << " bytes" << std::endl;
			}
			else{
				std::cout << "No such file: " << filename << std::endl;
        std::string payload = "<html><head><title></title></head><body><h1>The file " + filename + " does not exist!</h1></body></html>";
				int payloadSize = payload.length();
				// create http-response
        std::string httpResponse = getHtmlHeader(ContentType::html, payloadSize);				
        socket->send(boost::asio::buffer(httpResponse.c_str(), httpResponse.length()));
				// send the http-response payload
				socket->send(boost::asio::buffer(payload.c_str(), payloadSize));				
			}
      socket->shutdown(tcp::socket::shutdown_both);
			socket->close();

      delete socket;
  }
}