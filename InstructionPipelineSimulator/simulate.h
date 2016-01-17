#ifndef SIMULATE_H_INCLUDED
#define SIMULATE_H_INCLUDED
#define EXIT 10
int f1()
{
    printf("f1");
}
int f2()
{
    printf("f2");
}
int d1()
{
    printf("d1");
}
int d2()
{
    printf("d2");
}
int intfu()
{
    printf("intfu");
}


int you_do_the_imp_work(INSTRUCTION *F1,INSTRUCTION *F2,INSTRUCTION *D1,INSTRUCTION *D2,INSTRUCTION *INTFU)
{
    if(F1!=NULL)
    {

    }
    if(F2!=NULL)
    {

    }
    if(D1!=NULL)
    {
        decode1(D1);
      //  display_map();
    }
    if(D2!=NULL)
    {
       decode2(D2);
    }
    if(INTFU!=NULL)
    {    if(!strcmp(INTFU->opcode,"LOAD"))
         perform_memory_operation(INTFU);
         else if(!strcmp(INTFU->opcode,"STORE"))
         perform_memory_operation(INTFU);
         else
         {
             execute(INTFU);

         }

    }
      display_ROB();
      display_RNT();
      display_ARF();
    // printf("%d\n",head);
      display_memory();

     commit_and_retire();

}




simulate()
{
    int count=5,i=0,j=0,k=0,l=0,z=0,flag=0,cycle=0,cond=0,set1=0,set2=0,set3=0,set4=0,set5=0;
      F1=NULL;F2=NULL;D1=NULL;D2=NULL;INTFU=NULL;



    while(INTFU!=NULL || set4==0)
    {
      if(F1==NULL && set1==0)
       {
           F1=start;
       }
      else if(F1!=NULL)

      {
          F2=F1;

          //decode(F2);
          F1=F1->next;

      }
      else{}

      if(F2!=NULL && F2!=start)
       {
            D1=F2->prev;

           // execute(D1);

       }
       if(D1!=NULL && D1!=start)
       {
          D2=D1->prev;

        //  perform_memory_operation(D2);
         // if(!strcmp(D1->opcode,"LOAD"))
         // execute(D1);
       }


       if(D2!=NULL && D2!=start)
       {
          INTFU=D2->prev;

        //  writeback(INTFU);

       }
       if(F1==NULL)
        {   set1=1;
        }

       if(F1==NULL && F2==NULL)
        {
             set2=1;
        }
        if(F1==NULL && F2==NULL && D1==NULL )
         {
              set3=1;
         }
       if(F1==NULL && F2==NULL && D1==NULL && D2==NULL)
       {
           set4=1;
       }
       if(F1==NULL && F2==NULL && D1==NULL && D2==NULL && INTFU==NULL)
       {
            set5=1;
       }

    you_do_the_imp_work(F1,F2,D1,D2,INTFU);
  //  printf("%8d %8d %8d %8d %8d\n",F1,F2,D1,D2,INTFU);
        if(set1 && count==5)
        {  D1=F2; F2=NULL;
           count--;
        }
        if(set2 && count==4)
        {  D2=D1; D1=NULL;
           count--;
        }
        if(set3 && count==3)
        {  INTFU=D2; D2=NULL;
           count--;
        }
        if(set4 && count==2)
        {
            INTFU=NULL;
            count--;

        }

    }



}







#endif // SIMULATE_H_INCLUDED
