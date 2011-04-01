/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#pragma once

#include <boost\asio.hpp>
#include <boost\filesystem.hpp>
#include <iostream>
#include <fstream>

#include "BoundedBuffer.h"

using boost::asio::ip::tcp;

class Download
{

public:
	Download(std::string filename ,tcp::socket socket);
  ~Download(void);
  void run();


private:
  char requestBuffer[1024];
  std::string filename;
  tcp::socket socket;
};