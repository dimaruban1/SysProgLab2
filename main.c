#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "automata.h"

/// A - alphabet
/// S - set of states
/// F - set of final states
/// s0 - starting state
/// pA - power of set A etc.

// removes last character if it is \n
void processUserInput(char *input){
    size_t len = strlen(input);

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}

//by default when called states should be set to null and depth to 0
bool acceptsW0(char *w0, int *states, int depth, size_t size){
    if (depth == 0){
        states = malloc(sizeof (int));
        states[0] = A.s0;
        return(acceptsW0(w0, states, depth, 1));
    }
    if (depth == strlen(w0)){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < A.pF; j++){
                if (A.F[j] == states[i]){
                    return true;
                }
            }
        }
        return false;
    }
    for (int i = 0; i < size; i++){
        size_t resultSize = 0;
        processChar(states[i], w0[depth], &resultSize);
    }
    return false;
}
bool processWordRecursion(const int *states, char *w, int depth, size_t size){
    if (depth == strlen(w) && leadToFinalState(states, size)){
        return true;
    }
    for (int i = 1; i < size; i++){
        size_t newSize = 0;
        int *nextStates = processChar(states[i], w[depth], &newSize);
        if (nextStates == NULL) continue;
        else {
            if(processWordRecursion(nextStates, w, depth+1, newSize)){
                free(nextStates);
                return true;
            }
        }
    }
    return false;
}

int main() {
    char *PATH = "/home/serg/CLionjProjects/SysProgLab2/automata.txt";
    char buffer[100];
    while (!constructAutomataFromFile(PATH) && !constructAutomataFromFile(buffer)){
        printf("error reading text file at path: %s\n", PATH);
        printf("do you want to enter custom path? y/n");
        char answer = fgetc(stdin);
        while (getchar() != '\n');
        if (answer == 'n'){
            return 1;
        } else if (answer == 'y'){
            fgets(buffer, sizeof (buffer), stdin);
            processUserInput(buffer);
        } else{
            continue;
        }
    }
    char w[100];
    int *states = calloc(A.pS, sizeof(int));
    for (int i = 0; i < A.pS; i++){
        states[i] = i;
    }
    printf("enter w0\n");
    fgets(w, sizeof(w), stdin);
    processUserInput(w);
    if (processWordRecursion(states,w,0,A.pS)){
        printf("word found\n");
    } else {
        printf("word not found\n");
    }
    free(states);
    freeAll();
    return 0;
}