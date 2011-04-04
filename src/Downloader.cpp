#include "Downloader.h"

Downloader::~Downloader(void)
{
}

void Downloader::run(){
  for(;;){
    Download* download = downloadBuffer->get();
    download->run();
    delete download;
  }
}