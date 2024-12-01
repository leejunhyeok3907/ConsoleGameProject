#pragma once

#include <Windows.h>
#include <iostream>

#include <vector>
#include <queue>

using namespace std;

#define GetSet(Type, VarName, FuncName)\
const Type& Get##FuncName() const{return VarName;}\
void Set##FuncName(Type _##VarName) {VarName=_##VarName;}