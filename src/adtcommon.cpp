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
//    adtcommon.cpp
//
//  Purpose:
//
//
//  Author:
//    Paavo Jumppanen
//  ----------------------------------------------------------------------------


#include "adtcommon.hpp"


//  ----------------------------------------------------------------------------

void AdtExit(int nExitCode)
{
  ::exit(nExitCode);
}

//  ----------------------------------------------------------------------------

string unifyFilePath(const char* pFilePath)
{
  string    sUnifiedPath(pFilePath);
  size_t    nPos = 0;
  size_t    nLen = sUnifiedPath.length();

  for (size_t cn = 0 ; cn < nLen ; cn++)
  {
    char nChar = sUnifiedPath[cn];

  #if defined(_MSC_VER)
    if (nChar == '/')
    {
      sUnifiedPath[cn] = '\\';
    }
  #else
    if ((nChar  == '\\') &&
        (cn + 1 <= nLen) &&
        (sUnifiedPath[cn + 1] != ' '))
    {
      sUnifiedPath[cn] = '/';
    }
  #endif
  }

  return (sUnifiedPath);
}


//  ----------------------------------------------------------------------------

string unixifyFilePath(const char* pFilePath)
{
  string    sUnifiedPath(pFilePath);
  size_t    nPos = 0;
  size_t    nLen = sUnifiedPath.length();

  for (size_t cn = 0 ; cn < nLen ; cn++)
  {
    char nChar = sUnifiedPath[cn];

    if ((nChar  == '\\') &&
        (cn + 1 <= nLen) &&
        (sUnifiedPath[cn + 1] != ' '))
    {
      sUnifiedPath[cn] = '/';
    }
  }

  return (sUnifiedPath);
}


//  ----------------------------------------------------------------------------
//  UtlFilePath method implementations
//  ----------------------------------------------------------------------------
UtlFilePath::UtlFilePath()
 : Drive(),
   Directory(),
   Name(),
   Extension()
{

}

//  ----------------------------------------------------------------------------

UtlFilePath::UtlFilePath(const char* pFileAndPath)
 : Drive(),
   Directory(),
   Name(),
   Extension()
{
  split(pFileAndPath);
}

//  ----------------------------------------------------------------------------

UtlFilePath::UtlFilePath(const UtlFilePath& rCopy)
 : Drive(rCopy.Drive),
   Directory(rCopy.Directory),
   Name(rCopy.Name),
   Extension(rCopy.Extension)
{

}

//  ----------------------------------------------------------------------------

UtlFilePath::~UtlFilePath()
{

}

//  ----------------------------------------------------------------------------

void UtlFilePath::split(const char* pFileAndPath)
{
  const char* pChar;
  const char* pDriveBegin     = 0;
  const char* pDriveEnd       = 0;
  const char* pDirectoryBegin = 0;
  const char* pDirectoryEnd   = 0;
  const char* pNameBegin      = 0;
  const char* pNameEnd        = 0;
  const char* pExtensionBegin = 0;
  const char* pExtensionEnd   = 0;

  //Eliminate leading white space
  for (pChar = pFileAndPath ; *pChar != 0 ; pChar++)
  {
    if (*pChar != ' ')
    {
      break;
    }
  }

  if (*pChar == '\"')
  {
    pChar++;
  }

#if defined(_MSC_VER)
  //Look for drive specification
  pDriveBegin = pChar;

  for ( ; ((*pChar != 0) && (*pChar != '\"')) ; pChar++)
  {
    if (*pChar == ':')
    {
      pDriveEnd = pChar;
      break;
    }
  }

  if (pDriveEnd == 0)
  {
    //No drive specification
    pDirectoryBegin = pDriveBegin;
    pDriveBegin     = 0;
  }
  else
  {
    pDirectoryBegin = pDriveEnd + 1;
  }
#else
  pDirectoryBegin = pChar;
#endif

  //Look for directory specification
  for (pChar = pDirectoryBegin ; ((*pChar != 0) && (*pChar != '\"')) ; pChar++)
  {
#if defined(_MSC_VER)
    if (*pChar == '\\')
    {
      pDirectoryEnd = pChar;
    }
#else
    if (*pChar == '/')
    {
      pDirectoryEnd = pChar;
    }
#endif
  }

  if (pDirectoryEnd == 0)
  {
    //No directory specification
    pNameBegin      = pDirectoryBegin;
    pDirectoryBegin = 0;
  }
  else
  {
    pNameBegin      = pDirectoryEnd + 1;
  }

  //Look for name specification
  for (pChar = pNameBegin ; ((*pChar != 0) && (*pChar != '\"')) ; )
  {
    const char* pLastChar;

    pLastChar = pChar;
    pChar++;

    if (*pChar == '.')
    {
      pNameEnd = pLastChar;
    }
  }

  if (pNameEnd == 0)
  {
    //No name extension specification. Look for name end
    for (pChar = pNameBegin ; ((*pChar != 0) && (*pChar != '\"')) ; pChar++)
    {
      pNameEnd = pChar;
    }
  }
  else
  {
    //Look for extension specification
    pExtensionBegin = pNameEnd + 1;

    for (pChar = pExtensionBegin ; ((*pChar != 0) && (*pChar != '\"')) ; pChar++)
    {
      pExtensionEnd = pChar;
    }
  }

  //Set Drive
  if ((pDriveBegin != 0) && (pDriveEnd != 0))
  {
    Drive = string(pDriveBegin, 0, pDriveEnd - pDriveBegin + 1);
  }
  else
  {
    Drive = "";
  }

  //Set Directory
  if ((pDirectoryBegin != 0) && (pDirectoryEnd != 0))
  {
    Directory = string(pDirectoryBegin, 0, pDirectoryEnd - pDirectoryBegin + 1);
  }
  else
  {
    Directory = "";
  }

  //Set Name
  if ((pNameBegin != 0) && (pNameEnd != 0))
  {
    Name = string(pNameBegin, 0, pNameEnd - pNameBegin + 1);
  }
  else
  {
    Name = "";
  }

  //Set Extension
  if ((pExtensionBegin != 0) && (pExtensionEnd != 0))
  {
    Extension = string(pExtensionBegin, 0, pExtensionEnd - pExtensionBegin + 1);
  }
  else
  {
    Extension = "";
  }
}

//  ----------------------------------------------------------------------------

void UtlFilePath::join(string& rJoinedPath, bool bQuoted) const
{
  if (bQuoted)
  {
    rJoinedPath = "\"";
  }
  else
  {
    rJoinedPath = "";
  }

  rJoinedPath  += Drive;
  rJoinedPath  += Directory;
  rJoinedPath  += Name;
  rJoinedPath  += Extension;

  if (bQuoted)
  {
    rJoinedPath += "\"";
  }
}

//  ----------------------------------------------------------------------------

static AdtUseArrayClass _UseArrayClass = ArrayClass_offarray;

//  ----------------------------------------------------------------------------

AdtUseArrayClass useArrayClass()
{
  return (_UseArrayClass);
}

//  ----------------------------------------------------------------------------

void useArrayClass(AdtUseArrayClass nClass)
{
  _UseArrayClass = nClass;
}

//  ----------------------------------------------------------------------------

void getUseArrayClassName(string& rName)
{
  switch (_UseArrayClass)
  {
    case ArrayClass_offarray:
    {
      rName = "offarray";
      break;
    }

    case ArrayClass_Oarray:
    {
      rName = "Oarray";
      break;
    }

    default:
    {
      FAIL();
      break;
    }
  }
}
