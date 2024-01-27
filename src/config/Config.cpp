#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cerrno>

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

static void Cfg_OpenJSON (FILE **f)
{
	*f = fopen("conf.json", "r");
	if (!*f) {
		Util_Clear();
		os::error("Config::load: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void Cfg_CloseJSON (FILE **f)
{
	fclose(*f);
}

static size_t Cfg_SizeJSON (FILE **f)
{
	fseek(*f, 0L, SEEK_SET);
	size_t const beg = ftell(*f);
	fseek(*f, 0L, SEEK_END);
	size_t const end = ftell(*f);
	size_t const size = (end - beg);
	fseek(*f, 0L, SEEK_SET);
	return size;
}

static void *Cfg_ReadJSON (FILE **f)
{
	size_t const bytes = Cfg_SizeJSON(f);
	size_t const sz = (bytes + 1);
	void *json = Util_Malloc(sz);
	memset(json, 0, sz);
	size_t const size = fread(json, 1, bytes, *f);
	if (size != bytes) {
		Cfg_CloseJSON(f);
		Util_Clear();
		os::error("Config::load: error\n");
		exit(EXIT_FAILURE);
	}

	return json;
}

void Config::load ()
{
	FILE *f[] = {NULL};
	Cfg_OpenJSON(f);
	Cfg_SizeJSON(f);
	void *json = Cfg_ReadJSON(f);
	Cfg_CloseJSON(f);
	this->_json_= json;
}

void Config::parse ()
{
	const char *JSON = (const char*) this->_json_;
	const char *json[] = {JSON};
	if (!Cfg_Parse(json)) {
		Util_Clear();
		os::error("Config::config: syntax error in conf.json\n");
		exit(EXIT_FAILURE);
	}

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
	this->_objects_ = (void*) objects;
}

void Config::config ()
{
	return;
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
