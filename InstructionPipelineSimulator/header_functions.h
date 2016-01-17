#ifndef HEADER_FUNCTIONS_H_INCLUDED
#define HEADER_FUNCTIONS_H_INCLUDED

char *opcode_tokens[]={"ADD","SUB","MOVC","MOV","MUL","AND","OR","EX-OR","LOAD","STORE","BZ","BNZ","JUMP","BAL","HALT"};
char *register_tokens[]={"R0","R1","R2","R3","R4","R5","R6","R7","X"};

int memory[10000]={0};


menu2=0;
int l=0;
int done=0;
typedef struct stream
{   struct stream *prev;
    int address;
    int IQ_slot;
    char opcode[20];
    char first[10];
    int f_value;
    int f_tag;
    char second[10];
    int s_value;
    int s_tag;
    char third[10];
    int t_value;
    int t_tag;
    struct stream *next;
}INSTRUCTION;
struct loop
{
    char name[20];
    int address;

};
char x[100][5];
     int value[100]={0};

struct stream *start=NULL,*PC=NULL;


#endif // HEADER_FUNCTIONS_H_INCLUDED
