/* GSWGenericElement.m - GSWeb: Class GSWGenericElement
   Copyright (C) 1999 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@sbuilders.com>
   Date: 		Jan 1999
   
   This file is part of the GNUstep Web Library.
   
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
*/

static char rcsId[] = "$Id$";

#include <gsweb/GSWeb.framework/GSWeb.h>

//====================================================================
@implementation GSWGenericElement

-(id)initWithName:(NSString*)name_
	 associations:(NSDictionary*)associations_
		 template:(GSWElement*)templateElement_
{
  LOGObjectFnNotImplemented();	//TODOFN
  return nil;
};

//--------------------------------------------------------------------
-(void)dealloc
{
  LOGObjectFnNotImplemented();	//TODOFN
};

//--------------------------------------------------------------------
-(NSString*)description
{
  LOGObjectFnNotImplemented();	//TODOFN
  return nil;
};

//--------------------------------------------------------------------

-(void)appendToResponse:(GSWResponse*)response_
			  inContext:(GSWContext*)context_
{
  LOGObjectFnNotImplemented();	//TODOFN
};

//--------------------------------------------------------------------

-(GSWElement*)invokeActionForRequest:(GSWRequest*)request_
						  inContext:(GSWContext*)context_
{
  LOGObjectFnNotImplemented();	//TODOFN
  return nil;
};

//--------------------------------------------------------------------

-(void)takeValuesFromRequest:(GSWRequest*)request_
				   inContext:(GSWContext*)context_
{
  LOGObjectFnNotImplemented();	//TODOFN
};

//-------------------------------------------------------------------- 

-(id)_elementNameAppenedToResponse:(GSWResponse*)response_
						 inContext:(GSWContext*)context_
{
  LOGObjectFnNotImplemented();	//TODOFN
  return nil;
};

//--------------------------------------------------------------------
-(void)_appendTagWithName:(NSString*)name_
			   toResponse:(GSWResponse*)response_
				inContext:(GSWContext*)context_
{
  LOGObjectFnNotImplemented();	//TODOFN
};

//--------------------------------------------------------------------
-(void)_appendOtherAttributesToResponse:(GSWResponse*)response_
							  inContext:(GSWContext*)context_
{
  LOGObjectFnNotImplemented();	//TODOFN
};

//--------------------------------------------------------------------
-(NSString*)_elementNameInContext:(GSWContext*)context_
{
  LOGObjectFnNotImplemented();	//TODOFN
  return nil;
};

//--------------------------------------------------------------------
@end