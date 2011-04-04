#include "ReaderWriterMutex.h"

ReaderWriterMutex::ReaderWriterMutex(void):allowedWriters(1), readers(0)
{
}

ReaderWriterMutex::~ReaderWriterMutex(void)
{
}

void ReaderWriterMutex::readerLock(){
  boost::mutex::scoped_lock lock(readersMutex);
	  readers++;
	  if (readers == 1) // first reader locks out writers
		  allowedWriters.wait();
   
}

void ReaderWriterMutex::writerLock(){
  allowedWriters.wait();
	  
}

void ReaderWriterMutex::readerUnlock(){
  boost::mutex::scoped_lock lock(readersMutex);
	readers--;
	if (readers == 0) // last reader unlocks writers
		allowedWriters.post();
}

void ReaderWriterMutex::writerUnlock(){
  allowedWriters.post();
}