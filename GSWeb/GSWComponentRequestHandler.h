/** GSWComponentRequestHandler.h - <title>GSWeb: Class GSWComponentRequestHandler</title>

   Copyright (C) 1999-2002 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@orange-concept.com>
   Date: 	Feb 1999
   
   $Revision$
   $Date$

   This file is part of the GNUstep Web Library.
   
   <license>
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
   </license>
**/

// $Id$

#ifndef _GSWComponentRequestHandler_h__
	#define _GSWComponentRequestHandler_h__


@interface GSWComponentRequestHandler: GSWRequestHandler
{
}

/*
 returns YES. Subclassers might override this.
 Used to reject requests to /favicon.ico in direct connect mode.
 */
- (BOOL) rejectFavicon;

-(GSWResponse*)handleRequest:(GSWRequest*)aRequest;

+(id)handler;

@end


#endif //_GSWComponentRequestHandler_h__
