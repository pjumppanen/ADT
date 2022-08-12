/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA
 *
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */


#include <ScilabOptim.h>


// begin extern "C"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#define NOMINMAX
#endif

#include <limits.h>
#include <math.h>

#ifdef __STDC__
#include <stdlib.h>
#endif


#ifdef _MSC_VER     //windows
#include <float.h>
#define finite(x) _finite(x)
#else               //linux & mac
#ifdef __cplusplus  // C++
#define finite(x) std::isfinite(x)
#endif
#endif /* _MSC_VER */


// ----------------------------------------------------------------------------
// Message callback function to be called when ScilabOptim prints text output
// ----------------------------------------------------------------------------
messageCallback MessageCallback = 0;

// ----------------------------------------------------------------------------

int F77_NAME(vfinite)(int *n, double *v)
{
    int i;
    for (i = 0; i < *n; i++)
        if (finite(v[i]) == 0)
        {
            return 0;
        }
    return 1;
}

// ----------------------------------------------------------------------------

int F77_NAME(basout)(int *io, int *lunit, char *string, long int nbcharacters)
{
    char* strMsg = malloc((nbcharacters + 1) * sizeof(char));
    *io = 0;
    memcpy(strMsg, string, nbcharacters);
    strMsg[nbcharacters] = '\0';

    if (MessageCallback != 0)
    {
      MessageCallback(strMsg);
    }

    free(strMsg);

    return 0;
}

// ----------------------------------------------------------------------------

void registerMessageCallback(messageCallback pMessageCallback)
{
  MessageCallback = pMessageCallback;
}

// End extern "C"
#ifdef __cplusplus
}
#endif


