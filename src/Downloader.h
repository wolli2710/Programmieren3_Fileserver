#pragma once

#include "BoundedBuffer.h"
#include "Download.h"

class Downloader
{
public:
  Downloader(BoundedBuffer<Download*> *buffer) : downloadBuffer(buffer){}
  ~Downloader(void);
  void run();
private:
  BoundedBuffer<Download*> *downloadBuffer;

};

