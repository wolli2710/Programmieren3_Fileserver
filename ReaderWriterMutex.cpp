#include "ReaderWriterMutex.h"

ReaderWriterMutex::ReaderWriterMutex(void):allowedWriters(1), readers(0)
{
}

ReaderWriterMutex::~ReaderWriterMutex(void)
{
}

void ReaderWriterMutex::readerLock(){
}

void ReaderWriterMutex::writerLock(){
}

void ReaderWriterMutex::readerUnlock(){
}

void ReaderWriterMutex::writerUnlock(){
}