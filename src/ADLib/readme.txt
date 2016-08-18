Using the ADLib support library for simpler array programming
-------------------------------------------------------------
The ADT package (automatic differentiation through translation) utility has a
companion library to implement simplified and efficient array programming.
The arrays it creates and manages can have up to 10 dimensions with user
defined starting indices and sizes. The arrays are allocated in a single,
flat and contiguous block of memory to aid in improved computational
performance and easier interfacing with R arrays.

Arrays can be created independently or managed within an AdtArrays class in
a manner somewhat equivalent to Mark Bravington's Teasy_alloc_object delphi
class. A second class, AdtDiff, which inherits from AdtArrays, implements
extra mathematical functionality useful for scientific computing and is
somewhat equivalent to Mark Bravington's Tuseful_obj delphi class. You will
typically use the library by declaring your own class which publically inherits
from AdtDiff and then implements the required numerical computation through
class methods.


Array types
-----------
Multi-dimensional Arrays can be created for any of the intrinsic data types
within the C/C++ language. To simplify coding and readability, adtarrays.hpp
defines typdef'ed aliases for the different size and type arrays. The general
format of the type name follows the pattern,

ARRAY_{number of dimensions}{type characters}

The number of dimensions can be between 1 and 10 inclusive and the type
characters map to intrinsic types as in the following table.


type            type characters
-------------------------------
bool            B
char            C
unsigned char   UC
int             I
unsigned int    UI
short           S
unsigned short  US
long            L
unsigned long   UL
float           F
double          D

For example, if we want a 3 dimensional array of doubles then the type
would be ARRAY_3D.


Creating Arrays
---------------
Arrays can be created in one of two ways, either with explicitely defined
size/shape using an AdtArrayPlan instance, or implicitely by copying the
shape of an existing array.

Explicitely specifying the array size and base indices is done through an
AdtArrayPlan instance. The constructor is overloaded to cater for different
dimension arrays and follows the generalised form,

AdtArrayPlan(int nBaseIndex1, int nSize1,
             int nBaseIndex2, int nSize2,
             int nBaseIndex3, int nSize3,
                     .              .
                     .              .
                     .              .    );

up to a maximum dimension of 10. To create an array of that form with that
size we call the create() method. As an example, lets say we want to create
a series of 6 by 4 arrays whose indices are one based. We create an
AdtArrayPlan instance that describes the array size with,

AdtArrayPlan    SixByFour(1,6,1,4);

Then we call the create method to make the array with,

ARRAY_2D    Array1 = 0;
ARRAY_2D    Array2 = 0;
ARRAY_2I    Array3 = 0;

SixByFour.create(MemAllocator, Array1);
SixByFour.create(MemAllocator, Array2);
SixByFour.create(MemAllocator, Array3);

The above code creates three arrays, six by four in size, whose base index
is one. Array1 and Array2 are arrays of double's and Array3 is an array of
int's.

Note that we must supply an instance of the class AdtMemAllocator to do
the memory allocation for the arrays. It is structured this way to facilitate
simpler management of arrays and their life cycle because if we fail to
free the arrays explicitely they will be freed when MemAllocator is freed.
Similarly, MemAllocator knows all about the arrays it creates so it can
then easily create a same shaped array from any that it has previously
created without the need of a plan.

If the allocation code above appears in a method of your class derived
from AdtDiff (or AdtArrays for that matter) then you will not need to create
a AdtMemAllocator instance as the AdtArrays class has its own instance named
MemAllocator.

To create a same shaped array of an existing one we call the static create
method of AdtArrayPlan with a parent array as the third argument in the call.
Note that the parent array must be of the same type as the copy. For example,

ARRAY_2I    Array4 = 0;

AdtArrayPlan::create(MemAllocator, Array4, Array3);

will create Array4 with the same plan as Array3. If you are writing code
within a method of your derived AdtDiff class then we can use the simpler
equivalent create method in the AdtArrays class with the call,

create(Array4, Array5);


Mapping Memory as an Array
--------------------------
There is one other way we can create arrays and that is creating a map
into a block of memory to be accessed as an array. The typical usage might
be that you have a block of memory representing a 9 by 8 element matrix
that has been passed to you from R and you want to index it in a simple
fashion (R data structures are all simple blocks of memory irrespective
of the dimension). To do so, we create a plan that fits the structure of
the memory being passed to us and then pass an extra parameter in the
create call, which is the pointer to the existing block of memory. For
example,

AdtArrayPlan    NineByEigth(1,9,1,8);
ARRAY_2D        AliasArray = 0;

SixByFour.create(MemAllocator, AliasArray, (void*)pR_ArrayMemory);


Destroying Arrays
-----------------
If you wish to discard an array that is no longer needed and reclaim the
memory on the heap you can do so as follows. Either call,

AdtArrayPlan::destroy(MemAllocator, Array4);

or if in the context of a AdtDiff derived class method, call,

destroy(Array4);


Ragged Arrays
-------------
In certain problems we may have multi-dimensional arrays where many
elements are zero and need not be stored. In such circumstances being
able to create ragged arrays may be helpful. ADLib allows the outer
dimensions of an array to be ragged (vectors with different lengths)
though creating a plan for such arrays is a little more involved.

As an example, lets say we wish to create a two dimensional array which
comprises two vectors of different lengths, one 5 elements in length and
the other 25. Furthermore we will use zero based indexing. The following
code fragment creates an array plan matching these requirements.

AdtArrayPlan    Ragged;
int             BaseIndices[2] = {0, 0};
int             Sizes[2] = {5, 25};

Ragged.beginRagged(0, 2);

for (int cn = 0 ; cn < 2 ; cn++)
{
  AdtArrayPlan  InnerArrayPlan(BaseIndices[cn], Sizes[cn]);

  Ragged.addArrayPlan(InnerArrayPlan, cn);
}

Ragged.endRagged();

To make a ragged column we need to call the beginRagged() method of the
plan we are adding the column to specifying the base index and the size
of the column. This can be seen from the method prototype,

bool beginRagged(int nBaseIndex, int nSize);

which returns true if successful. After calling beginRagged() we need to
loop through all the indices of the column and add array plans that specify
the base index and size of that column entry using the addArrayPlan()
method, whose prototype is,

bool addArrayPlan(AdtArrayPlan& rArrayPlan, int nIndex);

After specifying plans for all column entries we finalise the plan by
calling the endRagged() method. It is essential that beginRagged() is
always paired with a corresponding endRagged() call.

After endRagged() has been called arrays conforming to that plan can be
created in the manner already outlined. These ragged arrays will be
allocated as one contiguous block of memory irrespective of the array
shape. Similarly, array mapping of existing blocks of memory works in the
same manner as for conventional arrays.


Using the Arrays
----------------
Once created the arrays are simply used in the same manner as conventional
n-dimensional C arrays. As an example, the code fragment below calculates
the average of all the elements in our 9 by 8 array passed from R above.

int    cn;
int    cm;
double dAverage = 0.0;

for (cn = 1 ; cn <= 9 ; cn++)
{
  for (cm = 1 ; cm <= 8 ; cm++)
  {
    dAverage += AliasArray[cn][cm];
  }
}

dAverage /= (9 * 8);

The main difference C/C++ code is that array bases are traditionally always
zero whereas the base index in our case is determined by the plan that
created the array.
