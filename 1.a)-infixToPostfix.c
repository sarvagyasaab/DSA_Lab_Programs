#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
    int size;
    int top;
    char* arr;
};

struct stack* createStack(int size){
    struct stack *st = (struct stack *)malloc(sizeof(struct stack));
    st -> size = size;
    st -> top = -1;
    st -> arr = (char *)malloc(sizeof(char) * st -> size);
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

void push(struct stack *st, char item){
    if(!isFull(st)){
        st -> top ++;
        st -> arr[st -> top] = item;
        // printf("Pushed the Element %c at %dth Index of Stack.\n", item, st -> top);
    }
    else{
        printf("Stack Overflow ! Cannot Push.\n");
    }
}

char pop(struct stack *st){
    if(!isEmpty(st)){
        char val = st -> arr[st -> top];
        st -> top -= 1;
        // printf("Popped the element %c from the Top.\n", val);
        return val;
    }
    else{
        printf("Cannot POP ! Stack Underflow.\n");
        return -1;
    }
}

char peek(struct stack *st){
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
            printf("%c, ", st -> arr[i]);
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

int preceedence(char ch){
    if(ch == '$'){
        return 5;
    }
    else if(ch == '*' || ch == '/'){
        return 3;
    }
    else if(ch == '+'|| ch == '-'){
        return 1;
    }
    else{
        return 0;
    }
}

char* infixToPostfix(char* infix){
    struct stack* st = createStack(strlen(infix) + 1);
    char* postfix = (char*)malloc(sizeof(char) * (strlen(infix) + 1));
    int i = 0;
    int j = 0;

    while(infix[i] != '\0'){
        //check if scanned symbol is operand
        if(!isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')'){
            postfix[j] = infix[i];
            i++;
            j++;
        }
        //check if the scanned symbol is left parenthesis
        else if(!isOperator(infix[i]) && infix[i] == '('){
            //push the left parenthesis to the stack
            push(st, infix[i]);
            i++;
        }
        //check if the scanned symbol is right parenthesis.
        else if(!isOperator(infix[i]) && infix[i] == ')'){
            //Pop the contents of the stack till you get a vorresponding left parenthesis.
            while(peek(st) != '('){
                postfix[j] = pop(st);
                j++;
            }
            if(peek(st) == '('){
                pop(st);
            }
            i++;
        }
        //check if the scanned symbol is an operator
        else if(isOperator(infix[i])){
            if(peek(st) == '(' || isEmpty(st)){
                push(st, infix[i]);
                i++;
            }
            else{
                while(preceedence(infix[i]) <= preceedence(peek(st))){
                    postfix[j] = pop(st);
                    j++;
                }
                push(st, infix[i]);
                i++;
            }
        }
    }
    //pop remaining contents of the stack
    while(!isEmpty(st)){
        postfix[j] = pop(st);
        j++;
    }
    postfix[j] = '\0';

    deleteStack(st);
    return postfix;
}

// int main() {
//     // Example test cases
//     char infix1[] = "a+b*c";
//     char infix2[] = "(a+b)*c";
//     char infix3[] = "(((a+(b-c)*d)$e)+f)";

//     char* postfix1 = infixToPostfix(infix1);
//     char* postfix2 = infixToPostfix(infix2);
//     char* postfix3 = infixToPostfix(infix3);

//     printf("Infix: %s, Postfix: %s\n", infix1, postfix1);
//     printf("Infix: %s, Postfix: %s\n", infix2, postfix2);
//     printf("Infix: %s, Postfix: %s\n", infix3, postfix3);

//     free(postfix1);
//     free(postfix2);
//     free(postfix3);

//     return 0;
// }

int main() {
    // Get infix expression from the user
    printf("Enter the infix expression: ");
    char infix[100];
    fgets(infix, sizeof(infix), stdin);

    // Remove the newline character from the input
    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }

    // Convert infix expression to postfix
    char* postfix = infixToPostfix(infix);

    // Display the result
    printf("Infix: %s, Postfix: %s\n", infix, postfix);

    // Free allocated memory
    free(postfix);
    return 0;
}