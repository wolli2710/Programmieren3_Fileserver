#pragma once
#include <boost/thread.hpp>

class ReaderWriterMutex
{
public:
	ReaderWriterMutex(void);
	~ReaderWriterMutex(void);

	void readerLock();

	void writerLock();

	void readerUnlock();

	void writerUnlock();



private:

	int readers;
	boost::interprocess::interprocess_semaphore allowedWriters;
	boost::mutex readerMutex;

};