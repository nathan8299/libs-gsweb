/** GSWCheckBox.m - <title>GSWeb: Class GSWCheckBox</title>

   Copyright (C) 1999-2002 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@orange-concept.com>
   Date: 		Jan 1999
   
   $Revision$
   $Date$
   $Id$

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

#include "GSWeb.h"

/**
Bindings

        value		Value for "valing" tag of the element. If none, GNUstepWeb generate one

        selection	During appendTo... if it's evaluation equal value evalutaion, the check box is checked. 
        		During takeValue..., it takes value evaluated value (or contextID if no value)

        checked		During appendTo... if it's evaluated to YES, the check box is checked. 
        		During takeValue..., it takes YES if checkbox is checked, NO otherwise.

        name		Name of the element in the form (should be unique). If not specified, GSWeb assign one.

        disabled	If evaluated to yes, the check box appear inactivated.
**/

static GSWIMP_BOOL standardEvaluateConditionInContextIMP = NULL;

static Class standardClass = Nil;

//====================================================================
@implementation GSWCheckBox

//--------------------------------------------------------------------
+ (void) initialize
{
  if (self == [GSWCheckBox class])
    {
      standardClass=[GSWCheckBox class];

      standardEvaluateConditionInContextIMP = 
        (GSWIMP_BOOL)[self instanceMethodForSelector:evaluateConditionInContextSEL];
    };
};

//--------------------------------------------------------------------
-(id)initWithName:(NSString*)aName
     associations:(NSDictionary*)associations
         template:(GSWElement*)template
{
  if ((self = [super initWithName:@"input"
		     associations:associations
		     template: nil]))
    {
      GSWAssignAndRemoveAssociation(&_checked,_associations,checked__Key);
      GSWAssignAndRemoveAssociation(&_selection,_associations,selection__Key);

      if ((_checked == nil && _value == nil)
	  || ((_checked != nil && _value != nil) 
	      || (_checked != nil && ![_checked isValueSettable])
	      || ((_value != nil && _selection != nil) 
		  && ![_selection isValueSettable])))
	{
	  [NSException raise:NSInvalidArgumentException
		       format:@"%s: Bad attribute list.",
		       __PRETTY_FUNCTION__];
	}
  }

  return self;
};

//--------------------------------------------------------------------
- (NSString *) type
{
  return @"checkbox";
}

//--------------------------------------------------------------------
-(void)dealloc
{
  DESTROY(_checked);
  DESTROY(_selection);
  [super dealloc];
};

//--------------------------------------------------------------------
-(NSString*)description
{
  return [NSString stringWithFormat:@"<%s %p>",
                   object_getClassName(self),
                   (void*)self];
};

//--------------------------------------------------------------------
-(void)takeValuesFromRequest:(GSWRequest*) request
                   inContext:(GSWContext*) context
{
  GSWComponent * component = GSWContext_component(context);
  
  if (![self disabledInComponent: component]
      && [context _wasFormSubmitted])
    {
      NSString * nameCtx = [self nameInContext:context];
      if (nameCtx != nil)
	{
	  BOOL isChecked = NO;
	  id value = nil;
	  NSArray* formValues = [request formValuesForKey: nameCtx];

	  if (_value != nil)
	    value = [_value valueInComponent:component];
	  else
	    value = [context elementID];
      
	  isChecked = [formValues containsObject: NSStringWithObject(value)];
                    
	  if (_value != nil
	      && _selection != nil)
	    {
	      if (isChecked)
		{
		  [_selection setValue: value
			      inComponent: component];
		}
	      else
		{
		  id selection = [_selection valueInComponent:component];
		  if (selection != nil)
		    {
		      [_selection setValue: nil
				  inComponent: component];;
		    }
		}
	    }
	  if (_checked != nil)
	    {
	      [_checked setValue: (isChecked ? GSWNumberYes : GSWNumberNo)
			inComponent: component];
	    }
	}
    }
};


//--------------------------------------------------------------------
-(void) _appendCloseTagToResponse:(GSWResponse *) response
                         inContext:(GSWContext*) context
{
  // nothing!
}

//--------------------------------------------------------------------
- (void) appendAttributesToResponse:(GSWResponse*)response
                inContext:(GSWContext*)context
{
  GSWComponent * component = GSWContext_component(context);

  [super appendAttributesToResponse:response inContext:context];

  if (_value != nil)
    {
      id value = [_value valueInComponent:component];
      if (value != nil
	  && _selection != nil)
	{
	  id selection = [_selection valueInComponent:component];

	  if (selection != nil
	      && [selection isEqual: value])
	    {
	      GSWResponse_appendContentAsciiString(response,@" checked");
	    }
	}
    }
  else
    { // _value == nil
      GSWResponse_appendTagAttributeValueEscapingHTMLAttributeValue(response, value__Key, [context elementID], NO);  
    }
  if (_checked != nil
      && [_checked boolValueInComponent:component])
    {
      GSWResponse_appendContentAsciiString(response,@" checked");
    }
}


@end


