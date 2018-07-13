// zero methods
procedure zero(pArray : <T>) ; overload;

// xcopy methods
procedure xcopy(pArraySrc, pArrayDest : <T>) ; overload;

// Same shape array creation method - copying shape from existing array
function create(var pArray : <T>; pRefArray : <T>) : boolean ; overload;

// array destruction method
procedure destroy(var pArray : <T>) ; overload;
