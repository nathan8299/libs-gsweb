/* GSWHTMLComment.m - GSWeb: Class GSWHTMLComment
   Copyright (C) 1999 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@sbuilders.com>
   Date: 		Sept 1999
   
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
@implementation GSWHTMLComment

//--------------------------------------------------------------------
-(id)init
{
  if ((self=[super init]))
	{
	  encoding=NSISOLatin1StringEncoding;
	};
  return self;
};

//--------------------------------------------------------------------
-(id)initWithString:(NSString*)_string
{
  if ((self=[self init]))
	{
	  ASSIGN(string,_string);
	};
  return self;
};

//--------------------------------------------------------------------
-(void)dealloc
{
  DESTROY(string);
  DESTROY(data);
  [super dealloc];
}

//--------------------------------------------------------------------
-(NSString*)description
{
  return [NSString stringWithFormat:@"<%s %p - String:[%@]>",
				   object_get_class_name(self),
				   (void*)self,
				   string];
};

@end

//====================================================================
@implementation GSWHTMLComment (GSWHTMLCommentA)

//--------------------------------------------------------------------
-(void)appendToResponse:(GSWResponse*)response_
			  inContext:(GSWContext*)context_
{
  LOGObjectFnStart();
  NSDebugMLLog(@"gswdync",@"ET=%@ id=%@",[self class],[context_ elementID]);
  [response_ _appendContentAsciiString:@"<!--"];
  [response_ _appendContentAsciiString:string];
  [response_ _appendContentAsciiString:@"-->"];
  NSDebugMLLog(@"gswdync",@"END ET=%@ id=%@",[self class],[context_ elementID]);
  LOGObjectFnStop();
};

@end

//====================================================================
@implementation GSWHTMLComment (GSWHTMLCommentB)

//--------------------------------------------------------------------
+(id)elementWithString:(NSString*)_string
{
  return [[[GSWHTMLComment alloc]initWithString:_string] autorelease];
};
@end