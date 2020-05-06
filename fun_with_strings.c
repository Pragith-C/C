#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_STR_LEN 1024

void pidgin(char input[MAX_STR_LEN])
{
  int i = 0;
  while ((input[i] != '\0') && (input[i+1] != '\0'))
  {
    char ele_1 = input[i];
    char ele_2 = input[i+1];
    input[i+1] = ele_1;
    input[i] = ele_2;
    i = i + 2;
  }
}

void vowel_caser(char input[MAX_STR_LEN])
{
  int i = 0;
  while (input[i] != '\0')
  {
    if (input[i] == ('a')|| 
        input[i] == ('e')|| 
        input[i] == ('i')|| 
        input[i] == ('o')|| 
        input[i] == ('u'))
    {
      input[i] = toupper(input[i]);
    }
    else if (input[i] == ('A')||
             input[i] == ('E')|| 
             input[i] == ('I')|| 
             input[i] == ('O')|| 
             input[i] == ('U'))
    {
      input[i] = tolower(input[i]);
    }
    i = i + 1;
  }
}

int main() 
{
  char string[MAX_STR_LEN] = "A strIng is jUst a bunch Of chArs sittIng togEthEr in A row!";
  printf("%s\n", string);
  pidgin(string);
  printf("%s\n", string);
  vowel_caser(string);
  printf("%s\n", string);
  return 0;
}