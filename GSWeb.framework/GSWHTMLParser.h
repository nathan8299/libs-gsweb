#ifndef INC_GSWHTMLParser_h_
#define INC_GSWHTMLParser_h_

/*
 * ANTLR-generated file resulting from grammar html.g
 * 
 * Terence Parr, MageLang Institute
 * with John Lilley, Empathy Software
 * and Manuel Guesdon, Software Builders
 * ANTLR Version 2.5.0; 1996,1997,1998,1999
 */


#include <gsweb/GSWeb.framework/GSWeb.h>

#include "gsantlr/ANTLRCommon.h"
#include "gsantlr/ANTLRTokenizer.h"
#include "gsantlr/ANTLRTokenBuffer.h"
#include "gsantlr/ANTLRLLkParser.h"

@class ANTLRBitSet;

@interface GSWHTMLParser : ANTLRLLkParser
 {

	NSMutableArray* errors;
	NSMutableArray* warnings;
 };
	-(id)initWithTokenBuffer:(ANTLRTokenBuffer *)_buffer maxK:(int)_k;
	-(id)initWithTokenBuffer:(ANTLRTokenBuffer *)_buffer;
	-(id)initWithTokenizer:(ANTLRDefTokenizer)_lexer maxK:(int)_k;
	-(id)initWithTokenizer:(ANTLRDefTokenizer)_lexer;
	/*public: */-(void) document;
@end;


extern CONST NSString* GSWHTMLParser___tokenNames[];

extern CONST unsigned long GSWHTMLParser___tokenSet_0_data_[];
extern ANTLRBitSet* GSWHTMLParser___tokenSet_0;

#endif /*INC_GSWHTMLParser_h_*/