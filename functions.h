/*
Homework 4, 600.120 Spring 2015

Tanay Agarwal
tagarwa2@jhu.edu
tagarwa2
03/11/2015
443-691-8192
*/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

#define NUM_SEMESTERS 10
#define TITLE_LENGTH 30

typedef struct
{
  char div[3];
  int depCode;
  int courseCode;
  double credCode;
  char title[TITLE_LENGTH+1];
  int index;
  char grade[2];
} Course;

typedef struct Node_struct
{
  Course* coursedata;
  struct Node_struct* next;
} Node;

void printMenu();
void interpretChoice(FILE* database, Node** semesterList, bool* quitClause);
void option1(FILE* database);
void option2(FILE* database);
void option3(FILE* database);
void option4(FILE* database);
void option5(FILE* database);
void option6(FILE* database);
void option7(Node** semesterList, FILE* database);
void option8(Node** semesterList);
void option9(Node** semesterList);
void addCourseLL(Node** lptr, Course* newCourse);
void deleteCourseLL(Node** lptr, int inputIndex);
int printLL(Node* head); //returns number of courses printed
Node* find(Node* head, Course* newCourse); //returns pointer to found node
void clearList(Node** lptr);
void readCourse(Course* course, FILE* inputFile, int index);
void writeCourse(Course* course, FILE* outputFile, int index);

#endif // FUNCTIONS_H_
