#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // You can use the string library!

// The values for the constants below could change, so make sure your
// program is using them where appropriate!
#define MAX_STRING_LENGTH 128
#define MAX_ROW_COUNT 100
#define DELIMITER ','

/**
 * Joins two tables (produces a larger table with combined information from both).
 * Note that the input tables each have fields (chunks of test) separated by 'DELIMITER'. 
 * The first field in each table is a person's name (see the example tables in main())
 * and the second field records appropriate information for the corresponding individual.
 *
 * This function will create a combined (joined) table such that the first field is the
 * person's name, the second is the nationality (from the nationality table), and the
 * third is their favorite food (from the food table).
 *
 * This requires you to *match* the person's name in the two tables, and to do a bit 
 * of string manipulation to build the combined row containing name, nationality, food,
 * and then putting that joined result into the joined table.
 *
 * Your joined table must not contain any rows from either table for which there is no
 * corresponding row in the other table (e.g. in the sample input from main(),
 * 'Nyah Way' appears only on the nationality table, and not in the food table, so there
 * will NOT be any rows in the joined table for this individual.
 *
 * Person's names in the first field must be *unique* within each table (e.g. 'Paco Estrada'
 * can only appear once in the nationality table, and only once in the food table).
 * But 'Paco Estrada' is not the same name as 'paco estradA' (these are considered 
 * different people).
 *
 * INPUT:
 *  nationalities_table:
 *      - an array of strings, each string has 2 DELIMITER-separated columns
 *      - represents Name -> Nationality mappings
 *  foods_table:
 *      - an array of strings, each string has 2 DELIMITER-separated columns
 *      - represents Name -> Favourite Food mappings
 *
 * OUTPUT:
 *  joined_table:
 *      - an array of strings, each with 3 DELIMITER-separated columns
 *      - represents the combined information for a person: name, nationality, food
 *      - The ORDER of the rows in this output table does not matter, so don't worry
 *        about it, as long as the rows are all there that should be there.
 */
void innerJoin(char nationalities_table[MAX_ROW_COUNT][MAX_STRING_LENGTH],
               char foods_table[MAX_ROW_COUNT][MAX_STRING_LENGTH],
               char joined_table[MAX_ROW_COUNT][MAX_STRING_LENGTH * 2])
{
  int i = 0;//index through all the elements
  int comp = 0;
  char name1[MAX_STRING_LENGTH];
  char name2[MAX_STRING_LENGTH];
  char country[MAX_STRING_LENGTH];
  char food[MAX_STRING_LENGTH];
  while (*(nationalities_table[i]) != '\0')
  {
    int x = 0;
    while ((nationalities_table[i][x]) != DELIMITER)
    {
      name1[x] = nationalities_table[i][x];
      x = x+1;
    }
    name1[x] = '\0';
    int j = 0;
    while (*(foods_table[j]) != '\0')
    {
      int k = 0;
      while ((foods_table[j][k]) != DELIMITER)
      {
      name2[k] = foods_table[j][k];
      k = k+1;
      }
      name2[k] = '\0';
      if (strcmp(name1, name2) == 0)
      {
        int start = 0;
        while ((nationalities_table[i][x]) != '\0')
        {
          country[start] = nationalities_table[i][x];
          x = x+1;
          start = start + 1;
        } 
        country[start] = '\0';
        int start2 = 0;
        while ((foods_table[j][k]) != '\0')
        {
        food[start2] = foods_table[j][k];
        k = k+1;
        start2 = start2 +1;
        }
        food[k] = '\0';
        char fin[MAX_STRING_LENGTH] = "";
        strcat(fin, name1);
        strcat(fin, country);
        strcat(fin, food);
        strcpy(joined_table[comp], fin);
        comp += 1;
      }
      j = j+1;
    }
    i = i + 1;
    strcpy(joined_table[comp], "");
  }
  //printf("%s\n", *(nationalities_table[0][1]));
    // TODO: implement this function, satisfying the description above.
    // Feel free to add rows to either table to test your solution, but mind the fact
    // that the names of individuals must be unique!

    // Later on in your studies (or perhaps during your CoOp term, or maybe you have
    // already used this) you'll see that what we're asking you to do is equivalent
    // to what SQL does with database tables when we ask for
    //
    // SELECT Nationalities.name, Nationalities.country, Foods.favourite 
    // FROM Nationalities 
    // INNER JOIN Foods 
    // ON Nationalities.name=Foods.name;
    //

    // NOTE: Please use the DELIMITER constant!
    // Ideally, this function should work even if all the constants above were changed

}

// We NEED this compiler directive to test your code with our own main(). Don't break it.
#ifndef __TESTING  // this compiler directive
int main()
{
    // Please note that these are JUST EXAMPLES!
    // You will be tested on a wide range of data
    //
    // IMPORTANT: The join function above doesn't know how many rows are in
    //            each table, so, we add an *empty string* as the last row
    //            of the tables below. You can assume any input tables we
    //            use to test your program will contain an empty string 
    //            at the last row so you can tell you've reached the end
    //            of the table.
    //
    //  As before - you are expected to make reasonable assumptions
    //  regarding any information not given in these instructions.
    //

    char example_nationalities_table[MAX_ROW_COUNT][MAX_STRING_LENGTH] = {
        "Paco Estrada,Mexico",
        "Joe Armitage,England",
        "Angela Zavaleta,Peru",
        "Nyah Way,Canada",
        "Anya Tafliovich,Ukraine",
        "Brian Harrington,Canada",
        "",                          // <-- Empty string signals end of table
    };
    char example_foods_table[MAX_ROW_COUNT][MAX_STRING_LENGTH] = {
        "Brian Harrington,Avocado Salad",
        "Paco Estrada,Chocolate",
        "Joe Armitage,Chocolate",
        "Angela Zavaleta,Green Eggs",
        "Jack Long,Ham",
        "",                         // <-- Empty string signals end of table
    };

    // Notes on indexing an array of strings:
    // example_nationalities_table[i]   <- gives you a pointer to the string at row i of this table
    // example_nationalities_table[i][j]  <- Is the actual character at row i, position j in the table

    // Note that the size of this output array could have the MAX_ROW_COUNT, but
    // the length of each row may be up to 2*MAX_STRING_LENGTH.
    // We set the first row of this output table to "" (empty string),
    // so we know the table doesn't contain any *valid* rows. Remember though, 
    // this is a large array of chars we haven't actually cleaned-up, so it
    // will contain JUNK - be sure your join function is filling up each row with
    // proper strings, that all have their end-of-string delimiter.
    char joined[MAX_ROW_COUNT][MAX_STRING_LENGTH * 2] = {""};       

    // calling your function...
    // This should create the example joined table from the handout (and put it in `joined`).
    innerJoin(example_nationalities_table, example_foods_table, joined);

    // Printing the table:
    // (leaving THIS print statement is fine, but leave NONE in the `innerJoin` function!)
    for (int idx = 0; 0 != strcmp("", joined[idx]); idx++)
    {
        printf("%s\n", joined[idx]);
    }
}
#endif  // and this compiler directive
