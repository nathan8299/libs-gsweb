/** GSWResponse.h - <title>GSWeb: Class GSWResponse</title>

   Copyright (C) 1999-2003 Free Software Foundation, Inc.
   
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

#ifndef _GSWResponse_h__
	#define _GSWResponse_h__

//====================================================================
@protocol GSWActionResults
-(GSWResponse*)generateResponse;
@end

//====================================================================
@interface GSWResponse : NSObject <NSCopying>
{
@private
    NSString* _httpVersion;
    unsigned int _status;
    NSMutableDictionary* _headers;
    NSMutableArray* _contentFaults;
    NSMutableData* _contentData;
    NSStringEncoding _contentEncoding;
    NSArray* _acceptedEncodings;
    NSDictionary* _userInfo;
    NSMutableArray* _cookies;
    BOOL _isClientCachingDisabled;
    BOOL _contentFaultsHaveBeenResolved;
    BOOL _isFinalizeInContextHasBeenCalled;
};

-(id)init;
-(void)dealloc;
-(id)copyWithZone:(NSZone*)zone;
-(NSData*)content;
-(void)willSend;//NDFN
-(void)forceFinalizeInContext;
-(NSString*)headerForKey:(NSString*)key;
-(NSArray*)headerKeys;
-(NSArray*)headersForKey:(NSString*)key;
-(NSString*)httpVersion;
-(NSArray*)acceptedEncodings;
-(void)setContent:(NSData*)someData;
-(void)setHeader:(NSString*)header
          forKey:(NSString*)key;
-(void)setHeaders:(NSArray*)headerList
           forKey:(NSString*)key;
-(void)setHeaders:(NSDictionary*)headerList;
-(NSMutableDictionary*)headers;
-(void)setHTTPVersion:(NSString*)version;
-(void)setStatus:(unsigned int)status;
-(void)setUserInfo:(NSDictionary*)userInfo;
-(void)setAcceptedEncodings:(NSArray*)acceptedEncodings;
-(unsigned int)status;
-(NSDictionary*)userInfo;
-(NSString*)description;

-(void)disableClientCaching;

@end

//====================================================================
@interface GSWResponse (GSWContentConveniences)
-(void)appendContentBytes:(const void*)contentsBytes
                   length:(unsigned)length;
-(void)appendContentCharacter:(char)aChar;
-(void)appendContentString:(NSString*)string;
-(void)appendDebugCommentContentString:(NSString*)string;
-(void)appendContentData:(NSData*)contentData;
-(void)setContentEncoding:(NSStringEncoding)encoding;
-(NSStringEncoding)contentEncoding;


@end

//====================================================================
@interface GSWResponse (GSWHTMLConveniences)

-(void)appendContentHTMLString:(NSString*)string;
-(void)appendContentHTMLAttributeValue:(NSString*)string;
-(void)appendContentHTMLConvertString:(NSString*)string;
-(void)appendContentHTMLEntitiesConvertString:(NSString*)string;
+(NSString*)stringByEscapingHTMLString:(NSString*)string;
+(NSString*)stringByEscapingHTMLAttributeValue:(NSString*)string;
+(NSString*)stringByConvertingToHTMLEntities:(NSString*)string;
+(NSString*)stringByConvertingToHTML:(NSString*)string;
@end

//====================================================================
@interface GSWResponse (Cookies)
-(NSString*)_formattedCookiesString;
-(NSMutableArray*)allocCookiesIFND;
-(void)addCookie:(GSWCookie*)cookie;
-(void)removeCookie:(GSWCookie*)cookie;
-(NSArray*)cookies;
-(NSArray*)cookiesHeadersValues;//NDFN

@end

//====================================================================
@interface GSWResponse (GSWResponseA)
-(BOOL)isFinalizeInContextHasBeenCalled;//NDFN
-(void)_finalizeInContext:(GSWContext*)context;
-(void)_initContentData;
-(void)_appendContentAsciiString:(NSString*)string;
-(void)_appendTagAttribute:(NSString*)attributeName
                     value:(id)value
escapingHTMLAttributeValue:(BOOL)escape;

@end

//====================================================================
@interface GSWResponse (GSWResponseB)
-(void)_resolveContentFaultsInContext:(GSWContext*)context;
-(void)_appendContentFault:(id)unknown;

@end

//====================================================================
@interface GSWResponse (GSWResponseC)
-(BOOL)_isClientCachingDisabled;
-(unsigned int)_contentDataLength;
@end

//====================================================================
@interface GSWResponse (GSWResponseD)
-(BOOL)_responseIsEqual:(GSWResponse*)response;
@end

//====================================================================
@interface GSWResponse (GSWActionResults) <GSWActionResults>

-(GSWResponse*)generateResponse;

@end

//====================================================================
@interface GSWResponse (GSWResponseDefaultEncoding)
+(void)setDefaultEncoding:(NSStringEncoding)encoding;
+(NSStringEncoding)defaultEncoding;
@end

//====================================================================
@interface GSWResponse (GSWResponseError)

//NDFN
//Last cHance Response
+(GSWResponse*)responseWithMessage:(NSString*)message
			 inContext:(GSWContext*)context
			forRequest:(GSWRequest*)request;

+(GSWResponse*)responseWithMessage:(NSString*)message
			 inContext:(GSWContext*)context
			forRequest:(GSWRequest*)request
                     forceFinalize:(BOOL)forceFinalize;
@end

//====================================================================
@interface GSWResponse (GSWResponseRefused)

//--------------------------------------------------------------------
//
//Refuse Response
+(GSWResponse*)generateRefusingResponseInContext:(GSWContext*)context
                                      forRequest:(GSWRequest*)request;
@end

//====================================================================
@interface GSWResponse (GSWResponseRedirected)

-(void)_generateRedirectResponseWithMessage:(NSString*)message
                                   location:(NSString*)location
                               isDefinitive:(BOOL)isDefinitive;

+(GSWResponse*)generateRedirectResponseWithMessage:(NSString*)message
                                          location:(NSString*)location
                                      isDefinitive:(BOOL)isDefinitive
                                         inContext:(GSWContext*)aContext
                                        forRequest:(GSWRequest*)aRequest;

+(GSWResponse*)generateRedirectResponseWithMessage:(NSString*)message
                                          location:(NSString*)location
                                      isDefinitive:(BOOL)isDefinitive;

+(GSWResponse*)generateRedirectDefaultResponseWithLocation:(NSString*)location
                                              isDefinitive:(BOOL)isDefinitive
                                                 inContext:(GSWContext*)aContext
                                                forRequest:(GSWRequest*)aRequest;

+(GSWResponse*)generateRedirectDefaultResponseWithLocation:(NSString*)location
                                              isDefinitive:(BOOL)isDefinitive;
@end




#endif //_GSWResponse_h__
