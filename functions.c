/*
Homework 4, 600.120 Spring 2015

Tanay Agarwal
tagarwa2@jhu.edu
tagarwa2
03/11/2015
443-691-8192
*/

#include "functions.h"

void printMenu()
{
  printf("Enter the number choice with the required data if any, all in one line (separated by spaces):\n");
  printf("0. Quit\n");
  printf("1. Create new courses from a plain text file (enter file name)\n");
  printf("2. Add a single course to the database (enter course data)\n");
  printf("3. Display details of particular course (enter department and course number: ddd.nnn)\n");
  printf("4. Display all actual courses in database\n");
  printf("5. Change the name of a course (enter ddd.nnn and new course name\n");
  printf("6. Delete a course from the database (enter department and course number: ddd.nnn)\n");
  printf("7. Add a course to a semester listing (enter semester, department, course number, letter grade in upper case)\n");
  printf("8. Remove a course from a semester listing (enter semester, department, course number, letter grade)\n");
  printf("9. Display a semester listing (enter semester number)\n");
}

void addCourseLL(Node ** lptr, Course* newCourse)
{
  //case where adding to first node/empty list
  if( (*lptr) == NULL )
    {
      Node * n = malloc(sizeof(Node));
      n->coursedata = newCourse;
      n->next = NULL;
      (*lptr) = n;
      return;
    }
  //case where adding right after first node
  if( (*lptr)->coursedata->index > newCourse->index )
    {
      Node* newNode = malloc(sizeof(Node));
      newNode->coursedata = newCourse;
      newNode->next = *lptr;
      *lptr = newNode;
      return;
    }
  //iterating to find where to add node
  Node* lptrCopy = *lptr;
  while( lptrCopy->next != NULL )
    {
      if( newCourse->index < lptrCopy->coursedata->index )
	{
	  Node* newNode = malloc(sizeof(Node));
	  newNode->coursedata = newCourse;
	  newNode->next = lptrCopy;

	  Node* lptrCopy2 = *lptr;
	  while( newCourse->index > lptrCopy2->next->coursedata->index )
	    {
	      lptrCopy2 = lptrCopy2->next;
	    }
	  lptrCopy2->next = newNode;
	  return;
	}
      else
	lptrCopy = lptrCopy->next;
    }
  //case where adding node right before last node
  if( newCourse->index < lptrCopy->coursedata->index )
    {
      Node* newNode = malloc(sizeof(Node));
      newNode->coursedata = newCourse;
      newNode->next = lptrCopy;

      Node* lptrCopy2 = *lptr;
      while( newCourse->index > lptrCopy2->next->coursedata->index )
	{
	  lptrCopy2 = lptrCopy2->next;
	}
      lptrCopy2->next = newNode;
      return;
    }
  else //case where adding node at the end of the list
    {
      Node * n = malloc(sizeof(Node));
      n->coursedata = newCourse;
      n->next = NULL;
      lptrCopy->next = n;
    }
}
//find and return pointer to node based on matching departmand and course numbers
Node* find(Node* head, Course* newCourse)
{
  if(head == NULL)
    {
      return NULL;
    }
  if (head->coursedata->depCode == newCourse->depCode && head->coursedata->courseCode == newCourse->courseCode)
    {
      return head;
    }
  else
    return find((head->next), newCourse);
}

void clearList(Node ** lptr)
{
  /*if (*lptr)
    {
      if( (*lptr)->next ) 
	clearList( &((*lptr)->next) );
      free( (*lptr)->coursedata );
      free(*lptr);
      *lptr = NULL;
    }*/

  Node* temp;
  while( (*lptr) != NULL )
    {
      temp = *lptr;
      *lptr = (*lptr)->next;
      free(temp->coursedata);
      free(temp);
      temp = NULL;
    }
}

void deleteCourseLL(Node ** lptr, int inputIndex)
{
  if (*lptr == NULL) //do nothing if list is empty
    return;
  if ((*lptr)->coursedata->index == inputIndex) //base case if node is found
    {
      Node* temp = *lptr;
      *lptr = (*lptr)->next;
      free(temp->coursedata);
      free(temp);
      temp = NULL;
      return;
    }
  else
    deleteCourseLL(&((*lptr)->next), inputIndex); //recurse till node is found, returns NULL if never found
}

int printLL(Node* head) //prints list while keeping track of how many nodes it prints
{
  int count = 0;
  if(head != NULL)
    {
      printf("%s.%03d.%03d %.1f %s %s\n", head->coursedata->div, head->coursedata->depCode, head->coursedata->courseCode, head->coursedata->credCode, head->coursedata->title, head->coursedata->grade);
      count++;
      return count + printLL(head->next);
    }
  else
    return count;
}

void readCourse(Course* course, FILE* inputFile, int index)
{
  fseek(inputFile, index*sizeof(Course), SEEK_SET);
  fread(course, sizeof(Course), 1, inputFile);
}

void writeCourse(Course* course, FILE* outputFile, int index)
{
  fseek(outputFile, index*sizeof(Course), SEEK_SET);
  fwrite(course, sizeof(Course), 1, outputFile);
  fflush(outputFile);
}

void interpretChoice(FILE* database, Node** semesterList, bool* quitClause) //takes in user input and picks correct option
{
  int userChoice;
  scanf("%d", &userChoice);

  switch(userChoice)
    {
    case 0: *quitClause = true; break;
    case 1: option1(database); break;
    case 2: option2(database); break;
    case 3: option3(database); break;
    case 4: option4(database); break;
    case 5: option5(database); break;
    case 6: option6(database); break;
    case 7: option7(semesterList, database); break;
    case 8: option8(semesterList); break;
    case 9: option9(semesterList); break;
    default: printf("Invalid choice. Please enter a correct choice.\n"); break;
    }
}

void option1(FILE* database)
{
  //get plain text file name
  char* textFileName = malloc(sizeof(char*));;
  scanf(" %s\n", textFileName);

  FILE* plainTextFile = fopen(textFileName, "r");
  if(!plainTextFile)
    {
      fprintf(stderr, "File cannot be opened.\n");
      return;
    }

  int line_counter = 0;
  
  //go through plain text file, reading and processing each line
  while(!feof(plainTextFile))
    { 
      line_counter++;
      //get one line
      int c1, c2; //code provided by Joanne
      char div[3], title[TITLE_LENGTH+1];
      int dept = 0;
      int num = 0;
      int count = 0;
      int c = ' ';
      fscanf(plainTextFile, "%2s.%d.%d %d.%d ", div, &dept, &num, &c1, &c2);
      while (count < TITLE_LENGTH && (c = fgetc(plainTextFile)) != '\n') {
	title[count++] = (char) c;
      }
      title[count] = '\0';
      while (c != '\n' && c != EOF) c = fgetc(plainTextFile);   // skip to end of line
      
      //check for invalid input
      if( dept<1 || dept>700 || num<100 || num>899 || c1<0 || c1>5 || (c2 != 0 && c2 != 5) )
	fprintf(stderr, "Invalid data in line %d of file.\n", line_counter);
      else
	{
	  //make placeholder course to check for existence
	  int new_index = (dept-1)*800 + (num-100);
	  Course* currCourse = malloc(sizeof(Course));
	  readCourse(currCourse, database, new_index);

	  if(currCourse->depCode != 0 || currCourse->courseCode != 0)
	    fprintf(stderr, "Course in line %d already exists.\n", line_counter);
	  else //add course to database
	    {
	      Course* newCourse = malloc(sizeof(Course));
	      newCourse->depCode = dept;
	      newCourse->courseCode = num;
	      newCourse->credCode = (double)c1 + ((double)c2)/10.0;
	      newCourse->index = new_index;
	      strcpy(newCourse->div, div);
	      strcpy(newCourse->title, title);
	      writeCourse(newCourse, database, new_index);
	      free(newCourse);
	    }
	  free(currCourse);
	}
    }
  fclose(plainTextFile);
}

void option2(FILE* database) //same as option 1, except only one course line
{
  int c1, c2; //code provided by Joanne
  char div[3], title[TITLE_LENGTH+1];
  int dept = 0;
  int num = 0;
  int count = 0;
  int c = ' ';
  fscanf(stdin, "%2s.%d.%d %d.%d ", div, &dept, &num, &c1, &c2);
  while (count < TITLE_LENGTH && (c = fgetc(stdin)) != '\n') {
    title[count++] = (char) c;
  }
  title[count] = '\0';
  while (c != '\n' && c != EOF) c = fgetc(stdin);   // skip to end of line

  if( dept<1 || dept>700 || num<100 || num>899 || c1<0 || c1>5 || (c2 != 0 && c2 != 5) )
    fprintf(stderr, "Invalid data in line.\n");
  else
    {
      int new_index = (dept-1)*800 + (num-100);
      Course* currCourse = malloc(sizeof(Course));
      readCourse(currCourse, database, new_index);

      if(currCourse->depCode != 0 || currCourse->courseCode != 0)
	fprintf(stderr, "Course already exists.\n");
      else
	{
	  Course* newCourse = malloc(sizeof(Course));
	  newCourse->depCode = dept;
	  newCourse->courseCode = num;
	  newCourse->credCode = (double)c1 + ((double)c2)/10.0;
	  newCourse->index = new_index;
	  strcpy(newCourse->div, div);
	  strcpy(newCourse->title, title);
	  writeCourse(newCourse, database, new_index);
	  free(newCourse);
	}
      free(currCourse);
    }
}

void option3(FILE* database)
{
  //get input and check for invalid data
  int dept = 0;
  int num = 0;
  fscanf(stdin, " %d.%d", &dept, &num);
  if( dept<1 || dept>700 || num<100 || num>899 )
    fprintf(stderr, "Invalid department and/or course number.\n");
  else //read and print course
    {
      int new_index = (dept-1)*800 + (num-100);
      Course* currCourse = malloc(sizeof(Course));
      readCourse(currCourse, database, new_index);
      if(currCourse->depCode == 0)
	fprintf(stderr, "Course doesn't exist.\n");
      else
	{
	  printf("%s.%03d.%03d %.1f %s\n", currCourse->div, currCourse->depCode, currCourse->courseCode, currCourse->credCode, currCourse->title);
	}
      free(currCourse);
    }
}

void option4(FILE* database)
{
  //go through entire database and print if course isn't blank
  for (int i = 0; i < 560000; i++)
    {
      Course* currCourse = malloc(sizeof(Course));
      readCourse(currCourse, database, i);
      
      if(currCourse->depCode != 0 && currCourse->courseCode != 0) //check if course is blank
	{
	  printf("%s.%03d.%03d %.1f %s\n", currCourse->div, currCourse->depCode, currCourse->courseCode, currCourse->credCode, currCourse->title);
	}
      
      free(currCourse);
    }
}

void option5(FILE* database)
{
  //get input and check for validity
  int dept = 0;
  int num = 0;
  char title[TITLE_LENGTH+1];
  int count = 0;
  int c = ' ';
  fscanf(stdin, " %d.%d", &dept, &num);
  while (count < TITLE_LENGTH && (c = fgetc(stdin)) != '\n') {
    title[count++] = (char) c;
  }
  title[count] = '\0';
  while (c != '\n' && c != EOF) c = fgetc(stdin);

  if( dept<1 || dept>700 || num<100 || num>899 )
    fprintf(stderr, "Invalid department and/or course number.\n");
  else
    {
      int index = (dept-1)*800 + (num-100);
      Course* currCourse = malloc(sizeof(Course));
      readCourse(currCourse, database, index);
      
      if(currCourse->depCode == 0 && currCourse->courseCode == 0) //check if course is empty
	fprintf(stderr, "Course doesn't exist.\n");
      else
	{
	  strcpy(currCourse->title, title);
	  writeCourse(currCourse, database, index); //change title and rewrite into database
	}
      free(currCourse);
    }
}

void option6(FILE* database)
{
  //get input and check for validity
  int dept = 0;
  int num = 0;
  fscanf(stdin, " %d.%d", &dept, &num);
  if( dept<1 || dept>700 || num<100 || num>899 )
    fprintf(stderr, "Invalid department and/or course number.\n");
  else 
    {
      int new_index = (dept-1)*800 + (num-100);
      Course* currCourse = malloc(sizeof(Course));
      readCourse(currCourse, database, new_index);
      if(currCourse->depCode == 0) //check if course is already blank
	fprintf(stderr, "Course doesn't exist.\n");
      else
	{
	  Course* empty_course = malloc(sizeof(Course)); //create and write empty course
	  strcpy(empty_course->div, "");
	  empty_course->depCode = 0;
	  empty_course->courseCode = 0;
	  empty_course->credCode = 0.0;
	  strcpy(empty_course->title, "");
	  empty_course->index = 560001;
	  
	  writeCourse(empty_course, database, new_index);

	  free(empty_course);
	}
      free(currCourse);
    }
}

void option7(Node** semesterList, FILE* database)
{
  //get input and check for validity
  int dept = 0;
  int num = 0;
  int semester = -1;
  char g1 = ' ';
  char g2 = ' ';
  fscanf(stdin, " %d %d.%d %c%c", &semester, &dept, &num, &g1, &g2);
  if( (g1 == 'F' && g2 != '/') || (g1 == 'D' && g2 == '-') )
    {
      fprintf(stderr, "Invalid grade in input.\n");
      return;
    }
  if( semester<0 || semester>9 || dept<1 || dept>700 || num<100 || num>899 || (g1 != 'A' && g1 != 'B' && g1 != 'C' && g1 != 'D' && g1 != 'F') || (g2 != '+' && g2 != '-' && g2 != '/') )
    fprintf(stderr, "Invalid input data.\n");
  else
    {
      int new_index = (dept-1)*800 + (num-100);
      Course* currCourse = malloc(sizeof(Course));
      readCourse(currCourse, database, new_index);
      if(currCourse->index != new_index) //check if course is in database
	fprintf(stderr, "Course doesn't exist in database.\n");
      else
	{
	  Node* tempCourse = find(semesterList[semester], currCourse); //check if course is already in linked list
	  if(tempCourse != NULL)
	    fprintf(stderr, "Course already exists in semester.\n");
	  else //add to linked list
	    {
	      currCourse->grade[0] = g1;
	      currCourse->grade[1] = g2;
	      addCourseLL(&(semesterList[semester]), currCourse);
	    }
	}
    }
}

void option8(Node** semesterList)
{
  //get input and check for validity
  int dept = 0;
  int num = 0;
  int semester = -1;
  fscanf(stdin, " %d %d.%d", &semester, &dept, &num);

  if( semester<0 || semester>9 || dept<1 || dept>700 || num<100 || num>899 )
    fprintf(stderr, "Invalid input data.\n");
  else
    {
      Course* newCourse = malloc(sizeof(Course));
      newCourse->depCode = dept;
      newCourse->courseCode = num;
      Node* existenceCheck = find(semesterList[semester], newCourse); //check if course is in linked list
      if(existenceCheck == NULL)
	fprintf(stderr, "Course doesn't exist in semester.\n");
      else
	{
	  int index = (dept-1)*800 + (num-100);
	  deleteCourseLL(&(semesterList[semester]), index); //delete course from linked list
	}
      free(newCourse);
    }
}

void option9(Node** semesterList)
{
  //get input and check for validity
  int semester = -1;
  fscanf(stdin, " %d", &semester);
  if( semester<0 || semester>9 )
    fprintf(stderr, "Invalid semester.\n");
  else
    {
      int numPrinted = printLL(semesterList[semester]); //call printLL function and check if any items are printed
      if(numPrinted == 0)
	printf("No courses this semester.\n");
    }
}
