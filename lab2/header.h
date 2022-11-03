#ifndef __HEADER_H__
#define __HEADER_H__
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;
typedef char ElemType;

typedef struct Tag{
    char s[30]="";
    char* p;
}Tag;
typedef Tag sElemType;

// #define BR 0
// #define HR 1
// #define AREA 2
// #define BASE 3
// #define IMG 4
// #define INPUT 5
// #define LINK 6
// #define META 7
// #define COL 8
// #define FRAME 9
// #define EMBED 10
// #define KEYGEN 11
// #define INVALID -1


#endif