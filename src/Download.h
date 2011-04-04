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

#include "tools.h"
#include "BoundedBuffer.h"
#include "ReaderWriterMutex.h"

using boost::asio::ip::tcp;

class Download
{
public:
  Download( std::string filename, tcp::socket *socket, ReaderWriterMutex* readerWriterMutex)
    : socket(socket), 
      filename(filename), 
      readerWriterMutex(readerWriterMutex){}
  ~Download(void);
  void run();

private:
  tcp::socket *socket;
  std::string filename;
  ReaderWriterMutex* readerWriterMutex;
};