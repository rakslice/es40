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
 * $Id: SingletonHolder.h,v 1.1 2008/03/31 19:13:33 iamcamiel Exp $
 *
 * X-1.1        Camiel Vanderhoeven                             31-MAR-2008
 *      Adapted for use by the ES40 Emulator.
 **/

//
// SingletonHolder.h
//
// $Id: SingletonHolder.h,v 1.1 2008/03/31 19:13:33 iamcamiel Exp $
//
// Library: Foundation
// Package: Core
// Module:  SingletonHolder
//
// Definition of the SingletonHolder template.
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


#ifndef Foundation_SingletonHolder_INCLUDED
#define Foundation_SingletonHolder_INCLUDED


#include "VMS/Foundation.h"
#include "VMS/Mutex.h"


namespace Poco {


template <class S>
class SingletonHolder
	/// This is a helper template class for managing
	/// singleton objects allocated on the heap.
	/// The class ensures proper deletion (including
	/// calling of the destructor) of singleton objects
	/// when the application that created them terminates.
{
public:
	SingletonHolder()
		/// Creates the SingletonHolder.
	{
		_pS = 0;
	}
	~SingletonHolder()
		/// Destroys the SingletonHolder and the singleton
		/// object that it holds.
	{
		delete _pS;
	}
	S* get()
		/// Returns a pointer to the singleton object
		/// hold by the SingletonHolder. The first call
		/// to get will create the singleton.
	{
		FastMutex::ScopedLock lock(_m);
		if (!_pS) _pS = new S;
		return _pS;
	}
	
private:
	S* _pS;
	FastMutex _m;
};


} // namespace Poco


#endif // Foundation_SingletonHolder_INCLUDED
