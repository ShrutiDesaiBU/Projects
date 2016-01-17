#ifndef HEADER_FUNCTIONS2_H_INCLUDED
#define HEADER_FUNCTIONS2_H_INCLUDED

int check_opcode_token(char *opcode)
{    int found=0,i=0;
     for(i=0;i<=13;i++)
     {

          found=strcmp(opcode_tokens[i],opcode);
          if(!found)
          return 1;
     }
return 0;
}

int check_register_token(char *opcode)
{
     int found=0,i=0;
     for(i=0;i<=8;i++)
     {


          if(!strcmp(register_tokens[i],opcode) || opcode[0]=='0' || opcode[0]=='1' || opcode[0]=='2' || opcode[0]=='3' || opcode[0]=='4' || opcode[0]=='5' || opcode[0]=='6' || opcode[0]=='7' || opcode[0]=='8' || opcode[0]=='9' || opcode[0]=='-')
          return 1;
     }
return 0;

}

INSTRUCTION * new_instruction()
{
    INSTRUCTION  *new_instr;
    new_instr=(INSTRUCTION *)malloc(sizeof(INSTRUCTION));
    return new_instr;
}
INSTRUCTION * check_and_create(char *word)
{     INSTRUCTION *temp;
      static int address=19999;
   if(check_opcode_token(word))
   {  temp=new_instruction();
      if(start==NULL)
      {
          start=temp;
          PC=start;
          PC->prev=start;

      }
      else
      {
          PC->next=temp;
          temp->prev=PC;
      }

      address=address+1;
      temp->IQ_slot=0;
      temp->address=address;
      temp->f_tag=0;
      temp->f_value=0;
      temp->s_tag=0;
      temp->s_value=0;
      temp->t_tag=0;
      temp->t_value=0;
      temp->next=NULL;
      strcpy(temp->first,"    ");
      strcpy(temp->second,"    ");
      strcpy(temp->third,"    ");
      strcpy(temp->opcode,word);
      //printf("%d\t %d\n",PC,temp);
      PC=temp;
   }

   return temp;
}

void check_and_add(INSTRUCTION *temp,char *word)
{
      static int x=1;
      if(x==1)
      {     //strcpy(temp->first,word);
          temp->first[0]=word[1];
          temp->first[1]='\0';
            x=x+1;
            if(!strcmp(temp->opcode,"BZ") || !strcmp(temp->opcode,"BNZ"))
                x=1;

            return 1;
      }
      if(x==2)
      {     strcpy(temp->second,word);

            x=x+1;
            if(!strcmp(temp->opcode,"MOVC") || !strcmp(temp->opcode,"MOV") ||  !strcmp(temp->opcode,"JUMP") || !strcmp(temp->opcode,"BAL"))
                x=1;

            return 1;
      }
      if(x==3)
      {
            strcpy(temp->third,word);

            x=1;
            return 1;
      }

}

void perform_file_operation()
{
      int traversal=0,loop=0,c;
    struct loop *loop_addr=(struct loop *)malloc (sizeof(struct loop));
    char *x=(char *)malloc(10*sizeof(char));
    for(loop=0;loop<10;loop++)
    x[loop]='\0';
    INSTRUCTION *temp;
    FILE *fp=fopen("instruction.txt","r");


    while((c=fgetc(fp))!=EOF)
    {
        if(c=='\n' || c==',' || c==' ')
        {
             if(check_opcode_token(x))
             {temp=check_and_create(x);
             }
             if(check_register_token(x))
             check_and_add(temp,x);
             if(!strcmp(loop_addr->name,x))
             {
                   sprintf(temp->first,"%d",loop_addr->address);

             }
            traversal=0;
            for(loop=0;loop<10;loop++)
            x[loop]='\0';
            continue;
        }
        if(c==':')
        {
            strcpy(loop_addr->name,x);
            if(PC==NULL)
            {    loop_addr->address=20000;
            }
            else
            {    loop_addr->address=PC->address+1;
            }
            strcpy(x,"hj");
            continue;
        }

        else
        {       x[traversal]=c;
                traversal++;
        }

    }




}

#endif // HEADER_FUNCTIONS2_H_INCLUDED
