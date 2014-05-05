/*
last check up
25/01/2012
------------

       _____________
      (             )
      (____________ )
       |           |
       |           |
      _|           |_
     /               \
   /                  \
  (___________________)
  |                   |
  |   ...:::Beer:::   |
  |..::Version:0.05::.|
  |                   |
  |___________________|
  |                   |
  |                   |
  |                   |
  |                   |
  |                   |
  (___________________)
0101010101010110101010101010101101010101010

is held by GNU license 2.0
-----------------------
Beer simple C header

Authors: Cooler_,m0nad,ryonagana,b4r0n,utroz,mentebinaria
E-mail: c00f3r[at]gmail[dot]com
date: 01/01/2010

thanks:
  _mlk_,m0nad,
  I4K,sigsegv,b-man,kov,utroz,eremitah,maycon(0ut0fBound),vorazbr,mentebinaria
  delfo,c0lt7r,B4r0n,joey,fokerbug,
  zepplin,voidpointer,muzgo,memset,b4r0n,novato_br...

  Beer is a C header to help you in small problems

Have a lot functions how
math functions(mmc,mdc,bitwise_sqrt,quadratic equation,factorial,test if number is prime..)
parsers,
string functions (split,strrev..),
validate e-mail,
SQL query filter,
Files Jobs how READ,WRITE,COPY,list DIRs,bytes of file...

strings,numbers convert

    |-hex2int
    |-dec2bin
    |-char2hex
    |-hex2char
    |-string2hex

bitwise macros ,another things
do you want help us ?
send your function...

in the future this header will a dynamic library...

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//time functions...
#include <time.h>
// use to dir functions
#include <dirent.h>


//macro to read stdin string
#define ReadString(a) fgets(a,sizeof(a),stdin),a[strlen(a)-1] = '\0';

//return elements of array
#define array_elements(array) (sizeof(array) / sizeof *(array))

//hide and unhide strings
#define UNHIDE_STR(str) do { char *p = str;  while (*p) *p++ += 0x19; } while (0)
#define HIDE_STR(str)   do { char *p = str;  while (*p) *p++ -= 0x19; } while (0)

// bitwise macros
#define XorSwap(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )
#define TST_FLAG(N, F)        ( (N) & (F) )
#define BIT_RANGE(N, M)       ( BIT_POS((M)+1 - (N))-1 << (N) )
#define BIT_SHIFTL(B, N)      ( (unsigned)(B) << (N) )
#define BIT_SHIFTR(B, N)      ( (unsigned)(B) >> (N) )
#define SET_MFLAG(N, F, V)    ( CLR_FLAG(N, F), SET_FLAG(N, V) )
#define CLR_MFLAG(N, F)       ( (N) &= ~(F) )
#define GET_MFLAG(N, F)       ( (N) & (F) )

// COLORS macros
#define LAST "\033[0m"
#define WHITE "\033[01;37m"
#define BLACK "\033[22;30m"
#define RED "\033[22;31m"
#define GREEN "\033[22;32m"
#define BLUE "\033[22;34m"
#define CYAN "\033[22;36m"
#define GRAY "\033[22;37m"
#define DGRAY "\033[01;30m"
#define LRED "\033[01;31m"
#define LGREEN "\033[01;32m"
#define YELLOW "\033[01;33m"
#define LBLUE "\033[01;34m"
#define LMAGENTA "\033[01;35m"
#define MAGENTA "\033[22;35m"
#define LCYAN "\033[01;36m"
#define BROWN "\033[22;33m"


#define BUGVIEW 1

#define DEBUG(x, s...) do { \
 if (!BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "%.*s %s[%d] %s(): ", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
} while (0);

// HEAP alignment :-X
void *xmalloc(unsigned int len)
{
 void *ptr;
 ptr=malloc(len);
 if(ptr==NULL)
  DEBUG("fail malloc");
 return ptr;
}

// bitwise div seven , faster than "n/7",by Cooler_
unsigned bit_div7(unsigned num)
{
 unsigned x,y;

 x=(num>>1)+(num>>4);
 x+=x>>6;
 x+=(x>>12)+(x>>24);
 x>>=2;
 y=num-((x<<3)-x);

 return x+((y+1)>>3);
}

// bitwise div three , by Cooler_
unsigned bit_div3(unsigned num)
{
 unsigned x,y;

 x=(num>>2)+(num>>4);
 x+=x>>4;
 x+=x>>8;
 x+=x>>16;
 y=num-((x<<2)-x);
// this form is bad , return x+( ((y<<3)+(y<<2)-y)>>5);
// this form is bad ,  return x+( (y+5+(y<<2)) >>4);
 return x+( (((y+1)<<2)+(y+1)) >>4);

}



// convert decimal to binary
char * dec2bin(int n, char * string)
{
 int i;
 static int size = 8 * sizeof(int);

  for(i = size - 1; i >= 0; i--, n >>= 1)
   string[i] = (01 & n) + '0';

 string[size] = '\0';
 return string;
}

// Hexadecimal to Character

// with bitwise
char Hex2Char(char *Hex)
{
 char rch=0;
 int i=0;

 while(i<2)
 {
  if ( *(Hex + i) >= '0' && *(Hex + i) <= '9' )
   rch = (rch << 4) + (*(Hex + i) - '0');
  else if ( *(Hex + i) >= 'A' && *(Hex + i) <= 'F' )
   rch = (rch << 4) + (*(Hex + i) - 'A' + 10);
  else
   break;
  i++;
 }
 return rch;
}

//simple version
static char char2Hex(unsigned char c)
{
 static const char *HexCharacters = "0123456789ABCDEF";
   if(c > 15)
   {
     DEBUG("error in char2Hex() %c",HexCharacters[c]);
     return -1;
   }
 return HexCharacters[c];
}

// unsigned char x[]={"google.com"}; string2hex(y,x,16)...
static void string2hex(char *Output, unsigned char *Input, int Length)
{
 char *Out;
 char First;
 char Second;

 Out = Output;
 while (Length > 0)
 {
  First = *Input / 0x10;
  Second = *Input % 0x10;
  *Out = char2Hex(First);
   Out++;
  *Out = char2Hex(Second);
   Out++;
   Length--;
   Input++;
 }
 *Out = '\0';
 return;
}

unsigned long hex2int(char *a, unsigned int len)
{
 int i=0;
 unsigned long val = 0;

 while(i<len)
 {
  if(a[i] <= 57)
   val += (a[i]-48)*(1<<(4*(len-1-i)));
  else
   val += (a[i]-55)*(1<<(4*(len-1-i)));
  i++;
 }
 return val;
}


//  Math functions
/*
MDC Máximo Divisor Comum,dois números inteiros é o maior número inteiro que divide
ambos sem deixar resto.
*/
int mdc(int a,int b)
{
  if(!b)
   return a;
  else
   return mdc(b,a%b);
}

/*
MMC = mínimo múltiplo comum entre dois números é representado
pelo menor valor comum pertencente aos múltiplos dos números.
*/
int mmc(int a,int b)
{
 int formula;
   if(!b)
    return a;
   else
    formula = (a*b)/(mdc(a,b));
 return (formula);
}

// quadratic equation
char * baskara(float a, float b, float c, float *raizes)
{
 float delta=((b*b)-4*(a*c));
 float x1=0,x2=0;
 char *reply;

 if((!a)||(delta<0))
 {
  DEBUG("error in equation baskara(), delta: %f ",delta);
  return 0;
 }
 if(delta>0)
  x1=((-b + ((float)bit_sqrt(delta)) )/(2*a));
 x2=((-b - ((float)bit_sqrt(delta)) )/(2*a));
 snprintf(reply,sizeof(reply)," X1 : %5.2f \n X2 : %5.2f\n",x1,x2);
 return reply;
}

// simple factorial
int factorial( int n )
{
 if(n<=1)
  return 1;
 else
  return n*factorial(n-1);
}


//Test if n is prime
bool isprime(long long int n){
    register int i;
    int raiz = sqrt(n);

    if(n == 2){
        return true;
    }

    if(n < 2 || !(n % 2)){
        return false;
    }

    for(i = 3; i <= raiz; i+=2){
        if(!(n % i)){
            return false;
        }
    }

    return true;
}

//square root by Cooler_
int bit_sqrt(int num)
{
//so 32 is sizeof(int)<<3
 int num0=num,result=0,tbit=1<<((sizeof(int)<<3)-2);

 if(num<=0)
 {
  DEBUG("error bit_sqrt(), num = %d ",num);
  return -1;
 }

 while(tbit>num0)
  tbit>>=2;
 while(tbit^0)
 {
  if(num0>=result+tbit)
  {
   num0-=result+tbit;
   result=(result>>1)+tbit;
  }else
   result>>=1;
  tbit>>=2;
 }
 return result;
}

// test if is palindrome
 int palindrome(const char *s)
 {
  int x=0,y=0;

  y = strlen(s);
  y>>=1;

  while(x<y)
  {
   if( s[x] != s[y-x-1] )
    return 0;
   x++;
  }
  return 1;
 }


// return time
// example OutPut Wed Aug  3 18:26:24 2011
char *TimeNow()
{
 struct tm *local;
 time_t t;
 t = time(NULL);
 local = localtime(&t);
 local = gmtime(&t);
 return asctime(local);
}

// Files jobs  ##############################################################
int CopyFile(char *fromfile, char *tofile)
{
 FILE *ifp, *ofp;
 int c;

 if((ifp = fopen(fromfile, "r")) == NULL)
  return -1;
 if((ofp = fopen(tofile, "w")) == NULL)
 {
  fclose(ifp);
  DEBUG("Error CopyFile()");
  return -1;
 }

 while((c = getc(ifp)) != EOF)
  putc(c, ofp);

 fclose(ifp);
 fclose(ofp);
 return 0;
}

int WriteFile(char *file,char *str)
{
 FILE *arq;

 arq=fopen(file,"a");
  if(!arq)
  {
   DEBUG("error in WriteFile() %s",file);
   return 0;
  }
 fprintf(arq,"%s\n",str);
 fclose(arq);
 return 1;
}

// return lines from file, example:  const char *buff=readLine("log.txt"),printf("%s",buff);
const char *readLine(char * NameFile)
{
 FILE * file;
 file = fopen(NameFile, "r");
 if(!file)
 {
  DEBUG("error in file");
  return;
 }
 char *lineBuffer=calloc(1,1), line[128];

 if(!lineBuffer)
 {
  DEBUG("error in readLine() at %s",NameFile);
  return;
 }

 while(fgets(line,sizeof line-1,file))
 {
  lineBuffer=realloc(lineBuffer,strlen(lineBuffer)+strlen(line)+1);
  if(!lineBuffer)
  {
   DEBUG("error in readLine() at %s",NameFile);
   return;
  }
  strcat(lineBuffer,line);
 }

 return lineBuffer;
}

// ListDir(directory_name_2_list,Max_chars)
char *ListDir(char *file2list,int MAX)
{
 DIR *d;
 struct dirent *dir;
 char *ret=xmalloc(sizeof(char)*MAX);

 d = opendir(file2list);

 if(!d)
 {
  DEBUG("error in directory");
  return NULL;
 }

 while((dir = readdir(d)) != NULL)
 {
  strncat(ret,dir->d_name,strlen(dir->d_name));
  strncat(ret,"\n",1);
 }

 free(ret);
 closedir(d);
 return ret;
}

// return size of bytes on file , same to unix cmd "du -b file"
long FileSize(const char *file)
{
  long ret;
  FILE *fh = fopen(file, "r");
  if(!fh)
  {
   DEBUG("error in file");
   return 0;
  }
  fseek(fh, 0, SEEK_END);
  ret = ftell(fh);
  fclose(fh);
  return ret;
}

// count number of lines
int count_lines(char *instring)
{
 int counter = 0;
 char *scratch, *txt, *delimiter = "\n";

 while ((txt = strtok_r(!counter ? instring : NULL, delimiter, &scratch)))
  counter++;

 return counter;
}
/*
 char *array_of_strings[]={"png","jpeg","jpg","gif","mp3","ogg","css","wma"};
 find_type_file("teste.wma",array_of_strings,8); if is OK have file on list so return 1
*/
int find_type_file(char *path,char *list_types[],short elements)
{
 char *typedot=strchr(path,'.'),*typefile=typedot+1; // remove dot char
 short i=0;
 do {

  puts(*(list_types+i));
  if( !strcmp(typefile,*(list_types+i)) )
   return 1;
  i++;
 } while(i!=elements);

 return 0;
}


/* #################################################################################
 to use with Sort functions
 example:
  char *list[] = { "madruga", "chaves", "kiko", "chiquinha", "inhonho" };
  qsort((void *)list, array_elements(list), sizeof(list[0]), sort_char);
*/

int sort_char( const void *a, const void *b)
{
 return( strcmp(a,b) );
}

int sort_int(const void *a, const void *b)
{
 long *a1, *b1;
 a1 = (long *)a; b1 = (long *)b;
 return (*a1 > *b1);
}

//example mergesort(a, 0, sizeof(a)/sizeof(i) - 1);
void mergesort(int *array, size_t first, size_t last)
{
 int middle;

 if(first>=last)
  return;

 middle = (first + last) / 2;
 mergesort(array, first, middle);
 mergesort(array, middle + 1, last);

 int *temp;
 size_t i = first,j = middle + 1,tp = 0;
 temp = (int *) xmalloc(sizeof(int) * (last - first + 1));

 while(i <= middle && j <= last)
 {
  if(array[i] <= array[j])
  {
   temp[tp] = array[i];
   ++i;
  }
  else
  {
   temp[tp] = array[j];
   ++j;
  }
  ++tp;
 }

 while(j<=last)
 {
  temp[tp] = array[j];
  ++tp;
  j++;
 }
 while(i<=middle)
 {
  temp[tp] = array[i];
  ++tp;
  i++;
 }

 i=first;
 while(i<=last)
 {
  array[i] = temp[i - first];
  i++;
 }

 free(temp);
}

void bubbleSort(void *p, int width, int N, int(*fptr)(const void *, const void *))
{
 int i, j, k;

 unsigned char buf[256];
 unsigned char *bp = p;

  for (i = N-1; i >= 0; i--)
  {
   for (j = 1; j <= i; j++)
   {
    k = fptr((void *)(bp + width*(j-1)), (void *)(bp + j*width));
    if(k > 0)
    {
     memcpy(buf, bp + width*(j-1), width);
     memcpy(bp + width*(j-1), bp + j*width , width);
     memcpy(bp + j*width, buf, width);
    }
   }
  }
}


// ########################### other functions

char *RandomIp(void)
{
 char *ipRand=NULL;
 int r1,r2,r3,r4;

 r1 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));
 r2 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));
 r3 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));
 r4 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));

 ipRand=xmalloc(16*sizeof(char));
 sprintf(ipRand,"%d.%d.%d.%d",r1,r2,r3,r4);

 return ipRand;
}


//test if e-mails is valid
int email_isvalid(const char *address)
{
  int count = 0;
  const char *c, *domain;
  static char *rfc822_specials = "()<>@,;:\\\"[]";

  /* first we validate the name portion (name@domain) */
  for (c = address;  *c;  c++)
  {
    if (*c == '\"' && (c == address || *(c - 1) == '.' || *(c - 1) == '\"'))
    {
      while (*++c)
      {
        if (*c == '\"')
         break;
        if (*c == '\\' && (*++c == ' '))
         continue;
        if (*c <= ' ' || *c >= 127)
         return 0;
      }
      if(!*c++)
       return 0;
      if(*c == '@')
       break;
      if(*c != '.')
       return 0;
      continue;
    }
    if(*c == '@')
     break;
    if(*c <= ' ' || *c >= 127)
     return 0;
    if(strchr(rfc822_specials, *c))
     return 0;
  }
  if(c == address || *(c - 1) == '.')
   return 0;
  /* next we validate the domain portion (name@domain) */
  if(!*(domain = ++c))
   return 0;
  do {
    if (*c == '.')
    {
      if (c == domain || *(c - 1) == '.') return 0;
      count++;
    }
    if (*c <= ' ' || *c >= 127) return 0;
    if (strchr(rfc822_specials, *c)) return 0;
  } while (*++c);
  return (count >= 1);
}

//use input to escape SQL Injection
char *scapeSQL(const char *input, char quote, int wildcards) {
  char       *out, *ptr;
  const char *c;

  /* If every character in the input needs to be escaped, the resulting string
   * would at most double in size.  Also, include room for the surrounding
   * quotes.
   */
  if (quote != '\'' && quote != '\"') return 0;
  if (!(out = ptr = (char *)sbrk(strlen(input) * 2 + 2 + 1))) return 0;
  *ptr++ = quote;
  for (c = input;  *c;  c++) {
    switch (*c) {
      case '\'': case '\"':
        if (quote == *c) *ptr++ = *c;
        *ptr++ = *c;
        break;
      case '%': case '_': case '[': case ']':
        if (wildcards) *ptr++ = '\\';
        *ptr++ = *c;
        break;
      case '\\': *ptr++ = '\\'; *ptr++ = '\\'; break;
      case '\b': *ptr++ = '\\'; *ptr++ = 'b';  break;
      case '\n': *ptr++ = '\\'; *ptr++ = 'n';  break;
      case '\r': *ptr++ = '\\'; *ptr++ = 'r';  break;
      case '\t': *ptr++ = '\\'; *ptr++ = 't';  break;
      default:
        *ptr++ = *c;
        break;
    }
  }
  *ptr++ = quote;
  *ptr = 0;
  return out;
}

// func by  m0nad
void urlobfuscator (char * url, char * obf)
{
  int i;
  for (i = 0; i < (int)strlen (url); i++)
   snprintf (obf+strlen(obf), sizeof obf, "%02X", url [i]);
//  obf [strlen (obf)] = 0;
   obf[i*2] = 0;
}

//base 64 encode
static inline char* base64_encode(char* str, unsigned long len)
{

  const char b64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz"
                     "0123456789+/";
  char *ret, *chunk;

  chunk = malloc(((len + 3) << 2) / 4);
  ret=chunk;

   do {
    if (len >= 3)
    {
      unsigned long bitwise = (str[0] << 16) | (str[1] << 8) | str[2];

      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = b64[(bitwise >> 6) & 0x3F];
      *(chunk++) = b64[bitwise & 0x3F];
      len -= 3;
      str += 3;

    } else if (len == 2) {
      unsigned long bitwise = (str[0] << 16) | (str[1] << 8);

      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = b64[(bitwise >> 6) & 0x3D];
      *(chunk++) = '=';
      len -= 2;
      str += 2;

    } else {
      unsigned long bitwise = (str[0] << 16);;

      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = '=';
      *(chunk++) = '=';
      len--;
      str++;
    }
  } while(len);

  *chunk=0;

  return ret;
}
//func by ryonagana
void changeCharacter(char *dest, const char* str, const char search, const char replace)
{
  while(*dest = *str)
  {
   if(*dest == search)
    *dest =  replace;
   *dest++;
   *str++;
  }
}

// return reverse string
char *strrev(char *str)
{
 char *p1, *p2;

 if(! str || ! *str)
  return str;
 for(p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
 {
  *p1 ^= *p2;
  *p2 ^= *p1;
  *p1 ^= *p2;
 }
 return str;
}


char *StrChunk(char *src, const int start, const int count)
{
 char *tmp;
 tmp = (char *)xmalloc(count+1);
 if (tmp == NULL)
 {
  DEBUG("error");
  return NULL;
 }

 strncpy(tmp, src+start, count);
 tmp[count] = '\0';

 free(tmp);

 return tmp;
}

//string replace
char *StrRep(char *st,char *orig,char *repl,int mim)
{
 char bufer[mim];
 char *ch;

 if(!orig)
  return "\0";

 if(!(ch=strstr(st, orig)) )
  return st;

 strncpy(bufer, st, ch-st);
 bufer[ch-st] = 0;
 sprintf(bufer+(ch-st),"%s%s",repl,ch+strlen(orig));

 char *out=bufer;

 return out;
}

// simple split return array of strings between string separator
char **split(char *src, const char *token, int *total)
{
 char **str;
 register int i, j, count, item, start;
 int len;

 if(!src || !token)
 {
  *total = 0;
  return NULL;
 }

 count = item = start = 0;
 j = 1;
 len = strlen(src);

 for(i = 0; i < len; i++)
 {
  if(src[i] == *token)
   count++;
 }

 if(!count)
 {
  *total = 0;
  return NULL;
 }

 str = (char **)xmalloc(count * sizeof(char *));
 if(str == NULL)
  DEBUG("error");

 for(i = 0; i < len; i++)
 {
  if(src[i] != *token)
   j++;
  else {
   str[item] = (char *)xmalloc(j-start);
    if (str[item] == NULL)
    {
     DEBUG("error");
     return NULL;
    }
   *(str+item) = StrChunk(src, start, j-1);
   str[item][j-start-1] = '\0';
   item++;
   start = j++;
  }
 }

 *(str+count) = (char *)xmalloc(j);
 if(str[count] == NULL)
  DEBUG("error");

 str[count] = StrChunk(src, start, j);
 str[count][j-start] = '\0';
 *total = ++count;

 free(str);

 return str;
}



// return string of bin file, coded by Mente Binária "http://www.mentebinaria.com.br/"
void strings(FILE *fp)
{
   unsigned char byte;
   int aux=0;
   int ofs=0;

   while (fread(&byte, sizeof(unsigned char), 1, fp))
   {
      if (aux==1)
      {
         putchar('\n');
         printf("%#x  ", ofs);
      }
      else if (!ofs && isprint(byte))
         printf("0x0  ");

      if (isprint(byte))
      {
         putchar(byte);
         aux=0;
      }
      else aux++;

      ofs++;
   }
   putchar('\n');
}

// return 1 if string is anagram
short TestAnagram(char *str1, char *str2)
{
 int i=0;
 int count1[BUF] = {0};
 int count2[BUF] = {0};

 do{
  count1[str1[i]]++;
  count2[str2[i]]++;
  i++;
 }while(str1[i] && str2[i]);

 if(str1[i] || str2[i])
  return 0;

 i=0;

 while(i < BUF)
 {
  if(count1[i] != count2[i])
   return 0;
  i++;
 }

 return 1;
}

// uri decode
char *UriDecode(char *uri)
{
 int count=0,ptr=0;
 char *word=(char *)xmalloc(sizeof(char)*strlen(uri));
 char hex[3],code;

 do{
    switch(*(uri+count))
    {
      case '+':
        *(word+ptr)=' ';
        ptr++;
        break;

      case '%':
        sprintf(hex, "%c%c\x00", *(uri+count+1), *(uri+count+2));
        count+=2;
        sscanf(hex, "%x", &code);
        *(word+ptr)=code;
        ptr++;
        break;

      default:
        *(word+ptr)=*(uri+count);
        ptr++;
        break;
      }
   count++;
 }while(count<strlen(uri));

 *(word+ptr)='\0';

 return word;
}

int base64_decode(char *in, int inlen, char *out)
{
  int i,y;
  char *entrada=NULL,*saida=NULL,*ptr=NULL;
  char array[4];

  entrada=in;
  saida=out;

  for(i=0; i<inlen; i+=4)
  {

    if(*entrada == '=')
     return 0;

    memcpy(array,entrada,4);
    memset(saida,0,3);

// desmapeia
    for(y=0; y<4; y++)
    {
     ptr = array+y;

     if(*ptr>='A' && *ptr<='Z')
     {
       *ptr-='A';
       continue;
     }

     if(*ptr>='a' && *ptr<='z')
     {
      *ptr-='a';
      *ptr+=26;
      continue;
     }

     if(*ptr == '+')
     {
       *ptr=62;
       continue;
     }

     if(*ptr == '/')
     {
       *ptr=63;
       continue;
     }

     if(*ptr == '=')
      *ptr=0;

     *ptr-='0';
     *ptr+=52;
    }

    saida[0]= ((array[1]>>4) & 3) | ((array[0]<<2) & 0xfc);
    saida[1]= ((array[2]>>2) & 0xf) | ((array[1]<<4) & 0xf0);
    saida[2]=((array[2]<<6) & 0xc0) | ((array[3]) & 0x3f);
    entrada+=4;
    saida+=3;

  }

  return 0;
}

int char_type_counter(char *string,char type)
{
 int counter=0;

 while(*string != '\0')
 {
  if(*string==type)
   counter++;
  string++;
 }
 return counter;
}

char *rand_str(char *dst, int size)
{
 static const char text[] = "abcdefghijklmnopqrstuvwxyz"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

 int i, len = rand() % (size - 1);
 if(!len)
  len=8;

  for(i=0; i<len; ++i)
   dst[i] = text[rand() % (sizeof text - 1)];

 dst[i] = '\0';

 return dst;
}
// search pattern on text
const char *bitwise_string_search(const char *text, const char *pattern)
{
 int num = strlen(pattern),i=0;
 unsigned long X;
 unsigned long mask[CHAR_MAX+1];

  if (pattern[0] == '\0')
   return text;

  if (num > 31)
   return "The pattern is too long!";

  X = ~1;

  for (i=0; i <= CHAR_MAX; ++i)
   mask[i] = ~0;

  for (i=0; i < num; ++i)
   mask[pattern[i]] &= ~(1UL << i);

  for (i=0; text[i] != '\0'; ++i)
  {
   X |= mask[text[i]];
   X <<= 1;
   if (!(X & (1UL << num)))
    return (text + i - num) + 1;
  }

 return NULL;
}
