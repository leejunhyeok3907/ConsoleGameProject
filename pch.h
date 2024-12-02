#pragma once

#include <Windows.h>
#include <iostream>

#include <vector>
#include <queue>

using namespace std;

#include "Enums.h"
#include "CustomStruct.h"
#include "Functions.h"

#define GetSet(Type, VarName, FuncName)\
const Type& Get##FuncName() const{return VarName;}\
void Set##FuncName(const Type& _##VarName) {VarName=_##VarName;}

#define SINGLE(type) \
public:\
static type* GetInst() \
{ \
	static type mgr; \
	return &mgr; \
} \
private:\
type();\
~type();