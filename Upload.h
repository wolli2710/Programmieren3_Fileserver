#pragma once

#include <boost\asio.hpp>
#include <boost\filesystem.hpp>
#include <iostream>
#include <fstream>

#include "BoundedBuffer.h"


class Upload
{
public:
  Upload(BoundedBuffer<tcp::socket> *buffer);
  ~Upload(void);
  void run();

private:

};

