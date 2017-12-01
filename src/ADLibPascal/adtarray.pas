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
//    adtarray.pas
//
//  Purpose:
//    This file implements classes for use in Auto-differentiation code
//    implemented in Pascal.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------
{$mode objfpc}{$H+}
Unit adtarray;

interface

uses
  Classes,
  SysUtils,
  gset,
  gmap,
  gutil,
  adtcommon,
  adtalloc,
  adtalias;

const
  DEFAULT_STACK_SIZE = 1024;

type
  //  ----------------------------------------------------------------------------
  //  record AdtArrayCoord
  //  ----------------------------------------------------------------------------
  //  This record describes the ordinate properties of an array index
  //  ----------------------------------------------------------------------------
  PAdtArrayCoord  = ^AdtArrayCoord;
  AdtArrayCoord   = Record
    IndexBase : longint;
    Size      : longint;
  end;


  //  ----------------------------------------------------------------------------
  // Forward declaration
  //  ----------------------------------------------------------------------------
  AdtArrayPlanActor   = class;
  PAdtArrayPlanActor  = ^AdtArrayPlanActor;

  //  ----------------------------------------------------------------------------
  //  struct AdtArrayInfo
  //  ----------------------------------------------------------------------------
  //  This structure contains information describing the allocated array.
  //  ----------------------------------------------------------------------------
  PAdtArrayInfo = ^AdtArrayInfo;
  AdtArrayInfo  = record
    LookupSize  : longint;
    BlockSize   : longint;
    SizeOf      : longint;
    BlockPtr    : pchar;
    Existing    : pchar;
    VarType     : AdtVarType;
    Actor       : AdtArrayPlanActor;
  end;


  //  ----------------------------------------------------------------------------
  //  Mappings of AdtArrayPlanActor by AnsiString
  //  ----------------------------------------------------------------------------
  AdtArrayPlanActorByCharPtrMap = specialize TMap<AnsiString, AdtArrayPlanActor, AdtLessAnsiString>;


  //  ----------------------------------------------------------------------------
  //  class AdtArrayPlanActor
  //  ----------------------------------------------------------------------------
  //  This class describes the ordinate properties of the indices making up an
  //  entire array and can use this information to create such an array. The array
  //  plan can cope with ragged arrays. It can also create array aliases in the
  //  case of having a multi-dimensional array in a contiguous memory block which
  //  we would like to access using normal array indexing syntax.
  //
  //  Calling the create method with pExisting defined as the memory block and the
  //  AdtArrayPlanActor initialised according to the actual array layout will
  //  generate a lookup for that array and return a pointer to that lookup.
  //
  //  AdtArrayPlanActor is not mean't to be used directly but is delegated to by
  //  instances of AdtArrayPlan. We have an inner AdtArrayPlanActor class so that
  //  the created array can maintain a reference counted instance of the actor
  //  class in it's memory for future reference in case, for example, the user
  //  would like to know about some property of the array, or copy it entirely.
  //  ----------------------------------------------------------------------------
  AdtArrayPlanActor = class

  private
    AliasMap              : AdtAliasArrayByCharPtrMap;
    CacheMap              : AdtArrayPlanActorByCharPtrMap ; static;
    CacheUsed             : boolean ; static;

  protected
    NextRagged            : PAdtArrayPlanActor;
    Next                  : AdtArrayPlanActor;
    _Coord                : AdtArrayCoord;
    _NumberOfCoOrdinates  : longint;
    _IsCached             : boolean;
    _LookupSize           : longint;
    _ArrayCount           : longint;
    _LockCount            : longint;

  protected
    function    findLookupSize() : longint;
    function    arraySize(const nSizeOf : longint) : longint ; inline;

    function    initialiseLookupInner(var pLookup : ppchar ;
                                      var pData : pchar ;
                                      nSizeOf : longint ;
                                      const pStartAddress : pchar ;
                                      const pEndAddress : pchar ;
                                      const pDataStartAddress : pchar ;
                                      const pDataEndAddress : pchar) : boolean;

    procedure   initialiseLookup(pArray : pchar ;
                                 nSizeOf,
                                 nLookupSize,
                                 nDataSize : longint;
                                 pExisting : pchar = nil);

    procedure   destroyNext();
    procedure   destroyNextRagged();
    procedure   copyNext(const pNext : AdtArrayPlanActor);
    procedure   copyNextRagged(const pNextRagged : PAdtArrayPlanActor);

    procedure   notifyDestroy(pArrayInfo : PAdtArrayInfo);

  public
    constructor create();
    constructor create(pCoords : PAdtArrayCoord ;
                       nCoords : longint ;
                       bTranspose : boolean = false ;
                       bSupressUpdate : boolean = false);

    constructor create(const rCopy : AdtArrayPlanActor);

    destructor  destroy() ; override;

    function    initialise(pCoords : PAdtArrayCoord;
                           nCoords : longint;
                           bTranspose : boolean = false;
                           bSupressUpdate : boolean = false) : boolean;

    function    beginRagged(var rCoord : AdtArrayCoord) : boolean;
    function    beginRagged(var Context : AdtArrayPlanActor ; var rCoord : AdtArrayCoord) : boolean;
    function    addArrayPlanActor(Actor : AdtArrayPlanActor ; nIndex : longint) : boolean;
    procedure   updateCoOrdinates(Context : AdtArrayPlanActor);
    procedure   endRagged();

    function    isCached() : boolean ; inline;

    function    create(var rAllocator : AdtMemAllocator ;
                       nVarType : AdtVarType ;
                       pExisting : pchar = nil) : pchar;

    function    createTransposed(var rAllocator : AdtMemAllocator ;
                                 nVarType : AdtVarType ;
                                 pExisting : pchar = nil) : pchar;

    function    existing(nVarType : AdtVarType ;
                         pExisting : pchar) : pchar;

    procedure   assign(var rCopy : AdtArrayPlanActor);
    function    eq(var rCopy : AdtArrayPlanActor) : boolean;

    function    isRegular() : boolean;
    function    isRagged() : boolean ; inline;

    function    numberOfCoOrdinates() : longint ; inline;

    function    indexArray(pIndices : plongint ;
                           nIndices : longint ;
                           pArray : pchar ;
                           nSizeOf : longint ;
                           ppActor : PAdtArrayPlanActor = nil) : pchar;

    function    getCoords(pCoords : PAdtArrayCoord ; nCoords : longint; bReversed : boolean = false) : longint;

    function    coord(nCoord : longint) : PAdtArrayCoord ; inline;
    function    coord(pIndices : plongint ;
                      nIndices : longint ;
                      ppActor : PAdtArrayPlanActor = nil) : PAdtArrayCoord;

    function    lookupSize() : longint ; inline;
    function    arrayCount() : longint ; inline;

    procedure   lock() ; inline;
    function    unlock() : boolean;
  end;


  //  ----------------------------------------------------------------------------
  //  Bounds checking context
  //  ----------------------------------------------------------------------------
  CHECK_CONTEXT = AdtArrayPlanActor;


  //  ----------------------------------------------------------------------------
  //  Ragged Array creation context
  //  ----------------------------------------------------------------------------
  RAGGED_CONTEXT = AdtArrayPlanActor;


  //  ----------------------------------------------------------------------------
  //  class AdtArrayPlan
  //  ----------------------------------------------------------------------------
  //  We use an instance of this class to create arrays of a given size and shape
  //  ----------------------------------------------------------------------------
  AdtArrayPlan = class

  protected
    Actor : AdtArrayPlanActor;

  public
    constructor create();
    constructor create(nBaseIndex, nSize : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3,
                       nBaseIndex4, nSize4 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3,
                       nBaseIndex4, nSize4,
                       nBaseIndex5, nSize5 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3,
                       nBaseIndex4, nSize4,
                       nBaseIndex5, nSize5,
                       nBaseIndex6, nSize6 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3,
                       nBaseIndex4, nSize4,
                       nBaseIndex5, nSize5,
                       nBaseIndex6, nSize6,
                       nBaseIndex7, nSize7 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3,
                       nBaseIndex4, nSize4,
                       nBaseIndex5, nSize5,
                       nBaseIndex6, nSize6,
                       nBaseIndex7, nSize7,
                       nBaseIndex8, nSize8 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3,
                       nBaseIndex4, nSize4,
                       nBaseIndex5, nSize5,
                       nBaseIndex6, nSize6,
                       nBaseIndex7, nSize7,
                       nBaseIndex8, nSize8,
                       nBaseIndex9, nSize9 : longint);

    constructor create(nBaseIndex1, nSize1,
                       nBaseIndex2, nSize2,
                       nBaseIndex3, nSize3,
                       nBaseIndex4, nSize4,
                       nBaseIndex5, nSize5,
                       nBaseIndex6, nSize6,
                       nBaseIndex7, nSize7,
                       nBaseIndex8, nSize8,
                       nBaseIndex9, nSize9,
                       nBaseIndex10, nSize10 : longint);

    constructor create(rCopy : AdtArrayPlan);
    destructor destroy() ; override;

    procedure initialise(nBaseIndex, nSize : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3,
                         nBaseIndex4, nSize4 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3,
                         nBaseIndex4, nSize4,
                         nBaseIndex5, nSize5 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3,
                         nBaseIndex4, nSize4,
                         nBaseIndex5, nSize5,
                         nBaseIndex6, nSize6 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3,
                         nBaseIndex4, nSize4,
                         nBaseIndex5, nSize5,
                         nBaseIndex6, nSize6,
                         nBaseIndex7, nSize7 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3,
                         nBaseIndex4, nSize4,
                         nBaseIndex5, nSize5,
                         nBaseIndex6, nSize6,
                         nBaseIndex7, nSize7,
                         nBaseIndex8, nSize8 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3,
                         nBaseIndex4, nSize4,
                         nBaseIndex5, nSize5,
                         nBaseIndex6, nSize6,
                         nBaseIndex7, nSize7,
                         nBaseIndex8, nSize8,
                         nBaseIndex9, nSize9 : longint);

    procedure initialise(nBaseIndex1, nSize1,
                         nBaseIndex2, nSize2,
                         nBaseIndex3, nSize3,
                         nBaseIndex4, nSize4,
                         nBaseIndex5, nSize5,
                         nBaseIndex6, nSize6,
                         nBaseIndex7, nSize7,
                         nBaseIndex8, nSize8,
                         nBaseIndex9, nSize9,
                         nBaseIndex10, nSize10 : longint);

    function  beginRagged(var Context : AdtArrayPlanActor ; nBaseIndex, nSize : longint) : boolean;
    function  addArrayPlan(Context : AdtArrayPlanActor; var rArrayPlan : AdtArrayPlan; nIndex : longint) : boolean;
    procedure endRagged(Context : AdtArrayPlanActor);

    function  beginRagged(nBaseIndex, nSize : longint) : boolean;
    function  addArrayPlan(rArrayPlan : AdtArrayPlan; nIndex : longint) : boolean;
    procedure endRagged();

    procedure assign(rCopy : AdtArrayPlan);
    function  eq(rArrayPlan : AdtArrayPlan) : boolean;

    function  numberOfCoOrdinates() : longint ; inline;
    function  lookupSize() : longint ; inline;

    {$INCLUDE adtarrayplan_decl.inc}
  end;


  //  ----------------------------------------------------------------------------
  //  AdtStackInfo record
  //  ----------------------------------------------------------------------------
  PAdtStackInfo = ^AdtStackInfo;
  AdtStackInfo = record
    StackSize : longint;
    SizeOf    : longint;
    VarType   : AdtVarType;
  end;


  //  ----------------------------------------------------------------------------
  //  class AdtArrays
  //  ----------------------------------------------------------------------------
  //  This class is a base class for auto-differentiation classes. It has an
  //  instance of AdtMemAllocator to be used to allocate arrays used in the AD
  //  work. Any allocated arrays will thus be freed automatically when the
  //  instance of AdtArrays is freed.
  //  ----------------------------------------------------------------------------
  PAdtArrays = ^AdtArrays;
  AdtArrays = class

  protected
    _MemAllocator  : AdtMemAllocator;
    IsShallowCopy  : boolean;

  protected
    function createStack(var pArray : pchar;
                         nInitialSize : longint;
                         nVarType : AdtVarType) : boolean;

    procedure copyAndGrowStack(var pArray : pchar;
                               pCurrentStackInfo : PAdtStackInfo;
                               nMinSizeNeeded : longint);

    procedure growStack(var pArray : pchar; nIndexNeeded : longint) ; inline;

  public
    DefaultStackSize : longint; static;

    constructor create(); overload;
    constructor create(pCopy : PAdtArrays; bShallow : boolean = true); overload;
    destructor  destroy(); override; overload;

    function stackInfo(pStack : pchar) : PAdtStackInfo ; inline;
    function memAllocator() : AdtMemAllocator ; inline;

    {$INCLUDE adtarrays_decl.inc}
  end;


  //  ----------------------------------------------------------------------------
  //  AdtArrayCoord method declarations
  //  ----------------------------------------------------------------------------
  procedure appendKey(var rCoord : AdtArrayCoord ; var rKey : AnsiString ; const bWithPrefix : boolean);


  //  ----------------------------------------------------------------------------
  //  AdtArrayInfo method declarations
  //  ----------------------------------------------------------------------------
  procedure zero(var ArrayInfo : AdtArrayInfo); inline ; overload;
  procedure xcopy(var ArrayInfo : AdtArrayInfo ; const pSrcArrayInfo : PAdtArrayInfo) ; overload;
  function  firstData(var ArrayInfo : AdtArrayInfo) : pchar; inline;
  function  lengthOfData(var ArrayInfo : AdtArrayInfo) : longint; inline;


  //  ----------------------------------------------------------------------------
  //  static methods. Argh!! Free Pascal doesn't implement static methods as truly
  //  static. They still have a this pointer but you can't see it which means
  //  you can't call a static method without an object instance which in my book
  //  then means it isn't static!
  //  ----------------------------------------------------------------------------
  procedure check(var pContext : AdtArrayPlanActor ;
                  var rAllocator : AdtMemAllocator ;
                  pArray : pchar ;
                  sArrayName,
                  sFileName, pFileLine : AnsiString ;
                  nIndices : longint ;
                  bThrowException : boolean ;
                  Args: Array of const);

  function  AdtArrayPlanActor_arrayInfo(var rAllocator : AdtMemAllocator ;
                                        pArray : pchar) : PAdtArrayInfo;

  procedure AdtArrayPlanActor_destroyArrayInfo(pData : pchar);

  function  AdtArrayPlanActor_createSlice(var rAllocator : AdtMemAllocator ;
                                          pArray : pchar ;
                                          pIndices : plongint ;
                                          nIndices : longint) : pchar;

  function  AdtArrayPlanActor_createSameShape(var rAllocator : AdtMemAllocator ;
                                              pRefArray : pchar) : pchar;

  procedure AdtArrayPlanActor_destroy(var rAllocator : AdtMemAllocator ; pArray : pchar) ; inline;

  procedure AdtArrayPlanActor_R_to_ADlib(var rAllocator : AdtMemAllocator ;
                                         pArraySrc : pchar ;
                                         pArrayDest : pchar);

  procedure AdtArrayPlanActor_ADlib_to_R(var rAllocator : AdtMemAllocator ;
                                         pArraySrc : pchar ;
                                         pArrayDest : pchar);


  function  AdtArrayPlanActor_createArrayPlanActor(const pCoords : PAdtArrayCoord;
                                                   nCoords : longint) : AdtArrayPlanActor;

  function  AdtArrayPlanActor_cachedArrayPlanActor(const pCoords : PAdtArrayCoord ;
                                                   nCoords : longint ;
                                                   bLock : boolean ;
                                                   bTranspose : boolean = false) : AdtArrayPlanActor;

  procedure AdtArrayPlanActor_flush();

  {$INCLUDE adtarray_decl.inc}


implementation

  //  ----------------------------------------------------------------------------
  //  AdtArrayCoord method implementations
  //  ----------------------------------------------------------------------------
  procedure appendKey(var rCoord : AdtArrayCoord ; var rKey : AnsiString ; const bWithPrefix : boolean);

  begin
    if (bWithPrefix) then
    begin
      AppendStr(rKey,',');
    end;

    AppendStr(rKey,IntToStr(rCoord.IndexBase));
    AppendStr(rKey,':');
    AppendStr(rKey,IntToStr(rCoord.Size));
  end;


  //  ----------------------------------------------------------------------------
  //  AdtArrayInfo method implementations
  //  ----------------------------------------------------------------------------
  procedure zero(var ArrayInfo : AdtArrayInfo); inline ; overload;

  begin
    FillChar(ArrayInfo.BlockPtr[ArrayInfo.LookupSize], SizeOf(char), 0);
  end;

  //  ----------------------------------------------------------------------------

  procedure xcopy(var ArrayInfo : AdtArrayInfo ; const pSrcArrayInfo : PAdtArrayInfo) ; overload;

  begin
    if ((ArrayInfo.Actor.eq(pSrcArrayInfo^.Actor)) and
        (ArrayInfo.SizeOf = pSrcArrayInfo^.SizeOf)) then
    begin
      Move(pSrcArrayInfo^.BlockPtr[pSrcArrayInfo^.LookupSize],
           ArrayInfo.BlockPtr[ArrayInfo.LookupSize],
           (ArrayInfo.BlockSize - ArrayInfo.LookupSize) * SizeOf(char));
    end
    else
    begin
      raise Exception.Create('Incompatible array x_copy');
    end;
  end;

  //  ----------------------------------------------------------------------------

  function firstData(var ArrayInfo : AdtArrayInfo) : pchar; inline;

  begin
    firstData := ArrayInfo.BlockPtr + ArrayInfo.LookupSize;
  end;

  //  ----------------------------------------------------------------------------

  function lengthOfData(var ArrayInfo : AdtArrayInfo) : longint; inline;

  begin
    lengthOfData := ArrayInfo.BlockSize - ArrayInfo.LookupSize;
  end;


  //  ----------------------------------------------------------------------------
  //  AdtArrayPlanActor method implementations
  //  ----------------------------------------------------------------------------
  function AdtArrayPlanActor.findLookupSize() : longint;

  var
    cn : longint;

  begin
    // Here we figure out the size of the lookup table needed to index the
    // multi-dimensional array as a contiguous block.
    _LookupSize := 0;
    _ArrayCount := 0;

    if (_NumberOfCoOrdinates > 1) then
    begin
      _LookupSize := _Coord.Size * SizeOf(pchar);

      if (Next <> nil) then
      begin
        _LookupSize := _LookupSize + _Coord.Size * Next.findLookupSize();
        _ArrayCount := _Coord.Size * Next._ArrayCount;
      end
      else if (NextRagged <> nil) then
      begin
        for cn := 0 to _Coord.Size - 1 do
        begin
          _LookupSize := _LookupSize + NextRagged[cn].findLookupSize();
          _ArrayCount := _ArrayCount + NextRagged[cn]._ArrayCount;
        end;
      end;
    end
    else
    begin
      _ArrayCount := _Coord.Size;
    end;

    findLookupSize := _LookupSize;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.arraySize(const nSizeOf : longint) : longint ; inline;

  begin
    arraySize := nSizeOf * _ArrayCount;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.initialiseLookupInner(var pLookup : ppchar ;
                                                   var pData : pchar ;
                                                   nSizeOf : longint ;
                                                   const pStartAddress : pchar ;
                                                   const pEndAddress : pchar ;
                                                   const pDataStartAddress : pchar ;
                                                   const pDataEndAddress : pchar) : boolean;

  var
    cn              : longint;
    pLastLookup     : ppchar;
    pThisLookup     : ppchar;
    bIsLookupLevel  : boolean;

  begin
    // If we are at the bottom of the indexing hierachy (ie at the data level)
    // set bIsLookupLevel to false, otherwise true.
    bIsLookupLevel := false;

    if (_NumberOfCoOrdinates > 1) then
    begin
      pThisLookup := pLookup;

      // Reserve space for this level of lookup
      pLookup := pLookup + _Coord.Size;

      if (Next <> nil) then
      begin
        for cn := 0 to _Coord.Size - 1 do
        begin
          // Save the root location for the lookup being pointed to by this entry
          pLastLookup := pLookup;

          if (Next.initialiseLookupInner(pLookup,
                                         pData,
                                         nSizeOf,
                                         pStartAddress,
                                         pEndAddress,
                                         pDataStartAddress,
                                         pDataEndAddress)) then
          begin
            // Point this entry to the next level of lookup. Alow for Index base
            // other than zero
            pThisLookup^ := (pchar(pLastLookup)) - (Next._Coord.IndexBase * SizeOf(pchar));

            assert(((pchar(pThisLookup)) >= pStartAddress) and ((pchar(pThisLookup)) <= pEndAddress));
            assert(((pchar(pLastLookup)) >= pStartAddress) and ((pchar(pLastLookup)) <= pEndAddress));
          end
          else
          begin
            // Point this entry to the next level of data. Alow for Index base
            // other than zero
            pThisLookup^ := pData - (Next._Coord.IndexBase * nSizeOf);

            assert((((pchar(pThisLookup)) >= pStartAddress) and ((pchar(pThisLookup)) <= pEndAddress)) or
                   (((pchar(pThisLookup)) >= pDataStartAddress) and ((pchar(pThisLookup)) <= pDataEndAddress)));
            assert((pData >= pDataStartAddress) and (pData <= pDataEndAddress));

            pData := pData + (Next._Coord.Size * nSizeOf);
          end;

          pThisLookup := pThisLookup + 1;
        end;
      end
      else if (NextRagged <> nil) then
      begin
        for cn := 0 to _Coord.Size - 1 do
        begin
          pLastLookup := pLookup;

          if (NextRagged[cn].initialiseLookupInner(pLookup,
                                                   pData,
                                                   nSizeOf,
                                                   pStartAddress,
                                                   pEndAddress,
                                                   pDataStartAddress,
                                                   pDataEndAddress)) then
          begin
            // Point this entry to the next level of lookup. Alow for Index base
            // other than zero
            pThisLookup^ := (pchar(pLastLookup)) - (NextRagged[cn]._Coord.IndexBase * SizeOf(pchar));

            assert(((pchar(pThisLookup)) >= pStartAddress) and ((pchar(pThisLookup)) <= pEndAddress));
            assert(((pchar(pLastLookup)) >= pStartAddress) and ((pchar(pLastLookup)) <= pEndAddress));
          end
          else
          begin
            // Point this entry to the next level of data. Alow for Index base
            // other than zero
            pThisLookup^ := pData - (NextRagged[cn]._Coord.IndexBase * nSizeOf);

            assert((((pchar(pThisLookup)) >= pStartAddress) and ((pchar(pThisLookup)) <= pEndAddress)) or
                   (((pchar(pThisLookup)) >= pDataStartAddress) and ((pchar(pThisLookup)) <= pDataEndAddress)));
            assert((pData >= pDataStartAddress) and (pData <= pDataEndAddress));

            pData := pData + (NextRagged[cn]._Coord.Size * nSizeOf);
          end;

          pThisLookup := pThisLookup + 1;
        end;
      end;

      bIsLookupLevel := true;
    end;

    initialiseLookupInner := bIsLookupLevel;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.initialiseLookup(pArray : pchar ;
                                               nSizeOf,
                                               nLookupSize,
                                               nDataSize : longint;
                                               pExisting : pchar = nil);

  var
    pLookup : ppchar;
    pData   : pchar;

  begin
    // Here we initialise the lookup to point to the correct locations in the
    // multi-dimensional array as a contiguous block. If the data is stored
    // externally in a seperate block of memory, that block will be pointed to
    // by pExisting and we index into that block instead.
    if (_NumberOfCoOrdinates > 1) then
    begin
      pLookup := ppchar(pArray);

      if (pExisting <> nil) then
        pData := pchar(pExisting)
      else
        pData := pArray + nLookupSize;

      initialiseLookupInner(pLookup,
                            pData,
                            nSizeOf,
                            pArray,
                            pArray + nLookupSize - SizeOf(pchar),
                            pData,
                            pData + nDataSize - nSizeOf);
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.destroyNext();

  begin
    _LookupSize := 0;
    _ArrayCount := 0;

    if (Next <> nil) then
    begin
      Next.unlock();

      Next := nil;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.destroyNextRagged();

  var
    cn : longint;

  begin
    _LookupSize := 0;
    _ArrayCount := 0;

    if (NextRagged <> nil) then
    begin
      for cn := 0 to _Coord.Size - 1 do
      begin
        if (NextRagged[cn] <> nil) then
        begin
          NextRagged[cn].unlock();

          NextRagged[cn] := nil;
        end;
      end;

      freeMem(NextRagged);

      NextRagged := nil;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.copyNext(const pNext : AdtArrayPlanActor);

  begin
    destroyNext();

    if (pNext <> nil) then
    begin
      Next := AdtArrayPlanActor.create(pNext);
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.copyNextRagged(const pNextRagged : PAdtArrayPlanActor);

  var
    cn : longint;

  begin
    destroyNextRagged();

    if ((pNextRagged <> nil) and (_Coord.Size > 0)) then
    begin
      NextRagged := PAdtArrayPlanActor(getMem(SizeOf(AdtArrayPlanActor) * _Coord.Size));

      if (NextRagged <> nil) then
      begin
        for cn := 0 to _Coord.Size do
        begin
          NextRagged[cn] := AdtArrayPlanActor.create(pNextRagged[cn]);
        end;
      end;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.notifyDestroy(pArrayInfo : PAdtArrayInfo);

  begin
    if ((pArrayInfo <> nil) and (pArrayInfo^.Existing <> nil)) then
    begin
      // Remove mapping of array from the plan actors map of existing arrays
      AliasMap.delete(pArrayInfo^.Existing);
    end;

    unlock();
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor_destroyArrayInfo(pData : pchar);

  var
    pArrayInfo : PAdtArrayInfo;

  begin
    pArrayInfo := PAdtArrayInfo(pData);

    if ((pArrayInfo <> nil) and (pArrayInfo^.Actor <> nil)) then
    begin
      pArrayInfo^.Actor.notifyDestroy(pArrayInfo);
    end;
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlanActor.create();

  begin
    _LockCount            := 1;
    Next                  := nil;
    NextRagged            := nil;
    _NumberOfCoOrdinates  := 0;
    _LookupSize           := 0;
    _ArrayCount           := 0;
    _IsCached             := false;
    _Coord.IndexBase      := 0;
    _Coord.Size           := 0;
    AliasMap              := AdtAliasArrayByCharPtrMap.create;
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlanActor.create(pCoords : PAdtArrayCoord ;
                     nCoords : longint ;
                     bTranspose : boolean = false ;
                     bSupressUpdate : boolean = false);

  begin
    _LockCount            := 1;
    Next                  := nil;
    NextRagged            := nil;
    _NumberOfCoOrdinates  := 0;
    _LookupSize           := 0;
    _ArrayCount           := 0;
    _IsCached             := false;
    _Coord.IndexBase      := 0;
    _Coord.Size           := 0;
    AliasMap              := AdtAliasArrayByCharPtrMap.create;

    initialise(pCoords, nCoords, bTranspose, bSupressUpdate);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlanActor.create(const rCopy : AdtArrayPlanActor);

  begin
    _LockCount            := 1;
    Next                  := nil;
    NextRagged            := nil;
    _NumberOfCoOrdinates  := 0;
    _Coord.IndexBase      := 0;
    _Coord.Size           := 0;
    AliasMap              := AdtAliasArrayByCharPtrMap.create;

    copyNext(rCopy.Next);
    copyNextRagged(rCopy.NextRagged);

    _LookupSize           := rCopy._LookupSize;
    _ArrayCount           := rCopy._ArrayCount;
    _IsCached             := false;
  end;

  //  ----------------------------------------------------------------------------

  destructor  AdtArrayPlanActor.destroy();

  begin
    destroyNext();
    destroyNextRagged();

    AliasMap.destroy();
  end;

  //  ----------------------------------------------------------------------------

  procedure check(var pContext : AdtArrayPlanActor ;
                  var rAllocator : AdtMemAllocator ;
                  pArray : pchar ;
                  sArrayName,
                  sFileName, pFileLine : AnsiString ;
                  nIndices : longint ;
                  bThrowException : boolean ;
                  Args: Array of const);

  var
    pInfo       : PAdtArrayInfo;
    cn          : longint;
    ix_index    : longint;
    ix_name     : longint;
    nIndex      : longint;
    pIndexName  : AnsiString;
    sBuffer     : AnsiString;
    pActor      : AdtArrayPlanActor;
    pCoord      : PAdtArrayCoord;

  begin
    if (pContext = nil) then
    begin
      pInfo := AdtArrayPlanActor_arrayInfo(rAllocator, pArray);

      if (pInfo <> nil) then
      begin
        pContext := pInfo^.Actor;
      end;
    end;

    if (pContext <> nil) then
    begin
      pActor := pContext;
      pCoord := @(pActor._Coord);

      assert(High(Args) + 1 = 2 * nIndices);

      for cn := 0 to nIndices - 1 do
      begin
        ix_index := 2 * cn;
        ix_name  := 2 * cn + 1;

        assert((Args[ix_index].vtype = vtInteger) and (Args[ix_name].vtype = vtAnsiString));

        nIndex      := Args[ix_index].VInteger;
        pIndexName  := AnsiString(Args[ix_name].VAnsiString);

        if (nIndex < pCoord^.IndexBase) then
        begin
          // Index too small
          sBuffer := 'Error in file ';

          AppendStr(sBuffer, sFileName);
          AppendStr(sBuffer, ' on line ');
          AppendStr(sBuffer, pFileLine);
          AppendStr(sBuffer, ' : Array "');
          AppendStr(sBuffer, sArrayName);
          AppendStr(sBuffer, '" index ');
          AppendStr(sBuffer, IntToStr(nIndex + 1));
          AppendStr(sBuffer, ' indexed with "');
          AppendStr(sBuffer, pIndexName);
          AppendStr(sBuffer, '" = ');
          AppendStr(sBuffer, IntToStr(nIndex));
          AppendStr(sBuffer, ' is too small. It must be greater than ');
          AppendStr(sBuffer, IntToStr(pCoord^.IndexBase - 1));
          AppendStr(sBuffer, '.');

          log_error(sBuffer);

          if (bThrowException) then
          begin
            raise Exception.Create(sBuffer);
          end;
          break;
        end
        else if (nIndex - pCoord^.IndexBase >= pCoord^.Size) then
        begin
          // Index too large
          sBuffer := 'Error in file ';

          AppendStr(sBuffer, sFileName);
          AppendStr(sBuffer, ' on line ');
          AppendStr(sBuffer, pFileLine);
          AppendStr(sBuffer, ' : Array "');
          AppendStr(sBuffer, sArrayName);
          AppendStr(sBuffer, '" index ');
          AppendStr(sBuffer, IntToStr(nIndex + 1));
          AppendStr(sBuffer, ' indexed with "');
          AppendStr(sBuffer, pIndexName);
          AppendStr(sBuffer, '" = ');
          AppendStr(sBuffer, IntToStr(nIndex));
          AppendStr(sBuffer, ' is too large. It must be less than ');
          AppendStr(sBuffer, IntToStr(pCoord^.IndexBase + pCoord^.Size));
          AppendStr(sBuffer, '.');

          log_error(sBuffer);

          if (bThrowException) then
          begin
            raise Exception.Create(sBuffer);
          end;
          break;
        end;

        // Go into next level of indexing
        if (pActor.Next <> nil) then
        begin
          pActor := pActor.Next;
        end
        else if (pActor.NextRagged <> nil) then
        begin
          pActor := pActor.NextRagged[nIndex - pCoord^.IndexBase];
        end;

        pCoord := @(pActor._Coord);
      end;
    end;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.initialise(pCoords : PAdtArrayCoord;
                                        nCoords : longint;
                                        bTranspose : boolean = false;
                                        bSupressUpdate : boolean = false) : boolean;

  var
    bInitialised  : boolean;
    pNextCoords   : PAdtArrayCoord;

  begin
    bInitialised := false;

    destroyNext();
    destroyNextRagged();

    _NumberOfCoOrdinates := 0;

    if ((pCoords <> nil) and (nCoords >= 1)) then
    begin
      _Coord               := pCoords^;
      _NumberOfCoOrdinates := nCoords;

      if (bTranspose) then
      begin
        pNextCoords := pCoords + nCoords - 1;
        _Coord      := pNextCoords^;

        if (nCoords > 1) then
        begin
          nCoords := nCoords - 1;
          Next    := AdtArrayPlanActor.create(pCoords, nCoords, bTranspose, true);
        end;
      end
      else
      begin
        _Coord := pCoords^;

        if (nCoords > 1) then
        begin
          pCoords := pCoords + 1;
          nCoords := nCoords - 1;
          Next    := AdtArrayPlanActor.create(pCoords, nCoords, bTranspose, true);
        end;
      end;

      if (not bSupressUpdate) then
      begin
        findLookupSize();
      end;

      bInitialised := true;
    end;

    initialise := bInitialised;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.beginRagged(var rCoord : AdtArrayCoord) : boolean;

  var
    bBegun  : boolean;
    cn      : longint;

  begin
    bBegun := false;

    destroyNext();
    destroyNextRagged();

    _Coord               := rCoord;
    _NumberOfCoOrdinates := 1;

    if (_Coord.Size > 0) then
    begin
      NextRagged := PAdtArrayPlanActor(getMem(sizeof(AdtArrayPlanActor) * _Coord.Size));

      if (NextRagged <> nil) then
      begin
        for cn := 0 to _Coord.Size - 1 do
        begin
          NextRagged[cn] := nil;
        end;

        bBegun := true;
      end
      else
      begin
        // Memory allocation failure
        raise Exception.Create('Memory allocation failure');
      end;
    end;

    beginRagged := bBegun;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.beginRagged(var Context : AdtArrayPlanActor ; var rCoord : AdtArrayCoord) : boolean;

  var
    bBegun    : boolean;
    pLastPlan : AdtArrayPlanActor;

  begin
    bBegun  := false;
    Context := nil;

    if (_NumberOfCoOrdinates = 0) then
    begin
      // Uninitialised plan case. Ragged from first co-ordinate
      Context := self;
    end
    else
    begin
      // Initialised plan case. Ragged from NumberOfCoOrdinates + 1 co-ordinate
      // Find last co-ordinate plan and add a new plan to it, set this plan to
      // the context and call beingRagged() on it.
      pLastPlan := self;

      while (pLastPlan.Next <> nil) do
      begin
        if (pLastPlan.NextRagged <> nil) then
        begin
          raise Exception.Create('calling beginRagged() on a Plan that is already ragged');
        end;

        pLastPlan := pLastPlan.Next;
      end;

      if (pLastPlan <> nil) then
      begin
        pLastPlan.Next  := AdtArrayPlanActor.create;
        Context         := pLastPlan.Next;
      end;
    end;

    if (Context <> nil) then
    begin
      bBegun := Context.beginRagged(rCoord);
    end;

    beginRagged := bBegun;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.addArrayPlanActor(Actor : AdtArrayPlanActor ; nIndex : longint) : boolean;

  var
    bAdded    : boolean;
    sMessage  : AnsiString;

  begin
    bAdded := false;

    if ((NextRagged <> nil) and (Next = nil)) then
    begin
      if ((nIndex >= _Coord.IndexBase) and (nIndex < _Coord.IndexBase + _Coord.Size)) then
      begin
        NextRagged[nIndex - _Coord.IndexBase] := Actor;

        if (Actor <> nil) then
        begin
          Actor.lock();
        end;
      end
      else
      begin
        // Index range error
        sMessage := 'Index value ';

        AppendStr(sMessage, IntToStr(nIndex));
        AppendStr(sMessage, ' is out of range [');
        AppendStr(sMessage, IntToStr(_Coord.IndexBase));
        AppendStr(sMessage, ',');
        AppendStr(sMessage, IntToStr(_Coord.IndexBase + _Coord.Size));
        AppendStr(sMessage, ')');

        raise Exception.Create(sMessage);
      end;
    end
    else
    begin
      // not in a beginRagged() endRagged() code sandwitch
      raise Exception.Create('addArrayPlan() must be called in a beginRagged() - endRagged() code sandwitch');
    end;

    addArrayPlanActor := bAdded;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.updateCoOrdinates(Context : AdtArrayPlanActor);

  var
    pLastPlan             : AdtArrayPlanActor;
    nNumberOfCoOrdinates  : longint;

  begin
    pLastPlan             := self;
    nNumberOfCoOrdinates  := Context._NumberOfCoOrdinates;

    while (pLastPlan.Next <> nil) do
    begin
      pLastPlan._NumberOfCoOrdinates  := pLastPlan._NumberOfCoOrdinates + nNumberOfCoOrdinates;
      pLastPlan                       := pLastPlan.Next;
    end;

    findLookupSize();

    if (pLastPlan <> Context) then
    begin
      raise Exception.Create('endRagged() called with context not connected with this plan.');
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.endRagged();

  var
    bFirst                : boolean;
    cn                    : longint;
    nNumberOfCoOrdinates  : longint;
    sMessage              : AnsiString;

  begin
    // Here we need to finalise instantiation of the ragged array by updating
    // the NumberOfCoOrdinates attribute and verifying that all entries in
    // NextRagged[] have been initialised
    if ((NextRagged <> nil) and (Next = nil)) then
    begin
      bFirst := true;

      for cn := 0 to _Coord.Size - 1 do
      begin
        if (NextRagged[cn] = nil) then
        begin
          sMessage := 'ArrayPlan not initialised for index ';

          AppendStr(sMessage, IntToStr(cn + _Coord.IndexBase));

          raise Exception.Create(sMessage);
        end
        else
        begin
          if (bFirst) then
          begin
            nNumberOfCoOrdinates  := NextRagged[cn]._NumberOfCoOrdinates;
            bFirst                := false;
          end
          else
          begin
            if (nNumberOfCoOrdinates <> NextRagged[cn]._NumberOfCoOrdinates) then
            begin
              raise Exception.Create('Inconsistent ArrayPlan co-ordinate sizes. They must be the same.');
            end;
          end;
        end;
      end;

      _NumberOfCoOrdinates := nNumberOfCoOrdinates + 1;

      findLookupSize();
    end
    else
    begin
      // beginRagged() not called
      raise Exception.Create('beginRagged() must be called before endRagged()');
    end;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.isCached() : boolean ; inline;

  begin
    isCached := _IsCached;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.create(var rAllocator : AdtMemAllocator ;
                                    nVarType : AdtVarType ;
                                    pExisting : pchar = nil) : pchar;

  var
    pArrayInfo    : PAdtArrayInfo;
    Alias         : AdtAliasArray;
    nIndexOffset  : longint;
    pArray        : pchar;
    nSizeOf       : longint;
    pUserData     : pchar;
    bForceCreate  : boolean;
    nDataSize     : longint;
    nMemBlockSize : longint;

  begin
    pArray        := nil;
    nSizeOf       := elementSizeFromVarType(nVarType);
    pUserData     := nil;
    bForceCreate  := false;
    nDataSize     := arraySize(nSizeOf);

    if (pExisting = nil) then
      nMemBlockSize := _LookupSize + nDataSize
    else
      nMemBlockSize := _LookupSize;

    if (_NumberOfCoOrdinates = 1) then
    begin
      nIndexOffset := -_Coord.IndexBase * nSizeOf;
      bForceCreate := (pExisting <> nil);
    end
    else
    begin
      nIndexOffset := -_Coord.IndexBase * SizeOf(pchar);
    end;

    if ((nMemBlockSize > 0) or bForceCreate) then
    begin
      pArray := rAllocator.alloc(nMemBlockSize,
                                 AdtAllocType_ARRAY,
                                 nIndexOffset,
                                 @AdtArrayPlanActor_destroyArrayInfo,
                                 @pUserData,
                                 SizeOf(AdtArrayInfo),
                                 pExisting);

      if (pUserData <> nil) then
      begin
        pArrayInfo := PAdtArrayInfo(pUserData);

        pArrayInfo^.LookupSize  := _LookupSize;
        pArrayInfo^.BlockSize   := nMemBlockSize;
        pArrayInfo^.SizeOf      := nSizeOf;
        pArrayInfo^.BlockPtr    := pArray - nIndexOffset;
        pArrayInfo^.Existing    := pExisting;
        pArrayInfo^.VarType     := nVarType;
        pArrayInfo^.Actor       := self;

        self.lock();
      end;
    end
    else
    begin
      raise Exception.Create('Array allocation failure');
    end;

    if ((_LookupSize > 0) and (pArray <> nil)) then
    begin
      initialiseLookup(pArray - nIndexOffset,
                       nSizeOf,
                       _LookupSize,
                       nDataSize,
                       pExisting);
    end;

    if ((pArray <> nil) and (pExisting <> nil)) then
    begin
      Alias.VarType   := nVarType;
      Alias.Dims      := numberOfCoOrdinates();
      Alias.Alias     := pArray;

      AliasMap[pExisting] := Alias;
    end;

    create := pArray;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.createTransposed(var rAllocator : AdtMemAllocator ;
                                              nVarType : AdtVarType ;
                                              pExisting : pchar = nil) : pchar;

  var
    pArray  : pchar;
    aCoords : array [0 .. ADLIB_MAX_COORDS - 1] of AdtArrayCoord;
    nCoords : longint;
    pActor  : AdtArrayPlanActor;

  begin
    nCoords := getCoords(aCoords, ADLIB_MAX_COORDS);
    pActor  := AdtArrayPlanActor_cachedArrayPlanActor(aCoords, nCoords, false, true);
    pArray  := pActor.create(rAllocator,
                             nVarType,
                             pExisting);

    createTransposed := pArray;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.existing(nVarType : AdtVarType ;
                                      pExisting : pchar) : pchar;

  var
    pArray  : pchar;
    Iter    : AdtAliasArrayByCharPtrMap.TIterator;

  begin
    pArray  := nil;
    Iter    := AliasMap.find(pExisting);

    if (Iter <> nil) then
    begin
      if (nVarType = Iter.Value.VarType) then
      begin
        pArray := Iter.Value.Alias;
      end
      else
      begin
        raise Exception.Create('Trying to create mapped array from an existing one but the AdtVarTypes don''t match');
      end;
    end;

    existing := pArray;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor_arrayInfo(var rAllocator : AdtMemAllocator ;
                                       pArray : pchar) : PAdtArrayInfo;

  var
    pArrayInfo : PAdtArrayInfo;

  begin
    pArrayInfo := PAdtArrayInfo(rAllocator.userPtr(pArray));

    if (pArrayInfo = nil) then
    begin
      raise Exception.Create('Unrecognised array');
    end;

    AdtArrayPlanActor_arrayInfo := pArrayInfo;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor_createSlice(var rAllocator : AdtMemAllocator ;
                                         pArray : pchar ;
                                         pIndices : plongint ;
                                         nIndices : longint) : pchar;

  var
    pSliceArray   : pchar;
    pRootActor    : AdtArrayPlanActor;
    pInfo         : PAdtArrayInfo;
    pArrayInfo    : PAdtArrayInfo;
    pData         : pchar;
    pUserData     : pchar;
    nIndexOffset  : longint;
    cn            : longint;
    pNewActor     : AdtArrayPlanActor;

  begin
    pSliceArray := nil;
    pRootActor  := nil;
    pInfo       := AdtArrayPlanActor_arrayInfo(rAllocator, pArray);

    // To create a slice we index the array to find the level of the LUT we need
    // along with the corresponding Actor and create a new one based array for
    // that level of indexing as per requirement for a slice operation. Then we
    // allocate the new slice array using rAllocator.alloc() so that its
    // attributes can be tracked by the normal means. Note that it is a shallow
    // allocation (requires only a small amount of resources) because most of
    // the array heirarchy is recycled and shares common memory with the parent.
    // The array slice should be freed when no longer needed though.
    if (pInfo <> nil) then
    begin
      pData := pInfo^.Actor.indexArray(pIndices,
                                       nIndices,
                                       pArray,
                                       pInfo^.SizeOf,
                                       @pRootActor);

      if ((pData       <> nil) and
          (pRootActor  <> nil)) then
      begin
        pUserData     := nil;
        nIndexOffset  := 0;
        pNewActor     := AdtArrayPlanActor.create;

        pNewActor._NumberOfCoOrdinates := pRootActor._NumberOfCoOrdinates;
        pNewActor._LookupSize          := pRootActor._LookupSize;
        pNewActor._ArrayCount          := pRootActor._ArrayCount;
        pNewActor._Coord.IndexBase     := 1;
        pNewActor._Coord.Size          := pRootActor._Coord.Size;

        if (pRootActor.Next <> nil) then
        begin
          pNewActor.Next := pRootActor.Next;

          pNewActor.Next.lock();
        end;

        if ((pRootActor.NextRagged <> nil) and (pRootActor._Coord.Size > 0)) then
        begin
          pNewActor.NextRagged := getMem(SizeOf(PAdtArrayPlanActor) * pRootActor._Coord.Size);

          if (pNewActor.NextRagged <> nil) then
          begin
            for cn := 0 to pRootActor._Coord.Size - 1 do
            begin
              pNewActor.NextRagged[cn] := pRootActor.NextRagged[cn];

              pNewActor.NextRagged[cn].lock();
            end;
          end;
        end;

        if (pNewActor._NumberOfCoOrdinates = 1) then
        begin
          pData        := pData + pRootActor._Coord.IndexBase * pInfo^.SizeOf;
          nIndexOffset := -pNewActor._Coord.IndexBase * pInfo^.SizeOf;
        end
        else
        begin
          pData        := pData + pRootActor._Coord.IndexBase * SizeOf(pchar);
          nIndexOffset := -pNewActor._Coord.IndexBase * SizeOf(pchar);
        end;

        pSliceArray := rAllocator.alloc(0,
                                        AdtAllocType_ARRAY,
                                        nIndexOffset,
                                        @AdtArrayPlanActor_destroyArrayInfo,
                                        @pUserData,
                                        SizeOf(AdtArrayInfo),
                                        pData);

        if (pUserData <> nil) then
        begin
          pArrayInfo := PAdtArrayInfo(pUserData);

          pArrayInfo^.LookupSize  := pRootActor.lookupSize();
          pArrayInfo^.BlockSize   := pRootActor.arraySize(pInfo^.SizeOf);
          pArrayInfo^.SizeOf      := pInfo^.SizeOf;
          pArrayInfo^.BlockPtr    := pSliceArray - nIndexOffset;
          pArrayInfo^.Existing    := pData;
          pArrayInfo^.VarType     := pInfo^.VarType;
          pArrayInfo^.Actor       := pNewActor;
        end;
      end;
    end;

    AdtArrayPlanActor_createSlice := pSliceArray;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor_createSameShape(var rAllocator : AdtMemAllocator ;
                                             pRefArray : pchar) : pchar;

  var
    pArray      : pchar;
    pArrayInfo  : PAdtArrayInfo;

  begin
    pArray      := nil;
    pArrayInfo  := AdtArrayPlanActor_arrayInfo(rAllocator, pRefArray);

    if ((pArrayInfo <> nil) and (pArrayInfo^.Actor <> nil)) then
    begin
      pArray := pArrayInfo^.Actor.create(rAllocator,
                                         pArrayInfo^.VarType);
    end;

    AdtArrayPlanActor_createSameShape := pArray;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor_destroy(var rAllocator : AdtMemAllocator ; pArray : pchar) ; inline;

  begin
    rAllocator.free(pArray);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor_R_to_ADlib(var rAllocator : AdtMemAllocator ;
                                         pArraySrc : pchar ;
                                         pArrayDest : pchar);

  var
    aCoords             : array [0 .. ADLIB_MAX_COORDS - 1] of AdtArrayCoord;
    pInfo               : PAdtArrayInfo;
    nCoords             : longint;
    c0                  : longint;
    c1                  : longint;
    c2                  : longint;
    c3                  : longint;
    c4                  : longint;
    c5                  : longint;
    c6                  : longint;
    c7                  : longint;
    c8                  : longint;
    c9                  : longint;
    cs                  : longint;
    nSizeOf             : longint;
    pArrayMappedSrc2    : ppchar;
    pArrayMappedDest2   : ppchar;
    pArrayMappedSrc3    : pppchar;
    pArrayMappedDest3   : pppchar;
    pArrayMappedSrc4    : ppppchar;
    pArrayMappedDest4   : ppppchar;
    pArrayMappedSrc5    : pppppchar;
    pArrayMappedDest5   : pppppchar;
    pArrayMappedSrc6    : ppppppchar;
    pArrayMappedDest6   : ppppppchar;
    pArrayMappedSrc7    : pppppppchar;
    pArrayMappedDest7   : pppppppchar;
    pArrayMappedSrc8    : ppppppppchar;
    pArrayMappedDest8   : ppppppppchar;
    pArrayMappedSrc9    : pppppppppchar;
    pArrayMappedDest9   : pppppppppchar;
    pArrayMappedSrc10   : ppppppppppchar;
    pArrayMappedDest10  : ppppppppppchar;

  begin
    pInfo   := AdtArrayPlanActor_arrayInfo(rAllocator, pArrayDest);
    nCoords := pInfo^.Actor.getCoords(aCoords, ADLIB_MAX_COORDS);

    case (nCoords) of
      1:
      begin
        Move(pArraySrc[0],
             pInfo^.BlockPtr[pInfo^.LookupSize],
             (pInfo^.BlockSize - pInfo^.LookupSize) * SizeOf(char));
      end;

      2:
      begin
        pArrayMappedSrc2  := ppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest2 := ppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for cs := 0 to nSizeOf - 1 do
            begin
              pArrayMappedDest2[c0][c1 * nSizeOf + cs] := pArrayMappedSrc2[c1][c0 * nSizeOf + cs];
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc2));
      end;

      3:
      begin
        pArrayMappedSrc3  := pppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest3 := pppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for cs := 0 to nSizeOf - 1 do
              begin
                pArrayMappedDest3[c0][c1][c2 * nSizeOf + cs] := pArrayMappedSrc3[c2][c1][c0 * nSizeOf + cs];
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc3));
      end;

      4:
      begin
        pArrayMappedSrc4  := ppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest4 := ppppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for cs := 0 to nSizeOf - 1 do
                begin
                  pArrayMappedDest4[c0][c1][c2][c3 * nSizeOf + cs] := pArrayMappedSrc4[c3][c2][c1][c0 * nSizeOf + cs];
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc4));
      end;

      5:
      begin
        pArrayMappedSrc5  := pppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest5 := pppppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for cs := 0 to nSizeOf - 1 do
                  begin
                    pArrayMappedDest5[c0][c1][c2][c3][c4 * nSizeOf + cs] := pArrayMappedSrc5[c4][c3][c2][c1][c0 * nSizeOf + cs];
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc5));
      end;

      6:
      begin
        pArrayMappedSrc6  := ppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest6 := ppppppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for cs := 0 to nSizeOf - 1 do
                    begin
                      pArrayMappedDest6[c0][c1][c2][c3][c4][c5 * nSizeOf + cs] := pArrayMappedSrc6[c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc6));
      end;

      7:
      begin
        pArrayMappedSrc7  := pppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest7 := pppppppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for cs := 0 to nSizeOf - 1 do
                      begin
                        pArrayMappedDest7[c0][c1][c2][c3][c4][c5][c6 * nSizeOf + cs] := pArrayMappedSrc7[c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc7));
      end;

      8:
      begin
        pArrayMappedSrc8  := ppppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest8 := ppppppppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for c7 := aCoords[7].IndexBase to aCoords[7].IndexBase + aCoords[7].Size - 1 do
                      begin
                        for cs := 0 to nSizeOf - 1 do
                        begin
                          pArrayMappedDest8[c0][c1][c2][c3][c4][c5][c6][c7 * nSizeOf + cs] := pArrayMappedSrc8[c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                        end;
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc8));
      end;

      9:
      begin
        pArrayMappedSrc9  := pppppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest9 := pppppppppchar(pArrayDest);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for c7 := aCoords[7].IndexBase to aCoords[7].IndexBase + aCoords[7].Size - 1 do
                      begin
                        for c8 := aCoords[8].IndexBase to aCoords[8].IndexBase + aCoords[8].Size - 1 do
                        begin
                          for cs := 0 to nSizeOf - 1 do
                          begin
                            pArrayMappedDest9[c0][c1][c2][c3][c4][c5][c6][c7][c8 * nSizeOf + cs] := pArrayMappedSrc9[c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                          end;
                        end;
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc9));
      end;

      10:
      begin
        pArrayMappedSrc10   := ppppppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArraySrc));
        pArrayMappedDest10  := ppppppppppchar(pArrayDest);
        nSizeOf             := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for c7 := aCoords[7].IndexBase to aCoords[7].IndexBase + aCoords[7].Size - 1 do
                      begin
                        for c8 := aCoords[8].IndexBase to aCoords[8].IndexBase + aCoords[8].Size - 1 do
                        begin
                          for c9 := aCoords[9].IndexBase to aCoords[9].IndexBase + aCoords[9].Size - 1 do
                          begin
                            for cs := 0 to nSizeOf - 1 do
                            begin
                              pArrayMappedDest10[c0][c1][c2][c3][c4][c5][c6][c7][c8][c9 * nSizeOf + cs] := pArrayMappedSrc10[c9][c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs];
                            end;
                          end;
                        end;
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedSrc10));
      end;
      else
      begin
        raise Exception.Create('Invalid var type');
      end;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor_ADlib_to_R(var rAllocator : AdtMemAllocator ;
                                         pArraySrc : pchar ;
                                         pArrayDest : pchar);

  var
    aCoords             : array [0 .. ADLIB_MAX_COORDS - 1] of AdtArrayCoord;
    pInfo               : PAdtArrayInfo;
    nCoords             : longint;
    c0                  : longint;
    c1                  : longint;
    c2                  : longint;
    c3                  : longint;
    c4                  : longint;
    c5                  : longint;
    c6                  : longint;
    c7                  : longint;
    c8                  : longint;
    c9                  : longint;
    cs                  : longint;
    nSizeOf             : longint;
    pArrayMappedSrc2    : ppchar;
    pArrayMappedDest2   : ppchar;
    pArrayMappedSrc3    : pppchar;
    pArrayMappedDest3   : pppchar;
    pArrayMappedSrc4    : ppppchar;
    pArrayMappedDest4   : ppppchar;
    pArrayMappedSrc5    : pppppchar;
    pArrayMappedDest5   : pppppchar;
    pArrayMappedSrc6    : ppppppchar;
    pArrayMappedDest6   : ppppppchar;
    pArrayMappedSrc7    : pppppppchar;
    pArrayMappedDest7   : pppppppchar;
    pArrayMappedSrc8    : ppppppppchar;
    pArrayMappedDest8   : ppppppppchar;
    pArrayMappedSrc9    : pppppppppchar;
    pArrayMappedDest9   : pppppppppchar;
    pArrayMappedSrc10   : ppppppppppchar;
    pArrayMappedDest10  : ppppppppppchar;

  begin
    pInfo   := AdtArrayPlanActor_arrayInfo(rAllocator, pArraySrc);
    nCoords := pInfo^.Actor.getCoords(aCoords, ADLIB_MAX_COORDS);

    case (nCoords) of
      1:
      begin
        Move(pInfo^.BlockPtr[pInfo^.LookupSize],
             pArrayDest[0],
             (pInfo^.BlockSize - pInfo^.LookupSize) * SizeOf(char));
      end;

      2:
      begin
        pArrayMappedDest2 := ppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc2  := ppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for cs := 0 to nSizeOf - 1 do
            begin
              pArrayMappedDest2[c1][c0 * nSizeOf + cs] := pArrayMappedSrc2[c0][c1 * nSizeOf + cs];
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest2));
      end;

      3:
      begin
        pArrayMappedDest3 := pppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc3  := pppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for cs := 0 to nSizeOf - 1 do
              begin
                pArrayMappedDest3[c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc3[c0][c1][c2 * nSizeOf + cs];
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest3));
      end;

      4:
      begin
        pArrayMappedDest4 := ppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc4  := ppppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for cs := 0 to nSizeOf - 1 do
                begin
                  pArrayMappedDest4[c3][c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc4[c0][c1][c2][c3 * nSizeOf + cs];
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest4));
      end;

      5:
      begin
        pArrayMappedDest5 := pppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc5  := pppppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for cs := 0 to nSizeOf - 1 do
                  begin
                    pArrayMappedDest5[c4][c3][c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc5[c0][c1][c2][c3][c4 * nSizeOf + cs];
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest5));
      end;

      6:
      begin
        pArrayMappedDest6 := ppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc6  := ppppppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for cs := 0 to nSizeOf - 1 do
                    begin
                      pArrayMappedDest6[c5][c4][c3][c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc6[c0][c1][c2][c3][c4][c5 * nSizeOf + cs];
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest6));
      end;

      7:
      begin
        pArrayMappedDest7 := pppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc7  := pppppppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for cs := 0 to nSizeOf - 1 do
                      begin
                        pArrayMappedDest7[c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc7[c0][c1][c2][c3][c4][c5][c6 * nSizeOf + cs];
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest7));
      end;

      8:
      begin
        pArrayMappedDest8 := ppppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc8  := ppppppppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for c7 := aCoords[7].IndexBase to aCoords[7].IndexBase + aCoords[7].Size - 1 do
                      begin
                        for cs := 0 to nSizeOf - 1 do
                        begin
                          pArrayMappedDest8[c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc8[c0][c1][c2][c3][c4][c5][c6][c7 * nSizeOf + cs];
                        end;
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest8));
      end;

      9:
      begin
        pArrayMappedDest9 := pppppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc9  := pppppppppchar(pArraySrc);
        nSizeOf           := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for c7 := aCoords[7].IndexBase to aCoords[7].IndexBase + aCoords[7].Size - 1 do
                      begin
                        for c8 := aCoords[8].IndexBase to aCoords[8].IndexBase + aCoords[8].Size - 1 do
                        begin
                          for cs := 0 to nSizeOf - 1 do
                          begin
                            pArrayMappedDest9[c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc9[c0][c1][c2][c3][c4][c5][c6][c7][c8 * nSizeOf + cs];
                          end;
                        end;
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest9));
      end;

      10:
      begin
        pArrayMappedDest10  := ppppppppppchar(pInfo^.Actor.createTransposed(rAllocator, pInfo^.VarType, pArrayDest));
        pArrayMappedSrc10   := ppppppppppchar(pArraySrc);
        nSizeOf             := pInfo^.SizeOf;

        for c0 := aCoords[0].IndexBase to aCoords[0].IndexBase + aCoords[0].Size - 1 do
        begin
          for c1 := aCoords[1].IndexBase to aCoords[1].IndexBase + aCoords[1].Size - 1 do
          begin
            for c2 := aCoords[2].IndexBase to aCoords[2].IndexBase + aCoords[2].Size - 1 do
            begin
              for c3 := aCoords[3].IndexBase to aCoords[3].IndexBase + aCoords[3].Size - 1 do
              begin
                for c4 := aCoords[4].IndexBase to aCoords[4].IndexBase + aCoords[4].Size - 1 do
                begin
                  for c5 := aCoords[5].IndexBase to aCoords[5].IndexBase + aCoords[5].Size - 1 do
                  begin
                    for c6 := aCoords[6].IndexBase to aCoords[6].IndexBase + aCoords[6].Size - 1 do
                    begin
                      for c7 := aCoords[7].IndexBase to aCoords[7].IndexBase + aCoords[7].Size - 1 do
                      begin
                        for c8 := aCoords[8].IndexBase to aCoords[8].IndexBase + aCoords[8].Size - 1 do
                        begin
                          for c9 := aCoords[9].IndexBase to aCoords[9].IndexBase + aCoords[9].Size - 1 do
                          begin
                            for cs := 0 to nSizeOf - 1 do
                            begin
                              pArrayMappedDest10[c9][c8][c7][c6][c5][c4][c3][c2][c1][c0 * nSizeOf + cs] := pArrayMappedSrc10[c0][c1][c2][c3][c4][c5][c6][c7][c8][c9 * nSizeOf + cs];
                            end;
                          end;
                        end;
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;

        rAllocator.free(pchar(pArrayMappedDest10));
      end;
      else
      begin
        raise Exception.Create('Invalid var type');
      end;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.assign(var rCopy : AdtArrayPlanActor);

  begin
    _Coord := rCopy._Coord;

    copyNext(rCopy.Next);
    copyNextRagged(rCopy.NextRagged);

    _NumberOfCoOrdinates := rCopy._NumberOfCoOrdinates;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.eq(var rCopy : AdtArrayPlanActor) : boolean;

  var
    bEqual : boolean;

  begin
    bEqual := false;

    if ((_Coord.IndexBase  = rCopy._Coord.IndexBase) and
        (_Coord.Size       = rCopy._Coord.Size     )) then
    begin
      if (rCopy.Next <> nil) then
      begin
        if ((Next <> nil) and (Next.eq(rCopy.Next))) then
        begin
          bEqual := true;
        end;
      end
      else if (Next = nil) then
      begin
        bEqual := true;
      end;
    end;

    eq := bEqual;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.isRegular() : boolean;

  var
    bIsRegular  : boolean;
    pActor      : AdtArrayPlanActor;
    cn          : longint;

  begin
    bIsRegular  := true;
    pActor      := self;

    for cn := 0 to _NumberOfCoOrdinates - 1 do
    begin
      if (pActor.Next <> nil) then
      begin
        pActor := pActor.Next;
      end
      else if (NextRagged <> nil) then
      begin
        bIsRegular := false;
        break;
      end;
    end;

    isRegular := bIsRegular;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.isRagged() : boolean ; inline;

  begin
    isRagged := not isRegular();
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.numberOfCoOrdinates() : longint ; inline;

  begin
    numberOfCoOrdinates := _NumberOfCoOrdinates;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.indexArray(pIndices : plongint ;
                                        nIndices : longint ;
                                        pArray : pchar ;
                                        nSizeOf : longint ;
                                        ppActor : PAdtArrayPlanActor = nil) : pchar;

  var
    pData   : pchar;
    pActor  : AdtArrayPlanActor;
    cn      : longint;
    nIndex  : longint;

  begin
    pData := nil;

    if ((pIndices <> nil) and (pArray <> nil)) then
    begin
      pData := pArray;

      if ((nIndices < 0) or (nIndices > _NumberOfCoOrdinates)) then
      begin
        raise Exception.Create('too many indices');
      end;

      pActor := self;

      for cn := 0 to nIndices - 1 do
      begin
        nIndex := pIndices[cn] - pActor._Coord.IndexBase;

        if ((nIndex < 0) or (nIndex >= pActor._Coord.Size)) then
        begin
          raise Exception.Create('co-ordinate out of range');
        end;

        if ((cn + 1) = _NumberOfCoOrdinates) then
        begin
          pData   := pData + (pIndices[cn] * nSizeOf);
          pActor  := nil;
        end
        else
        begin
          pData   := ppchar(pData)[pIndices[cn]];

          if (pActor.Next <> nil) then
          begin
            pActor := pActor.Next;
          end
          else if (NextRagged <> nil) then
          begin
            pActor := pActor.NextRagged[nIndex];
          end
          else
          begin
            raise Exception.Create('invalid AdtArrayPlanActor');
          end;
        end;
      end;

      if (ppActor <> nil) then
      begin
        ppActor^ := pActor;
      end;
    end;

    indexArray := pData;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.getCoords(pCoords : PAdtArrayCoord ; nCoords : longint ; bReversed : boolean) : longint;

  var
    cn      : longint;
    pActor  : AdtArrayPlanActor;

  begin
    if (nCoords < _NumberOfCoOrdinates) then
    begin
      raise Exception.Create('buffer too small to hold co-ordinate data');
    end;

    pActor := self;

    for cn := 0 to _NumberOfCoOrdinates - 1 do
    begin
      if (bReversed) then
      begin
        pCoords[_NumberOfCoOrdinates - 1 - cn] := pActor._Coord;
      end
      else
      begin
        pCoords[cn] := pActor._Coord;
      end;

      if (pActor.Next <> nil) then
      begin
        pActor := pActor.Next;
      end
      else if (pActor.NextRagged <> nil) then
      begin
        raise Exception.Create('cannot retrieve ragged array co-ordinate data');
      end;
    end;

    getCoords := _NumberOfCoOrdinates;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.coord(nCoord : longint) : PAdtArrayCoord ; inline;

  begin
    coord := coord(nil, nCoord);
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.coord(pIndices : plongint ;
                                   nIndices : longint ;
                                   ppActor : PAdtArrayPlanActor = nil) : PAdtArrayCoord;

  var
    pCoord  : PAdtArrayCoord;
    pActor  : AdtArrayPlanActor;
    cn      : longint;
    nIndex  : longint;

  begin
    if ((nIndices < 0) or (nIndices >= _NumberOfCoOrdinates)) then
    begin
      raise Exception.Create('co-ordinate out of range');
    end;

    pCoord := @Coord;
    pActor := self;

    for cn := 0 to nIndices - 1 do
    begin
      if (pActor.Next <> nil) then
      begin
        pActor := pActor.Next;
      end
      else if (pActor.NextRagged <> nil) then
      begin
        if (pIndices <> nil) then
        begin
          nIndex := pIndices[cn] - pActor._Coord.IndexBase;

          if ((nIndex < 0) or (nIndex >= pActor._Coord.Size)) then
          begin
            raise Exception.Create('co-ordinate out of range');
          end;

          pActor := pActor.NextRagged[nIndex];
        end
        else
        begin
          pActor := pActor.NextRagged[0];
        end;
      end;

      if (pActor <> nil) then
      begin
        pCoord := @(pActor._Coord);
      end;
    end;

    if (ppActor <> nil) then
    begin
      ppActor^ := pActor;
    end;

    coord := pCoord;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.lookupSize() : longint ; inline;

  begin
    lookupSize := _LookupSize;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.arrayCount() : longint ; inline;

  begin
    arrayCount := _ArrayCount;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor.lock() ; inline;

  begin
    _LockCount := _LockCount + 1;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor.unlock() : boolean;

  var
    bDestroyed  : boolean;

  begin
    bDestroyed := false;
    _LockCount := _LockCount - 1;

    assert(_LockCount >= 0);

    if (_LockCount = 0) then
    begin
      bDestroyed := true;

      self.destroy;
    end;

    unlock := bDestroyed;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor_createArrayPlanActor(const pCoords : PAdtArrayCoord;
                                                  nCoords : longint) : AdtArrayPlanActor;

  begin
    AdtArrayPlanActor_createArrayPlanActor := AdtArrayPlanActor.create(pCoords, nCoords);
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlanActor_cachedArrayPlanActor(const pCoords : PAdtArrayCoord ;
                                                  nCoords : longint ;
                                                  bLock : boolean ;
                                                  bTranspose : boolean = false) : AdtArrayPlanActor;

  var
    cn      : longint;
    sKey    : AnsiString;
    pActor  : AdtArrayPlanActor;
    Iter    : AdtArrayPlanActorByCharPtrMap.TIterator;

  begin
    sKey    := '';
    pActor  := nil;

    if (bTranspose) then
    begin
      for cn := nCoords downto 1 do
      begin
        appendKey(pCoords[cn - 1], sKey, (cn <> nCoords));
      end;
    end
    else
    begin
      for cn := 0 to nCoords - 1 do
      begin
        appendKey(pCoords[cn], sKey, (cn <> 0));
      end;
    end;

    Iter := AdtArrayPlanActor.CacheMap.find(sKey);

    if (Iter <> nil) then
    begin
      pActor := Iter.Value;
    end
    else
    begin
      pActor                            := AdtArrayPlanActor.create(pCoords, nCoords, bTranspose);
      AdtArrayPlanActor.CacheMap[sKey]  := pActor;

      if (not AdtArrayPlanActor.CacheUsed) then
      begin
        AdtArrayPlanActor.CacheUsed := true;

        AddExitProc(@AdtArrayPlanActor_flush);
      end;

      if (pActor <> nil) then
      begin
        pActor._IsCached := true;
      end;
    end;

    if (bLock and (pActor <> nil)) then
    begin
      pActor.lock();
    end;

    AdtArrayPlanActor_cachedArrayPlanActor := pActor;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlanActor_flush();

  var
    Iter : AdtArrayPlanActorByCharPtrMap.TIterator;

  begin
    Iter := AdtArrayPlanActor.CacheMap.Min();

    if (Iter <> nil) then
    begin
    repeat
      if (Iter.Value <> nil) then
      begin
        Iter.Value.unlock();
      end;

      until not Iter.Next();

      Iter.Destroy();
    end;

    AdtArrayPlanActor.CacheMap.Destroy();

    AdtArrayPlanActor.CacheMap := AdtArrayPlanActorByCharPtrMap.Create();
  end;


  //  ----------------------------------------------------------------------------
  //  AdtArrayPlan method implementations
  //  ----------------------------------------------------------------------------
  constructor AdtArrayPlan.create();

  begin
    Actor := AdtArrayPlanActor.create();
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex, nSize : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex, nSize);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3,
                                  nBaseIndex4, nSize4 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3,
               nBaseIndex4, nSize4);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3,
                                  nBaseIndex4, nSize4,
                                  nBaseIndex5, nSize5 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3,
               nBaseIndex4, nSize4,
               nBaseIndex5, nSize5);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3,
                                  nBaseIndex4, nSize4,
                                  nBaseIndex5, nSize5,
                                  nBaseIndex6, nSize6 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3,
               nBaseIndex4, nSize4,
               nBaseIndex5, nSize5,
               nBaseIndex6, nSize6);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3,
                                  nBaseIndex4, nSize4,
                                  nBaseIndex5, nSize5,
                                  nBaseIndex6, nSize6,
                                  nBaseIndex7, nSize7 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3,
               nBaseIndex4, nSize4,
               nBaseIndex5, nSize5,
               nBaseIndex6, nSize6,
               nBaseIndex7, nSize7);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3,
                                  nBaseIndex4, nSize4,
                                  nBaseIndex5, nSize5,
                                  nBaseIndex6, nSize6,
                                  nBaseIndex7, nSize7,
                                  nBaseIndex8, nSize8 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3,
               nBaseIndex4, nSize4,
               nBaseIndex5, nSize5,
               nBaseIndex6, nSize6,
               nBaseIndex7, nSize7,
               nBaseIndex8, nSize8);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3,
                                  nBaseIndex4, nSize4,
                                  nBaseIndex5, nSize5,
                                  nBaseIndex6, nSize6,
                                  nBaseIndex7, nSize7,
                                  nBaseIndex8, nSize8,
                                  nBaseIndex9, nSize9 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3,
               nBaseIndex4, nSize4,
               nBaseIndex5, nSize5,
               nBaseIndex6, nSize6,
               nBaseIndex7, nSize7,
               nBaseIndex8, nSize8,
               nBaseIndex9, nSize9);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(nBaseIndex1, nSize1,
                                  nBaseIndex2, nSize2,
                                  nBaseIndex3, nSize3,
                                  nBaseIndex4, nSize4,
                                  nBaseIndex5, nSize5,
                                  nBaseIndex6, nSize6,
                                  nBaseIndex7, nSize7,
                                  nBaseIndex8, nSize8,
                                  nBaseIndex9, nSize9,
                                  nBaseIndex10, nSize10 : longint);

  begin
    Actor := nil;

    initialise(nBaseIndex1, nSize1,
               nBaseIndex2, nSize2,
               nBaseIndex3, nSize3,
               nBaseIndex4, nSize4,
               nBaseIndex5, nSize5,
               nBaseIndex6, nSize6,
               nBaseIndex7, nSize7,
               nBaseIndex8, nSize8,
               nBaseIndex9, nSize9,
               nBaseIndex10, nSize10);
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrayPlan.create(rCopy : AdtArrayPlan);

  begin
    Actor := rCopy.Actor;

    if (Actor <> nil) then
    begin
      Actor.lock();
    end;
  end;

  //  ----------------------------------------------------------------------------

  destructor AdtArrayPlan.destroy();

  begin
    if (Actor <> nil) then
    begin
      Actor.unlock();

      Actor := nil;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex, nSize : longint);

  var
    rCoord : AdtArrayCoord;

  begin
    rCoord.IndexBase  := nBaseIndex;
    rCoord.Size       := nSize;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(@rCoord, 1);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2 : longint);

  var
    rCoords : Array [0..1] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 2);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3 : longint);

  var
    rCoords : Array [0..2] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 3);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3,
                                    nBaseIndex4, nSize4 : longint);

  var
    rCoords : Array [0..3] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;
    rCoords[3].IndexBase  := nBaseIndex4;
    rCoords[3].Size       := nSize4;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 4);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3,
                                    nBaseIndex4, nSize4,
                                    nBaseIndex5, nSize5 : longint);

  var
    rCoords : Array [0..4] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;
    rCoords[3].IndexBase  := nBaseIndex4;
    rCoords[3].Size       := nSize4;
    rCoords[4].IndexBase  := nBaseIndex5;
    rCoords[4].Size       := nSize5;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 5);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3,
                                    nBaseIndex4, nSize4,
                                    nBaseIndex5, nSize5,
                                    nBaseIndex6, nSize6 : longint);

  var
    rCoords : Array [0..5] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;
    rCoords[3].IndexBase  := nBaseIndex4;
    rCoords[3].Size       := nSize4;
    rCoords[4].IndexBase  := nBaseIndex5;
    rCoords[4].Size       := nSize5;
    rCoords[5].IndexBase  := nBaseIndex6;
    rCoords[5].Size       := nSize6;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 6);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3,
                                    nBaseIndex4, nSize4,
                                    nBaseIndex5, nSize5,
                                    nBaseIndex6, nSize6,
                                    nBaseIndex7, nSize7 : longint);

  var
    rCoords : Array [0..6] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;
    rCoords[3].IndexBase  := nBaseIndex4;
    rCoords[3].Size       := nSize4;
    rCoords[4].IndexBase  := nBaseIndex5;
    rCoords[4].Size       := nSize5;
    rCoords[5].IndexBase  := nBaseIndex6;
    rCoords[5].Size       := nSize6;
    rCoords[6].IndexBase  := nBaseIndex7;
    rCoords[6].Size       := nSize7;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 7);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3,
                                    nBaseIndex4, nSize4,
                                    nBaseIndex5, nSize5,
                                    nBaseIndex6, nSize6,
                                    nBaseIndex7, nSize7,
                                    nBaseIndex8, nSize8 : longint);

  var
    rCoords : Array [0..7] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;
    rCoords[3].IndexBase  := nBaseIndex4;
    rCoords[3].Size       := nSize4;
    rCoords[4].IndexBase  := nBaseIndex5;
    rCoords[4].Size       := nSize5;
    rCoords[5].IndexBase  := nBaseIndex6;
    rCoords[5].Size       := nSize6;
    rCoords[6].IndexBase  := nBaseIndex7;
    rCoords[6].Size       := nSize7;
    rCoords[7].IndexBase  := nBaseIndex8;
    rCoords[7].Size       := nSize8;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 8);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3,
                                    nBaseIndex4, nSize4,
                                    nBaseIndex5, nSize5,
                                    nBaseIndex6, nSize6,
                                    nBaseIndex7, nSize7,
                                    nBaseIndex8, nSize8,
                                    nBaseIndex9, nSize9 : longint);

  var
    rCoords : Array [0..8] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;
    rCoords[3].IndexBase  := nBaseIndex4;
    rCoords[3].Size       := nSize4;
    rCoords[4].IndexBase  := nBaseIndex5;
    rCoords[4].Size       := nSize5;
    rCoords[5].IndexBase  := nBaseIndex6;
    rCoords[5].Size       := nSize6;
    rCoords[6].IndexBase  := nBaseIndex7;
    rCoords[6].Size       := nSize7;
    rCoords[7].IndexBase  := nBaseIndex8;
    rCoords[7].Size       := nSize8;
    rCoords[8].IndexBase  := nBaseIndex9;
    rCoords[8].Size       := nSize9;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 9);
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.initialise(nBaseIndex1, nSize1,
                                    nBaseIndex2, nSize2,
                                    nBaseIndex3, nSize3,
                                    nBaseIndex4, nSize4,
                                    nBaseIndex5, nSize5,
                                    nBaseIndex6, nSize6,
                                    nBaseIndex7, nSize7,
                                    nBaseIndex8, nSize8,
                                    nBaseIndex9, nSize9,
                                    nBaseIndex10, nSize10 : longint);

  var
    rCoords : Array [0..9] of AdtArrayCoord;

  begin
    rCoords[0].IndexBase  := nBaseIndex1;
    rCoords[0].Size       := nSize1;
    rCoords[1].IndexBase  := nBaseIndex2;
    rCoords[1].Size       := nSize2;
    rCoords[2].IndexBase  := nBaseIndex3;
    rCoords[2].Size       := nSize3;
    rCoords[3].IndexBase  := nBaseIndex4;
    rCoords[3].Size       := nSize4;
    rCoords[4].IndexBase  := nBaseIndex5;
    rCoords[4].Size       := nSize5;
    rCoords[5].IndexBase  := nBaseIndex6;
    rCoords[5].Size       := nSize6;
    rCoords[6].IndexBase  := nBaseIndex7;
    rCoords[6].Size       := nSize7;
    rCoords[7].IndexBase  := nBaseIndex8;
    rCoords[7].Size       := nSize8;
    rCoords[8].IndexBase  := nBaseIndex9;
    rCoords[8].Size       := nSize9;
    rCoords[9].IndexBase  := nBaseIndex10;
    rCoords[9].Size       := nSize10;

    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := AdtArrayPlanActor.create(rCoords, 10);
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlan.beginRagged(var Context : AdtArrayPlanActor ; nBaseIndex, nSize : longint) : boolean;

  var
    bBegun  : boolean;
    pCached : AdtArrayPlanActor;
    rCoord  : AdtArrayCoord;

  begin
    bBegun    := false;
    Context   := nil;

    if (Actor <> nil) then
    begin
      if (Actor.isCached()) then
      begin
        pCached := Actor;

        // We can't use a cached actor for a ragged array plan as we are modifying
        // the plan which will invalidate it's linkage to whatever arrays it has
        // already created. Therefore we create a copy that isn't cached.
        Actor := AdtArrayPlanActor.create(pCached);
        pCached.unlock();
      end;

      rCoord.IndexBase  := nBaseIndex;
      rCoord.Size       := nSize;

      bBegun := Actor.beginRagged(Context, rCoord);
    end;

    beginRagged := bBegun;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlan.addArrayPlan(Context : AdtArrayPlanActor; var rArrayPlan : AdtArrayPlan; nIndex : longint) : boolean;

  var
    bAdded : boolean;

  begin
    bAdded := false;

    if ((Actor <> nil) and (Context <> nil)) then
    begin
      bAdded := Context.addArrayPlanActor(rArrayPlan.Actor, nIndex);
    end;

    addArrayPlan := bAdded;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.endRagged(Context : AdtArrayPlanActor);

  begin
    if ((Actor <> nil) and (Context <> nil)) then
    begin
      Context.endRagged();

      if (Actor <> Context) then
      begin
        // update NumberOfCoOrdinates to include dimensions added by this context
        Actor.updateCoOrdinates(Context);
      end;
    end;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlan.beginRagged(nBaseIndex, nSize : longint) : boolean;

  var
    bBegun : boolean;
    rCoord : AdtArrayCoord;

  begin
    bBegun := false;

    if (Actor <> nil) then
    begin
      rCoord.IndexBase  := nBaseIndex;
      rCoord.Size       := nSize;

      bBegun := Actor.beginRagged(rCoord);
    end;

    beginRagged := bBegun;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlan.addArrayPlan(rArrayPlan : AdtArrayPlan; nIndex : longint) : boolean;

  var
    bAdded : boolean;

  begin
    bAdded := false;

    if (Actor <> nil) then
    begin
      bAdded := Actor.addArrayPlanActor(rArrayPlan.Actor, nIndex);
    end;

    addArrayPlan := bAdded;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.endRagged();

  begin
    if (Actor <> nil) then
    begin
      Actor.endRagged();
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrayPlan.assign(rCopy : AdtArrayPlan);

  begin
    if (Actor <> nil) then
    begin
      Actor.unlock();
    end;

    Actor := rCopy.Actor;

    if (Actor <> nil) then
    begin
      Actor.lock();
    end;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlan.eq(rArrayPlan : AdtArrayPlan) : boolean;

  var
    bEqual : boolean;

  begin
    bEqual := false;

    if ((Actor = rArrayPlan.Actor) or
        ((Actor <> nil) and (rArrayPlan.Actor <> nil) and (Actor.eq(rArrayPlan.Actor)))) then
    begin
      bEqual := true;
    end;

    eq := bEqual;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlan.numberOfCoOrdinates() : longint ; inline;

  var
    nNumCoords : longint;

  begin
    if (Actor <> nil) then
      nNumCoords := Actor.numberOfCoOrdinates()
    else
      nNumCoords := 0;

    numberOfCoOrdinates := nNumCoords;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrayPlan.lookupSize() : longint ; inline;

  var
    nLookupSize : longint;

  begin
    if (Actor <> nil) then
      nLookupSize := Actor.lookupSize()
    else
      nLookupSize := 0;

    lookupSize := nLookupSize;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrays.createStack(var pArray : pchar;
                                 nInitialSize : longint;
                                 nVarType : AdtVarType) : boolean;

  var
    bCreated      : boolean;
    nSizeOf       : longint;
    nBlockOffset  : longint;
    nBlockSize    : longint;
    pOffsetBlock  : pchar;
    pStackInfo    : PAdtStackInfo;

  begin
    bCreated := false;
    nSizeOf  := elementSizeFromVarType(nVarType);

    // Tricky issue. We want to alloc stacks in such a manner that createSameShape
    // will work but we also want to allocated it such that the block has header
    // Info that stores the current stack size so we can check that value quickly
    // (ie. without the need of using the infoMap). Maybe not supporting
    // createSameShape for stacks makes more sense!!! I'm not at all sure about
    // this, other than I believe allocSameShape isn't supported for stacks in
    // Mark's code
    nBlockOffset := sizeof(AdtStackInfo);
    nBlockSize   := (nSizeOf * (nInitialSize + 1)) + nBlockOffset; // Add 1 to account for possible 1 based array usage
    pOffsetBlock := memAllocator().alloc(nBlockSize, AdtAllocType_STACK, nBlockOffset);

    if (pOffsetBlock <> nil) then
    begin
      pStackInfo := stackInfo(pOffsetBlock);

      pStackInfo^.StackSize := nInitialSize;
      pStackInfo^.SizeOf    := nSizeOf;
      pStackInfo^.VarType   := nVarType;
      bCreated              := true;
    end;

    pArray      := pOffsetBlock;
    createStack := bCreated;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrays.copyAndGrowStack(var pArray : pchar;
                                       pCurrentStackInfo : PAdtStackInfo;
                                       nMinSizeNeeded : longint);

  var
    nVarType          : AdtVarType;
    nSizeOf           : longint;
    nOldStackSize     : longint;
    nNewStackSize     : longint;
    nNewMinStackSize  : longint;
    pNewStack         : pchar;

  begin
    // Note that we double the minimum required stack size so that we don't
    // get a re-size immediately after the current one. It should take some
    // time for the new to be exhausted.
    nVarType          := pCurrentStackInfo^.VarType;
    nSizeOf           := pCurrentStackInfo^.SizeOf;
    nOldStackSize     := pCurrentStackInfo^.StackSize;
    nNewStackSize     := nOldStackSize;
    nNewMinStackSize  := 2 * nMinSizeNeeded;
    pNewStack         := nil;

    while (nNewStackSize < nNewMinStackSize) do
    begin
      nNewStackSize := nNewStackSize * 2;
    end;

    if (createStack(&pNewStack, nNewStackSize, nVarType)) then
    begin
      Move(pArray[0], pNewStack[0], ((nOldStackSize + 1) * nSizeOf)); // Add 1 to account for possible 1 based array usage

      memAllocator().free(pArray);

      pArray := pNewStack;
    end;
  end;

  //  ----------------------------------------------------------------------------

  procedure AdtArrays.growStack(var pArray : pchar; nIndexNeeded : longint) ; inline;

  var
    pStackInfo  : PAdtStackInfo;

  begin
    pStackInfo := stackInfo(pArray);

    if (pStackInfo^.StackSize <= nIndexNeeded) then
    begin
      copyAndGrowStack(pArray, pStackInfo, nIndexNeeded);
    end;
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrays.create();

  begin
    _MemAllocator := AdtMemAllocator.create();
    IsShallowCopy := false;
  end;

  //  ----------------------------------------------------------------------------

  constructor AdtArrays.create(pCopy : PAdtArrays; bShallow : boolean = true);

  begin
    if (bShallow) then
    begin
      _MemAllocator := pCopy^._MemAllocator;
    end
    else
    begin
      _MemAllocator := AdtMemAllocator.create();
    end;

    IsShallowCopy := bShallow;
  end;

  //  ----------------------------------------------------------------------------

  destructor AdtArrays.destroy();

  begin
    if (not IsShallowCopy) then
    begin
      _MemAllocator.destroy();
    end;
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrays.stackInfo(pStack : pchar) : PAdtStackInfo ; inline;

  begin
    stackInfo := PAdtStackInfo(pStack - sizeof(AdtStackInfo));
  end;

  //  ----------------------------------------------------------------------------

  function AdtArrays.memAllocator() : AdtMemAllocator ; inline;

  begin
    memAllocator := _MemAllocator;
  end;

  //  ----------------------------------------------------------------------------

  {$INCLUDE adtarray_impl.inc}


initialization
  AdtArrayPlanActor.CacheMap  := AdtArrayPlanActorByCharPtrMap.create();
  AdtArrayPlanActor.CacheUsed := false;
  AdtArrays.DefaultStackSize  := DEFAULT_STACK_SIZE;


end.
