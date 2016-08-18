// R_to_ADlib methods
procedure AdtArrays.R_to_ADlib(pArraySrc : plongint ; pArrayDest : <T>) ; overload;

begin
  AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(pArraySrc), pchar(pArrayDest));
end;

procedure AdtArrays.R_to_ADlib(pArraySrc : pdouble ; pArrayDest : <T>) ; overload;

begin
  AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(pArraySrc), pchar(pArrayDest));
end;

// ADlib_to_R methods
procedure AdtArrays.ADlib_to_R(pArraySrc : <T> ; pArrayDest : plongint) ; overload;

begin
  AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(pArraySrc), pchar(pArrayDest));
end;

procedure AdtArrays.ADlib_to_R(pArraySrc : <T> ; pArrayDest : pdouble) ; overload;

begin
  AdtArrayPlanActor_R_to_ADlib(_MemAllocator, pchar(pArraySrc), pchar(pArrayDest));
end;

// zero methods
procedure AdtArrays.zero(pArray : <T>) ; overload;

var
  pArrayInfo : PAdtArrayInfo;

begin
  pArrayInfo := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));

  AdtArray.zero(pArrayInfo^);
end;

// xcopy methods
procedure AdtArrays.xcopy(pArraySrc, pArrayDest : <T>) ; overload;

var
  pArrayInfoSrc   : PAdtArrayInfo;
  pArrayInfoDest  : PAdtArrayInfo;

begin
  pArrayInfoSrc   := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArraySrc));
  pArrayInfoDest  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArrayDest));

  AdtArray.xcopy(pArrayInfoDest^, pArrayInfoSrc);
end;

// Same shape array creation method - copying shape from existing array
function AdtArrays.create(var pArray : <T>; pRefArray : <T>) : boolean ; overload;

begin
  create := AdtArrayPlan_create(_MemAllocator, pArray, pRefArray);
end;

// array destruction method
procedure AdtArrays.destroy(var pArray : <T>) ; overload;

begin
  AdtArrayPlan_destroy(_MemAllocator, pArray);
end;

