// $Id: common.c,v 1.12 2005/09/09 12:04:48 daveewart Exp $

#include <stdio.h>
#include <stdlib.h>
#include "const.h"

/*
 *
 * DosUnix - File converter - changes DOS end-of-lines to Unix
 * end-of-lines
 * Copyright (C)1997-2002 Dave Ewart (davee@sungate.co.uk)
 *
 * This file is part of the DosUnix project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

int NoInput(char *somefile);
int NoOutput(char *somefile);
int PrintSummary(char *progname, long NumChanges);
int BasicInfo(char *progname);
int UsageInfo(char *command, int style);
int ShowOptions(char *command);

int NoInput(char *somefile)
{
    printf("ERROR: Cannot open input file: %s\n", somefile);
    return (0);
}

int NoOutput(char *somefile)
{
    printf("ERROR: Cannot open output file: %s\n", somefile);
    return (0);
}

int PrintSummary(char *progname, long NumChanges)
{
    printf("%s %s - SUMMARY: A total of %ld ", progname, VERSION,
           NumChanges);
    printf("end of line characters were modified.\n");
    return (0);
}

int BasicInfo(char *progname)
{
    printf("%s version %s ", progname, VERSION);
    printf("(C)%s %s (%s)\n", COPYYEAR, AUTHOR, AUTHOREMAIL);
    printf("%s is part of the DosUnix project.\n", progname);
    return (0);
}

int FullInfo(char *progname)
{
    printf("Last revised %s\n\n", REVDATE);
    printf("%s comes with ABSOLUTELY NO WARRANTY.  This is free software\n",
           progname);
    printf("and you are welcome to redistribute it under certain conditions.\n");
    printf("Read the file COPYING supplied with this distribution, or\n");
    printf("http://www.gnu.org/licenses/gpl.txt for details.\n\n");
    return (0);
}

int UsageInfo(char *command, int style)
{
    printf("Usage:\n");
    if (style == 1)
    {
        printf("  %s INPUTFILE\n\n", command);
    }
    else
    {
        printf("  %s INPUTFILE OUTPUTFILE\n\n", command);
    }
    return (0);
}

int ShowOptions(char *command)
{
    printf("  %s -V  for version and license info;\n", command);
    printf("  %s -h  for usage info\n", command);
    return (0);
}
