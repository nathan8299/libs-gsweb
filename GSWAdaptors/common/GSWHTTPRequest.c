/* GSWHTTPRequest.c - GSWeb: Adaptors: HTTP Request
   Copyright (C) 1999 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@sbuilders.com>
   Date: 		Jully 1999
   
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

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "GSWUtil.h"
#include "GSWDict.h"
#include "GSWURLUtil.h"
#include "GSWAppRequestStruct.h"
#include "GSWAppConnect.h"
#include "GSWHTTPRequest.h"
#include "GSWHTTPResponse.h"
#include "GSWAppRequest.h"
#include "GSWHTTPHeaders.h"

static ERequestMethod GetHTTPRequestMethod();
static CONST char* GSWebHeaderForHTTPHeader(CONST char *header);
static char* GSWHTTPRequest_PackageHeaders(GSWHTTPRequest* p_pHTTPRequest,
										   char* pszBuffer,
										   int p_iBufferSize);


GSWHTTPRequest* GSWHTTPRequest_New(CONST char* p_pszMethod,char* p_pszURI)
{
  GSWHTTPRequest* pHTTPRequest=calloc(1,sizeof(GSWHTTPRequest));
  pHTTPRequest->eMethod = GetHTTPRequestMethod(p_pszMethod);
  pHTTPRequest->pszRequest = p_pszURI;		// It will be freed
  return pHTTPRequest;
};

void GSWHTTPRequest_Free(GSWHTTPRequest* p_pHTTPRequest)
{
  if (p_pHTTPRequest)
	{
	  if (p_pHTTPRequest->pHeaders)
		{
		  GSWDict_Free(p_pHTTPRequest->pHeaders);
		  p_pHTTPRequest->pHeaders=NULL;
		};
	  if (p_pHTTPRequest->pszRequest)
		{
		  free(p_pHTTPRequest->pszRequest);
		  p_pHTTPRequest->pszRequest=NULL;
		};
	  if (p_pHTTPRequest->pContent)
		{
		  free(p_pHTTPRequest->pContent);
		  p_pHTTPRequest->pContent=NULL;
		};
	  free(p_pHTTPRequest);
	  p_pHTTPRequest=NULL;
	};
};


CONST char* GSWHTTPRequest_ValidateMethod(GSWHTTPRequest* p_pHTTPRequest)
{
  switch(p_pHTTPRequest->eMethod)
	{
	case ERequestMethod_None:
	  return "GSWeb Application must be launched by HTTP Server";
	  break;
	case ERequestMethod_Unknown:
	case ERequestMethod_Head:
	case ERequestMethod_Put:
		return "Invalid Method";
		break;
	case ERequestMethod_Get:
	case ERequestMethod_Post:
	default:
	  return NULL;
	};
};

void GSWHTTPRequest_HTTPToAppRequest(GSWHTTPRequest* p_pHTTPRequest,
									 GSWAppRequest* p_pAppRequest,
									 GSWURLComponents* p_pURLComponents,
									 CONST char* p_pszHTTPVersion)
{
  char szInstanceBuffer[65]="";
  char* pszDefaultHTTPVersion = "HTTP/1.0";
  int iHTTPVersionLength = p_pszHTTPVersion ? strlen(p_pszHTTPVersion) : strlen(pszDefaultHTTPVersion);
  if (p_pAppRequest->iInstance > 0)	/* should be -1 !!! */
	sprintf(szInstanceBuffer,"%d",p_pAppRequest->iInstance);
  p_pURLComponents->stAppName.pszStart = p_pAppRequest->pszName;
  p_pURLComponents->stAppName.iLength = strlen(p_pAppRequest->pszName);
  p_pURLComponents->stAppNumber.pszStart = szInstanceBuffer;		
  p_pURLComponents->stAppNumber.iLength = strlen(szInstanceBuffer);
  p_pURLComponents->stAppHost.pszStart = p_pAppRequest->pszHost;
  p_pURLComponents->stAppHost.iLength = strlen(p_pAppRequest->pszHost);
  
  if (p_pHTTPRequest->pszRequest)
	{
	  free(p_pHTTPRequest->pszRequest);
	  p_pHTTPRequest->pszRequest=NULL;
	};
		
  p_pHTTPRequest->pszRequest = malloc(8 + (GSWComposeURLLen(p_pURLComponents)+1) + iHTTPVersionLength);

  if (p_pHTTPRequest->uContentLength>0)
	{
	  strcpy(p_pHTTPRequest->pszRequest,"POST ");
	  GSWHTTPRequest_AddHeader(p_pHTTPRequest,g_szHeader_GSWeb_RequestMethod,"POST");
	}
  else
	{
	  strcpy(p_pHTTPRequest->pszRequest,"GET ");
	  GSWHTTPRequest_AddHeader(p_pHTTPRequest,g_szHeader_GSWeb_RequestMethod,"GET");
	};
  GSWComposeURL(p_pHTTPRequest->pszRequest+strlen(p_pHTTPRequest->pszRequest),p_pURLComponents);
  strcat(p_pHTTPRequest->pszRequest," ");
  if (p_pszHTTPVersion)
	  strcat(p_pHTTPRequest->pszRequest,p_pszHTTPVersion);
  else
	strcat(p_pHTTPRequest->pszRequest,pszDefaultHTTPVersion);
  strcat(p_pHTTPRequest->pszRequest,"\n");
	
  GSWLog(GSW_INFO,NULL,"App Request: %s",p_pHTTPRequest->pszRequest);
};

void GSWHTTPRequest_AddHeader(GSWHTTPRequest* p_pHTTPRequest,
							  CONST char* p_pszKey,
							  CONST char* p_pszValue)
{
  CONST char* pszCustomKey=GSWebHeaderForHTTPHeader(p_pszKey);
  CONST char* pszHeaderKey=(pszCustomKey) ? pszCustomKey : p_pszKey;
  
  if (!p_pHTTPRequest->pHeaders)
	p_pHTTPRequest->pHeaders = GSWDict_New(64);

  // Search Content Length
  if (p_pHTTPRequest->eMethod==ERequestMethod_Post
	  && p_pHTTPRequest->uContentLength==0
	  && strcasecmp(pszHeaderKey,g_szHeader_ContentLength)==0)
	p_pHTTPRequest->uContentLength = atoi(p_pszValue);

  GSWDict_AddString(p_pHTTPRequest->pHeaders,pszHeaderKey,p_pszValue,FALSE);
};

CONST char* GSWHTTPRequest_HeaderForKey(GSWHTTPRequest* p_pHTTPRequest,CONST char* p_pszKey)
{
  if (p_pHTTPRequest->pHeaders) 
	return GSWDict_ValueForKey(p_pHTTPRequest->pHeaders,p_pszKey);
  else
	return NULL;
};

static void GetHeaderLength(GSWDictElem* p_pElem,
							void* p_piAddTo)
{
  int* piAddTo=(int*)p_piAddTo;
  // +2=": "
  // +1="\n"
  (*piAddTo)+=strlen(p_pElem->pszKey)+strlen((char*)(p_pElem->pValue))+2+1+1;
}

static void FormatHeader(GSWDictElem* p_pElem,
						 void* p_ppszBuffer)
{
  char** ppszBuffer=(char**)p_ppszBuffer;
  strcpy(*ppszBuffer,p_pElem->pszKey);
  strcat(*ppszBuffer, ": ");
  strcat(*ppszBuffer,(char*)p_pElem->pValue);
  (*ppszBuffer)+= strlen(*ppszBuffer);
  **ppszBuffer = '\n';
  (*ppszBuffer)++;
};

// Handle Request (send it to Application)

BOOL GSWHTTPRequest_SendRequest(void* p_pLogServerData,GSWHTTPRequest* p_pHTTPRequest,AppConnectHandle p_socket)
{
  BOOL fOk = TRUE;
  char* pszBuffer=NULL;
  char* pszTmp=NULL;
  int iLength = 0;
  int iHeaderLength = 0;
  int iRequestLength = strlen(p_pHTTPRequest->pszRequest);
  int iContentLength = p_pHTTPRequest->uContentLength;
    
  GSWDict_PerformForAllElem(p_pHTTPRequest->pHeaders,
							GetHeaderLength,
							&iHeaderLength);
  iHeaderLength++;   // Last /n

  iLength=iRequestLength+iHeaderLength+iContentLength;

  pszBuffer = malloc(iLength+1);

  strncpy(pszBuffer,
		  p_pHTTPRequest->pszRequest,
		  iRequestLength);

  pszTmp = pszBuffer+iRequestLength;
  GSWDict_PerformForAllElem(p_pHTTPRequest->pHeaders,
							FormatHeader,
							(void*)&pszTmp);

  *pszTmp++ = '\n';
    
  if (iContentLength>0)
	{
	  memcpy(pszTmp,p_pHTTPRequest->pContent,iContentLength);
	  pszTmp+=iContentLength;
	};

  GSWLog(GSW_INFO,p_pLogServerData,
		 "Sending AppRequest Content: %s\n(iContentLength Bytes)",
		 p_pHTTPRequest->pszRequest,
		 iContentLength);
  // Just To be sure of the length
  iLength = pszTmp - pszBuffer;
  fOk = GSWApp_SendBlock(p_pLogServerData,p_socket,pszBuffer,iLength);
  free(pszBuffer);
  pszBuffer=NULL;
  return fOk;
}

static char* GSWHTTPRequest_PackageHeaders(GSWHTTPRequest* p_pHTTPRequest,
										   char* p_pszBuffer,
										   int p_iBufferSize)
{
  int iHeaderLength=0;
  char* pszBuffer=NULL;
  char* pszTmp=NULL;
	
  GSWDict_PerformForAllElem(p_pHTTPRequest->pHeaders,
							GetHeaderLength,
							(void*)&iHeaderLength);
  pszBuffer = ((p_iBufferSize > (iHeaderLength+1)) ? p_pszBuffer : malloc(p_iBufferSize+2));
  pszTmp = pszBuffer;
	
  GSWDict_PerformForAllElem(p_pHTTPRequest->pHeaders,FormatHeader,&pszTmp);
  *pszTmp++ = '\n';
  *pszTmp++ = '\0';
  return pszBuffer;
};


static ERequestMethod GetHTTPRequestMethod(CONST char* pszMethod)
{
  if (pszMethod)
	{
	  if (strcmp(pszMethod,g_szMethod_Get)==0)
		return ERequestMethod_Get;
	  else if (strcmp(pszMethod, g_szMethod_Post)==0)
		return ERequestMethod_Post;
	  else if (!strcmp(pszMethod, g_szMethod_Head)==0)
		return ERequestMethod_Head;
	  else if (!strcmp(pszMethod,g_szMethod_Put)==0)
		return ERequestMethod_Put;
	  else
		return ERequestMethod_Unknown;
    }
  else
	return ERequestMethod_None;
};



static int compareHeader(CONST void* p_pKey0,CONST void* p_pKey1)
{
  CONST char* pKey1=((GSWHeaderTranslationItem*)p_pKey1)->pszHTTP;
/*
  if (p_pKey0)
	GSWLog(GSW_ERROR,NULL,"p_pKey0=%p (CONST char*)p_pKey0=%s",p_pKey0,(CONST char*)p_pKey0);
  if (p_pKey1)
	{
	  if (((GSWHeaderTranslationItem*)p_pKey1)->pszHTTP)
		GSWLog(GSW_ERROR,NULL,"p_pKey1=%p  (CONST char*)p_pKey1=%s",p_pKey1,((GSWHeaderTranslationItem*)p_pKey1)->pszHTTP);
	  
	};
*/
  if (pKey1)
	return strcmp((CONST char*)p_pKey0,pKey1);
  else if (!p_pKey0)
	return 0;
  else
	return 1;
}

static CONST char* GSWebHeaderForHTTPHeader(CONST char* p_pszHTTPHeader)
{
  GSWHeaderTranslationItem* pItem=NULL;
  if (GSWHeaderTranslationTableItemsNb==0)
	GSWHeaderTranslationTable_Init();
  pItem=bsearch(p_pszHTTPHeader,
				GSWHeaderTranslationTable,
				GSWHeaderTranslationTableItemsNb,
				sizeof(GSWHeaderTranslationItem),
				compareHeader);
  return (pItem ? pItem->pszGSWeb : NULL);
};