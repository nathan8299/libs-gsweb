/* GSWAdaptor.m - GSWeb: Class GSWAdaptor
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
@implementation GSWAdaptor

//--------------------------------------------------------------------
//	initWithName:arguments:application:

-(id)initWithName:(NSString*)name_
		arguments:(NSDictionary*)arguments_
{
  self=[super init];
  return self;
};


//--------------------------------------------------------------------
//	registerForEvents

- (void)registerForEvents 
{
  //Does Nothing
};

//--------------------------------------------------------------------
//	unregisterForEvents

- (void)unregisterForEvents 
{
  //Does Nothing
};

//--------------------------------------------------------------------
//	runOnce
-(void)runOnce
{
  //TODOFN
};

//--------------------------------------------------------------------
//	doesBusyRunOnce
-(BOOL)doesBusyRunOnce
{
  LOGObjectFnNotImplemented();	//TODOFN
  return NO;
};

//--------------------------------------------------------------------
-(BOOL)dispatchesRequestsConcurrently
{
  LOGObjectFnNotImplemented();	//TODOFN
  return NO;
};

//--------------------------------------------------------------------
//	port
-(int)port
{
  LOGObjectFnNotImplemented();	//TODOFN
  return 0;
};

//--------------------------------------------------------------------
-(id)workerThreadCount
{
  [self subclassResponsibility: _cmd];
  return nil;
};

//--------------------------------------------------------------------
-(void)adaptorThreadExited:(GSWDefaultAdaptorThread*)adaptorThread_
{
  [self subclassResponsibility: _cmd];
};

@end

//====================================================================
@implementation GSWAdaptor (GSWAdaptorOldFn)

//--------------------------------------------------------------------
-(void)	registerPort:(int)_port
 forApplicationNamed:(NSString*)_applicationName
{
  LOGObjectFnNotImplemented();	//TODOFN
};
@end