#ifndef _HEXDUMP
#define _HEXDUMP

#define FILEPATH 1
#define VALUES_INLINE 20
#define PRINT_BUFFER_SIZE 10000
#define RAM "-ram"
#define LINE "-line"
#define OUT "-out"
#define HELP "-help"
#define HELP_TEXT "Syntax:\n\t hexdump PATH -line LINE DELIMITER -ram RAM -out OUTPATH\n\nParameters:\n\t PATH - Path of file to hexdump\n\t LINE - Amount of bytes to dump every line\n\t RAM - In MBs, Amount of memory for print buffer, the more the faster program executes.\n\t OUTPATH - Path of file to hexdump into"
#define NO_ARGUMENTS_TEXT "Syntax Error: Too Few Arguments Given!\n\nProgram Terminated..."
#define ARGUMENT_MISSING_TEXT "Syntax Error: Argument Missing!"
#define ARGUMENT_WRONG_TEXT "Syntax Error: Argument Type Wrong!"
#define SYNTAX_WRONG "Syntax is Wrong! try 'hexdump -help'"
#define MEMORY_ALLOCATION_FAILED "Memory Allocation Failed!\n\nProgram Terminated..."

enum actionResult { DEFAULT = -1, NO_ARGUMENTS = -2, ARGUMENT_MISSING = -3, ARGUMENT_WRONG = -3 };
enum boolean { FALSE = 0, TRUE = 1 };
/*END*/


/*Function-Prototypes*/

/*Recieves a String-Array and Generates path with SPACE (' ') Seperating Values*/
char* getPath(char* argv[], int start, int end, char* dest);
char* hexform(char buffer[], int bytesRead, char dest[], int lineDelimiter);
int indexFirstArgument(char* argv[], int argc,const char* possibleArguments[], int argumentsLen);
int isAlphaString(char* str);
int isNumericString(char* str);
void allocate(void** dest, int bytes);
/*END*/

#endif
