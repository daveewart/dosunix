// $Id: chktxt.c,v 1.9 2005/09/09 12:04:48 daveewart Exp $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 * ChkTxt
 * Determines, by inspection, whether a given text file is in DOS or
 * Unix text format.
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
extern int PrintSummary(char *progrname, long NumChanges);
extern int BasicInfo(char *progname);
extern int UsageInfo(char *command, int style);
extern int ShowOptions(char *command);
extern int main(int argc, char *argv[])
{
    FILE *InputFile;
    int c;
    long n_dos   = 0;
    long n_unix  = 0;
    long n_dummy = 0;
    char cmd[256];

    if (argc == 1) {
        c = BasicInfo("ChkTxt");
        c = ShowOptions("chktxt");
        exit(0);
    }
    if (argc == 2) {
        if ((strcmp(argv[1], "-V")) == 0) {
            c = BasicInfo("ChkTxt");
            c = FullInfo("ChkTxt");
            exit(0);
        }
        else if ((strcmp(argv[1], "-h")) == 0) {
            c = BasicInfo("ChkTxt");
            c = UsageInfo("chktxt", 1);
            printf("ChkTxt will attempt to determine, ");
            printf("by inspection, whether\n");
            printf("the given text file is in DOS text ");
            printf("format or Unix text format.\n");
            printf("If this fails to determine the file format, ");
            printf("the 'file' command\n");
            printf("is used to identify the file type.\n\n");
            exit(0);
        }
    }

    if (!(InputFile = fopen(argv[1], "r"))) {
        c = NoInput(argv[1]);
        c = UsageInfo("chktxt", 1);
        exit(0);
    };
    while (1) {
        c = getc(InputFile);
        if (c == -1) {
            break;
        }
        else if (c == 13) {
            if ((c = getc(InputFile)) == 10) {
                n_dos++;
            }
            else {
                n_dummy++;
            }
        }
        else if (c == 10) {
            n_unix++;
        }
    }
    fclose(InputFile);
    printf("ChkTxt %s: ", VERSION);
    /* Some DOS line-endings and no Unix line-endings suggests
     * file is DOS
     */
    if (n_dos > 0 && n_unix == 0) {
        printf("%s is a DOS text file.\n", argv[1]);
    }
    /* Some Unix line-endings and DOS line-endings suggests
     * file is Unix
     */
    else if (n_unix > 0 && n_dos == 0 && n_dummy == 0) {
        printf("%s is a Unix text file.\n", argv[1]);
    }
    /* This is very simplistic but will probably work OK
     * for most systems
     */
    else {
        printf("Cannot determine filetype of %s\n", argv[1]);
        printf("It is probably not a simple text file.\n\n");
        printf("Running 'file %s' ...\n\n", argv[1]);
        strcpy(cmd, "file ");
        strcat(cmd, argv[1]);
        system(cmd);
    }
    return (0);
}
