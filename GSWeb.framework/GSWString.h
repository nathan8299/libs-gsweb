/** GSWString.h - <title>GSWeb: Class GSWString</title>

   Copyright (C) 1999-2002 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@orange-concept.com>
   Date: 		Jan 1999
   
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

#ifndef _GSWString_h__
	#define _GSWString_h__


@interface GSWString: GSWHTMLDynamicElement
{
  GSWAssociation* _value;
  GSWAssociation* _dateFormat;
  GSWAssociation* _numberFormat;
  GSWAssociation* _escapeHTML;
//GSWeb Additions {
  GSWAssociation* _convertHTML;
  GSWAssociation* _convertHTMLEntities;
// }
  GSWAssociation* _formatter;
};

-(void)dealloc;

-(id)initWithName:(NSString*)name
     associations:(NSDictionary*)associations
  contentElements:(NSArray*)elements;

-(NSString*)description;

-(void)appendToResponse:(GSWResponse*)response
              inContext:(GSWContext*)context;

-(BOOL)appendStringAtRight:(id)unkwnon
               withMapping:(char*)mapping;

-(BOOL)appendStringAtLeft:(id)unkwnon
              withMapping:(char*)mapping;

-(NSFormatter*)formatterForComponent:(GSWComponent*)component
                               value:(id)value;
-(NSString*)elementName;
@end

//====================================================================
@interface GSWString (GSWInputA)
+(BOOL)hasGSWebObjectsAssociations;
@end

#endif //_GSWString_h__
