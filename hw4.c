/*
Homework 4, 600.120 Spring 2015

Tanay Agarwal
tagarwa2@jhu.edu
tagarwa2
03/11/2015
443-691-8192
*/

#include "functions.h"

int main (int argc, char * argv[])
{ 
  if (argc == 1)
  {
    printf("Usage: Enter name of random access file\n");
    return 1;  // exit program
  }

  //create and fill database with empty courses if it doesn't exist
  FILE* ranAccFile = fopen(argv[1], "r+b");
  if (ranAccFile == NULL)
    {
      ranAccFile = fopen(argv[1], "w+b");
      if(!ranAccFile)
	{
	  perror("ERROR");
	  return EXIT_FAILURE;
	}
      fseek(ranAccFile, 0, SEEK_SET);
      Course* empty_course = malloc(sizeof(Course));
      strcpy(empty_course->div, "");
      empty_course->depCode = 0;
      empty_course->courseCode = 0;
      empty_course->credCode = 0.0;
      strcpy(empty_course->title, "");
      empty_course->index = 560001;
      for (int i = 0; i < 560000; i++)
	{
	  //writeCourse(empty_course, ranAccFile);
	  fwrite(empty_course, sizeof(Course), 1, ranAccFile);
	}
      free(empty_course);
      
      fflush(ranAccFile);
    }
  
  fseek(ranAccFile, 0, SEEK_SET);
  
  bool quitClause = false;

  //Semester listing initialization
  Node* semesterList[NUM_SEMESTERS];
  for (int i = 0; i < NUM_SEMESTERS; i++)
    {
      semesterList[i] = NULL;
    }

  printMenu(); //print menu once at the beginning of the program
  while (!quitClause) //main loop, takes user input till user decides to quit
    {
      interpretChoice(ranAccFile, semesterList, &quitClause);
    }
  
  //free all linked list memory
  for(int i = 0; i < NUM_SEMESTERS; i++)
    {
      clearList(&(semesterList[i]));
    }
  fclose(ranAccFile);
}
