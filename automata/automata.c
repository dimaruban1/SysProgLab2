#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "automata.h"

int numberOfTransitions; // number of transitions
struct StateTransition *transitions;
struct Automata A;

bool constructAutomataFromFile(const char *path){
    FILE *fp = fopen(path,"r");
    if (fp == NULL){
        return false;
    }

    fscanf(fp, "%i", &A.pA);
    fscanf(fp, "%i", &A.pS);
    fgetc(fp);
    fscanf(fp, "%i", &A.s0);
    fscanf(fp, "%i", &A.pF);
    A.F = malloc(sizeof(int) * A.pF);
    for (int i = 0; i < A.pF; i++){
        if (fscanf(fp, "%i", &A.F[i]) != 1) {
            free(A.F);
            fclose(fp);
            return false;
        }
    }
    struct StateTransition transition;
    while(fscanf(fp, "%i", &transition.stateFrom)){
        numberOfTransitions++;
        getc(fp); //space character
        transition.symbol = (char) getc(fp);
        fscanf(fp, "%i", &transition.stateTo);
        if (transition.symbol == EOF){
            break;
        }
        transitions = realloc(transitions, numberOfTransitions * sizeof(transition));
        transitions[numberOfTransitions-1] = transition;
    }
    fclose(fp);
    return true;
}

// returns array of next states, NULL if no states ahead\n
//result size should be passed as 0
int *processChar(int state, char c, size_t *resultSize){
    int *res = NULL;
    int count = 0;
    for (int i = 0; i < numberOfTransitions; i++){
        struct StateTransition t = transitions[i];
        if (t.stateFrom == state && t.symbol == c){
            count++;
            res = realloc(res, count);
            res[count-1] = t.stateTo;
        }
    }
    *resultSize = count;
    return res;
}

int addMoreReachableStates(bool *statesSet, int pS){
    int newStatesCount = 0;
    for (int i = 0; i < pS; i++){
        if (!statesSet[i]) continue;

        for (int j = 0; j < numberOfTransitions; j++){
            int newState = transitions[j].stateTo;
            if (transitions[j].stateFrom == i && !statesSet[newState]){
                statesSet[newState] = true;
                newStatesCount++;
            }
        }
    }
    return newStatesCount;
}

// checks if given states lead to any final state
bool leadToFinalState(const int *states, size_t size){
    bool *reachableStatesSet = calloc(A.pS, sizeof(bool));
    for (int i = 0; i < size; i++){
        reachableStatesSet[states[i]] = true;
    }

    while (addMoreReachableStates(reachableStatesSet, A.pS) > 0) {}
    //starting states don`t count
    for (int i = 0; i < size; i++){
        reachableStatesSet[states[i]] = true;
    }
    for (int i = 0; i < A.pF; i++){
        if(reachableStatesSet[A.F[i]]){
            free(reachableStatesSet);
            return true;
        }
    }
    free(reachableStatesSet);
    return false;
}

void freeAll(){
    free(transitions);
    free(A.F);
}