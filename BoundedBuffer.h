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


class BoundedBuffer
{
public:
  BoundedBuffer(int maxElements) : availableElements(0), freeElements(maxElements){}

  void put(tcp::socket *socket);
	tcp::socket* get(void);
private:
  std::deque<tcp::socket*> queue;
  boost::mutex queueMutext;
  boost::interprocess::interprocess_semaphore availableElements, freeElements;
};

