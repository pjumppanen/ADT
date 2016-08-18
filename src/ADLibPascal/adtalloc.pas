//  ----------------------------------------------------------------------------
//  ADT - automatic differentiation through translation
//  ----------------------------------------------------------------------------
//  Software for the generation of auto-differentiated code using TAPENADE.
//
//  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
//  ORGANISATION (CSIRO), Australia.
//  All rights reserved.
//
//  This file is part of ADT.  The full ADT copyright notice, including
//  terms governing use, modification, and redistribution, is contained in
//  the file COPYING. COPYING can be found at the root of the source code
//  distribution tree;
//  ----------------------------------------------------------------------------
//  File:
//    adtalloc.pas
//
//  Purpose:
//    This file implements classes for allocating trackable memory objects. This
//    code would have normally resided in adtarrays.pas but because of a
//    bug in the implementation of generics it cannot. Because of that bug
//    you can only specialize TMap within a program unit.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------
{$mode objfpc}{$H+}
Unit adtalloc;

interface

uses
  Classes,
  SysUtils,
  gset,
  gmap,
  adtcommon;

type

  //  ----------------------------------------------------------------------------
  //  AdtUserDestroyCallback type definition
  //  ----------------------------------------------------------------------------
  AdtUserDestroyCallback = procedure (pData : pchar);


  //  ----------------------------------------------------------------------------
  //  enum AdtAllocType
  //  ----------------------------------------------------------------------------
  PAdtAllocType = ^AdtAllocType;
  AdtAllocType  = (AdtAllocType_ARRAY,
                   AdtAllocType_STACK,
                   AdtAllocType_UNSPECIFIED);


  //  ----------------------------------------------------------------------------
  //  struct AdtAllocRecord
  //  ----------------------------------------------------------------------------
  AdtAllocRecord = record
    Callback    : AdtUserDestroyCallback;
    AllocType   : AdtAllocType;
    IsOurBlock  : boolean;
    BlockOffset : longint;
    BlockPtr    : pchar;
    BlockSize   : longint;
    UserPtr     : pchar;
    UserSize    : longint;
    LockCount   : longint;
  end;


  //  ----------------------------------------------------------------------------
  //  Mappings of AdtAllocRecord by pchar
  //  ----------------------------------------------------------------------------
  AdtAllocRecordByCharPtrMap = specialize TMap<pchar, AdtAllocRecord, AdtLessPChar>;


  //  ----------------------------------------------------------------------------
  //  class AdtMemAllocator
  //  ----------------------------------------------------------------------------
  //  This class is used to manage allocate memory so it can be automatically
  //  freed without user intervention when used in an AdtDiff class context.
  //  ----------------------------------------------------------------------------
  AdtMemAllocator = class

  private
    AllocMap : AdtAllocRecordByCharPtrMap;

  protected
    function    free(var rAllocRecord : AdtAllocRecord) : boolean;overload;

  public
    constructor create();
    destructor  destroy() ; override;

    function    alloc(nSize : longint ;
                      nAllocType : AdtAllocType ;
                      nBlockOffset : longint = longint(0) ;
                      pCallback : AdtUserDestroyCallback = nil ;
                      ppUserPtr : ppchar = nil ;
                      nUserSize : longint = longint(0) ;
                      pExisting : pchar = nil) : pchar;

    function    blockPtr(pOffsetBlock : pchar ;
                         pBlockSize : plongint = nil ;
                         pAllocType : PAdtAllocType = nil) : pchar;

    function    userPtr(pOffsetBlock : pchar ;
                        pUserSize : plongint = nil) : pchar;

    function    lock(pOffsetBlock : pchar) : boolean;
    function    free(pOffsetBlock : pchar) : boolean;overload;
    procedure   free();overload;
  end;


implementation

//  ----------------------------------------------------------------------------
//  AdtMemAllocator method implementations
//  ----------------------------------------------------------------------------
function AdtMemAllocator.free(var rAllocRecord : AdtAllocRecord) : boolean;overload;

var
  bFreed : boolean;

begin
  bFreed := false;

  rAllocRecord.LockCount := rAllocRecord.LockCount - 1;

  if (rAllocRecord.LockCount = 0) then
  begin
    if ((rAllocRecord.IsOurBlock) and (rAllocRecord.BlockPtr <> nil)) then
    begin
      freeMem(rAllocRecord.BlockPtr);
      rAllocRecord.BlockPtr := nil;
    end;

    if (rAllocRecord.UserPtr <> nil) then
    begin
      if (rAllocRecord.Callback <> nil) then
      begin
        rAllocRecord.Callback(rAllocRecord.UserPtr);
      end;

      freeMem(rAllocRecord.UserPtr);
      rAllocRecord.UserPtr := nil;
    end;

    bFreed := true;
  end;

  free := bFreed;
end;


//  ----------------------------------------------------------------------------

constructor AdtMemAllocator.create();

begin
  AllocMap := AdtAllocRecordByCharPtrMap.Create();
end;

//  ----------------------------------------------------------------------------

destructor  AdtMemAllocator.destroy();

begin
  free();
  AllocMap.destroy();
end;

//  ----------------------------------------------------------------------------

function AdtMemAllocator.alloc(nSize : longint ;
                               nAllocType : AdtAllocType ;
                               nBlockOffset : longint = longint(0) ;
                               pCallback : AdtUserDestroyCallback = nil ;
                               ppUserPtr : ppchar = nil ;
                               nUserSize : longint = longint(0) ;
                               pExisting : pchar = nil) : pchar;

var
  pOffsetBlock  : pchar;
  AllocRecord   : AdtAllocRecord;

begin
  pOffsetBlock := nil;

  AllocRecord.AllocType   := nAllocType;
  AllocRecord.Callback    := pCallback;
  AllocRecord.BlockOffset := nBlockOffset;
  AllocRecord.BlockSize   := 0;
  AllocRecord.UserSize    := 0;
  AllocRecord.LockCount   := 1;

  if (nSize = 0) then
  begin
    AllocRecord.IsOurBlock := false;
    AllocRecord.BlockPtr   := pExisting;
  end
  else
  begin
    AllocRecord.IsOurBlock := true;

    if (nSize <> 0) then
    begin
      AllocRecord.BlockPtr  := getMem(nSize);
      AllocRecord.BlockSize := nSize;
    end
    else
    begin
      AllocRecord.BlockPtr  := nil;
    end;
  end;

  if (nUserSize <> 0) then
  begin
    AllocRecord.UserPtr   := getMem(nUserSize);
    AllocRecord.UserSize  := nUserSize;
  end
  else
  begin
    AllocRecord.UserPtr := nil;
  end;

  if (AllocRecord.BlockPtr <> nil) then
  begin
    // The nIndexingOffset parameter is required for being able to track the
    // existence of arrays with non-zero bases because the pointer the user
    // code will have access to and pass to the free() method will be offset.
    // Hence we calculate what the offset pointer would be and use that as
    // the index into the map of the allocated pointer so we can later free it.
    pOffsetBlock := AllocRecord.BlockPtr + nBlockOffset;

    if (AllocMap.find(pOffsetBlock) = nil) then
    begin
      AllocMap[pOffsetBlock] := AllocRecord;
    end
    else
    begin
      raise Exception.Create('Existing memory block already referrenced by a different allocation record.');
    end;
  end;

  if (ppUserPtr <> nil) then
  begin
    ppUserPtr^ := AllocRecord.UserPtr;
  end;

  alloc := pOffsetBlock;
end;

//  ----------------------------------------------------------------------------

function AdtMemAllocator.blockPtr(pOffsetBlock : pchar ;
                                  pBlockSize : plongint = nil ;
                                  pAllocType : PAdtAllocType = nil) : pchar;

var
  pBlockPtr : pchar;
  Iter      : AdtAllocRecordByCharPtrMap.TIterator;

begin
  pBlockPtr := nil;

  if (pOffsetBlock <> nil) then
  begin
    Iter := AllocMap.find(pOffsetBlock);

    if (Iter <> nil) then
    begin
      pBlockPtr := Iter.Value.BlockPtr;

      if (pBlockSize <> nil) then
      begin
        pBlockSize^ := Iter.Value.BlockSize;
      end;

      if (pAllocType <> nil) then
      begin
        pAllocType^ := Iter.Value.AllocType;
      end;

      Iter.destroy();
    end;
  end;

  blockPtr := pBlockPtr;
end;

//  ----------------------------------------------------------------------------

function AdtMemAllocator.userPtr(pOffsetBlock : pchar ;
                                 pUserSize : plongint = nil) : pchar;

var
  pUserPtr  : pchar;
  Iter      : AdtAllocRecordByCharPtrMap.TIterator;

begin
  pUserPtr := nil;

  if (pOffsetBlock <> nil) then
  begin
    Iter := AllocMap.find(pOffsetBlock);

    if (Iter <> nil) then
    begin
      pUserPtr := Iter.Value.UserPtr;

      if (pUserSize <> nil) then
      begin
        pUserSize^ := Iter.Value.UserSize;
      end;

      Iter.destroy();
    end;
  end;

  userPtr := pUserPtr;
end;

//  ----------------------------------------------------------------------------

function AdtMemAllocator.lock(pOffsetBlock : pchar) : boolean;

var
  bLocked     : boolean;
  AllocRecord : AdtAllocRecord;
  Iter        : AdtAllocRecordByCharPtrMap.TIterator;

begin
  bLocked := false;

  if (pOffsetBlock <> nil) then
  begin
    Iter := AllocMap.find(pOffsetBlock);

    if (Iter <> nil) then
    begin
      AllocRecord           := Iter.Value;
      AllocRecord.LockCount := AllocRecord.LockCount + 1;
      AllocMap[Iter.Key]    := AllocRecord;

      bLocked := true;

      Iter.destroy();
    end;
  end;

  lock := bLocked;
end;

//  ----------------------------------------------------------------------------

function AdtMemAllocator.free(pOffsetBlock : pchar) : boolean;overload;

var
  bFreed      : boolean;
  AllocRecord : AdtAllocRecord;
  Iter        : AdtAllocRecordByCharPtrMap.TIterator;

begin
  bFreed := false;

  if (pOffsetBlock <> nil) then
  begin
    Iter := AllocMap.find(pOffsetBlock);

    if (Iter <> nil) then
    begin
      AllocRecord := Iter.Value;

      if (free(AllocRecord)) then
      begin
        AllocMap.delete(pOffsetBlock);
      end;

      Iter.destroy();
    end;
  end;

  free := bFreed;
end;

//  ----------------------------------------------------------------------------

procedure AdtMemAllocator.free();overload;

var
  Iter        : AdtAllocRecordByCharPtrMap.TIterator;
  AllocRecord : AdtAllocRecord;

begin
  Iter := AllocMap.Min();

  if (Iter <> nil) then
  begin
    repeat
      AllocRecord := Iter.Value;

      free(AllocRecord);
    until not Iter.Next();

    Iter.Destroy();
  end;

  AllocMap.Destroy();

  AllocMap := AdtAllocRecordByCharPtrMap.Create();
end;


end.
