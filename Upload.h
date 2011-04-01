#pragma once

#include <boost\asio.hpp>
#include <boost\filesystem.hpp>
#include <fstream>


#include "BoundedBuffer.h"


class Upload
{
public:
	Upload(std::string filename, tcp::socket socket);
  ~Upload(void);
  void run();

private:
	char requestBuffer[1024];
	std::string filename;
	tcp::socket socket;
};

