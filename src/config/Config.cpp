#include <cstring>
#include <cstdlib>

#include "os.h"
#include "util.h"
#include "Stack.h"
#include "Config.h"

#define MAX_FIELD_NAME_SIZE 80

struct Object;

struct ObjectStack
{
	Stack *stack = NULL;
	ObjectStack(Stack *stack);
	size_t cap() const;
	size_t numel() const;
	int add(Object *object);
	Object *last();
	const Object **begin() const;
	const Object **end() const;
	void *operator new(size_t size);
	void operator delete(void *p);
};

struct Object
{
	const char *type = NULL;
	const char *key = NULL;
	const char *value = NULL;
	ObjectStack *ostack = NULL;
	Object();
	void *operator new(size_t size);
	void operator delete(void *p);
};

Object::Object()
{
	return;
}

void *Object::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Object::operator delete (void *p)
{
	p = Util_Free(p);
}

ObjectStack::ObjectStack(Stack *stack)
{
	this->stack = stack;
}

size_t ObjectStack::cap () const
{
        return this->stack->cap();
}

size_t ObjectStack::numel () const
{
        return this->stack->numel();
}

int ObjectStack::add (Object *object)
{
        void *elem = (void*) object;
        return this->stack->add(elem);
}

Object *ObjectStack::last ()
{
	if (!this->numel()) {
		return NULL;
	}

	Object **iter = ((Object **) (this->stack->end()));
	Object *lastObj = *(--iter);
	return lastObj;
}

const Object **ObjectStack::begin () const
{
        return ((const Object**) this->stack->begin());
}

const Object **ObjectStack::end () const
{
        return ((const Object**) this->stack->end());
}

void *ObjectStack::operator new (size_t size)
{
	return Util_Malloc(size);
}

void ObjectStack::operator delete (void *p)
{
	p = Util_Free(p);
}

Config::Config ()
{
	return;
}

void Config::bind (BDX *app)
{
	this->app = app;
}

void *Config::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Config::operator delete (void *p)
{
	p = Util_Free(p);
}

static size_t Cfg_Count (const char **json, char const c)
{
	size_t count = 0;
	const char *iter = *json;
	while (*iter) {
		if (c == *iter) {
			++count;
		}
		++iter;
	}

	return count;
}

static bool Cfg_SyntaxQuote (const char **json)
{
        size_t const count = Cfg_Count(json, '\"');
        return !(count % 2);
}

static bool Cfg_SyntaxBrace (const char **json)
{
	size_t const left = Cfg_Count(json, '{');
	size_t const right = Cfg_Count(json, '}');
	return (left == right);
}

static bool Cfg_FindQuote (const char **json)
{
	bool newobj = false;
	while (**json && **json != '\"') {
		if (**json == '}') {
			newobj = true;
		}
		++*json;
	}

	return newobj;
}

static void Cfg_GetFieldName (char *name,
                              const char *beg,
                              const char *end,
                              size_t const sz)
{
	memset(name, 0, sz);
	strncpy(name, beg, end - beg);

	os::print("fieldname: %s\n", name);
	os::print("len: %lu\n", end - beg);
}

static bool Cfg_FindField (const char **json,
			   const char **beg,
			   const char **end,
			   char *fieldname)
{
	bool const newobj = Cfg_FindQuote(json);
	if (newobj) {
		return newobj;
	}

	if (!**json) {
		*beg = NULL;
		*end = NULL;
		return false;
	}

	*beg = ++*json;
	Cfg_FindQuote(json);
	if (!**json) {
		*beg = NULL;
		*end = NULL;
		return false;
	}

	*end = *json;
	++*json;

	Cfg_GetFieldName(fieldname, *beg, *end, MAX_FIELD_NAME_SIZE);
	return false;
}

static void Cfg_FindAllFields (const char **json)
{
	const char *beg[] = {NULL};
	const char *end[] = {NULL};
	char fieldname[MAX_FIELD_NAME_SIZE];
	const char *start = *json;
	while (**json) {
		Cfg_FindField(json, beg, end, fieldname);
	}

	*json = start;
}

static bool Cfg_Parse (const char **json)
{
	bool rc = true;
	rc = Cfg_SyntaxQuote(json);
	if (!rc) {
		return rc;
	}

	rc = Cfg_SyntaxBrace(json);
	if (!rc) {
		return rc;
	}

	return rc;
}

static const char *JSON (void)
{
        const char *txt = "\"Box\": {\n"
                          "     \"length\": \"12.0\",\n"
                          "     \"width\": \"12.0\",\n"
                          "     \"height\": \"16.0\"\n"
                          "},\n"
			  "\"System\": {\n"
                          "     \"size\": \"512\",\n"
                          "     \"periodic\": \"true\"\n"
                          "},\n"
			  "\"Sphere\": {\n"
                          "     \"size\": \"256\",\n"
                          "     \"radius\": \"1.0\"\n"
                          "},\n"
			  "\"Janus\": {\n"
                          "     \"size\": \"256\",\n"
                          "     \"radius\": \"1.0\"\n"
                          "}\n";
        return txt;
}

static bool Cfg_AddPairs (Object *object, const char **json)
{
	const char *beg[] = {NULL};
	const char *end[] = {NULL};
	char fieldname[MAX_FIELD_NAME_SIZE];
	while (**json) {

		bool const newobj = Cfg_FindField(json, beg, end, fieldname);
		if (newobj) {
			return newobj;
		}

		if (!**json) {
			break;
		}

		Object *next = new Object();
		if (!next) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		next->type = Util_CopyString("data");
		if (!next->type) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		next->key = Util_CopyString(fieldname);
		if (!next->key) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		Cfg_FindField(json, beg, end, fieldname);
		next->value = Util_CopyString(fieldname);
		if (!next->value) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		object->ostack->add(next);
	}

	return false;
}

static void Cfg_AddObjects (ObjectStack *objects, const char **json)
{
	do {
		const char *beg[] = {NULL};
		const char *end[] = {NULL};
		char fieldname[MAX_FIELD_NAME_SIZE];
		Cfg_FindField(json, beg, end, fieldname);

		Object *object = new Object();
		if (!object) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		object->type = Util_CopyString("object");
		if (!object->type) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		object->key = Util_CopyString(fieldname);
		if (!object->key) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		Stack *stack = new Stack();
		if (!stack) {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		object->ostack = new ObjectStack(stack);
		if (!object->ostack)  {
			Util_Clear();
			os::error("Config::config: memory error\n");
			exit(EXIT_FAILURE);
		}

		os::print("type: %s\n", object->type);
		os::print("key:  %s\n", object->key);

		Cfg_AddPairs(object, json);
		objects->add(object);

	} while (**json);
}

void Config::config ()
{
	const char *json[] = {JSON()};
	bool rc = Cfg_Parse(json);
	if (!rc) {
		os::print("FAIL\n");
		return;
	} else {
		os::print("PASS\n");
	}

//	Cfg_FindAllFields(json);
	Stack *stack = new Stack();
	if (!stack) {
		Util_Clear();
		os::error("Config::config: memory error\n");
		exit(EXIT_FAILURE);
	}

	ObjectStack *objects = new ObjectStack(stack);
	if (!objects) {
		Util_Clear();
		os::error("Config::config: memory error\n");
		exit(EXIT_FAILURE);
	}

	Cfg_AddObjects(objects, json);
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado
Copyright (C) 2024 UCF-Research Group

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

author: @misael-diaz
source: src/config/Config.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
