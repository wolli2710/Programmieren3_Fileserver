/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#include <fstream>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

#include "Upload.h"
#include "BoundedBuffer.h"
#include "RequestHandler.h"
#include "Download.h"

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {

	try {
    BoundedBuffer<tcp::socket> buffer(10);
    RequestHandler requestHandler(&buffer);

    requestHandler.run();
		
	} catch (std::exception &cause) {
		std::cout<<"Fail! check if port 80 is available..."<<std::endl;
		system("pause");
		std::cerr << cause.what() << std::endl;
	}
  
	return 0;
}