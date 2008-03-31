/* ES40 emulator.
 * Copyright (C) 2007-2008 by the ES40 Emulator Project
 *
 * WWW    : http://sourceforge.net/projects/es40
 * E-mail : camiel@camicom.com
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
 * Although this is not required, the author would appreciate being notified of, 
 * and receiving any modifications you may make to the source code that might serve
 * the general public.
 */

/**
 * \file 
 * From the Poco C++ Libraries; used for ES40 for OpenVMS only, as Poco
 * has dropped OpenVMS support.
 *
 * $Id: Semaphore.h,v 1.1 2008/03/31 19:13:33 iamcamiel Exp $
 *
 * X-1.1        Camiel Vanderhoeven                             31-MAR-2008
 *      Adapted for use by the ES40 Emulator.
 **/

//
// Semaphore.h
//
// $Id: Semaphore.h,v 1.1 2008/03/31 19:13:33 iamcamiel Exp $
//
// Library: Foundation
// Package: Threading
// Module:  Semaphore
//
// Definition of the Semaphore class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_Semaphore_INCLUDED
#define Foundation_Semaphore_INCLUDED


#include "VMS/Foundation.h"
#include "VMS/Exception.h"

#include "VMS/Semaphore_POSIX.h"

namespace Poco {


class Foundation_API Semaphore: private SemaphoreImpl
	/// A Semaphore is a synchronization object with the following 
	/// characteristics:
	/// A semaphore has a value that is constrained to be a non-negative
	/// integer and two atomic operations. The allowable operations are V 
	/// (here called set()) and P (here called wait()). A V (set()) operation 
	/// increases the value of the semaphore by one. 
	/// A P (wait()) operation decreases the value of the semaphore by one, 
	/// provided that can be done without violating the constraint that the 
	/// value be non-negative. A P (wait()) operation that is initiated when 
	/// the value of the semaphore is 0 suspends the calling thread. 
	/// The calling thread may continue when the value becomes positive again.
{
public:
	Semaphore(int n);
	Semaphore(int n, int max);
		/// Creates the semaphore. The current value
		/// of the semaphore is given in n. The
		/// maximum value of the semaphore is given
		/// in max.
		/// If only n is given, it must be greater than
		/// zero.
		/// If both n and max are given, max must be
		/// greater than zero, n must be greater than
		/// or equal to zero and less than or equal
		/// to max.
		
	~Semaphore();
		/// Destroys the semaphore.

	void set();
		/// Increments the semaphore's value by one and
		/// thus signals the semaphore. Another thread
		/// waiting for the semaphore will be able
		/// to continue.

	void wait();
		/// Waits for the semaphore to become signalled.
		/// To become signalled, a semaphore's value must
		/// be greater than zero. 
		/// Decrements the semaphore's value by one.

	void wait(long milliseconds);
		/// Waits for the semaphore to become signalled.
		/// To become signalled, a semaphore's value must
		/// be greater than zero.
		/// Throws a TimeoutException if the semaphore
		/// does not become signalled within the specified
		/// time interval.
		/// Decrements the semaphore's value by one
		/// if successful.

	bool tryWait(long milliseconds);
		/// Waits for the semaphore to become signalled.
		/// To become signalled, a semaphore's value must
		/// be greater than zero.
		/// Returns true if the semaphore
		/// became signalled within the specified
		/// time interval, false otherwise.
		/// Decrements the semaphore's value by one
		/// if successful.
	
private:
	Semaphore();
	Semaphore(const Semaphore&);
	Semaphore& operator = (const Semaphore&);
};


//
// inlines
//
inline void Semaphore::set()
{
	setImpl();
}


inline void Semaphore::wait()
{
	waitImpl();
}


inline void Semaphore::wait(long milliseconds)
{
	if (!waitImpl(milliseconds))
		throw TimeoutException();
}


inline bool Semaphore::tryWait(long milliseconds)
{
	return waitImpl(milliseconds);
}


} // namespace Poco


#endif // Foundation_Semaphore_INCLUDED
