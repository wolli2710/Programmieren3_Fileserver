#pragma once

#include "BoundedBuffer.h"
#include "Upload.h"

class Uploader
{
public:
  Uploader(BoundedBuffer<Upload*> *buffer) : uploadBuffer(buffer){}
  ~Uploader(void);
  void run();
private:
  BoundedBuffer<Upload*> *uploadBuffer;
};

