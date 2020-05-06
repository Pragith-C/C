// CSC A48 - Exercise 10 - Breaking Caesar Cipher+
// Complete where indicated below.
//
// Do not add any additional functions
// and do not leave any print statements
// in your final submission for testing!
//
// Updated by F. Estrada, March 2020.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>		// Yes, you can use functions from the string library!

#define MAX_STR_LEN 2048

void caesar_cipher(unsigned char plaintext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN])
{
  int text_loop = 0;
  int pass_loop = 0;
  while (plaintext[text_loop] != '\0')
  {
    int element;
    if (pass_loop >= strlen((char*)password))
    {
      pass_loop = 0;
    }
    element = (((int)plaintext[text_loop]) + ((int)password[pass_loop]));
    plaintext[text_loop] = (char)element;
    pass_loop++;
    text_loop++;
  }

 // This function encodes the input text in plaintext[] using the caesar
 // cipher process with the specified password (please see the exercise
 // description to see how that works).
 //
 // The function must ensure that the 'end-of-string' delimiter is preserved,
 // and that no other character can become the 'end-of-string'.
 //
 // You want to make sure you understand what values can be stored in each
 // entry of the plaintext[] string, and you'll want to look at an ASCII table
 // to check that your function does the right thing.
 //
 // *** TEST your code with multiple input strings, using different passwords,
 //     and verify it works in
 //     every case! if you get incomplete because your function failed our
 //     tests it means you did not test carefully enough.

}

void caesar_decipher(unsigned char cryptotext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN])
{
  int text_loop = 0;
  int pass_loop = 0;
  while (cryptotext[text_loop] != '\0')
  {
    int element;
    if (pass_loop >= strlen((char*)password))
    {
      pass_loop = 0;
    }
    element = (((int)cryptotext[text_loop]) - ((int)password[pass_loop]));
    cryptotext[text_loop] = (char)element;
    pass_loop++;
    text_loop++;
  }

}

void caesar_breaker(unsigned char crypto_message[MAX_STR_LEN], unsigned char password[MAX_STR_LEN], unsigned char dictionary[10][MAX_STR_LEN])
{
  unsigned char possible_passwords[10][MAX_STR_LEN];
  unsigned char possible_words[12][MAX_STR_LEN]={"ssignment", "A48", "ecture", "ecursion", "ead", "otes", "orting", "a48", "aco", "omplexity", "BST", "ello"};
  int count = 0;
  for (int i = 0; i < 10; i++)
  {
    unsigned char end_line [MAX_STR_LEN];
    strcpy((char*) end_line, (char*) crypto_message);
    caesar_decipher(end_line, dictionary[i]);
    int index = strlen((char*)end_line)-1;
    if ((int)(end_line[index]) == 10)
    {
      strcpy((char*)possible_passwords[count], (char*)dictionary[i]);
      count += 1;
    }
  }
  if (count == 1)
  {
    strcpy((char*)password, (char*)possible_passwords[0]);
    return;
  }
  else
  {
    int pass_num = 0;
    while (pass_num < 12)
    {
      for (int i = 0; i < count; i++)
      {
        unsigned char end_line [MAX_STR_LEN];
        strcpy((char*) end_line, (char*) crypto_message);
        caesar_decipher(end_line, possible_passwords[i]);
        if (strstr((char*)end_line, (char*)possible_words[pass_num]) != NULL)
        {
          strcpy((char*)password, (char*)possible_passwords[i]);
          return;
        }
      }
      pass_num++;
    }
  }
}
 // This function takes as input
 // - One line of text encrypted using Caesar Cipher+
 // - An array to hold the password that cracks the cipher
 // - A dictionary to be used for a dictionary-attack (here it only has 10 entries, each is a string)
 //
 // The function determines which is the word in the dictionary that cracks the cipher, and returns it
 // by updating the 'password' string with the correct password.
 //
 // TO DO: Complete this function
 //
 // Constraints: You can assume the input message contains only valid text characters (letters, numbers,
 //              and punctuation signs)
 //              The message is somehow related to A48, it was written by Paco
 //              That's it, you should think about how to use this information to solve your task.
 //              there are many ways to approach this problem, some better than others. Think carefully!

#ifndef __testing

int main()
{

    unsigned char a_passage[5][MAX_STR_LEN]={"Hello All A48 people! this is a reminder that the on-line lecture\n",
                                    "will be on recursion, please make sure you've read the notes,\n",
                                    "before you watch the lecture!\n",
                                    "Also, don't forget to complete your BST assignment. We hope you've\n",
                                    "learned lots about complexity and sorting!\n"};

    unsigned char dictionary[10][MAX_STR_LEN]={"Zucchini",
				      "Carrot",
                                      "Radish",
				      "Broccoli",
				      "Eggplant",
				      "Cilantro",
				      "Sweet Potato",
				      "Tomatoes",
				      "Garlic",
				      "Arugula"};

    unsigned char password[MAX_STR_LEN];

    printf("**** Original input text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);

    // Encode the input test lines
    caesar_cipher(a_passage[0],dictionary[0]);
    caesar_cipher(a_passage[1],dictionary[3]);
    caesar_cipher(a_passage[2],dictionary[5]);
    caesar_cipher(a_passage[3],dictionary[8]);
    caesar_cipher(a_passage[4],dictionary[9]);

    // VERY IMPORTANTLY
    // It should be clear to you, we will test your code with a DIFFERENT message,
    // encoded using DIFFERENT entries in the dictionary, and also a DIFFERENT
    // dictionary! so be sure to test very well!

    printf("\n**** Encrypted text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);

    // Crack the passwords for each text line, and use them to decrypt the text
    printf("\n\n***** Decoding message! *****\n\n");
    for (int i=0; i<5; i++)
    {
        memset(&password[0],0,MAX_STR_LEN*sizeof(unsigned char));   // Clear out password
        caesar_breaker(a_passage[i],password,dictionary);           // Try to get the password for this message
	caesar_decipher(a_passage[i],password);                     // Use the password to decrypt
	// You should check here that your code retrieved the correct password!
	printf("Password=%s, decoded message=%s",password,a_passage[i]);
    }

    return 0;
}

#endif
