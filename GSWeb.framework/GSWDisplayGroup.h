/* GSWDisplayGroup.h - GSWeb: Class GSWDisplayGroup
   Copyright (C) 1999 Free Software Foundation, Inc.
   
   Written by:	Manuel Guesdon <mguesdon@sbuilders.com>
   Date: 		Jan 1999
   
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

#ifndef _GSWDisplayGroup_h__
	#define _GSWDisplayGroup_h__

#include <eoaccess/EOModel.h>
#include <eoaccess/EOEntity.h>
#include <eoaccess/EOAttribute.h>
#include <eoaccess/EOAttributeOrdering.h>
#include <eoaccess/EORelationship.h>
#include <eoaccess/EOQualifier.h>

#include <eoaccess/EOAdaptor.h>
#include <eoaccess/EOAdaptorContext.h>
#include <eoaccess/EOAdaptorChannel.h>

#include <eoaccess/EODatabase.h>
#include <eoaccess/EODatabaseContext.h>
#include <eoaccess/EODatabaseChannel.h>
#include <eoaccess/EODataSources.h>
#include <eoaccess/EODatabaseDataSource.h>

#include <eoaccess/EOGenericRecord.h>
#include <eoaccess/EONull.h>
#include <eoaccess/EOSQLExpression.h>

#define EODataSource EODatabaseDataSource

@interface GSWDisplayGroup : NSObject <NSCoding>
{
  id delegate;
/*
     objects (array) supplied by the EODataSource 
     EOQualifier and EOSortOrderings to filter the objects for display 
     Array of selection indexes 

*/
};

-(NSArray*)allObjects;
-(NSArray*)allQualifierOperators;
-(unsigned)batchCount;
-(BOOL)buildsQualifierFromInput;
-(BOOL)clearSelection;
-(unsigned)currentBatchIndex;
-(EODataSource*)dataSource;
-(NSString*)defaultStringMatchFormat;
-(NSString*)defaultStringMatchOperator;
-(id)delegate;
-(id)delete;
-(BOOL)deleteObjectAtIndex:(unsigned)index;
-(BOOL)deleteSelection;
-(NSString*)detailKey;
-(id)displayBatchContainingSelectedObject;
-(NSArray*)displayedObjects;
-(id)displayNextBatch;
-(id)displayPreviousBatch;
-(BOOL)endEditing;
-(id)executeQuery;
-(id)fetch;
-(BOOL)fetchesOnLoad;
-(BOOL)hasDetailDataSource;
-(BOOL) hasMultipleBatches;
-(id)init;
-(NSMutableDictionary*)inputObjectForQualifier;
-(BOOL)inQueryMode;
-(id)insert;
-(NSDictionary*)insertedObjectDefaultValues;
-(void)insertObject:object_
			atIndex:(unsigned)index;
-(id)insertObjectAtIndex:(unsigned)index_;
-(EOQualifier*)lastQualifierFromInputValues;
-(NSArray*)localKeys;
-(id)masterObject;
-(unsigned)numberOfObjectsPerBatch;
-(EOQualifier*)qualifier;
-(EOQualifier*)qualifierFromInputValues;
-(EOQualifier*)qualifierFromQueryValues;
-(void)qualifyDataSource;
-(void)qualifyDisplayGroup;
-(NSMutableDictionary*)queryMatch;
-(NSMutableDictionary*)queryMax;
-(NSMutableDictionary*)queryMin;
-(NSMutableDictionary*)queryOperator;
-(void)redisplay;
-(void)relationalQualifierOperators;
-(NSMutableDictionary*)secondObjectForQualifier;
-(id)selectedObject;
-(NSArray*)selectedObjects;
-(NSArray*)selectionIndexes;
-(id)selectNext;
-(BOOL)selectObject:(id)object;
-(BOOL)selectObjectsIdenticalTo:(NSArray*)objects;
-(BOOL)selectObjectsIdenticalTo:(NSArray*)objects
		   selectFirstOnNoMatch:(BOOL)flag;
-(id)selectPrevious;
-(BOOL)selectsFirstObjectAfterFetch;
-(void)setBuildsQualifierFromInput:(BOOL)flag;
-(void)setCurrentBatchIndex:(unsigned)index_;
-(void)setDataSource:(EODataSource*)dataSource_;
-(void)setDefaultStringMatchFormat:(NSString*)format;
-(void)setDefaultStringMatchOperator:(NSString*)operator;
-(void)setDelegate:(id)object_;
-(void)setDetailKey:(NSString*)detailKey;
-(void)setFetchesOnLoad:(BOOL)flag;
-(void)setInQueryMode:(BOOL)flag;
-(void)setInsertedObjectDefaultValues:(NSDictionary*)defaultValues;
-(void)setLocalKeys:(NSArray*)keys;
-(void)setMasterObject:(id)masterObject;
-(void)setNumberOfObjectsPerBatch:(unsigned)count;
-(void)setObjectArray:(NSArray*)objects;
-(void)setQualifier:(EOQualifier*)qualifier_;
-(BOOL)setSelectionIndexes:(NSArray*)selection;
-(void)setSelectsFirstObjectAfterFetch:(BOOL)flag;
-(void)setSortOrdering:(NSArray*)orderings;
-(void)setValidatesChangesImmediately:(BOOL)flag;
-(NSArray*)sortOrdering;
-(void)updateDisplayedObjects;
-(BOOL)validatesChangesImmediately;

/*
By Delegate

-(void)displayGroup:(GSWDisplayGroup*)displayGroup_
createObjectFailedForDataSource:(id)dataSource_;

-(void)displayGroup:(GSWDisplayGroup*)displayGroup_
	didDeleteObject:(id)object_;

-(void)displayGroup:(GSWDisplayGroup*)displayGroup_
	didFetchObjects:(NSArray*)objects;

-(void)displayGroup:(GSWDisplayGroup*)displayGroup_
	didInsertObject:object_;

-(void)displayGroup:(GSWDisplayGroup*)displayGroup_
		didSetValue:(id)value
		  forObject:(id)object_ key:(NSString*)key;

-(NSArray*)displayGroup:(GSWDisplayGroup*)displayGroup_
 displayArrayForObjects:(NSArray*)objects;

-(BOOL)displayGroup:(GSWDisplayGroup*)displayGroup_
shouldChangeSelectionToIndexes:(NSArray*)newIndexes;

-(BOOL)displayGroup:(GSWDisplayGroup*)displayGroup_
 shouldInsertObject:object_
			atIndex:(unsigned)index_;

-(BOOL)displayGroup:(GSWDisplayGroup*)displayGroup_
shouldRedisplayForEditingContextChangeNotification:(NSNotification*)notification_;

-(BOOL)displayGroup:(GSWDisplayGroup*)displayGroup_
shouldRefetchForInvalidatedAllObjectsNotification:(NSNotification*)notification_;

-(void)displayGroupDidChangeDataSource:(GSWDisplayGroup*)displayGroup_;
-(void)displayGroupDidChangeSelectedObjects:(GSWDisplayGroup*)displayGroup_;
-(void)displayGroupDidChangeSelection:(GSWDisplayGroup*)displayGroup_;
-(BOOL)displayGroupShouldFetch:(GSWDisplayGroup*)displayGroup_;
*/

@end
#endif //_GSWDisplayGroup_h__