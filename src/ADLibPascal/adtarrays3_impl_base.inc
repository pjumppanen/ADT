// flatten methods
function AdtArrays.createFlattened(pArray : ARRAY_2<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_3<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_4<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_5<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_6<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_7<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_8<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_9<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

function AdtArrays.createFlattened(pArray : ARRAY_10<T>) : ARRAY_1<T> ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pFlattened  : ARRAY_1<T>;
  pData       : pchar;
  nCount      : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := firstData(pArrayInfo^);
  pFlattened  := nil;
  nCount      := lengthOfData(pArrayInfo^) div sizeof(pFlattened[0]);

  AdtArrayPlan_create(_MemAllocator, pFlattened, 1, nCount, pData);

  createFlattened := pFlattened;
end;

// createSlice methods
function AdtArrays.createSlice(pArray : ARRAY_2<T>; i1 : longint) : ARRAY_1<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_3<T>; i1 : longint) : ARRAY_2<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_3<T>; i1, i2 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_4<T>; i1 : longint) : ARRAY_3<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_3<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_4<T>; i1, i2 : longint) : ARRAY_2<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_4<T>; i1, i2, i3 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..2] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          3));
end;

function AdtArrays.createSlice(pArray : ARRAY_5<T>; i1 : longint) : ARRAY_4<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_4<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_5<T>; i1, i2 : longint) : ARRAY_3<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_3<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_5<T>; i1, i2, i3 : longint) : ARRAY_2<T> ; overload;

var
  aIndices  : array [0..2] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          3));
end;

function AdtArrays.createSlice(pArray : ARRAY_5<T>; i1, i2, i3, i4 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..3] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_6<T>; i1 : longint) : ARRAY_5<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_5<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_6<T>; i1, i2 : longint) : ARRAY_4<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_4<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_6<T>; i1, i2, i3 : longint) : ARRAY_3<T> ; overload;

var
  aIndices  : array [0..2] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  createSlice := ARRAY_3<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          3));
end;

function AdtArrays.createSlice(pArray : ARRAY_6<T>; i1, i2, i3, i4 : longint) : ARRAY_2<T> ; overload;

var
  aIndices  : array [0..3] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_6<T>; i1, i2, i3, i4, i5 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..4] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          5));
end;

function AdtArrays.createSlice(pArray : ARRAY_7<T>; i1 : longint) : ARRAY_6<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_6<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_7<T>; i1, i2 : longint) : ARRAY_5<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_5<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_7<T>; i1, i2, i3 : longint) : ARRAY_4<T> ; overload;

var
  aIndices  : array [0..2] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  createSlice := ARRAY_4<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_7<T>; i1, i2, i3, i4 : longint) : ARRAY_3<T> ; overload;

var
  aIndices  : array [0..3] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  createSlice := ARRAY_3<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_7<T>; i1, i2, i3, i4, i5 : longint) : ARRAY_2<T> ; overload;

var
  aIndices  : array [0..4] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          5));
end;

function AdtArrays.createSlice(pArray : ARRAY_7<T>; i1, i2, i3, i4, i5, i6 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..5] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          6));
end;

function AdtArrays.createSlice(pArray : ARRAY_8<T>; i1 : longint) : ARRAY_7<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_7<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_8<T>; i1, i2 : longint) : ARRAY_6<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_6<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_8<T>; i1, i2, i3 : longint) : ARRAY_5<T> ; overload;

var
  aIndices  : array [0..2] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  createSlice := ARRAY_5<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_8<T>; i1, i2, i3, i4 : longint) : ARRAY_4<T> ; overload;

var
  aIndices  : array [0..3] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  createSlice := ARRAY_4<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_8<T>; i1, i2, i3, i4, i5 : longint) : ARRAY_3<T> ; overload;

var
  aIndices  : array [0..4] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  createSlice := ARRAY_3<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          5));
end;

function AdtArrays.createSlice(pArray : ARRAY_8<T>; i1, i2, i3, i4, i5, i6 : longint) : ARRAY_2<T> ; overload;

var
  aIndices  : array [0..5] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          6));
end;

function AdtArrays.createSlice(pArray : ARRAY_8<T>; i1, i2, i3, i4, i5, i6, i7 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..6] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  aIndices[6] := i7;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          7));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1 : longint) : ARRAY_8<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_8<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1, i2 : longint) : ARRAY_7<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_7<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1, i2, i3 : longint) : ARRAY_6<T> ; overload;

var
  aIndices  : array [0..2] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  createSlice := ARRAY_6<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1, i2, i3, i4 : longint) : ARRAY_5<T> ; overload;

var
  aIndices  : array [0..3] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  createSlice := ARRAY_5<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1, i2, i3, i4, i5 : longint) : ARRAY_4<T> ; overload;

var
  aIndices  : array [0..4] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  createSlice := ARRAY_4<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          5));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1, i2, i3, i4, i5, i6 : longint) : ARRAY_3<T> ; overload;

var
  aIndices  : array [0..5] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  createSlice := ARRAY_3<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          6));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1, i2, i3, i4, i5, i6, i7 : longint) : ARRAY_2<T> ; overload;

var
  aIndices  : array [0..6] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  aIndices[6] := i7;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          7));
end;

function AdtArrays.createSlice(pArray : ARRAY_9<T>; i1, i2, i3, i4, i5, i6, i7, i8 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..7] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  aIndices[6] := i7;
  aIndices[7] := i8;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          8));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1 : longint) : ARRAY_9<T> ; overload;

var
  nIndex  : longint;

begin
  nIndex      := i1;
  createSlice := ARRAY_9<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          @nIndex,
                                                          1));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2 : longint) : ARRAY_8<T> ; overload;

var
  aIndices  : array [0..1] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  createSlice := ARRAY_8<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          2));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2, i3 : longint) : ARRAY_7<T> ; overload;

var
  aIndices  : array [0..2] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  createSlice := ARRAY_7<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2, i3, i4 : longint) : ARRAY_6<T> ; overload;

var
  aIndices  : array [0..3] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  createSlice := ARRAY_6<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          4));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2, i3, i4, i5 : longint) : ARRAY_5<T> ; overload;

var
  aIndices  : array [0..4] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  createSlice := ARRAY_5<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          5));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2, i3, i4, i5, i6 : longint) : ARRAY_4<T> ; overload;

var
  aIndices  : array [0..5] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  createSlice := ARRAY_4<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          6));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2, i3, i4, i5, i6, i7 : longint) : ARRAY_3<T> ; overload;

var
  aIndices  : array [0..6] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  aIndices[6] := i7;
  createSlice := ARRAY_3<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          7));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2, i3, i4, i5, i6, i7, i8 : longint) : ARRAY_2<T> ; overload;

var
  aIndices  : array [0..7] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  aIndices[6] := i7;
  aIndices[7] := i8;
  createSlice := ARRAY_2<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          8));
end;

function AdtArrays.createSlice(pArray : ARRAY_10<T>; i1, i2, i3, i4, i5, i6, i7, i8, i9 : longint) : ARRAY_1<T> ; overload;

var
  aIndices  : array [0..8] of longint;

begin
  aIndices[0] := i1;
  aIndices[1] := i2;
  aIndices[2] := i3;
  aIndices[3] := i4;
  aIndices[4] := i5;
  aIndices[5] := i6;
  aIndices[6] := i7;
  aIndices[7] := i8;
  aIndices[8] := i9;
  createSlice := ARRAY_1<T>(AdtArrayPlanActor_createSlice(_MemAllocator,
                                                          pchar(pArray),
                                                          aIndices,
                                                          9));
end;

// Stack size method
function AdtArrays.stackSize(pArray : ARRAY_1<T>) : longint ; overload;

var
  pStackInfo : PAdtStackInfo;

begin
  pStackInfo  := stackInfo(pchar(pArray));
  stackSize   := pStackInfo^.StackSize;
end;

// Stack creation method
function AdtArrays.createStack(var pArray : ARRAY_1<T>; nInitialSize : longint = DEFAULT_STACK_SIZE) : boolean ; overload;

var
  pStack : pchar;

begin
  pStack      := pchar(pArray);
  createStack := createStack(pStack, nInitialSize, varType(pArray));
  pArray      := ARRAY_1<T>(pStack);
end;

// Stack growing method
procedure AdtArrays.growStack(var pArray : ARRAY_1<T>; nIndexNeeded : longint); overload;

var
  pStack : pchar;

begin
  pStack := pchar(pArray);
  growStack(pStack, nIndexNeeded);
  pArray := ARRAY_1<T>(pStack);
end;

// Simplified array creation methods
// 1D
function AdtArrays.create(var pArray : ARRAY_1<T>;
                          nBaseIndex, nSize : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex, nSize,
                                pExisting);
end;

// 2D
function AdtArrays.create(var pArray : ARRAY_2<T>;
                          nBaseIndex1, nSize1 : longint;
                          nBaseIndex2, nSize2 : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                pExisting);
end;

// 3D
function AdtArrays.create(var pArray : ARRAY_3<T>;
                          nBaseIndex1, nSize1 : longint;
                          nBaseIndex2, nSize2 : longint;
                          nBaseIndex3, nSize3 : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                pExisting);
end;

// 4D
function AdtArrays.create(var pArray : ARRAY_4<T>;
                          nBaseIndex1, nSize1 : longint;
                          nBaseIndex2, nSize2 : longint;
                          nBaseIndex3, nSize3 : longint;
                          nBaseIndex4, nSize4 : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                pExisting);
end;

// 5D
function AdtArrays.create(var pArray : ARRAY_5<T>;
                          nBaseIndex1, nSize1 : longint;
                          nBaseIndex2, nSize2 : longint;
                          nBaseIndex3, nSize3 : longint;
                          nBaseIndex4, nSize4 : longint;
                          nBaseIndex5, nSize5 : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                pExisting);
end;

// 6D
function AdtArrays.create(var pArray : ARRAY_6<T>;
                          nBaseIndex1, nSize1 : longint;
                          nBaseIndex2, nSize2 : longint;
                          nBaseIndex3, nSize3 : longint;
                          nBaseIndex4, nSize4 : longint;
                          nBaseIndex5, nSize5 : longint;
                          nBaseIndex6, nSize6 : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                pExisting);
end;

// 7D
function AdtArrays.create(var pArray : ARRAY_7<T>;
                          nBaseIndex1, nSize1 : longint;
                          nBaseIndex2, nSize2 : longint;
                          nBaseIndex3, nSize3 : longint;
                          nBaseIndex4, nSize4 : longint;
                          nBaseIndex5, nSize5 : longint;
                          nBaseIndex6, nSize6 : longint;
                          nBaseIndex7, nSize7 : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                pExisting);
end;

// 8D
function AdtArrays.create(var pArray : ARRAY_8<T>;
                          nBaseIndex1, nSize1 : longint;
                          nBaseIndex2, nSize2 : longint;
                          nBaseIndex3, nSize3 : longint;
                          nBaseIndex4, nSize4 : longint;
                          nBaseIndex5, nSize5 : longint;
                          nBaseIndex6, nSize6 : longint;
                          nBaseIndex7, nSize7 : longint;
                          nBaseIndex8, nSize8 : longint;
                          pExisting : pchar = nil) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                nBaseIndex8, nSize8,
                                pExisting);
end;

// 9D
function AdtArrays.create(var pArray : ARRAY_9<T>;
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

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                nBaseIndex8, nSize8,
                                nBaseIndex9, nSize9,
                                pExisting);
end;

// 10D
function AdtArrays.create(var pArray : ARRAY_10<T>;
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

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray,
                                nBaseIndex1, nSize1,
                                nBaseIndex2, nSize2,
                                nBaseIndex3, nSize3,
                                nBaseIndex4, nSize4,
                                nBaseIndex5, nSize5,
                                nBaseIndex6, nSize6,
                                nBaseIndex7, nSize7,
                                nBaseIndex8, nSize8,
                                nBaseIndex9, nSize9,
                                nBaseIndex10, nSize10,
                                pExisting);
end;
