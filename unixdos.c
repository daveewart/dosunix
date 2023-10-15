// $Id: unixdos.c,v 1.12 2005/09/09 12:04:48 daveewart Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *
 * UnixDos  - File converter - changes Unix end-of-lines to DOS
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

extern int NoInput(char *somefile);
extern int NoOutput(char *somefile);
extern int PrintSummary(char *progname, long NumChanges);
extern int BasicInfo(char *progname);
extern int FullInfo(char *progname);
extern int UsageInfo(char *command, int style);
extern int ShowOptions(char *command);

int main(int argc, char *argv[])
{
    FILE *InputFile, *OutputFile;
    int c;
    long NumChanges = 0;

    if (argc == 1)
    {
        c = BasicInfo("UnixDos");
        c = ShowOptions("unixdos");
        exit(0);
    }
    if (argc == 2)
    {
        if ((strcmp(argv[1], "-V")) == 0)
        {
            c = BasicInfo("UnixDos");
            c = FullInfo("UnixDos");
        }
        else if ((strcmp(argv[1], "-h")) == 0)
        {
            c = BasicInfo("UnixDos");
            c = UsageInfo("unixdos", 2);
            printf("UnixDos converts files from Unix text ");
            printf("format to DOS text format\n");
            printf("by replacing each newline character with ");
            printf("a carriage return and\nline-feed pair.\n\n");
        }
        else
        {
            printf("Unknown option: %s\n", argv[1]);
        }
        exit(0);
    }

    if (!(InputFile = fopen(argv[1], "r")))
    {
        c = NoInput(argv[1]);
        c = UsageInfo("unixdos", 2);
        exit(0);
    };
    if (!(OutputFile = fopen(argv[2], "w")))
    {
        c = NoOutput(argv[2]);
        c = UsageInfo("unixdos", 2);
        exit(0);
    };
    while (1)
    {
        c = getc(InputFile);
        if (c == -1)
        {
            break;
        }
        else if (c == 10)
        {
            putc(13, OutputFile);
            putc(10, OutputFile);
            NumChanges++;
        }
        else
        {
            putc(c, OutputFile);
        }
    }
    fclose(InputFile);
    fclose(OutputFile);
    c = PrintSummary("UnixDos", NumChanges);
    return (0);
}
