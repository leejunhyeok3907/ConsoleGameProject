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

#define GETSET(Type, VarName, FuncName)\
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

#define KEY_CHECK(key, state) KeyManager::GetInst()->GetKeyState(key)==state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
