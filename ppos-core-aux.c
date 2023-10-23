#include "ppos-core-globals.h"
#include "ppos.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//#define DEBUG 1

// ****************************************************************************
// Coloque aqui as suas modificações, p.ex. includes, defines variáveis,
// estruturas e funções
// estrutura que define um tratador de sinal (deve ser global ou static)
// int um_tick = 0;
struct sigaction action;

// estrutura de inicialização to timer
struct itimerval timer;

// tratador do sinal

void task_setflag(task_t *task) { task->flag = 1; }

int task_getflag(task_t *task) { return task->flag; }

void task_setquantum(task_t *task, int q) {
  if (task == NULL)
    taskExec->quantum = q;
  else
    task->quantum = q;
}

int task_getquantum(task_t *task) {
  if (task == NULL)
    return taskExec->quantum;
  else
    return task->quantum;
}

void task_set_eet(task_t *task, int et) {
  task->eet = et;
  // task->quant_tick = et * um_tick;
  task->running_time = 0;
  task->ret = et;
}

int task_get_eet(task_t *task) {
  if (task == NULL)
    return taskExec->eet;
  else
    return task->eet;
}

int task_get_ret(task_t *task) {
  if (task == NULL)
    return taskExec->ret;
  else
    return task->ret;
}

void task_setprio(task_t *task, int prio) {
  if (task == NULL)
    taskExec->prioridade = prio;
  else
    task->prioridade = prio;
}

int task_getprio(task_t *task) {
  if (task == NULL)
    return taskExec->prioridade;
  else
    return task->prioridade;
}

void tratador() {
  int q;
  int flag = task_getflag(taskExec);
  systemTime++;
  // printf("oi7777\n");
  if (flag == 1) {
    task_setquantum(taskExec, task_getquantum(NULL) - 1);
    // printf("oi3333\n");
    taskExec->running_time++;
    taskExec->ret--;

    if (task_getquantum(NULL) == 0) {
      // taskExec->quant_tick = taskExec->quant_tick - 20 * um_tick;
      printf("oi1000\n");

      task_yield();
    }
  }
}

// ****************************************************************************

void before_ppos_init() {

  /*int aux_time;
  // put your customization here
  // waiting for the first microsecond
  while (systime() <= 0)
    ;
  // estimate how many iterations is a microsecond
  aux_time = systime() + 1;
  while (systime() < aux_time)
    um_tick++;
  printf("oi");
  // adjusting value
  // one_tick = (one_tick*90)/100;
  printf("Loop iterations to microseconds = %d\n", um_tick);*/
#ifdef DEBUG
  printf("\ninit - BEFORE");
#endif
}

void after_ppos_init() {
  // put your customization here
  action.sa_handler = tratador;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  if (sigaction(SIGALRM, &action, 0) < 0) {
    perror("Erro em sigaction: ");
    exit(1);
  }
  // ajusta valores do temporizador
  timer.it_value.tv_usec = 1000; // primeiro disparo, em micro-segundos
  // timer.it_value.tv_sec = 0;        // primeiro disparo, em segundos
  timer.it_interval.tv_usec = 1000; // disparos subsequentes, em micro-segundos
  // timer.it_interval.tv_sec = 0;     // disparos subsequentes, em segundos

  // arma o temporizador ITIMER_REAL (vide man setitimer)
  if (setitimer(ITIMER_REAL, &timer, 0) < 0) {
    perror("Erro em setitimer: ");
    exit(1);
  }
#ifdef DEBUG
  printf("\ninit - AFTER");
#endif
}

void before_task_create(task_t *task) {
  // put your customization here

#ifdef DEBUG
  printf("\ntask_create - BEFORE - [%d]", task->id);
#endif
}

void after_task_create(task_t *task) {
  // put your customization here
  task_setflag(task);
#ifdef DEBUG
  printf("\ntask_create - AFTER - [%d]", task->id);
#endif
}

void before_task_exit() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_exit - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_exit() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_exit - AFTER- [%d]", taskExec->id);
#endif
}

void before_task_switch(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_switch - BEFORE - [%d -> %d]", taskExec->id, task->id);
#endif
}

void after_task_switch(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_switch - AFTER - [%d -> %d]", taskExec->id, task->id);
#endif
}

void before_task_yield() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_yield - BEFORE - [%d]", taskExec->id);
#endif
}
void after_task_yield() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_yield - AFTER - [%d]", taskExec->id);
#endif
}

void before_task_suspend(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_suspend - BEFORE - [%d]", task->id);
#endif
}

void after_task_suspend(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_suspend - AFTER - [%d]", task->id);
#endif
}

void before_task_resume(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_resume - BEFORE - [%d]", task->id);
#endif
}

void after_task_resume(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_resume - AFTER - [%d]", task->id);
#endif
}

void before_task_sleep() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_sleep - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_sleep() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_sleep - AFTER - [%d]", taskExec->id);
#endif
}

int before_task_join(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_join - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_task_join(task_t *task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_join - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_sem_create(semaphore_t *s, int value) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_create - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_sem_create(semaphore_t *s, int value) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_create - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_sem_down(semaphore_t *s) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_down - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_sem_down(semaphore_t *s) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_down - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_sem_up(semaphore_t *s) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_up - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_sem_up(semaphore_t *s) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_up - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_sem_destroy(semaphore_t *s) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_destroy - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_sem_destroy(semaphore_t *s) {
  // put your customization here
#ifdef DEBUG
  printf("\nsem_destroy - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mutex_create(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_create - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mutex_create(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_create - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mutex_lock(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_lock - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mutex_lock(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_lock - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mutex_unlock(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_unlock - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mutex_unlock(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_unlock - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mutex_destroy(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_destroy - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mutex_destroy(mutex_t *m) {
  // put your customization here
#ifdef DEBUG
  printf("\nmutex_destroy - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_barrier_create(barrier_t *b, int N) {
  // put your customization here
#ifdef DEBUG
  printf("\nbarrier_create - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_barrier_create(barrier_t *b, int N) {
  // put your customization here
#ifdef DEBUG
  printf("\nbarrier_create - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_barrier_join(barrier_t *b) {
  // put your customization here
#ifdef DEBUG
  printf("\nbarrier_join - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_barrier_join(barrier_t *b) {
  // put your customization here
#ifdef DEBUG
  printf("\nbarrier_join - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_barrier_destroy(barrier_t *b) {
  // put your customization here
#ifdef DEBUG
  printf("\nbarrier_destroy - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_barrier_destroy(barrier_t *b) {
  // put your customization here
#ifdef DEBUG
  printf("\nbarrier_destroy - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mqueue_create(mqueue_t *queue, int max, int size) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_create - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mqueue_create(mqueue_t *queue, int max, int size) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_create - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mqueue_send(mqueue_t *queue, void *msg) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_send - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mqueue_send(mqueue_t *queue, void *msg) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_send - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mqueue_recv(mqueue_t *queue, void *msg) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_recv - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mqueue_recv(mqueue_t *queue, void *msg) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_recv - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mqueue_destroy(mqueue_t *queue) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_destroy - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mqueue_destroy(mqueue_t *queue) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_destroy - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

int before_mqueue_msgs(mqueue_t *queue) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_msgs - BEFORE - [%d]", taskExec->id);
#endif
  return 0;
}

int after_mqueue_msgs(mqueue_t *queue) {
  // put your customization here
#ifdef DEBUG
  printf("\nmqueue_msgs - AFTER - [%d]", taskExec->id);
#endif
  return 0;
}

task_t *scheduler() {
  // FCFS scheduler
  /*if (readyQueue != NULL) {
    return readyQueue;
  }
  return NULL;*/
  task_t *aux, *aux2;
  int idInicioFila = readyQueue->id, idIgnore = -1;

  aux = readyQueue->next;
  aux2 = readyQueue;
  if (countTasks > 1) {
    idIgnore = 0;
  }

  printf("\ntarefas = %ld\n%d - sheduler", countTasks, aux->id);
  while (aux->id != idInicioFila) {
    if (aux->ret < aux2->ret && aux->ret != idIgnore) {
      aux2 = aux;
      printf("ret = %d e id = %d", aux2->ret, aux2->id);
    }
    aux = aux->next;
  }
  aux2->quantum = 20;

  return aux2;
}