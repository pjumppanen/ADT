//  ----------------------------------------------------------------------------
// existing array query method - use to obtain an array from a pointer
// passed from R that has previously been mapped by this array plan
function existing(var pArray : <T>; pExisting : pchar) : boolean ; overload;

// New array creation method
function create(rAllocator : AdtMemAllocator; var pArray : <T>; pExisting : pchar = nil) : boolean ; overload;
