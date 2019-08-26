#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define number_size 100

struct target
{
	int number;
	struct target* next;	
};

struct stack
{
	struct target* top;
	int num;
	struct target* (*pop)(struct stack* temp);
	void (*push)(struct stack* temp, struct target* target_temp);
	void (*clear_stack)(struct stack* temp);
};

void clear_stack(struct stack* temp)
{
	struct target* target_temp = NULL;
	for(int i = 0; i < temp->num; i++){
		target_temp = temp->pop(temp);
		free(target_temp);
	}
}

struct target* pop(struct stack* temp)
{
	if(temp->num == 0)
		return NULL;
	struct target* target_temp = NULL;
	target_temp = temp->top;
	temp->top = temp->top->next;
	temp->num--;
	return target_temp;
}

void push(struct stack* temp, struct target* target_temp)
{
	target_temp->next = temp->top;
	temp->top = target_temp;
	temp->num++;
}

int main()
{
	struct stack* main_stack;
	main_stack = (struct stack*)calloc(1, sizeof(struct stack));

	main_stack->top = NULL;
	main_stack->num = 0;
	main_stack->pop = pop;
	main_stack->push = push;
	main_stack->clear_stack = clear_stack;

	srand((unsigned int)time(0));
	printf("Stack start\n");
	
	for(int i = 0; i < number_size; i++){
		struct target* node = NULL;
		node = (struct target*)calloc(1, sizeof(struct target));
		node->number = rand() % 1000;
		printf("%d ", node->number);
		main_stack->push(main_stack, node);
	}
	printf("\n");

	printf("Pops..\n");

	for(int i = 0; i < number_size; i++){
		struct target* node = NULL;
		node= main_stack->pop(main_stack);
		printf("%d ", node->number);
		free(node);
	}
	printf("\n");
	
	main_stack->clear_stack(main_stack);
	return 0;
}
