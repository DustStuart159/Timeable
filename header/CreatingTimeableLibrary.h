#ifndef CreatingTimeableLibrary_H_
#define CreatingTimeableLibrary_H_

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<conio.h>

typedef struct{
    float fBegin;
    float fEnd;
}strTimeTimeable;
typedef struct{
    char sNameTask[100];
    float fTimeScope;
} strTask;
typedef struct{
    char sNameTask[100];
    strTimeTimeable sTTTimeScope;

} strTimeableTask;

#endif // CreatingTimeableLibrary_H_
