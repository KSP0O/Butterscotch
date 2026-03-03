#include "runner.h"

Runner* Runner_create(DataWin* dataWin, VMContext* vm) {
    Runner* runner = malloc(sizeof(Runner));
    runner->dataWin = dataWin;
    runner->vmContext = vm;
    // GameMaker always starts the game in the first room
    runner->currentRoom = &dataWin->room.rooms[0];

    return runner;
}

void Runner_free(Runner* runner) {
    free(runner);
}