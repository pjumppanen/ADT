// R_to_ADlib methods
procedure R_to_ADlib(pArraySrc : plongint ; pArrayDest : <T>) ; overload;

procedure R_to_ADlib(pArraySrc : pdouble ; pArrayDest : <T>) ; overload;

// ADlib_to_R methods
procedure ADlib_to_R(pArraySrc : <T> ; pArrayDest : plongint) ; overload;

procedure ADlib_to_R(pArraySrc : <T> ; pArrayDest : pdouble) ; overload;

// zero methods
procedure zero(pArray : <T>) ; overload;

// xcopy methods
procedure xcopy(pArraySrc, pArrayDest : <T>) ; overload;

// Same shape array creation method - copying shape from existing array
function create(var pArray : <T>; pRefArray : <T>) : boolean ; overload;

// array destruction method
procedure destroy(var pArray : <T>) ; overload;

