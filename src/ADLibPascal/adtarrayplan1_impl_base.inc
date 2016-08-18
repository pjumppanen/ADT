//  ----------------------------------------------------------------------------
// existing array query method - use to obtain an array from a pointer
// passed from R that has previously been mapped by this array plan
function AdtArrayPlan.existing(var pArray : <T>; pExisting : pchar) : boolean ; overload;

begin
  if (Actor <> nil) then
    pArray := <T>(Actor.existing(varType(pArray), pExisting))
  else
    pArray := nil;

  existing := (pArray <> nil);
end;

// New array creation method
function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : <T>; pExisting : pchar = nil) : boolean ; overload;

begin
  if (Actor <> nil) then
    pArray := <T>(Actor.create(rAllocator, varType(pArray), pExisting))
  else
    pArray := nil;

  create := (pArray <> nil);
end;

