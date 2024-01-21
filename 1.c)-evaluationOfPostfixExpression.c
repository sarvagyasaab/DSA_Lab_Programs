#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct stack{
    int size;
    int top;
    int* arr;
};

struct stack* createStack(int size){
    struct stack *st = (struct stack *)malloc(sizeof(struct stack));
    st -> size = size;
    st -> top = -1;
    st -> arr = (int *)malloc(sizeof(int) * st -> size);
    printf("Successfully Initialized Stack of Size %d.\n", st -> size);
    return st;
}

void deleteStack(struct stack* st){
    if(st != NULL && st -> arr != NULL){
        free(st -> arr);
        free(st);
        printf("Stack Memory cleared Successfully.\n");
    }
    else{
        printf("Invalid Stack Pointer.\n");
    }
}

int isFull(struct stack *st){
    if(st -> top >= st -> size - 1){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(struct stack *st){
    if(st -> top == -1){
        return 1;
    }
    else{
        return 0;
    }
}

void push(struct stack *st, int item){
    if(!isFull(st)){
        st -> top ++;
        st -> arr[st -> top] = item;
    }
    else{
        printf("Stack Overflow ! Cannot Push.\n");
    }
}

int pop(struct stack *st){
    if(!isEmpty(st)){
        int val = st -> arr[st -> top];
        st -> top -= 1;
        return val;
    }
    else{
        printf("Cannot POP ! Stack Underflow.\n");
        return -1;
    }
}

int peek(struct stack *st){
    if(!isEmpty(st)){
        return st -> arr[st -> top];
    }
    else{
        return -1;
    }
}

void printStack(struct stack *st){
    if(isEmpty(st)){
        printf("Stack is Empty.\n");
    }
    else{
        for(int i = 0; i <= st -> top; i++){
            printf("%d, ", st -> arr[i]);
        }
        printf("\n");
    }
}

int isOperator(char ch){
    if(ch == '+'|| ch == '-'|| ch == '*' || ch == '/' || ch == '$'){
        return 1;
    }
    else{
        return 0;
    }
}

int evaluatePostfix(char* postfix){
    struct stack* st = createStack(strlen(postfix) + 1);
    int i = 0;

    while(postfix[i] != '\0'){
        int operand_1 = 0;
        int operand_2 = 0;
        //scanned symbol is an operand
        if(!isOperator(postfix[i])){
            push(st, postfix[i] - '0');
        }
        //scanned symbol is an operator
        else{
            operand_2 = pop(st);
            operand_1 = pop(st);

            if(postfix[i] == '+'){
                push(st, operand_2 + operand_1);
            }
            else if(postfix[i] == '-'){
                push(st, operand_1 - operand_2);
            }
            else if(postfix[i] == '*'){
                push(st, operand_1 * operand_2);
            }
            else if(postfix[i] == '/'){
                push(st, operand_1 / operand_2);
            }
            else if(postfix[i] == '$'){
                push(st, pow(operand_1, operand_2));
            }
        }
        i++;
    }

    // The final result will be at the top of the stack
    int result = pop(st);

    // Free the stack memory
    deleteStack(st);

    return result;
}

int main() {
    // Get infix expression from the user
    printf("Enter the postfix expression: ");
    char postfix[100];
    fgets(postfix, sizeof(postfix), stdin);

    // Remove the newline character from the input
    size_t len = strlen(postfix);
    if (len > 0 && postfix[len - 1] == '\n') {
        postfix[len - 1] = '\0';
    }

    // Evaluate postfix expression
    int ans = evaluatePostfix(postfix);

    // Display the result
    printf("Postfix: %s, Answer: %d\n", postfix, ans);

    return 0;
}
