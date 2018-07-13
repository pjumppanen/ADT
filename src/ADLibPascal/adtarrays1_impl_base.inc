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
