/* GSWUtil.c - GSWeb: Util
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
#include <sys/param.h>
#include <stdarg.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "GSWLock.h"

#if defined(Netscape)
#include <frame/log.h>
#elif	(Apache)
#include <httpd.h>
#include <http_log.h>
#endif

#include "config.h"
#include "GSWUtil.h"
#include "GSWDict.h"
#include "GSWConfig.h"


static BOOL fLogInitialized = FALSE;
static const char* pszLogPath = NULL;
static const char* pszLogFlagPath = NULL;
static const char* pszDumpFlagPath = NULL;

static GSWLock  g_lockLog=NULL;

const char* const pszLogLevels[] = {"Info", "Warn",  "Error", "" };

#define	MINLEVEL GSW_INFO
#define	MAXLEVEL GSW_ERROR

static int iLogMinLevel = MINLEVEL;

// Hosts Cache
static GSWDict* g_pHostCache = NULL;


void GSWLog_Init(GSWDict* p_pDict,int p_iLevel)
{
  char szPath[MAXPATHLEN];
  GSWLock_Init(g_lockLog);

  if (p_pDict)
	{
	  pszLogFlagPath=GSWDict_ValueForKey(p_pDict,GSWEB_CONF__LOG_FLAG_FILE_PATH);
	  pszLogPath=GSWDict_ValueForKey(p_pDict,GSWEB_CONF__LOG_FILE_PATH);
	  pszDumpFlagPath=GSWDict_ValueForKey(p_pDict,GSWEB_CONF__DUMP_FLAG_FILE_PATH);
	};
  if (pszLogFlagPath)
	pszLogFlagPath = strdup(pszLogFlagPath);
  else
	pszLogFlagPath = strdup(g_szGSWeb_DefaultLogFlagPath);
  
  if (pszLogPath)
	pszLogPath = strdup(pszLogPath);
  else
	pszLogPath = strdup(g_szGSWeb_DefaultLogFilePath);
  
  if (pszDumpFlagPath)
	pszDumpFlagPath = strdup(pszDumpFlagPath);
  else
	pszDumpFlagPath = strdup(g_szGSWeb_DefaultDumpFlagPath);
 
  {
	int fd;
	fd = open(pszLogPath, O_WRONLY, 0666);
	close(fd);
	chmod(pszLogPath, 0666);
  };
  iLogMinLevel = p_iLevel;
  fLogInitialized = 1;
  GSWLog(GSW_INFO,NULL,"GSWebLog init");
  GSWLog(GSW_INFO,NULL,"pszLogFlagPath=%s",pszLogFlagPath);
  GSWLog(GSW_INFO,NULL,"pszDumpFlagPath=%s",pszDumpFlagPath);
  GSWLog(GSW_INFO,NULL,"pszLogPath=%s",pszLogPath);
};

static BOOL isLoggingEnabled()
{
  static BOOL fLog=FALSE;
  static int iStatCounter=0;
  if (iStatCounter==0)
	{
	  struct stat stStat;
	  iStatCounter = LOG_FILE_STAT_COUNTER;		// reset counter
	  fLog = ( (stat(pszLogFlagPath,&stStat) == 0) && (stStat.st_uid == 0));
	}
  else
	iStatCounter--;
  return fLog;
};

BOOL GSWDumpConfigFile_CanDump() 
{
  static BOOL fDump=FALSE;
  static int iDumpStatCounter=0;
  if (iDumpStatCounter==0)
	{
	  struct stat stStat;
	  iDumpStatCounter = DUMP_FILE_STAT_COUNTER;		// reset counter
	  fDump = ( (stat(pszDumpFlagPath,&stStat) == 0) && (stStat.st_uid == 0));
	}
  else
	iDumpStatCounter--;
  return fDump;
};

void VGSWLogSized(int p_iLevel,
#if	defined(Apache)
			server_rec* p_pLogServerData,
#else
			void* p_pLogServerData,
#endif
			int p_iBufferSize,
			CONST char* p_pszFormat,
			va_list ap)
{
  FILE* pLog = NULL;
  char szBuffer[p_iBufferSize+128];
	
  if (p_iLevel>=iLogMinLevel)
	{
	  BOOL fIsLoggingEnabled=FALSE;
	  if (!fLogInitialized)
        GSWLog_Init(NULL,iLogMinLevel);

	  GSWLock_Lock(g_lockLog);
	  fIsLoggingEnabled=isLoggingEnabled();
	  if (fIsLoggingEnabled
#if	defined(Netscape) || defined(Apache)
		  || p_iLevel == GSW_ERROR
#endif
		  )
		{
		  vsprintf(szBuffer,p_pszFormat,ap);
		  pLog=fopen(pszLogPath,"a+");
		  if (pLog)
			{
			  fprintf(pLog,"%s: %s\n",pszLogLevels[p_iLevel],szBuffer);
			  fclose(pLog);
            };
		};
	  GSWLock_Unlock(g_lockLog);
	
#if	defined(Netscape) || defined(Apache)
	  if (p_iLevel == GSW_ERROR)
		{
#if	defined(Netscape)
            log_error(0,"GSWeb",NULL,NULL,szBuffer);
#endif
#if defined(Apache)
			ap_log_error(APLOG_MARK,APLOG_EMERG,
						 NULL/*(server_rec*)p_pLogServerData*/,"%s",szBuffer);
			  //log_error(szBuffer,(server_rec*)p_pLogServerData);
#endif 
		};
#endif 
	};
};

void GSWLog(int p_iLevel,
#if	defined(Apache)
			server_rec* p_pLogServerData,
#else
			void* p_pLogServerData,
#endif
			CONST char* p_pszFormat,...)
{
  va_list ap;
  va_start(ap,p_pszFormat);
  VGSWLogSized(p_iLevel,
			   p_pLogServerData,
			   4096,
			   p_pszFormat,
			   ap);
  va_end(ap);
};

void GSWLogSized(int p_iLevel,
#if	defined(Apache)
			server_rec* p_pLogServerData,
#else
			void* p_pLogServerData,
#endif
			int p_iBufferSize,
			CONST char* p_pszFormat,...)
{
  va_list ap;
  va_start(ap,p_pszFormat);
  VGSWLogSized(p_iLevel,
		 p_pLogServerData,
		 p_iBufferSize,
		 p_pszFormat,
		 ap);
  va_end(ap);
};


// return new len
int DeleteTrailingCRNL(char* p_pszString) 
{
  int i=0;
  if (p_pszString)
	{
	  i=strlen(p_pszString)-1;
	  while (i>=0 && p_pszString[i] && (p_pszString[i]=='\r' || p_pszString[i]=='\n'))
		p_pszString[i--]=0;
	  i++;
	};
  return i;
}

int DeleteTrailingSlash(char* p_pszString)
{
  int i=0;
  if (p_pszString)
	{
	  i=strlen(p_pszString)-1;
	  while (i>=0 && p_pszString[i] && p_pszString[i]=='/')
		p_pszString[i--]=0;
	  i++;
	};
  return i;
}

int DeleteTrailingSpaces(char* p_pszString)
{
  int i=0;
  if (p_pszString)
	{
	  i=strlen(p_pszString)-1;
	  while (i>=0 && p_pszString[i] && p_pszString[i]==' ')
		p_pszString[i--]=0;
	  i++;
	};
  return i;
}

CONST char* strcasestr(CONST char* p_pszString,CONST char* p_pszSearchedString)
{
  if (p_pszString && p_pszSearchedString)
	{
	  int i=0;
	  int iStringLen=strlen(p_pszString);
	  int iSearchedStringLen=strlen(p_pszSearchedString);
	  if (iStringLen>0 && iSearchedStringLen>0)
		{
		  char ch1stUpper=toupper(p_pszSearchedString[0]);
		  for(i=0;i<iStringLen-iSearchedStringLen+1;i++)
			{
			  if (toupper(p_pszString[i])==ch1stUpper)
				{
				  BOOL fSame=TRUE;
				  int j=0;
				  for(j=1;j<iSearchedStringLen && fSame;j++)
					fSame=toupper(p_pszString[i+j])==toupper(p_pszSearchedString[j]);
				  if (fSame)
					return p_pszString+i;
				};
			};
		};
	};
  return NULL;
};

#if defined(HAS_REENTRANT_GETHOSTENT) && !defined(_REENTRANT)
#define _REENTRANT	/* needs to be defined so proper structs get included */
#endif





void GSWUtil_ClearHostCache()
{
  if (g_pHostCache)
	{
	  GSWDict_Free(g_pHostCache);
	  g_pHostCache=NULL;
	};
};

PSTHostent GSWUtil_FindHost(void* p_pLogServerData,CONST char* p_pszHost)
{
  PSTHostent pHost=NULL;
  if (!p_pszHost) 
	p_pszHost="localhost";

  pHost = (g_pHostCache) ? (PSTHostent)GSWDict_ValueForKey(g_pHostCache,p_pszHost) : NULL;
  if (!pHost)
	{
	  pHost = GSWUtil_HostLookup(p_pLogServerData,p_pszHost);
	  if (pHost)
		{
		  if (!g_pHostCache)
			g_pHostCache = GSWDict_New(32);
		  GSWDict_Add(g_pHostCache,p_pszHost,pHost,TRUE);
		  GSWLog(GSW_INFO,p_pLogServerData,"Caching hostent for %s",p_pszHost);
		};
	};
  return pHost;
};


#define ROUND_UP(n, m)  (((unsigned)(n)+(m)-1)&~((m)-1))
#define	BUFLEN			4096


#if	defined(NEEDS_HSTRERR)
#ifndef	NETDB_SUCCESS
#define	NETDB_SUCCESS 0
#endif

CONST char *hstrerror(int herr)
{
  if (herr == -1)				/* see errno */
	return strerror(errno);
  else if (herr == HOST_NOT_FOUND)
	return "Host not found";
  else if (herr == TRY_AGAIN)
	return "Try again";				/* ? */
  else if (herr == NO_RECOVERY)
	return "Non recoverable error";
  else if (herr == NO_DATA)
	return "No data";
  else if (herr == NO_ADDRESS)
	return "No address";			/* same as no data */
  else if (herr == NETDB_SUCCESS)		
	return "No error";				/* strange */
  else
	return "unknown error";
}
#endif

static PSTHostent GSWUtil_CopyHostent(PSTHostent p_pHost)
{
  PSTHostent pNewHost=NULL;
  int iSize=(ROUND_UP(sizeof(struct hostent), sizeof(void *)))+strlen(p_pHost->h_name)+1;
  int iAliasNb=0;
  int iAddressesNb = 0;
  char** ppszAliasOrAddress=NULL;
  char** ppszNewHostAliasOrAddress=NULL;
  void* pTmp=NULL;
  
  // Aliases
  for (ppszAliasOrAddress=p_pHost->h_aliases;
	   ppszAliasOrAddress && *ppszAliasOrAddress;
	   ppszAliasOrAddress++)
	{
	  iSize+=strlen(*ppszAliasOrAddress)+1;
	  iAliasNb++;
	};

  // Aliases Pointers Null Terminated List
  iSize=ROUND_UP(iSize,sizeof(char *));
  iSize+=(iAliasNb+1)*sizeof(char*);
	
  for (ppszAliasOrAddress=p_pHost->h_addr_list;
	   ppszAliasOrAddress && *ppszAliasOrAddress;
	   ppszAliasOrAddress++)
	iAddressesNb++;
  
  iSize+=iAddressesNb*(sizeof(char*)+p_pHost->h_length+1);
  
  pNewHost=malloc(ROUND_UP(iSize,sizeof(char*)));
  pTmp=pNewHost;
  pNewHost->h_addrtype = p_pHost->h_addrtype;
  pNewHost->h_length = p_pHost->h_length;
		
  pTmp+=ROUND_UP(sizeof(struct hostent),sizeof(void*));
  pNewHost->h_aliases = (char **)pTmp;
  pTmp+=(iAliasNb+1)*sizeof(char*);
  pNewHost->h_addr_list = (char**)pTmp;
  pTmp+=(iAddressesNb+1)*sizeof(char*);
	
  pNewHost->h_name = pTmp;
  strcpy(pNewHost->h_name,p_pHost->h_name);
  pTmp+=strlen(pNewHost->h_name)+1;

  // Copy Aliases
  for (ppszAliasOrAddress=p_pHost->h_aliases,ppszNewHostAliasOrAddress=pNewHost->h_aliases;
	   ppszAliasOrAddress && *ppszAliasOrAddress;
	   ppszAliasOrAddress++,ppszNewHostAliasOrAddress++)
	{
	  *ppszNewHostAliasOrAddress = (char*)pTmp;
	  strcpy((char*)pTmp,*ppszAliasOrAddress);
	  pTmp+=strlen(*ppszAliasOrAddress) + 1;
	};
  *ppszNewHostAliasOrAddress=NULL;
  
  pTmp=(void *)ROUND_UP(pTmp,pNewHost->h_length);
  for (ppszAliasOrAddress=p_pHost->h_addr_list,ppszNewHostAliasOrAddress=pNewHost->h_addr_list;
	   ppszAliasOrAddress && *ppszAliasOrAddress;
	   ppszAliasOrAddress++,ppszNewHostAliasOrAddress++)
	{
		*ppszNewHostAliasOrAddress=(char*)pTmp;
		memcpy(*ppszNewHostAliasOrAddress,*ppszAliasOrAddress,pNewHost->h_length);
		pTmp+=pNewHost->h_length;
	};
  *ppszNewHostAliasOrAddress=NULL;
  return pNewHost;
};

PSTHostent GSWUtil_HostLookup(void* p_pLogServerData,CONST char *p_pszHost)
{
  PSTHostent pHost=NULL;
  struct in_addr hostaddr;
  int error=0;

#if	defined(HAS_REENTRANT_GETHOSTENT)
  struct hostent stTmpHost;
  char szBuffer[BUFLEN];
  
  pHost = &stTmpHost;		/* point to struct on the stack */
  memset(pHost,0,sizeof(struct hostent));
  memset(szBuffer,0,sizeof(szBuffer));
#endif	
  
  if (!p_pszHost) 
	p_pszHost="localhost";

  if (isdigit(*p_pszHost)) 
	hostaddr.s_addr=inet_addr(p_pszHost);
	
#if	defined(HAS_REENTRANT_GETHOSTENT)
	if (isdigit(*p_pszHost))
	  {
#if	defined(SOLARIS)
		pHost = gethostbyaddr_r((char *)&hostaddr.s_addr,
								sizeof(hostaddr.s_addr),
								AF_INET,
								pHost,
								szBuffer,
								BUFLEN, &error);
#else	// !SOLARIS
		if (gethostbyaddr_r((char *)&hostaddr.s_addr, 
							sizeof(hostaddr.s_addr),
							AF_INET,
							&stTmpHost,
							szBuffer) == 0)
		  {
			pHost = &stTmpHost;
			error = 0;
		  }
		else
		  {
			pHost=NULL;
			error = h_errno;
		  };
#endif  // SOLARIS
	  }
	else
	  {
#if	defined(SOLARIS)
		pHost = gethostbyname_r(p_pszHost,
								&stTmpHost,
								szBuffer,
								BUFLEN,
								&error);
#else	// !SOLARIS
		pHost = (gethostbyname_r(p_pszHost,&stTmpHost,szBuffer)==0) ? &stTmpHost : NULL;
		error = (pHost) ? 0 : h_errno;
#endif  // SOLARIS
	  };
#else   // !HAS_REENTRANT_GETHOSTENT
	if (isdigit(*p_pszHost))
	  {
		pHost = gethostbyaddr((char *)&hostaddr.s_addr, sizeof(hostaddr.s_addr), AF_INET);
		error = (pHost) ? 0 : h_errno;
	  }
	else
	  {
		pHost = gethostbyname(p_pszHost);
		error = (pHost) ? 0 : h_errno;
	  }
#endif  // HAS_REENTRANT_GETHOSTENT

	if (!pHost)
	  {
		GSWLog(GSW_ERROR,p_pLogServerData,"gethostbyname(%s) returns no host: %s",
			   p_pszHost,
			   hstrerror(error));
	  }
	else if (pHost->h_addrtype != AF_INET)
	  {
		GSWLog(GSW_ERROR,p_pLogServerData,"Wrong address type in hostptr for host %s",p_pszHost);
	  };
	if (pHost)
	  pHost=GSWUtil_CopyHostent(pHost);
	return pHost;
};
