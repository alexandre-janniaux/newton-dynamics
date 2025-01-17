/* Copyright (c) <2003-2016> <Julio Jerez, Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __DG_MUTEX_THREAD_H__
#define __DG_MUTEX_THREAD_H__

#include "dgTypes.h"
#include "dgThread.h"

class dgMutexThread: public dgThread
{
	public:
	dgMutexThread(const char* const name, dgInt32 id);
	virtual ~dgMutexThread(void);

	void Tick(); 
	void Terminate(); 

	protected:
	virtual void Execute (dgInt32 threadID);
	virtual void TickCallback (dgInt32 threadID) = 0;

	private:
	dgSemaphore m_mutex;
	dgSemaphore m_parentMutex;
};


class dgAsyncThread: public dgThread
{
	public:
	dgAsyncThread(const char* const name, dgInt32 id);
	virtual ~dgAsyncThread(void);

	void Tick();
	void Sync();
	void Terminate();

	protected:
	virtual void Execute(dgInt32 threadID);
	virtual void TickCallback(dgInt32 threadID) = 0;

	private:
	dgSemaphore m_mutex;
	dgInt32 m_inUpdate;
	dgInt32 m_beginUpdate;
};
#endif