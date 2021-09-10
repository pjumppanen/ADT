//  ----------------------------------------------------------------------------
//  ADT - automatic differentiation through translation
//  ----------------------------------------------------------------------------
//  Software for the generation of auto-differentiated code using TAPENADE.
//
//  Copyright by the COMMONWEALTH SCIENTIFIC AND INDUSTRIAL RESEARCH
//  ORGANISATION (CSIRO), Australia.
//  All rights reserved.
//
//  This file is part of ADT.  The full ADT copyright notice, including
//  terms governing use, modification, and redistribution, is contained in
//  the file COPYING. COPYING can be found at the root of the source code
//  distribution tree;
//  ----------------------------------------------------------------------------
//  File:
//    adtlibtests.cpp
//
//  Purpose:
//    This file implements test harness code to check the validity of the
//    ADLib library code. ADLib is the functional equivalent of TUseful in
//    delphi applications.
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtstack.hpp"
#include "adtarrays.hpp"
#include <stdio.h>


//  ----------------------------------------------------------------------------
//  Mappings of int by char*
//  ----------------------------------------------------------------------------
typedef std::pair<const char*, int>           CharPtrIntPair;
typedef std::map<char*, int>                  IntByCharPtrMap;
typedef std::map<char*, int>::iterator        IntByCharPtrMapIter;
typedef std::map<char*, int>::const_iterator  IntByCharPtrMapConstIter;


//  ----------------------------------------------------------------------------
//  AdtADLibTest template class
//  ----------------------------------------------------------------------------
//  T is the raw array data type, one of:
//    bool
//    char
//    unsigned char
//    int
//    unsigned int
//    short
//    unsigned short
//    long
//    unsigned long
//    float
//    double
//
//  We do tests on a range of issues over the supported dimensions in the
//  library (from 1 dimensional to 10 dimensional).
//  ----------------------------------------------------------------------------
template <class T> class AdtADLibTest
{
private:
  bool    Passed;

protected:
  void test_1D(const char* pTypeName)
  {
    T*              pArray      = 0;
    int             nBaseIndex  = 5 - rand() % 10;
    int             nSize       = 1000;
    AdtArrayPlan    ArrayPlan(nBaseIndex, nSize);
    AdtMemAllocator Allocator;

    printf("Testing %s 1D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      int c0;

      for (c0 = nBaseIndex ; c0 < nBaseIndex + nSize ; c0++)
      {
        pArray[c0] = (T)(1000 - (rand() % 2000));
      }

      // Testing max and min array functions
      T rMax = max(pArray, nBaseIndex, nBaseIndex + nSize);
      T rMin = min(pArray, nBaseIndex, nBaseIndex + nSize);

      for (c0 = nBaseIndex ; c0 < nBaseIndex + nSize ; c0++)
      {
        if (pArray[c0] > rMax)
        {
          printf("FAILED, max() array function returned wrong result\n");
          Passed = false;
          break;
        }
        else if (pArray[c0] < rMin)
        {
          printf("FAILED, min() array function returned wrong result\n");
          Passed = false;
          break;
        }
      }

      // Note that for 1D arrays we cannot pass the existing array created
      // above as the existing array into the create() method of AdtArrayPlan
      // because that address is already "known" to the Allocator.
      //
      // To stop the code from failing and to allow the test to run we create
      // a copy of the array and use that to pass to the create method.
      //
      // This work-around is a non-issue in real applications where the
      // "existing" array being aliased will always be unknown to the Allocator.
      T*  pExisting = new T[1000];

      if (pExisting != 0)
      {
        T*  pArray2         = 0;
        T*  pExistingArray  = 0;

        if (ArrayPlan.existing(pExistingArray, (void*)pExisting))
        {
          printf("FAILED, existing array found when a mapping hasn't been created yet\n");
          Passed = false;
        }

        memcpy(pExisting, &pArray[nBaseIndex], sizeof(T) * 1000);

        if (ArrayPlan.create(Allocator, pArray2, (void*)pExisting))
        {
          for (int c0 = nBaseIndex ; c0 < nBaseIndex + nSize ; c0++)
          {
            if (Passed && (pArray[c0] != pArray2[c0]))
            {
              printf("FAILED, Array contents don't match\n");
              Passed = false;
              break;
            }
          }

          if (!ArrayPlan.existing(pExistingArray, (void*)pExisting))
          {
            printf("FAILED, existing array not found when a previous mapping has been created\n");
            Passed = false;
          }
          else if (pExistingArray != pArray2)
          {
            printf("FAILED, returned existing array pointer invalid\n");
            Passed = false;
          }
        }
        else
        {
          printf("FAILED, Can't create array\n");
          Passed = false;
        }

        delete[] pExisting;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_2D(const char* pTypeName)
  {
    T**             pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nSize1      = 40;
    int             nSize2      = 30;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2);
    AdtMemAllocator Allocator;

    printf("Testing %s 2D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      for (int c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (int c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          pArray[c1][c2] = (T)(1000 - (rand() % 2000));
        }
      }

      T** pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2]))
      {
        for (int c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (int c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            if (Passed && (pArray[c1][c2] != pArray2[c1][c2]))
            {
              printf("FAILED, Array contents don't match\n");
              Passed = false;
              break;
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_3D(const char* pTypeName)
  {
    T***            pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nSize1      = 10;
    int             nSize2      = 15;
    int             nSize3      = 20;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3);
    AdtMemAllocator Allocator;

    printf("Testing %s 3D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && ((Addr3 < pDataAddress) || (Addr3 > pMaxAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            if (Passed && ((Addr3 - pLastDataAddr) != sizeof(T)))
            {
              printf("FAILED, Data addresses are not monitonically increasing\n");
              Passed = false;
            }

            pLastDataAddr = Addr3;
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            pArray[c1][c2][c3] = (T)(1000 - (rand() % 2000));
          }
        }
      }

      T*** pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              if (Passed && (pArray[c1][c2][c3] != pArray2[c1][c2][c3]))
              {
                printf("FAILED, Array contents don't match\n");
                Passed = false;
                break;
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_4D(const char* pTypeName)
  {
    T****           pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nBaseIndex4 = 5 - rand() % 10;
    int             nSize1      = 8;
    int             nSize2      = 12;
    int             nSize3      = 7;
    int             nSize4      = 5;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3,
                              nBaseIndex4, nSize4);
    AdtMemAllocator Allocator;

    printf("Testing %s 4D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      int             c4;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && (AddrMap.find(Addr3) != AddrMap.end()))
            {
              printf("FAILED, Addresses being recycled\n");
              Passed = false;
              break;
            }

            AddrMap[Addr3] = 1;

            if (Passed && ((Addr3 < pMinAddress) || (Addr3 > pDataAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              char* Addr4 = (char*)(&(pArray[c1][c2][c3][c4]));

              if (Passed && ((Addr4 < pDataAddress) || (Addr4 > pMaxAddress)))
              {
                printf("FAILED, LUT out of address range\n");
                Passed = false;
                break;
              }

              if (Passed && ((Addr4 - pLastDataAddr) != sizeof(T)))
              {
                printf("FAILED, Data addresses are not monitonically increasing\n");
                Passed = false;
              }

              pLastDataAddr = Addr4;
            }
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              pArray[c1][c2][c3][c4] = (T)(1000 - (rand() % 2000));
            }
          }
        }
      }

      T**** pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3][nBaseIndex4]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
              {
                if (Passed && (pArray[c1][c2][c3][c4] != pArray2[c1][c2][c3][c4]))
                {
                  printf("FAILED, Array contents don't match\n");
                  Passed = false;
                  break;
                }
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_5D(const char* pTypeName)
  {
    T*****          pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nBaseIndex4 = 5 - rand() % 10;
    int             nBaseIndex5 = 5 - rand() % 10;
    int             nSize1      = 6;
    int             nSize2      = 7;
    int             nSize3      = 9;
    int             nSize4      = 4;
    int             nSize5      = 3;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3,
                              nBaseIndex4, nSize4,
                              nBaseIndex5, nSize5);
    AdtMemAllocator Allocator;

    printf("Testing %s 5D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      int             c4;
      int             c5;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && (AddrMap.find(Addr3) != AddrMap.end()))
            {
              printf("FAILED, Addresses being recycled\n");
              Passed = false;
              break;
            }

            AddrMap[Addr3] = 1;

            if (Passed && ((Addr3 < pMinAddress) || (Addr3 > pDataAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              char* Addr4 = (char*)(&(pArray[c1][c2][c3][c4]));

              if (Passed && (AddrMap.find(Addr4) != AddrMap.end()))
              {
                printf("FAILED, Addresses being recycled\n");
                Passed = false;
                break;
              }

              AddrMap[Addr4] = 1;

              if (Passed && ((Addr4 < pMinAddress) || (Addr4 > pDataAddress)))
              {
                printf("FAILED, LUT out of address range\n");
                Passed = false;
                break;
              }

              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                char* Addr5 = (char*)(&(pArray[c1][c2][c3][c4][c5]));

                if (Passed && ((Addr5 < pDataAddress) || (Addr5 > pMaxAddress)))
                {
                  printf("FAILED, LUT out of address range\n");
                  Passed = false;
                  break;
                }

                if (Passed && ((Addr5 - pLastDataAddr) != sizeof(T)))
                {
                  printf("FAILED, Data addresses are not monitonically increasing\n");
                  Passed = false;
                }

                pLastDataAddr = Addr5;
              }
            }
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                pArray[c1][c2][c3][c4][c5] = (T)(1000 - (rand() % 2000));
              }
            }
          }
        }
      }

      T***** pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3][nBaseIndex4][nBaseIndex5]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
              {
                for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
                {
                  if (Passed && (pArray[c1][c2][c3][c4][c5] != pArray2[c1][c2][c3][c4][c5]))
                  {
                    printf("FAILED, Array contents don't match\n");
                    Passed = false;
                    break;
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_6D(const char* pTypeName)
  {
    T******         pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nBaseIndex4 = 5 - rand() % 10;
    int             nBaseIndex5 = 5 - rand() % 10;
    int             nBaseIndex6 = 5 - rand() % 10;
    int             nSize1      = 5;
    int             nSize2      = 6;
    int             nSize3      = 9;
    int             nSize4      = 4;
    int             nSize5      = 3;
    int             nSize6      = 3;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3,
                              nBaseIndex4, nSize4,
                              nBaseIndex5, nSize5,
                              nBaseIndex6, nSize6);
    AdtMemAllocator Allocator;

    printf("Testing %s 6D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      int             c4;
      int             c5;
      int             c6;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && (AddrMap.find(Addr3) != AddrMap.end()))
            {
              printf("FAILED, Addresses being recycled\n");
              Passed = false;
              break;
            }

            AddrMap[Addr3] = 1;

            if (Passed && ((Addr3 < pMinAddress) || (Addr3 > pDataAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              char* Addr4 = (char*)(&(pArray[c1][c2][c3][c4]));

              if (Passed && (AddrMap.find(Addr4) != AddrMap.end()))
              {
                printf("FAILED, Addresses being recycled\n");
                Passed = false;
                break;
              }

              AddrMap[Addr4] = 1;

              if (Passed && ((Addr4 < pMinAddress) || (Addr4 > pDataAddress)))
              {
                printf("FAILED, LUT out of address range\n");
                Passed = false;
                break;
              }

              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                char* Addr5 = (char*)(&(pArray[c1][c2][c3][c4][c5]));

                if (Passed && (AddrMap.find(Addr5) != AddrMap.end()))
                {
                  printf("FAILED, Addresses being recycled\n");
                  Passed = false;
                  break;
                }

                AddrMap[Addr5] = 1;

                if (Passed && ((Addr5 < pMinAddress) || (Addr5 > pDataAddress)))
                {
                  printf("FAILED, LUT out of address range\n");
                  Passed = false;
                  break;
                }

                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  char* Addr6 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6]));

                  if (Passed && ((Addr6 < pDataAddress) || (Addr6 > pMaxAddress)))
                  {
                    printf("FAILED, LUT out of address range\n");
                    Passed = false;
                    break;
                  }

                  if (Passed && ((Addr6 - pLastDataAddr) != sizeof(T)))
                  {
                    printf("FAILED, Data addresses are not monitonically increasing\n");
                    Passed = false;
                  }

                  pLastDataAddr = Addr6;
                }
              }
            }
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  pArray[c1][c2][c3][c4][c5][c6] = (T)(1000 - (rand() % 2000));
                }
              }
            }
          }
        }
      }

      T****** pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3][nBaseIndex4][nBaseIndex5][nBaseIndex6]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
              {
                for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
                {
                  for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                  {
                    if (Passed && (pArray[c1][c2][c3][c4][c5][c6] != pArray2[c1][c2][c3][c4][c5][c6]))
                    {
                      printf("FAILED, Array contents don't match\n");
                      Passed = false;
                      break;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_7D(const char* pTypeName)
  {
    T*******        pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nBaseIndex4 = 5 - rand() % 10;
    int             nBaseIndex5 = 5 - rand() % 10;
    int             nBaseIndex6 = 5 - rand() % 10;
    int             nBaseIndex7 = 5 - rand() % 10;
    int             nSize1      = 5;
    int             nSize2      = 6;
    int             nSize3      = 7;
    int             nSize4      = 4;
    int             nSize5      = 3;
    int             nSize6      = 3;
    int             nSize7      = 3;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3,
                              nBaseIndex4, nSize4,
                              nBaseIndex5, nSize5,
                              nBaseIndex6, nSize6,
                              nBaseIndex7, nSize7);
    AdtMemAllocator Allocator;

    printf("Testing %s 7D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      int             c4;
      int             c5;
      int             c6;
      int             c7;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && (AddrMap.find(Addr3) != AddrMap.end()))
            {
              printf("FAILED, Addresses being recycled\n");
              Passed = false;
              break;
            }

            AddrMap[Addr3] = 1;

            if (Passed && ((Addr3 < pMinAddress) || (Addr3 > pDataAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              char* Addr4 = (char*)(&(pArray[c1][c2][c3][c4]));

              if (Passed && (AddrMap.find(Addr4) != AddrMap.end()))
              {
                printf("FAILED, Addresses being recycled\n");
                Passed = false;
                break;
              }

              AddrMap[Addr4] = 1;

              if (Passed && ((Addr4 < pMinAddress) || (Addr4 > pDataAddress)))
              {
                printf("FAILED, LUT out of address range\n");
                Passed = false;
                break;
              }

              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                char* Addr5 = (char*)(&(pArray[c1][c2][c3][c4][c5]));

                if (Passed && (AddrMap.find(Addr5) != AddrMap.end()))
                {
                  printf("FAILED, Addresses being recycled\n");
                  Passed = false;
                  break;
                }

                AddrMap[Addr5] = 1;

                if (Passed && ((Addr5 < pMinAddress) || (Addr5 > pDataAddress)))
                {
                  printf("FAILED, LUT out of address range\n");
                  Passed = false;
                  break;
                }

                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  char* Addr6 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6]));

                  if (Passed && (AddrMap.find(Addr6) != AddrMap.end()))
                  {
                    printf("FAILED, Addresses being recycled\n");
                    Passed = false;
                    break;
                  }

                  AddrMap[Addr6] = 1;

                  if (Passed && ((Addr6 < pMinAddress) || (Addr6 > pDataAddress)))
                  {
                    printf("FAILED, LUT out of address range\n");
                    Passed = false;
                    break;
                  }

                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    char* Addr7 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7]));

                    if (Passed && ((Addr7 < pDataAddress) || (Addr7 > pMaxAddress)))
                    {
                      printf("FAILED, LUT out of address range\n");
                      Passed = false;
                      break;
                    }

                    if (Passed && ((Addr7 - pLastDataAddr) != sizeof(T)))
                    {
                      printf("FAILED, Data addresses are not monitonically increasing\n");
                      Passed = false;
                    }

                    pLastDataAddr = Addr7;
                  }
                }
              }
            }
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    pArray[c1][c2][c3][c4][c5][c6][c7] = (T)(1000 - (rand() % 2000));
                  }
                }
              }
            }
          }
        }
      }

      T******* pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3][nBaseIndex4][nBaseIndex5][nBaseIndex6][nBaseIndex7]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
              {
                for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
                {
                  for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                  {
                    for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                    {
                      if (Passed && (pArray[c1][c2][c3][c4][c5][c6][c7] != pArray2[c1][c2][c3][c4][c5][c6][c7]))
                      {
                        printf("FAILED, Array contents don't match\n");
                        Passed = false;
                        break;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_8D(const char* pTypeName)
  {
    T********       pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nBaseIndex4 = 5 - rand() % 10;
    int             nBaseIndex5 = 5 - rand() % 10;
    int             nBaseIndex6 = 5 - rand() % 10;
    int             nBaseIndex7 = 5 - rand() % 10;
    int             nBaseIndex8 = 5 - rand() % 10;
    int             nSize1      = 5;
    int             nSize2      = 5;
    int             nSize3      = 6;
    int             nSize4      = 4;
    int             nSize5      = 3;
    int             nSize6      = 3;
    int             nSize7      = 3;
    int             nSize8      = 2;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3,
                              nBaseIndex4, nSize4,
                              nBaseIndex5, nSize5,
                              nBaseIndex6, nSize6,
                              nBaseIndex7, nSize7,
                              nBaseIndex8, nSize8);
    AdtMemAllocator Allocator;

    printf("Testing %s 8D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      int             c4;
      int             c5;
      int             c6;
      int             c7;
      int             c8;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && (AddrMap.find(Addr3) != AddrMap.end()))
            {
              printf("FAILED, Addresses being recycled\n");
              Passed = false;
              break;
            }

            AddrMap[Addr3] = 1;

            if (Passed && ((Addr3 < pMinAddress) || (Addr3 > pDataAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              char* Addr4 = (char*)(&(pArray[c1][c2][c3][c4]));

              if (Passed && (AddrMap.find(Addr4) != AddrMap.end()))
              {
                printf("FAILED, Addresses being recycled\n");
                Passed = false;
                break;
              }

              AddrMap[Addr4] = 1;

              if (Passed && ((Addr4 < pMinAddress) || (Addr4 > pDataAddress)))
              {
                printf("FAILED, LUT out of address range\n");
                Passed = false;
                break;
              }

              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                char* Addr5 = (char*)(&(pArray[c1][c2][c3][c4][c5]));

                if (Passed && (AddrMap.find(Addr5) != AddrMap.end()))
                {
                  printf("FAILED, Addresses being recycled\n");
                  Passed = false;
                  break;
                }

                AddrMap[Addr5] = 1;

                if (Passed && ((Addr5 < pMinAddress) || (Addr5 > pDataAddress)))
                {
                  printf("FAILED, LUT out of address range\n");
                  Passed = false;
                  break;
                }

                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  char* Addr6 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6]));

                  if (Passed && (AddrMap.find(Addr6) != AddrMap.end()))
                  {
                    printf("FAILED, Addresses being recycled\n");
                    Passed = false;
                    break;
                  }

                  AddrMap[Addr6] = 1;

                  if (Passed && ((Addr6 < pMinAddress) || (Addr6 > pDataAddress)))
                  {
                    printf("FAILED, LUT out of address range\n");
                    Passed = false;
                    break;
                  }

                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    char* Addr7 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7]));

                    if (Passed && (AddrMap.find(Addr7) != AddrMap.end()))
                    {
                      printf("FAILED, Addresses being recycled\n");
                      Passed = false;
                      break;
                    }

                    AddrMap[Addr7] = 1;

                    if (Passed && ((Addr7 < pMinAddress) || (Addr7 > pDataAddress)))
                    {
                      printf("FAILED, LUT out of address range\n");
                      Passed = false;
                      break;
                    }

                    for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                    {
                      char* Addr8 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7][c8]));

                      if (Passed && ((Addr8 < pDataAddress) || (Addr8 > pMaxAddress)))
                      {
                        printf("FAILED, LUT out of address range\n");
                        Passed = false;
                        break;
                      }

                      if (Passed && ((Addr8 - pLastDataAddr) != sizeof(T)))
                      {
                        printf("FAILED, Data addresses are not monitonically increasing\n");
                        Passed = false;
                      }

                      pLastDataAddr = Addr8;
                    }
                  }
                }
              }
            }
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                    {
                      pArray[c1][c2][c3][c4][c5][c6][c7][c8] = (T)(1000 - (rand() % 2000));
                    }
                  }
                }
              }
            }
          }
        }
      }

      T******** pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3][nBaseIndex4][nBaseIndex5][nBaseIndex6][nBaseIndex7][nBaseIndex8]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
              {
                for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
                {
                  for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                  {
                    for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                    {
                      for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                      {
                        if (Passed && (pArray[c1][c2][c3][c4][c5][c6][c7][c8] != pArray2[c1][c2][c3][c4][c5][c6][c7][c8]))
                        {
                          printf("FAILED, Array contents don't match\n");
                          Passed = false;
                          break;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_9D(const char* pTypeName)
  {
    T*********      pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nBaseIndex4 = 5 - rand() % 10;
    int             nBaseIndex5 = 5 - rand() % 10;
    int             nBaseIndex6 = 5 - rand() % 10;
    int             nBaseIndex7 = 5 - rand() % 10;
    int             nBaseIndex8 = 5 - rand() % 10;
    int             nBaseIndex9 = 5 - rand() % 10;
    int             nSize1      = 4;
    int             nSize2      = 5;
    int             nSize3      = 3;
    int             nSize4      = 4;
    int             nSize5      = 3;
    int             nSize6      = 4;
    int             nSize7      = 3;
    int             nSize8      = 2;
    int             nSize9      = 2;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3,
                              nBaseIndex4, nSize4,
                              nBaseIndex5, nSize5,
                              nBaseIndex6, nSize6,
                              nBaseIndex7, nSize7,
                              nBaseIndex8, nSize8,
                              nBaseIndex9, nSize9);
    AdtMemAllocator Allocator;

    printf("Testing %s 9D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      int             c4;
      int             c5;
      int             c6;
      int             c7;
      int             c8;
      int             c9;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && (AddrMap.find(Addr3) != AddrMap.end()))
            {
              printf("FAILED, Addresses being recycled\n");
              Passed = false;
              break;
            }

            AddrMap[Addr3] = 1;

            if (Passed && ((Addr3 < pMinAddress) || (Addr3 > pDataAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              char* Addr4 = (char*)(&(pArray[c1][c2][c3][c4]));

              if (Passed && (AddrMap.find(Addr4) != AddrMap.end()))
              {
                printf("FAILED, Addresses being recycled\n");
                Passed = false;
                break;
              }

              AddrMap[Addr4] = 1;

              if (Passed && ((Addr4 < pMinAddress) || (Addr4 > pDataAddress)))
              {
                printf("FAILED, LUT out of address range\n");
                Passed = false;
                break;
              }

              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                char* Addr5 = (char*)(&(pArray[c1][c2][c3][c4][c5]));

                if (Passed && (AddrMap.find(Addr5) != AddrMap.end()))
                {
                  printf("FAILED, Addresses being recycled\n");
                  Passed = false;
                  break;
                }

                AddrMap[Addr5] = 1;

                if (Passed && ((Addr5 < pMinAddress) || (Addr5 > pDataAddress)))
                {
                  printf("FAILED, LUT out of address range\n");
                  Passed = false;
                  break;
                }

                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  char* Addr6 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6]));

                  if (Passed && (AddrMap.find(Addr6) != AddrMap.end()))
                  {
                    printf("FAILED, Addresses being recycled\n");
                    Passed = false;
                    break;
                  }

                  AddrMap[Addr6] = 1;

                  if (Passed && ((Addr6 < pMinAddress) || (Addr6 > pDataAddress)))
                  {
                    printf("FAILED, LUT out of address range\n");
                    Passed = false;
                    break;
                  }

                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    char* Addr7 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7]));

                    if (Passed && (AddrMap.find(Addr7) != AddrMap.end()))
                    {
                      printf("FAILED, Addresses being recycled\n");
                      Passed = false;
                      break;
                    }

                    AddrMap[Addr7] = 1;

                    if (Passed && ((Addr7 < pMinAddress) || (Addr7 > pDataAddress)))
                    {
                      printf("FAILED, LUT out of address range\n");
                      Passed = false;
                      break;
                    }

                    for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                    {
                      char* Addr8 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7][c8]));

                      if (Passed && (AddrMap.find(Addr8) != AddrMap.end()))
                      {
                        printf("FAILED, Addresses being recycled\n");
                        Passed = false;
                        break;
                      }

                      AddrMap[Addr8] = 1;

                      if (Passed && ((Addr8 < pMinAddress) || (Addr8 > pDataAddress)))
                      {
                        printf("FAILED, LUT out of address range\n");
                        Passed = false;
                        break;
                      }

                      for (c9 = nBaseIndex9 ; c9 < nBaseIndex9 + nSize9 ; c9++)
                      {
                        char* Addr9 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7][c8][c9]));

                        if (Passed && ((Addr9 < pDataAddress) || (Addr9 > pMaxAddress)))
                        {
                          printf("FAILED, LUT out of address range\n");
                          Passed = false;
                          break;
                        }

                        if (Passed && ((Addr9 - pLastDataAddr) != sizeof(T)))
                        {
                          printf("FAILED, Data addresses are not monitonically increasing\n");
                          Passed = false;
                        }

                        pLastDataAddr = Addr9;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                    {
                      for (c9 = nBaseIndex9 ; c9 < nBaseIndex9 + nSize9 ; c9++)
                      {
                        pArray[c1][c2][c3][c4][c5][c6][c7][c8][c9] = (T)(1000 - (rand() % 2000));
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      T********* pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3][nBaseIndex4][nBaseIndex5][nBaseIndex6][nBaseIndex7][nBaseIndex8][nBaseIndex9]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
              {
                for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
                {
                  for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                  {
                    for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                    {
                      for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                      {
                        for (c9 = nBaseIndex9 ; c9 < nBaseIndex9 + nSize9 ; c9++)
                        {
                          if (Passed && (pArray[c1][c2][c3][c4][c5][c6][c7][c8][c9] != pArray2[c1][c2][c3][c4][c5][c6][c7][c8][c9]))
                          {
                            printf("FAILED, Array contents don't match\n");
                            Passed = false;
                            break;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_10D(const char* pTypeName)
  {
    T**********     pArray      = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nBaseIndex3 = 5 - rand() % 10;
    int             nBaseIndex4 = 5 - rand() % 10;
    int             nBaseIndex5 = 5 - rand() % 10;
    int             nBaseIndex6 = 5 - rand() % 10;
    int             nBaseIndex7 = 5 - rand() % 10;
    int             nBaseIndex8 = 5 - rand() % 10;
    int             nBaseIndex9 = 5 - rand() % 10;
    int             nBaseIndex10 = 5 - rand() % 10;
    int             nSize1      = 4;
    int             nSize2      = 5;
    int             nSize3      = 3;
    int             nSize4      = 4;
    int             nSize5      = 3;
    int             nSize6      = 4;
    int             nSize7      = 3;
    int             nSize8      = 2;
    int             nSize9      = 2;
    int             nSize10     = 2;
    AdtArrayPlan    ArrayPlan(nBaseIndex1, nSize1,
                              nBaseIndex2, nSize2,
                              nBaseIndex3, nSize3,
                              nBaseIndex4, nSize4,
                              nBaseIndex5, nSize5,
                              nBaseIndex6, nSize6,
                              nBaseIndex7, nSize7,
                              nBaseIndex8, nSize8,
                              nBaseIndex9, nSize9,
                              nBaseIndex10, nSize10);
    AdtMemAllocator Allocator;

    printf("Testing %s 10D arrays : ", pTypeName);

    if (ArrayPlan.create(Allocator, pArray))
    {
      // Check lookup table for addresses in range
      int             c1;
      int             c2;
      int             c3;
      int             c4;
      int             c5;
      int             c6;
      int             c7;
      int             c8;
      int             c9;
      int             c10;
      size_t          nLookupSize   = ArrayPlan.lookupSize();
      size_t          nBlockSize    = 0;
      char*           pMinAddress   = Allocator.blockPtr((char*)pArray, &nBlockSize);
      char*           pMaxAddress   = pMinAddress + nBlockSize - 1;
      char*           pDataAddress  = pMinAddress + nLookupSize;
      char*           pLastDataAddr = pDataAddress - sizeof(T);
      IntByCharPtrMap AddrMap;

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        char* Addr1 = (char*)(&(pArray[c1]));

        if (Passed && (AddrMap.find(Addr1) != AddrMap.end()))
        {
          printf("FAILED, Addresses being recycled\n");
          Passed = false;
          break;
        }

        AddrMap[Addr1] = 1;

        if (Passed && ((Addr1 < pMinAddress) || (Addr1 > pDataAddress)))
        {
          printf("FAILED, LUT out of address range\n");
          Passed = false;
          break;
        }

        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          char* Addr2 = (char*)(&(pArray[c1][c2]));

          if (Passed && (AddrMap.find(Addr2) != AddrMap.end()))
          {
            printf("FAILED, Addresses being recycled\n");
            Passed = false;
            break;
          }

          AddrMap[Addr2] = 1;

          if (Passed && ((Addr2 < pMinAddress) || (Addr2 > pDataAddress)))
          {
            printf("FAILED, LUT out of address range\n");
            Passed = false;
            break;
          }

          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            char* Addr3 = (char*)(&(pArray[c1][c2][c3]));

            if (Passed && (AddrMap.find(Addr3) != AddrMap.end()))
            {
              printf("FAILED, Addresses being recycled\n");
              Passed = false;
              break;
            }

            AddrMap[Addr3] = 1;

            if (Passed && ((Addr3 < pMinAddress) || (Addr3 > pDataAddress)))
            {
              printf("FAILED, LUT out of address range\n");
              Passed = false;
              break;
            }

            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              char* Addr4 = (char*)(&(pArray[c1][c2][c3][c4]));

              if (Passed && (AddrMap.find(Addr4) != AddrMap.end()))
              {
                printf("FAILED, Addresses being recycled\n");
                Passed = false;
                break;
              }

              AddrMap[Addr4] = 1;

              if (Passed && ((Addr4 < pMinAddress) || (Addr4 > pDataAddress)))
              {
                printf("FAILED, LUT out of address range\n");
                Passed = false;
                break;
              }

              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                char* Addr5 = (char*)(&(pArray[c1][c2][c3][c4][c5]));

                if (Passed && (AddrMap.find(Addr5) != AddrMap.end()))
                {
                  printf("FAILED, Addresses being recycled\n");
                  Passed = false;
                  break;
                }

                AddrMap[Addr5] = 1;

                if (Passed && ((Addr5 < pMinAddress) || (Addr5 > pDataAddress)))
                {
                  printf("FAILED, LUT out of address range\n");
                  Passed = false;
                  break;
                }

                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  char* Addr6 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6]));

                  if (Passed && (AddrMap.find(Addr6) != AddrMap.end()))
                  {
                    printf("FAILED, Addresses being recycled\n");
                    Passed = false;
                    break;
                  }

                  AddrMap[Addr6] = 1;

                  if (Passed && ((Addr6 < pMinAddress) || (Addr6 > pDataAddress)))
                  {
                    printf("FAILED, LUT out of address range\n");
                    Passed = false;
                    break;
                  }

                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    char* Addr7 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7]));

                    if (Passed && (AddrMap.find(Addr7) != AddrMap.end()))
                    {
                      printf("FAILED, Addresses being recycled\n");
                      Passed = false;
                      break;
                    }

                    AddrMap[Addr7] = 1;

                    if (Passed && ((Addr7 < pMinAddress) || (Addr7 > pDataAddress)))
                    {
                      printf("FAILED, LUT out of address range\n");
                      Passed = false;
                      break;
                    }

                    for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                    {
                      char* Addr8 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7][c8]));

                      if (Passed && (AddrMap.find(Addr8) != AddrMap.end()))
                      {
                        printf("FAILED, Addresses being recycled\n");
                        Passed = false;
                        break;
                      }

                      AddrMap[Addr8] = 1;

                      if (Passed && ((Addr8 < pMinAddress) || (Addr8 > pDataAddress)))
                      {
                        printf("FAILED, LUT out of address range\n");
                        Passed = false;
                        break;
                      }

                      for (c9 = nBaseIndex9 ; c9 < nBaseIndex9 + nSize9 ; c9++)
                      {
                        char* Addr9 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7][c8][c9]));

                        if (Passed && (AddrMap.find(Addr9) != AddrMap.end()))
                        {
                          printf("FAILED, Addresses being recycled\n");
                          Passed = false;
                          break;
                        }

                        AddrMap[Addr9] = 1;

                        if (Passed && ((Addr9 < pMinAddress) || (Addr9 > pDataAddress)))
                        {
                          printf("FAILED, LUT out of address range\n");
                          Passed = false;
                          break;
                        }

                        for (c10 = nBaseIndex10 ; c10 < nBaseIndex10 + nSize10 ; c10++)
                        {
                          char* Addr10 = (char*)(&(pArray[c1][c2][c3][c4][c5][c6][c7][c8][c9][c10]));

                          if (Passed && ((Addr10 < pDataAddress) || (Addr10 > pMaxAddress)))
                          {
                            printf("FAILED, LUT out of address range\n");
                            Passed = false;
                            break;
                          }

                          if (Passed && ((Addr10 - pLastDataAddr) != sizeof(T)))
                          {
                            printf("FAILED, Data addresses are not monitonically increasing\n");
                            Passed = false;
                          }

                          pLastDataAddr = Addr10;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
      {
        for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
        {
          for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
          {
            for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
            {
              for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
              {
                for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                {
                  for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                  {
                    for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                    {
                      for (c9 = nBaseIndex9 ; c9 < nBaseIndex9 + nSize9 ; c9++)
                      {
                        for (c10 = nBaseIndex10 ; c10 < nBaseIndex10 + nSize10 ; c10++)
                        {
                          pArray[c1][c2][c3][c4][c5][c6][c7][c8][c9][c10] = (T)(1000 - (rand() % 2000));
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      T********** pArray2 = 0;

      if (ArrayPlan.create(Allocator, pArray2, (void*)&pArray[nBaseIndex1][nBaseIndex2][nBaseIndex3][nBaseIndex4][nBaseIndex5][nBaseIndex6][nBaseIndex7][nBaseIndex8][nBaseIndex9][nBaseIndex10]))
      {
        for (c1 = nBaseIndex1 ; c1 < nBaseIndex1 + nSize1 ; c1++)
        {
          for (c2 = nBaseIndex2 ; c2 < nBaseIndex2 + nSize2 ; c2++)
          {
            for (c3 = nBaseIndex3 ; c3 < nBaseIndex3 + nSize3 ; c3++)
            {
              for (c4 = nBaseIndex4 ; c4 < nBaseIndex4 + nSize4 ; c4++)
              {
                for (c5 = nBaseIndex5 ; c5 < nBaseIndex5 + nSize5 ; c5++)
                {
                  for (c6 = nBaseIndex6 ; c6 < nBaseIndex6 + nSize6 ; c6++)
                  {
                    for (c7 = nBaseIndex7 ; c7 < nBaseIndex7 + nSize7 ; c7++)
                    {
                      for (c8 = nBaseIndex8 ; c8 < nBaseIndex8 + nSize8 ; c8++)
                      {
                        for (c9 = nBaseIndex9 ; c9 < nBaseIndex9 + nSize9 ; c9++)
                        {
                          for (c9 = nBaseIndex9 ; c9 < nBaseIndex9 + nSize9 ; c9++)
                          {
                            if (Passed && (pArray[c1][c2][c3][c4][c5][c6][c7][c8][c9][c10] != pArray2[c1][c2][c3][c4][c5][c6][c7][c8][c9][c10]))
                            {
                              printf("FAILED, Array contents don't match\n");
                              Passed = false;
                              break;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        printf("FAILED, Can't create array\n");
        Passed = false;
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

  void test_disk_stack(const char* pTypeName)
  {
    T*              pArray1     = 0;
    T*              pArray1C    = 0;
    T*              pArray2     = 0;
    T*              pArray2C    = 0;
    int             nBaseIndex1 = 5 - rand() % 10;
    int             nBaseIndex2 = 5 - rand() % 10;
    int             nSize1      = 1000;
    int             nSize2      = 50;
    AdtArrayPlan    ArrayPlan1(nBaseIndex1, nSize1);
    AdtArrayPlan    ArrayPlan2(nBaseIndex2, nSize2);
    AdtMemAllocator Allocator;
    AdtADStack      Stack(500);

    printf("Testing %s disk stack : ", pTypeName);

    if ((ArrayPlan1.create(Allocator, pArray1)  != 0) &&
        (ArrayPlan1.create(Allocator, pArray1C) != 0) &&
        (ArrayPlan2.create(Allocator, pArray2)  != 0) &&
        (ArrayPlan2.create(Allocator, pArray2C) != 0))
    {
      int c0;
      T   TestIn  = (T)(1000 - (rand() % 2000));
      T   TestOut = (T)(1000 - (rand() % 2000));

      for (c0 = nBaseIndex1 ; c0 < nBaseIndex1 + nSize1 ; c0++)
      {
        pArray1[c0] = (T)(1000 - (rand() % 2000));
      }

      for (c0 = nBaseIndex2 ; c0 < nBaseIndex2 + nSize2 ; c0++)
      {
        pArray2[c0] = (T)(1000 - (rand() % 2000));
      }

      Stack.push(Allocator, pArray2, nSize2);
      Stack.push(Allocator, pArray1, nSize1);

      Stack.push(TestIn);
      Stack.look(TestOut);

      if (TestOut != TestIn)
      {
        printf("FAILED, look() output does not match push()\n");
        Passed = false;
      }

      Stack.pop(TestOut);

      if (TestOut != TestIn)
      {
        printf("FAILED, pop() output does not match push()\n");
        Passed = false;
      }

      Stack.pop(Allocator, pArray1C, nSize1);
      Stack.pop(Allocator, pArray2C, nSize2);

      for (c0 = nBaseIndex1 ; c0 < nBaseIndex1 + nSize1 ; c0++)
      {
        if (pArray1[c0] != pArray1C[c0])
        {
          printf("FAILED, pop() array output does not match push() array\n");
          Passed = false;
          break;
        }
      }

      for (c0 = nBaseIndex2 ; c0 < nBaseIndex2 + nSize2 ; c0++)
      {
        if (pArray2[c0] != pArray2C[c0])
        {
          printf("FAILED, pop() array output does not match push() array\n");
          Passed = false;
          break;
        }
      }

      if (Passed)
      {
        printf("PASSED\n");
      }
    }
    else
    {
      Passed = false;
    }
  };

public:
  AdtADLibTest()
  {
    Passed = true;
  };

  virtual ~AdtADLibTest()
  {

  };

  bool test(const char* pTypeName)
  {
    if (Passed)
    {
      test_1D(pTypeName);
    }

    if (Passed)
    {
      test_2D(pTypeName);
    }

    if (Passed)
    {
      test_3D(pTypeName);
    }

    if (Passed)
    {
      test_4D(pTypeName);
    }

    if (Passed)
    {
      test_5D(pTypeName);
    }

    if (Passed)
    {
      test_6D(pTypeName);
    }

    if (Passed)
    {
      test_7D(pTypeName);
    }

    if (Passed)
    {
      test_8D(pTypeName);
    }

    if (Passed)
    {
      test_9D(pTypeName);
    }

    if (Passed)
    {
      test_10D(pTypeName);
    }

    if (Passed)
    {
      test_disk_stack(pTypeName);
    }

    return (Passed);
  };
};


//  ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  int Result = 0;

  AdtADLibTest<char>            Test_char;
  AdtADLibTest<unsigned char>   Test_unsigned_char;
  AdtADLibTest<int>             Test_int;
  AdtADLibTest<unsigned int>    Test_unsigned_int;
  AdtADLibTest<short>           Test_short;
  AdtADLibTest<unsigned short>  Test_unsigned_short;
  AdtADLibTest<long>            Test_long;
  AdtADLibTest<unsigned long>   Test_unsigned_long;
  AdtADLibTest<float>           Test_float;
  AdtADLibTest<double>          Test_double;

  printf("\nADLib Test Harness\n");
  printf("------------------\n");

  Result = (Test_char.test("char")                      &&
            Test_unsigned_char.test("unsigned char")    &&
            Test_int.test("int")                        &&
            Test_unsigned_int.test("unsigned int")      &&
            Test_short.test("short")                    &&
            Test_unsigned_short.test("unsigned short")  &&
            Test_long.test("long")                      &&
            Test_unsigned_long.test("unsigned long")    &&
            Test_float.test("float")                    &&
            Test_double.test("double")) ? 0 : -1;

  return (Result);
}
