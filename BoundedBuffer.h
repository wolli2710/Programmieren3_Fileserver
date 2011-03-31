/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <deque>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using boost::asio::ip::tcp;

template <class T>
class BoundedBuffer
{
public:
  BoundedBuffer<T>(int maxElements) : availableElements(0), freeElements(maxElements){}

  void put(T *socket);
	T* get(void);
private:
  std::deque<T*> queue;
  boost::mutex queueMutext;
  boost::interprocess::interprocess_semaphore availableElements, freeElements;
};

template <class T>
void BoundedBuffer<T>::put(T *socket) {
    freeElements.wait();
    {
      boost::mutex::scoped_lock lock(queueMutext);
		  queue.push_back(socket);
    }
    availableElements.post();
}

template <class T>
T* BoundedBuffer<T>::get() {
  T *element;
	availableElements.wait();
	{
		boost::mutex::scoped_lock lock(queueMutext);
		element = queue.front();
		queue.pop_front();
	}
	freeElements.post();
	return element;
}