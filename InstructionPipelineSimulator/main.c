#include <stdio.h>
#include <stdlib.h>
#include "header_functions.h"
#include "header_functions2.h"
#include "header_functions3.h"
#include "header_functions4.h"
int head=0,tail=0;
INSTRUCTION *F1=NULL,*F2=NULL,*D1=NULL,*D2=NULL,*INTFU,*MULFU1,*MULFU2,*MULFU3,*MEMFU1,*MEMFU2,*MEMFU3;
int ARF[10][2]={0};
int PRF[16][2]={0};
int RNT[10][3]={-1};
int MAP[10][2]={0};


INSTRUCTION *IQ[8];
INSTRUCTION *LSQ[4];
INSTRUCTION *ROB[16];
#include "simulate.h"



int find_archi_from_map(int x)
{
    int i=0;
    for(i=0;i<10;i++)
    {
        if(MAP[i][1]==x)
            return MAP[i][0];
    }
}


int insert_into_ROB(INSTRUCTION *instr)
{     int x;
      if(head==tail-1 || (tail==0 && head==31))
      {
          return 1;
      }
      ROB[head]=instr;
      x=atoi(instr->first);
     // printf("%s",instr->first);
      x=find_archi_from_map(x);
      RNT[x][1]=head;
      RNT[x][2]=1;
      head=(head+1)%16;


      return 0;
}
INSTRUCTION  *delete_from_ROB(INSTRUCTION *instr)
{
        //INSTRUCTION *instr;
        if(head==tail)
        {
            return 1;
        }
        instr=ROB[tail];
        ROB[tail]=NULL;
        tail=(tail+1)%16;
        return instr;
}

int  initialize_IQ()
{
      int i=0;
      for(i=0;i<8;i++)
        IQ[i]=NULL;


}


int initialize_LSQ()
{
      int i=0;
      for(i=0;i<4;i++)
        LSQ[i]=NULL;
        return;
}



int initialize_ROB()
{
      int i=0;
      for(i=0;i<32;i++)
        ROB[i]=NULL;
}

int initialize_ARF()
{   int i=0;
    for( i=0;i<10;i++)
    {
        ARF[i][0]=i;
        ARF[i][1]=(rand()%100)+1;
    }
    return;
}

int initialize_PRF()
{    int i=0;
    for(i=0;i<16;i++)
    {
        PRF[i][0]=i;
        PRF[i][1]=0;
    }

    return;
}
int initialize_RNT()
{        int i=0;
         for(i=0;i<10;i++)
         {
             RNT[i][0]=i;
             RNT[i][1]=i;
             RNT[i][2]=0;
         }
         return;
}

int initialize_MAP()
{        int i=0;
         for(i=0;i<10;i++)
         {
             MAP[i][0]=i;
         }
         return;
}

int get_free_physical_register()
{     int i=0;
    for(i=7;i<16;i++)
    {
        if(PRF[i][1]==0)
        {
            PRF[i][1]=1;
            return i;
        }
    }
    return i;
}
int check_RNT(int tail)
{     int i=0;
      for(i=0;i<10;i++)
      {
          if((RNT[i][1]==tail) && RNT[i][2]==1 )
            return RNT[i][0];
      }

     return;

}


int commit_and_retire()
{   int archi_register=0;
    int phy_register=0;
    if(ROB[tail]==NULL )
    {
        return 1;
    }



    if(ROB[tail]->f_tag==0)
    {   archi_register=check_RNT(tail);
        phy_register=atoi(ROB[tail]->first);
    PRF[phy_register][1]=0;
    if(!strcmp(ROB[tail]->opcode,"LOAD"))
    {
    }
    else if (strcmp(ROB[tail]->opcode,"STORE"))
    {
    }
    else
    ARF[archi_register][1]=ROB[tail]->f_value;

    RNT[archi_register][1]=archi_register;
    RNT[archi_register][2]=0;
    printf("\nRetired From ROB: %d\n",delete_from_ROB(ROB[tail])->address);

    }
    return 0;
}
void initialize_all()
{
    initialize_IQ();
    initialize_LSQ();
    initialize_ROB();
    initialize_ARF();
    initialize_PRF();
    initialize_RNT();
    initialize_MAP();
    return;
}
int forward_to_all(INSTRUCTION *instr)
{       int i=0;

        for(i=0;i<16;i++)
        {
            if(ROB[i]!=NULL)
            {


            if(instr->IQ_slot==ROB[i]->f_tag)
            {
                ROB[i]->f_value=instr->f_value;
                ROB[i]->f_tag=0;

            }
            }
        }
        for(i=1;i<9;i++)
        {   if(IQ[i]!=NULL)
            {
                    if(instr->IQ_slot==IQ[i]->s_tag)
                    {
                        IQ[i]->s_value=instr->f_value;
                        IQ[i]->s_tag=0;
                    }
                    if(instr->IQ_slot==IQ[i]->t_tag)
                    {
                        IQ[i]->t_value=instr->f_value;
                        IQ[i]->t_tag=0;
                    }
            }
        }

        for(i=1;i<5;i++)
        {   if(LSQ[i]!=NULL)
            {

                    if(instr->IQ_slot==LSQ[i]->s_tag)
                    {
                        LSQ[i]->s_value=instr->f_value;
                        LSQ[i]->s_tag=0;
                    }
                    if(instr->IQ_slot==LSQ[i]->t_tag)
                    {
                        LSQ[i]->t_value=instr->f_value;
                        LSQ[i]->t_tag=0;
                    }
                    if(!strcmp(LSQ[i]->opcode,"STORE"))
                    {
                            if(instr->IQ_slot==LSQ[i]->f_tag)
                        {
                            LSQ[i]->f_value=instr->f_value;
                            LSQ[i]->f_tag=0;
                        }
                    }
            }
        }
}

int  getvalue_of_register(char *regist)
{    char temp[10];
     int i=0,k=0;
    if(!strcmp(regist,"R0")){return ARF[0][1];}
    if(!strcmp(regist,"R1")){return ARF[1][1];}
    if(!strcmp(regist,"R2")){return ARF[2][1];}
    if(!strcmp(regist,"R3")){return ARF[3][1];}
    if(!strcmp(regist,"R4")){return ARF[4][1];}
    if(!strcmp(regist,"R5")){return ARF[5][1];}
    if(!strcmp(regist,"R6")){return ARF[6][1];}
    if(!strcmp(regist,"R7")){return ARF[7][1];}
    if(!strcmp(regist,"X")){return ARF[8][1];}
   if(regist[0]=='0' || regist[0]=='1' || regist[0]=='2' || regist[0]=='3' || regist[0]=='4' || regist[0]=='5' || regist[0]=='6' || regist[0]=='7' || regist[0]=='8' || regist[0]=='9' || regist[0]=='-')
            {

		    k = atoi (regist);
            return k;
            }
}


int decode1(INSTRUCTION *instr)
{   int success=0,phy_register=0;
    phy_register=get_free_physical_register();
     if(phy_register==16)
     {
            return 1;
     }
     int s;

     if(strcmp(instr->opcode,"STORE"))
     {
         s=instr->first[0]-48;
        MAP[s][1]=phy_register;
         itoa(phy_register,instr->first,10);
     }

     return 0;

}

int decode2(INSTRUCTION *instr)
{       int i=0;
        for(i=0;i<10;i++)
        {
            if(RNT[i][0]==instr->second[1]-48)
            {
                if(RNT[i][2]==0)
                {
                    instr->s_value=ARF[i][1];
                    instr->s_tag=0;

                }
                if(RNT[i][2]==1)
                {

                    if(ROB[RNT[i][1]]->f_tag==0)
                    {
                        instr->s_value=ROB[RNT[i][1]]->f_value;
                        instr->s_tag=0;

                    }
                    if(ROB[RNT[i][1]]->f_tag!=0)
                    {

                        instr->s_tag=ROB[RNT[i][1]]->f_tag;

                    }


                }
            }
            if(RNT[i][0]==instr->third[1]-48)
            {
                if(RNT[i][2]==0)
                {
                    instr->t_value=ARF[i][1];
                    instr->t_tag=0;

                }
                if(RNT[i][2]==1)
                {
                    if(ROB[RNT[i][1]]->f_tag==0)
                    {
                        instr->t_value=ROB[RNT[i][1]]->f_value;
                        instr->t_tag=0;

                    }
                    if(ROB[RNT[i][1]]->f_tag!=0)
                    {

                        instr->t_tag=ROB[RNT[i][1]]->f_tag;

                    }


                }
            }
            if(!strcmp(instr->opcode,"STORE"))
            {

                 if(RNT[i][0]==instr->first[0]-48)
                {
                if(RNT[i][2]==0)
                {
                    instr->f_value=ARF[i][1];
                    instr->f_tag=0;

                }
                if(RNT[i][2]==1)
                {
                    if(ROB[RNT[i][1]]->f_tag==0)
                    {
                        instr->f_value=ROB[RNT[i][1]]->f_value;
                        instr->f_tag=0;

                    }
                    if(ROB[RNT[i][1]]->f_tag!=0)
                    {

                        instr->f_tag=ROB[RNT[i][1]]->f_tag;

                    }


                }
            }


            }

        }
        if(strcmp(instr->opcode,"STORE") || strcmp(instr->opcode,"LOAD") || strcmp(instr->opcode,"MOVC"))
        {       if(condition_IQ())
                {
                    if(push(instr))
                        return 0;
                        else return 1;
                }


        }
        else
        {
           if(condition_LSQ())
                {
                    if(push(instr))
                        return 0;
                        else return 1;
                }
        }

        return 1;

}

int condition_IQ()
{     int rob=0,iq=0,i=0;
    if(head!=tail-1)
    {
        rob=1;
    }
    for(i=0;i<8;i++)
    {
         if(IQ[i]==NULL)
                iq=1;
    }
    if(rob && iq)
        return 1;
    return 0;

}

int condition_LSQ()
{   int rob=0,lsq=0,i=0;
    if(head!=tail-1)
    {
        rob=1;
    }
    for(i=0;i<2;i++)
    {
         if(LSQ[i]==NULL)
                lsq=1;
    }
    if(rob && lsq)
        return 1;
    return 0;
}

int available_IQ()
{    int i=0;
    for(i=1;i<9;i++)
    {
        if(IQ[i]==NULL)
            return i;
    }
    return i;
}
int available_LSQ()
{    int i=0;
    for(i=1;i<5;i++)
    {
        if(LSQ[i]==NULL)
            return i;
    }
    return i;
}


int push(INSTRUCTION *instr)
{
     if(strcmp(instr->opcode,"STORE") || strcmp(instr->opcode,"LOAD"))
     {
         instr->IQ_slot=available_IQ();
         IQ[available_IQ()]=instr;
         instr->f_tag=instr->IQ_slot;

         insert_into_ROB(instr);


     }
     else
     {
           instr->IQ_slot=available_LSQ()+8;
           LSQ[available_LSQ()]=instr;
           instr->f_tag=instr->IQ_slot;
           insert_into_ROB(instr);
     }
     return 0;

}

int perform_operation(char *operatr,int operand1,int operand2)
{
     if(!strcmp(operatr,"ADD")){ return operand1+operand2;}
     if(!strcmp(operatr,"SUB")){ return operand1-operand2;}
     if(!strcmp(operatr,"MUL")){ return operand1*operand2;}
     if(!strcmp(operatr,"AND")){ return operand1 & operand2;}
     if(!strcmp(operatr,"OR")){ return operand1 | operand2;}
     if(!strcmp(operatr,"EX-OR")){ return operand1 ^ operand2;}
}





//-----------------------------------------------------------------------

int execute(INSTRUCTION *E)
{
     if(!strcmp(E->opcode,"ADD") || !strcmp(E->opcode,"SUB") || !strcmp(E->opcode,"MUL") )
    {
             E->f_value=perform_operation(E->opcode,E->s_value,E->t_value);
             //printf("%d\t %d\t %d\n",E->s_value,E->t_value,E->f_value);

    }
    if(!strcmp(E->opcode,"AND") || !strcmp(E->opcode,"OR") || !strcmp(E->opcode,"EX-OR"))
    {
            E->f_value=perform_operation(E->opcode,E->s_value,E->t_value);
    }
    if(!strcmp(E->opcode,"MOVC"))
    {
            E->f_value=E->s_value;
    }

    /*
    if(!strcmp(E->opcode,"BAL"))
    {
           E->t_value=E->f_value+E->s_value;
           X=E->next->address;
    }
    if(!strcmp(E->opcode,"JUMP"))
    {
               E->t_value=E->f_value+E->s_value;


    }

             if(!strcmp(E->opcode,"BNZ"))
     {    if(E->prev->f_value!=0)
          {F=add_of_add(E->address+E->f_value);
          D=NULL;EX=NULL;MEM=NULL;WB=NULL;
          check_for_flow_dependency();

          return;
          }
     }
     if(!strcmp(E->opcode,"BZ"))
     {
         if(E->prev->f_value==0)
          {F=add_of_add(E->address+E->f_value);
              D=NULL;EX=NULL;MEM=NULL;WB=NULL;
              check_for_flow_dependency();
          return;
          }

     }




    */
    forward_to_all(E);
    return;

}

void perform_memory_operation(INSTRUCTION * ME)
{     int x=0;

    if(!strcmp(ME->opcode,"LOAD"))
    {
            x=memory[ME->s_value+ME->t_value];

            ME->f_value=x;
            ME->f_tag=0;
    }
    if(!strcmp(ME->opcode,"STORE"))
    {
            memory[getvalue_of_register(ME->second)+getvalue_of_register(ME->third)]=ME->f_value;
            ME->f_tag=0;

    }
    forward_to_all(ME);
    return;
}

int display_ROB()
{   printf("\n----------ROB-------------\n");
    int i=0;
    printf("ROB CONTENTS:");
    for(i=0;i<16;i++)
    {
        if(ROB[i]!=NULL)
        {
            printf("%d\t",ROB[i]->address);
        }
    }
    printf("\n");
}

int display_RNT()
{   printf("\n----------RNT-------------\n");
    int i=0;
    for(i=0;i<10;i++)
        printf("%d\t%d\t%d\n",RNT[i][0],RNT[i][1],RNT[i][2]);
}
int display_ARF()
{   printf("\n----------ARF-------------\n");
    int i=0;
    for(i=0;i<10;i++)
        printf("%d\t%d\n",ARF[i][0],ARF[i][1]);
}

int display_map()
{
     printf("\n----------MAP-------------\n");
     int i=0;
     for(i=0;i<10;i++)
        printf("%d\t%d\n",MAP[i][0],MAP[i][1]);

}
int display_memory()
{int i=0;
    for(i=0;i<10000;i++)
    {
        if(memory[i]!=0)
            printf("\nmemory[%d]:%d\n",i,memory[i]);
    }
}


int trial()
{
    while(head!=tail)
    {
        commit_and_retire();
    }
}

int main()
{    int menu=0,i=0;

     perform_file_operation();
     initialize_all();
     simulate();


return 0;
}
