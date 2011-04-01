#include "Upload.h"

#include <fstream>


using boost::asio::ip::tcp;

Upload::Upload(std::string filename, tcp::socket socket)
{
  this->socket = socket;
  this->filename = filename;
}

Upload::~Upload(void)
{
}

static enum ContentType{

  html,
  application

 };

/*
void save(std::string filename , char* buff ){

	std::ofstream file(filename.c_str);

	 while(1) { //loop until (see break after)
      boost::array<char, buff_size> buf; //create read buffer
      boost::system::error_code error; //in case of error
      size_t len = socket.read_some(boost::asio::buffer(buf), error); //read data
      std::cout << "Read " << len <<  std::endl;
      count += len;
      std::cout << "Read a total of " << count << " bytes " << std::endl;
      if (error == boost::asio::error::eof ) { //if end of file reached
	file.write(buf.data(),len); //finish write data
	file.close();   break; // Connection closed cleanly by peer.
      }
}
*/

void Upload::run(){
  for(;;){
		boost::filesystem::path path(("Files/"+ filename).c_str());
		std::cout << "testpath: " << path.directory_string() << std::endl;
		std::cout << method << std::endl;

		if(boost::filesystem::is_regular_file(path)){
			if(){
			}
			else{
			}
				std::ifstream file(("Files/"+ filename).c_str(), std::ios::binary); //we open this file
				unsigned int buff_size = 1024;
				char* buff = new char[buff_size]; //creating the buffer
				unsigned int count = 0; //counter
				std::cout << "Sending" << std::endl;
				std::cout << "length: " << boost::filesystem::file_size(path) << std::endl;        


		unsigned int buff_size = 441024;
		char* buff = new char[buff_size]; //creating the buffer
		unsigned int count = 0; //counter
       // std::string httpResponse = getHtmlHeader(ContentType::application, boost::filesystem::file_size(path));
				// send the http-response header        
		//socket->receive(boost::asio::buffer(httpResponse.c_str(), httpResponse.length()));
		//save(filename, buff);

		//
		//file.close(); //close file
		delete(buff);  //delete buffer
		std::cout << "Finished" << std::endl;
		std::cout << "Sent "  << count << " bytes" << std::endl;
			

  }
}