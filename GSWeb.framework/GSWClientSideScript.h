/* GSWClientSideScript.h - GSWeb: Class GSWClientSideScript
   Copyright (C) 1999 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@sbuilders.com>
   Date: 		Feb 1999
   
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

// $Id$

#ifndef _GSWClientSideScript_h__
	#define _GSWClientSideScript_h__

//OK
//====================================================================
@interface GSWClientSideScript: GSWHTMLDynamicElement
{
  GSWAssociation* scriptFile;
  GSWAssociation* scriptString;
  GSWAssociation* scriptSource;
  GSWAssociation* hideInComment;
  GSWAssociation* language;
  NSDictionary* otherAttributes;
};

-(id)initWithName:(NSString*)name_
	 associations:(NSDictionary*)associations_
		 template:(GSWElement*)templateElement_;
-(void)dealloc;

@end

//====================================================================
@interface GSWClientSideScript (GSWClientSideScriptA)
-(void)appendToResponse:(GSWResponse*)response_
			  inContext:(GSWContext*)context_;
@end

#endif //GSWClientSideScript