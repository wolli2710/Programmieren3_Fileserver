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

typedef boost::interprocess::interprocess_semaphore semaphore;

using boost::asio::ip::tcp;

template <class T>
class BoundedBuffer
{
public:
  BoundedBuffer<T>(int maxElements) : availableElements(0), freeElements(maxElements){}

  void put(T element){
    freeElements.wait();
    {
      boost::mutex::scoped_lock lock(queueMutext);
      queue.push_back(element);
    }
    availableElements.post();
  }
  T get(void){
    T element;
    availableElements.wait();
    {
      boost::mutex::scoped_lock lock(queueMutext);
      element = queue.front();
      queue.pop_front();
    }
    freeElements.post();
    return element;
  }
private:
  std::deque<T> queue;
  boost::mutex queueMutext;
  semaphore availableElements, freeElements;
};


