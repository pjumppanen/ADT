// Same shape array creation method
function AdtArrayPlan_create(var rAllocator : AdtMemAllocator; var pArray : <T>; const pRefArray : <T>) : boolean ; overload;

begin
  pArray := <T>(AdtArrayPlanActor_createSameShape(rAllocator, pchar(pRefArray)));

  AdtArrayPlan_create := (pArray <> nil);
end;

// array destruction method
procedure AdtArrayPlan_destroy(var rAllocator : AdtMemAllocator; var pArray : <T>) ; overload;

begin
  AdtArrayPlanActor_destroy(rAllocator, pchar(pArray));
end;
