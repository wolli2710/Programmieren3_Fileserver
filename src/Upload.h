#pragma once

#include <boost\asio.hpp>
#include <boost\filesystem.hpp>
#include <fstream>

#define BUFFERSIZE 1024


#include "BoundedBuffer.h"
#include "ReaderWriterMutex.h"

using boost::asio::ip::tcp;

class Upload
{
public:
  Upload(std::string filename, tcp::socket *socket, std::string request, ReaderWriterMutex* readerWriterMutex)
    : filename(filename), 
      socket(socket), 
      request(request),
      readerWriterMutex(readerWriterMutex){}
  ~Upload(void);
  void run();

private:
	char requestBuffer[1024];
  ReaderWriterMutex* readerWriterMutex;
	std::string filename;
	tcp::socket *socket;
  std::string request;
};

