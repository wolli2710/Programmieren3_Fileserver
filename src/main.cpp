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
#include "ReaderWriterMutex.h"
#include "Downloader.h"
#include "Uploader.h"


using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {

	try {
    BoundedBuffer<Download*> downloadBuffer(10);
    BoundedBuffer<Upload*> uploadBuffer(10);
    
     
    for(int i = 0; i < 10; i++){
      Downloader downloader(&downloadBuffer);
      boost::thread downladerThread(boost::bind(&Downloader::run, &downloader));
    }
    
    for(int i = 0; i < 10; i++){
      Uploader uploader(&uploadBuffer);
      boost::thread uploaderThread(boost::bind(&Uploader::run, &uploader));
    }

    RequestHandler requestHandler(&downloadBuffer, &uploadBuffer);
    requestHandler.run();
		
	} catch (std::exception &cause) {
		std::cout<<"Fail! check if port 80 is available..."<<std::endl;
		system("pause");
		std::cerr << cause.what() << std::endl;
	}
  
	return 0;
}