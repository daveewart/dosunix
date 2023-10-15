// $Id: dosunix.c,v 1.12 2005/09/09 12:04:48 daveewart Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
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

extern int NoInput(char *somefile);
extern int NoOutput(char *somefile);
extern int PrintSummary(char *progrname, long NumChanges);
extern int BasicInfo(char *progname);
extern int FullInfo(char *progname);
extern int UsageInfo(char *command, int style);
extern int ShowOptions(char *command);
extern int main(int argc, char *argv[])
{
    FILE *InputFile, *OutputFile;
    int c;
    long NumChanges = 0;

    if (argc == 1)
    {
        c = BasicInfo("DosUnix");
        c = ShowOptions("dosunix");
        exit(0);
    }
    if (argc == 2)
    {
        if ((strcmp(argv[1], "-V")) == 0)
        {
            c = BasicInfo("DosUnix");
            c = FullInfo("DosUnix");
        }
        else if ((strcmp(argv[1], "-h")) == 0)
        {
            c = BasicInfo("DosUnix");
            c = UsageInfo("dosunix", 2);
            printf("DosUnix converts files from DOS text ");
            printf("format to Unix text format\n");
            printf("by replacing each carriage return & ");
            printf("newline pair with a single\n");
            printf("newline character.\n\n");
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
        c = UsageInfo("dosunix", 2);
        exit(0);
    };
    if (!(OutputFile = fopen(argv[2], "w")))
    {
        c = NoOutput(argv[2]);
        c = UsageInfo("dosunix", 2);
        exit(0);
    };
    while (1)
    {
        c = getc(InputFile);
        if (c == -1)
        {
            break;
        }
        else if (c == 13)
        {
            if ((c = getc(InputFile)) == 10)
            {
                putc(10, OutputFile);
                NumChanges++;
            }
        }
        else
        {
            putc(c, OutputFile);
        }
    }
    fclose(InputFile);
    fclose(OutputFile);
    c = PrintSummary("DosUnix", NumChanges);
    return (0);
}
