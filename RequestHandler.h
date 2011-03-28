/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#pragma once

#include <boost/asio.hpp>
#include <iostream>

#include "BoundedBuffer.h"

using boost::asio::ip::tcp;

class RequestHandler
{
public:
  RequestHandler(BoundedBuffer* buffer);
  void run();
  ~RequestHandler(void);

private:
  BoundedBuffer *socketBuffer;
  int port;
};

