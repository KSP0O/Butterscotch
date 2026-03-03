#pragma once

#include "vm.h"

typedef RValue (*BuiltinFunc)(VMContext* ctx, RValue* args, int32_t argCount);

void VMBuiltins_registerAll(void);
BuiltinFunc VMBuiltins_find(const char* name);
