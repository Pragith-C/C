#include<stdio.h>
#include<stdlib.h>
#define MAX_STR_LEN 1024

// DO NOT USE the string library <string.h> for this exercise
int lengthy(char *source)
{
  int count = 0;
  while (*(source+count) != '\0')
  {
    count += 1;
  }
  return count;
}

void wordSwapper(char *source, char *destination)
{
  int x = (lengthy(source) - 1); //Help Iterate over Source
  int end = (lengthy(source) - 1);
  int i = 0; //Help Iterate over Destination
  while (x >= 0)
  {
    if (*(source+x) == ' ')
    {
      if ((x) == (lengthy(source) - 1))//Space End
      {
        x = x - 1;
        end = end - 1;
      }
      else if ((*(source + x + 1) == ' ') && (x != 0)) //Skip WhiteSpaces
      {
        x = x - 1;
        end = end - 1;
      }
      else //If it detects a space
      {
        int start = x + 1;
        int word_len = end - start + i+ 1;
        int j = 0; //Help Iterate over a word in Source
        while (i < word_len)
        {
          *(destination + i) = *(source + start + j);
          i = i + 1;
          j = j + 1;
        }
        *(destination + i) = ' ';
        i = i + 1;
        end = start - 2;
        x = x - 1;
      }
    }
    else if (x == 0)//Last Word
    {
      int start = x;
      int word_len = end - start + i+ 1;
      int j = 0; //Help Iterate over a word in Source
      while (i < word_len)
      {
        *(destination + i) = *(source + start + j);
        i = i + 1;
        j = j + 1;
      }
      *(destination + i) = '\0';
      x = x - 1;
    }
    else
    {
      x = x - 1;
    }
  }
  *(destination + i ) = '\0';
}
  // This function takes a pointer to a 'source' string (an array
  // of chars, with maximum size MAX_STR_LEN), and
  // makes a new string inside the 'destination' string
  // (which is also passed as a pointer) so that the order
  // of the words in the destination string is the reverse
  // of the order in the source string. 
  //
  // e.g. if:
  // The 'surce' string contains "Hello I Am A String!"
  //
  // then the destination string will contain
  //
  // 'String! A Am I Hello"
  // (notice that we add a space between each word in the
  // destination string - these are *added*, not *copied*)
  //
  // The only character to be used in separating words is
  // a blank space, so any other characters are considered
  // part of a word, for example "Hello, I; Am! A. *String*"
  // will becoe "*String* A. Am! I; Hello,"
  //
  // You *MUST* use pointers and pointer addressing to complete
  // this exercise (that is, no array notation with brackets []),
  // and you can not assume the 'destination' string is empty,
  // it could (and likely does) contain junk.
  //
  // If you decide to write helper functions, make sure they
  // are placed *above* this function's code.
  
  // TO DO: Complete this function

#ifndef __TESTING
int main()
{
    char source[MAX_STR_LEN]="silence .is a looking bird:the turning; edge, of life. e. e. cummings";
    char destination[MAX_STR_LEN]="I am a destination string and I contain lots of junk 1234517265716572@qsajdkuhasdgsahiehwjauhiuiuhdsj!";

    printf("The original string is: \n%s\n",source);

    // Call word swapper with the address of the first character in 'source' and the first character in 'destination'
    wordSwapper(&source[0],&destination[0]);
    // You could also call wordSwapper like this: wordSwapper(source,destination) since, as we will have seen in
    // lecture this week, the array's name can be used to pass into a function the address of the first entry
    // in the array.
    
    printf("Destination string after swapping: \n%s\n",destination);    
}
#endif