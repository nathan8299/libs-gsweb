/** GSWNestedList.h - <title>GSWeb: Class GSWNestedList</title>

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

#ifndef _GSWNestedList_h__
	#define _GSWNestedList_h__

//OK
//====================================================================
@interface GSWNestedList: GSWDynamicElement
{
  GSWAssociation* _list;
  GSWAssociation* _item;
  GSWAssociation* _displayString;
  GSWAssociation* _sublist;
  GSWAssociation* _action;
  GSWAssociation* _selection;
  GSWAssociation* _index;
  GSWAssociation* _level;
  GSWAssociation* _isOrdered;
  GSWAssociation* _prefix;
  GSWAssociation* _suffix;
  BOOL _defaultEscapeHTML;
};

-(void)dealloc;

-(id)initWithName:(NSString*)aName
     associations:(NSDictionary*)associations
         template:(GSWElement*)templateElement;

-(void)appendToResponse:(GSWResponse*)aResponse
              inContext:(GSWContext*)aContext;
-(void)_appendToResponse:(GSWResponse*)aResponse
               inContext:(GSWContext*)aContext
             orderedList:(id)orderedList
                   level:(int)level;
-(GSWElement*)invokeActionForRequest:(GSWRequest*)aRequest
                           inContext:(GSWContext*)aContext;

-(id)objectAtIndexPath:(id)indexPath
                inList:(id)list
           inComponent:(id)component;
-(id)_objectAtIndexPath:(id)indexPath
                 inList:(id)list
           currentIndex:(unsigned int)index
            inComponent:(id)component;
@end

#endif //_GSWNestedList_h__
