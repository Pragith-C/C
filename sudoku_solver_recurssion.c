/*
 * CSC A48 - Exercise 11 - Sudoku Solver
 *
 * Your goal in this exercise is to practice recursion and
 * to see how a properly written recursive solution can
 * take care of fairly complicated tasks with a few lines
 * of (well thought out) code.
 *
 * We will be solving Sudoku puzzles. In case you have never
 * solved or seen a Sudoku, you can learn more about them
 * here:
 *
 * https://en.wikipedia.org/wiki/Sudoku
 *
 * Your task if to write a function that takes an input
 * Sudoku in the form of a 9x9 array of integers. the
 * array will have a few entries filled with numbers in
 * [1, 9], and the remaining entries set to zero.
 *
 * For the example in the wiki, the input array will
 * be
 *
 * 5 3 0 0 7 0 0 0 0
 * 6 0 0 1 9 5 0 0 0
 * 0 9 8 0 0 0 0 6 0
 * 8 0 0 0 6 0 0 0 3
 * 4 0 0 8 0 3 0 0 1
 * 7 0 0 0 2 0 0 0 6
 * 0 6 0 0 0 0 2 8 0
 * 0 0 0 4 1 9 0 0 5
 * 0 0 0 0 8 0 0 7 9
 *
 * Your code should find the values that correctly
 * complete the Sudoku.
 *
 * As a brief reminder, a correctly solved Sudoku is
 * one in which there are no repeated digits in any
 * row, any column, or any of the 3x3 sub-arrays that
 * make up the large 9x9 grid. Another way to think
 * about it is, every row, column, and 3x3 subgrid
 * uses all of the different digits.
 *
 * How to solve this?
 *
 * * RECURSIVELY!
 *
 * (hint) - Solving a Sudoku with N unknown values
 * may involve trying something, then solving an
 * easier Sudoku problem.
 *
 * * How to approach this?
 *
 * - As noted in class:
 * 	a) Determine the base case(s)
 * 	b) Figure out the recursive case
 * 	c) Determine what needs to happen to
 * 	   the solution for the entire problem
 * 	   is returned once the recursion hits
 * 	   the base case(s)
 *
 * - Conditions on the input Sudoku
 * 	- It will have AT LEAST ONE DIGIT in each
 * 	  3x3 subgrid. Likely there will be several
 * 	  3x3 subgrids with several digits already
 * 	  set to some value.
 *
 * - Conditions on your solution
 * 	- It should return a solution if there
 * 	  exists one.
 * 	- If no solution can be found, return the
 * 	  original input array
 * 	- If multiple solutions exist, any one of
 *        them is valid
 *
 * - Can I use helper functions?
 * 	- Yes, by all means!
 *
 * - Can I add extra libraries?
 * 	- No, they won't be needed.
 *
 * - Can I change the 'print_sudoku()' function?
 * 	- Please don't, we may need it for testing!
 *
 * (c) F. Estrada, March 2019
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  for (int j=0; j<9; j++)
  {
    for (int i=0; i<9;i++)
    {
      printf("%d  ",sudoku[j][i]);
    }
    printf("\n");
  }
}

int empty_row (int sudoku[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (sudoku [i][j] == 0)
      {
        return i;
      }
    }
  }
  return 100; // No empty Row Found
}

int empty_column (int sudoku[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (sudoku [i][j] == 0)
      {
        return j;
      }
    }
  }
  return 100; // No empty column Found
}

int values_row(int sudoku[9][9], int row, int num)
{
  int count = 0;
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[row][i] == num)
    {
      count++;
    }
  }
  return count;
}

int values_column(int sudoku[9][9], int column, int num)
{
  int count = 0;
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[i][column] == num)
    {
      count++;
    }
  }
  return count;
}

int values_square(int sudoku[9][9], int row, int col, int num)
{
  int ori_row = 0;
  int ori_col = 0;
  if ((row >= 0) && (row <= 2))
  {
    ori_row = 0;
  }
  else if ((row >= 3) && (row <= 5))
  {
    ori_row = 3;
  }
  else if ((row >= 6) && (row <= 9))
  {
    ori_row = 6;
  }
  if ((col >= 0) && (col <= 2))
  {
    ori_col = 0;
  }
  else if ((col >= 3) && (col <= 5))
  {
    ori_col= 3;
  }
  else if ((col >= 6) && (col <= 9))
  {
    ori_col = 6;
  }
  int count = 0;
  for (int i = ori_row; i < ori_row + 3; i++)
  {
    for (int x = ori_col; x < ori_col + 3; x++)
    {
      if(sudoku[i][x] == num)
      {
        count++;
      }
    }
  }
  return count;
}


int check_sudoku(int sudoku[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (sudoku[i][j] != 0)
      {
        if ((values_row(sudoku, i, sudoku[i][j]) > 1) || (values_column(sudoku, j, sudoku[i][j]) > 1) || (values_square(sudoku, i, j, sudoku[i][j]) > 1) || (sudoku[i][j] < 1) || (sudoku[i][j] > 9))
        {
          return 1;
        }
      }
    }
  }
  return 0;
}

int solved(int sudoku[9][9])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if ((values_row(sudoku, i, sudoku[i][j]) != 1) || (values_column(sudoku, j, sudoku[i][j]) != 1) || (values_square(sudoku, i, j, sudoku[i][j]) != 1) || (sudoku[i][j] == 0))
      {
        return 0;
      }
    }
  }
  return 1;
}

void solve_sudoku(int sudoku[9][9], int depth)
{
  depth++;
  if (check_sudoku(sudoku) == 1)
  {
    return;
  }
  int emp_row = empty_row(sudoku);
  int emp_col = empty_column(sudoku);
  if ((emp_row == 100) || (emp_col == 100))
  {
    return;
  }
  for (int i = 1; i <= 9; i++)
  {
    if ((values_row(sudoku, emp_row, i) == 0) && (values_column(sudoku, emp_col, i) == 0) && (values_square(sudoku, emp_row, emp_col, i) == 0))
    {
      sudoku[emp_row][emp_col] = i;
      int next_emp_row = empty_row(sudoku);
      int next_emp_col = empty_column(sudoku);
      solve_sudoku(sudoku, depth);
      if (solved(sudoku) == 1)
      {
        return;
      }
      sudoku[next_emp_row][next_emp_col] = 0;
    }
  }
  if (sudoku[emp_row][emp_col] == 0)
  {
    return; // no valid repalcement is found
  }
}

#ifndef __testing

int main()
{
   // We'll provide you with the same test case
   // from the Wiki, so you can check your output.
   // But as always, be aware we will test your
   // solution on different Sudoku puzzles.

   int Sudoku[9][9]={{5, 3, 0, 0, 7, 0, 0, 0, 0},
		     {6, 0, 0, 1, 9, 5, 0, 0, 0},
		     {0, 9, 8, 0, 0, 0, 0, 6, 0},
		     {8, 0, 0, 0, 6, 0, 0, 0, 3},
		     {4, 0, 0, 8, 0, 3, 0, 0, 1},
		     {7, 0, 0, 0, 2, 0, 0, 0, 6},
		     {0, 6, 0, 0, 0, 0, 2, 8, 0},
		     {0, 0, 0, 4, 1, 9, 0, 0, 5},
		     {0, 0, 0, 0, 8, 0, 0, 7, 9}};


  printf("Input puzzle is:\n");
  print_sudoku(Sudoku);

  solve_sudoku(Sudoku,0);

  printf("Solution is:\n");
  print_sudoku(Sudoku);

}

#endif
