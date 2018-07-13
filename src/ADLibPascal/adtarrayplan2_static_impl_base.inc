// Simplified array creation methods
// 1D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_1<T>;
                             nBaseIndex, nSize : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoord  : AdtArrayCoord;
  pActor  : AdtArrayPlanActor;

begin
  rCoord.IndexBase  := nBaseIndex;
  rCoord.Size       := nSize;
  pActor            := AdtArrayPlanActor_cachedArrayPlanActor(@rCoord, 1, false);

  if (pActor <> nil) then
    pArray := ARRAY_1<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 2D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_2<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..1] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

begin
  rCoords[0].IndexBase  := nBaseIndex1;
  rCoords[0].Size       := nSize1;
  rCoords[1].IndexBase  := nBaseIndex2;
  rCoords[1].Size       := nSize2;
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 2, false);

  if (pActor <> nil) then
    pArray := ARRAY_2<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 3D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_3<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..2] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

begin
  rCoords[0].IndexBase  := nBaseIndex1;
  rCoords[0].Size       := nSize1;
  rCoords[1].IndexBase  := nBaseIndex2;
  rCoords[1].Size       := nSize2;
  rCoords[2].IndexBase  := nBaseIndex3;
  rCoords[2].Size       := nSize3;
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 3, false);

  if (pActor <> nil) then
    pArray := ARRAY_3<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 4D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_4<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             nBaseIndex4, nSize4 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..3] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

begin
  rCoords[0].IndexBase  := nBaseIndex1;
  rCoords[0].Size       := nSize1;
  rCoords[1].IndexBase  := nBaseIndex2;
  rCoords[1].Size       := nSize2;
  rCoords[2].IndexBase  := nBaseIndex3;
  rCoords[2].Size       := nSize3;
  rCoords[3].IndexBase  := nBaseIndex4;
  rCoords[3].Size       := nSize4;
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 4, false);

  if (pActor <> nil) then
    pArray := ARRAY_4<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 5D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_5<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             nBaseIndex4, nSize4 : longint;
                             nBaseIndex5, nSize5 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..4] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

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
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 5, false);

  if (pActor <> nil) then
    pArray := ARRAY_5<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 6D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_6<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             nBaseIndex4, nSize4 : longint;
                             nBaseIndex5, nSize5 : longint;
                             nBaseIndex6, nSize6 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..5] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

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
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 6, false);

  if (pActor <> nil) then
    pArray := ARRAY_6<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 7D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_7<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             nBaseIndex4, nSize4 : longint;
                             nBaseIndex5, nSize5 : longint;
                             nBaseIndex6, nSize6 : longint;
                             nBaseIndex7, nSize7 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..6] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

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
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 7, false);

  if (pActor <> nil) then
    pArray := ARRAY_7<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 8D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_8<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             nBaseIndex4, nSize4 : longint;
                             nBaseIndex5, nSize5 : longint;
                             nBaseIndex6, nSize6 : longint;
                             nBaseIndex7, nSize7 : longint;
                             nBaseIndex8, nSize8 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..7] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

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
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 8, false);

  if (pActor <> nil) then
    pArray := ARRAY_8<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 9D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_9<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             nBaseIndex4, nSize4 : longint;
                             nBaseIndex5, nSize5 : longint;
                             nBaseIndex6, nSize6 : longint;
                             nBaseIndex7, nSize7 : longint;
                             nBaseIndex8, nSize8 : longint;
                             nBaseIndex9, nSize9 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..8] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

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
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 9, false);

  if (pActor <> nil) then
    pArray := ARRAY_9<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;

// 10D
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator;
                             var pArray : ARRAY_10<T>;
                             nBaseIndex1, nSize1 : longint;
                             nBaseIndex2, nSize2 : longint;
                             nBaseIndex3, nSize3 : longint;
                             nBaseIndex4, nSize4 : longint;
                             nBaseIndex5, nSize5 : longint;
                             nBaseIndex6, nSize6 : longint;
                             nBaseIndex7, nSize7 : longint;
                             nBaseIndex8, nSize8 : longint;
                             nBaseIndex9, nSize9 : longint;
                             nBaseIndex10, nSize10 : longint;
                             pExisting : pchar = nil) : boolean ; overload;

var
  rCoords  : Array [0..9] of AdtArrayCoord;
  pActor   : AdtArrayPlanActor;

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
  pActor                := AdtArrayPlanActor_cachedArrayPlanActor(rCoords, 10, false);

  if (pActor <> nil) then
    pArray := ARRAY_10<T>(pActor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  AdtArrayPlan_create := (pArray <> nil);
end;
