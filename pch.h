#pragma once

#pragma region Console
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma endregion

#include <iostream>
#include <stdio.h>

#include <vector>
#include <queue>

using namespace std;

#include "Enums.h"
#include "CustomStruct.h"

#define PURE =0

#define GetSet(Type, VarName, FuncName)\
const Type& Get##FuncName() const{return VarName;}\
void Set##FuncName(const Type& _##FuncName) {VarName=_##FuncName;}

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