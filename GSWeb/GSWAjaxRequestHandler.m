/** GSWAjaxRequestHandler.m - <title>GSWeb: Class GSWAjaxRequestHandler</title>
 
 Copyright (C) 2017 Free Software Foundation, Inc.
 
 Written by:    David Wetzel <dave@turbocat.de>
 Date:     Nov 2017
 
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

#include "config.h"

#include "GSWeb.h"
#include "GSWPrivate.h"

@implementation GSWAjaxRequestHandler

-(GSWResponse*)handleRequest:(GSWRequest*)aRequest
{
    GSWResponse* response = nil;
    
    [aRequest setStorePageInBacktrackCache:NO];
    
    response = [super handleRequest:aRequest];
    
    return response;
}

@end
