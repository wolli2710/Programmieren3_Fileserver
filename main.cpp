/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#include <fstream>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

#include "BoundedBuffer.h"
#include "RequestHandler.h"
#include "Download.h"

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {

	try {
    BoundedBuffer buffer(10);
    RequestHandler requestHandler(&buffer);

    for(int i = 0; i < 20; i++){
      Download download(&buffer);
      boost::thread downladThread(boost::bind(&Download::run, &download));
    }
    requestHandler.run();
		
	} catch (std::exception &cause) {
		std::cout<<"Fail! check if port 80 is available..."<<std::endl;
		system("pause");
		std::cerr << cause.what() << std::endl;
	}
  
	return 0;
}