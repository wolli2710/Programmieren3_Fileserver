/*
Prog3 - Fileserver
Wolfgang Vogl & Andreas Stallinger
Multimediatechnology SS2010
*/

#include "BoundedBuffer.h"

void BoundedBuffer::put(tcp::socket *socket) {

    freeElements.wait();

    {
        boost::mutex::scoped_lock lock(queueMutext);
		queue.push_back(socket);
    }

    availableElements.post();
}

tcp::socket* BoundedBuffer::get() {
  tcp::socket *element;
	availableElements.wait();

	{
		boost::mutex::scoped_lock lock(queueMutext);
		element = queue.front();
		queue.pop_front();
	}
	freeElements.post();
	return element;
}
