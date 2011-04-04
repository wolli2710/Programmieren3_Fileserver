#include "Uploader.h"

Uploader::~Uploader(void)
{
}

void Uploader::run(){
  for(;;){
    Upload* upload = uploadBuffer->get();
    upload->run();
    delete upload;
  }
}
