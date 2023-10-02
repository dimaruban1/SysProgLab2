#ifndef SYSPROGLAB2_AUTOMATA_H
#define SYSPROGLAB2_AUTOMATA_H

struct Automata{
    int pA;
    int pS;
    int pF;
    //int *A
    int s0;
    int *F;
};
extern struct Automata A;
struct StateTransition{
    int stateFrom;
    char symbol;
    int stateTo;
};
bool constructAutomataFromFile(const char *path);
int *processChar(int state, char c, size_t *resultSize);
bool leadToFinalState(const int *states, size_t size);
void freeAll();
#endif //SYSPROGLAB2_AUTOMATA_H
