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

//frees pointers after usage
/*
 * pseudocode:
 * if depth == strlen(w) and newStates are not null(w2 is not empty):
 *       return true
 * foreach state in states:
 *       get all connected states via symbol w[depth] as newStates
 *       if NULL then proceed to next state
 *       else:
 *
 *              repeat for newStates
 * if we run out of states, return false
 * */
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
    const char *PATH = "/home/serg/CLionProjects/SysProgLab2/automata.txt";
    constructAutomataFromFile(PATH);
    char w[100] = "a";
    int *states = calloc(A.pS, sizeof(int));
    for (int i = 0; i < A.pS; i++){
        states[i] = i;
    }
//    fgets(w, sizeof(w), stdin);
    if (processWordRecursion(states,w,0,A.pS)){
        printf("word found\n");
    } else {
        printf("word not found\n");
    }
    free(states);
    freeAll();
    return 0;
}
