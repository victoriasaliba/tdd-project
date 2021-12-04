#include "types.h"
#include "user.h"
#include "date.h"

int stdout = 1;
int stderr = 2;
/*
int
main(int argc, char *argv[])
{
  struct rtcdate r;

  if (date(&r)) {
    printf(stderr, "Erro na chamada de sistema\n");
    exit();
  }
  // Imprima a data aqui
  //printf(1," %d:%d:%d",r.hour,r.minute,r.second);
  int tempoTotal = uptime()/60;
  int tempoInicial = 0;
  char *command = argv[1];
  char **arguments = argv + 1;
  printf(0,"%c",command);
  printf(0,"%c",arguments);

  printf(1,"%d",tempoTotal);
  printf(1,"%d",tempoInicial);
  exit();
}
*/

//Inicia obtendo o acumulado até o disparo do time;
        //real_a = realtime();
       // user_a = usertime();
        //sys_a = systemtime();
//Executa o programa do usuário com seus parâmetros
       // exec(prog, params);
       // wait(prog);

//Obtém o acumulado ao término da execução do programa
        //real_b = realtime();
        //user_b = usertime();
        //sys_b = systemtime();

//Imprime os dados demandados
         //imprime(real_b - real_a, user_b - user_a,sys_b - sys_a);



     
void printTime(char *cname, int real_end, int sys_end, int user_end){
//Imprime o resultado calculando o tempo baseado nos ticks do processador;
printf(1, "\n\nComando %s:\nReal time: %d.%d%d.\nSystem time: %d.%d%d.\nUser time: %d.%d%d.\n\n",
              cname,
              real_end / 100,
              real_end % 100 / 10,
              real_end % 100 % 10,
              sys_end / 100,
              sys_end % 100 / 10,
              sys_end % 100 % 10,
              user_end / 100,
              user_end % 100 / 10,
              user_end % 100 % 10);  
}


int
call(char *argv[])
{ 
  int pid = fork();
  
  //Inicia a contagem do real_time
  int real_start = uptime(); 
  
  //Chama essa função pra poder zerar o valor acumulado no contador de tempo das chamadas de sistema.
  //systime();
  int sys_a = time();
  time();
  
  if(pid == 0)
  {
    //Executa o comando recebido como parâmetro pela função time.    
    if(exec(argv[0], &argv[0]) < 0)
    {
      printf(2, "Erro\n");
    }    
  } else if(pid > 0)
  {
    wait();
  }
  else
  {
    printf(2, "Erro");
    exit();
  }
  
  //Número de ticks acumulados das chamadas de sistema.
  int sys_end = time();
  //int sys_end = systime();
  //Número de ticks entre o começo real da chamada e o fim real da chamada.
  int real_end = uptime() - real_start;
  //Considerei o user time como o real_time - sys_time.
  //int user_end = real_end - sys_end;
  int user_end = sys_end - real_end;
  int sys_final;
  sys_final = sys_end - sys_a;
  printf(1,"%d\n",sys_end);
  printf(1,"%d\n",real_end);
  printf(1,"%d\n",user_end);
  printf(1,"%d\n",sys_final);
  printTime(argv[0],  sys_end,real_end, user_end);
                                
  exit();
} 

int
main(int argc, char *argv[])
{
  if (argv[1] != 0)
    call(&argv[1]);
  else
    printf(1, "ran in 0.00 seconds.\n");
     
  exit();
}
