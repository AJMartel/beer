#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//time functions...
#include <time.h>
// use to dir functions
#include <dirent.h>

#ifndef __BEER_H__
#define __BEER_H__

void *xmalloc(unsigned int len);
char * dec2bin(int n, char * string);
char Hex2Char(char *Hex);
static char char2Hex(unsigned char c);
static void string2hex(char *Output, unsigned char *Input, int Length);
unsigned long hex2int(char *a, unsigned int len);
int mdc(int a,int b);
int mmc(int a,int b);
char * baskara(float a, float b, float c, float *raizes);
int factorial( int n );
int isprime(int n);
int bit_sqrt(int num);
int palindrome(const char *s);
char *TimeNow();
int CopyFile(char *fromfile, char *tofile);
int WriteFile(char *file,char *str);
const char *readLine(char * NameFile);
char *ListDir(char *file2list,int MAX);
long FileSize(const char *file);
int sort_char( const void *a, const void *b);
int sort_int(const void *a, const void *b);
void mergesort(int *array, size_t first, size_t last);
void bubbleSort(void *p, int width, int N, int(*fptr)(const void *, const void *));
char *RandomIp(void);
int email_isvalid(const char *address);
char *scapeSQL(const char *input, char quote, int wildcards);
void urlobfuscator (char * url, char * obf);
static inline char* base64_encode(char* str, unsigned long len);
void changeCharacter(char *dest, const char* str, const char search, const char replace);
char *strrev(char *str);
char *StrChunk(char *src, const int start, const int count);
char *StrRep(char *st,char *orig,char *repl,int mim);
char **split(char *src, const char *token, int *total);
void strings(FILE *fp);
short TestAnagram(char *str1, char *str2);
char *UriDecode(char *uri); 
int base64_decode(char *in, int inlen, char *out) 
