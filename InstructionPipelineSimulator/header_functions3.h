#ifndef HEADER_FUNCTIONS3_H_INCLUDED
#define HEADER_FUNCTIONS3_H_INCLUDED


int display()
{    PC=start;
     while(1)
     {
       printf("Address IQ_slot opcode first_op f_value f_tag second_op sec_val sec_tag thd_op thd_val thd_tag\n");
       printf("%d \t %d \t %s\t %s\t %d\t %d\t %s\t %d\t %d\t %s\t %d\t %d\n",PC->address,PC->IQ_slot,PC->opcode,PC->first,PC->f_value, PC->f_tag,PC->second,PC->s_value, PC->s_tag,PC->third,PC->t_value, PC->t_tag);
       PC=PC->next;
       if(PC==NULL)
      {
          PC=start;
          return;
      }
     }
}























#endif // HEADER_FUNCTIONS3_H_INCLUDED
