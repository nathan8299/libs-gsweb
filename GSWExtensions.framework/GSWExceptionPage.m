/* GSWExceptionPage.m - GSWeb: Class GSWExceptionPage
   Copyright (C) 1999 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@sbuilders.com>
   Date: 		Apr 1999
   
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
#include <gsweb/GSWeb.framework/GSWeb.h>
#include "GSWExceptionPage.h"

//===================================================================================
@implementation GSWExceptionPage

-(void)dealloc
{
  GSWLogCStdOut("Dealloc GSWExceptionPage\n");
  GSWLogC("Dealloc GSWExceptionPage\n");  
  DESTROY(exception);
  GSWLogCStdOut("Dealloc GSWExceptionPage reasons\n");
  GSWLogC("Dealloc GSWExceptionPage reasons\n");  
  DESTROY(reasons);
  GSWLogCStdOut("Dealloc GSWExceptionPage super\n");
  GSWLogC("Dealloc GSWExceptionPage super\n");  
  [super dealloc];
  GSWLogCStdOut("Dealloc GSWExceptionPage end\n");
  GSWLogC("Dealloc GSWExceptionPage end\n");  
};

-(void)awake
{
  [super awake];
};

-(void)sleep
{
  [super sleep];
};

-(NSArray*)getReasons
{
  if (!reasons)
	{
	  ASSIGN(reasons,[[exception description] componentsSeparatedByString:@"\n"]);
	};
  return reasons;
};

-(void)appendToResponse:(GSWResponse*)response_
			  inContext:(GSWContext*)context_
{
  [super appendToResponse:response_
			  inContext:context_];
  [response_ disableClientCaching];
};

-(void)setException:(NSException*)exception_
{
  ASSIGN(exception,exception_);
};

@end