/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <map>

#include "BoundedBuffer.h"
#include "Download.h"
#include "Upload.h"
#include "ReaderWriterMutex.h"

using boost::asio::ip::tcp;

class RequestHandler
{
public:
  RequestHandler(BoundedBuffer<Download*> *downloadBuffer, BoundedBuffer<Upload*> *uploadBuffer);
  void run();
  ~RequestHandler(void);

private:
  std::map<std::string, ReaderWriterMutex*> mutexMap;
  char requestBuffer[1024];
  BoundedBuffer<Download*> *downloadBuffer;
  BoundedBuffer<Upload*> *uploadBuffer;
  int port;
};

