#include <base/env.h>
#include <base/printf.h>
#include <base/rpc_server.h>
#include <base/sleep.h>
//#include <os/server.h>
#include <base/component.h>
#include <libc/component.h>
#include "parser_session_component.h"
#include <base/heap.h>

namespace Parser{ struct Main;}
struct Parser::Main
{
	enum { ROOT_STACK_SIZE = 16*1024 };
	
	Genode::Env &_env;

	Genode::Heap _heap { _env.ram(), _env.rm() };

	Parser_root_component parser_root { _env, &_env.ep(), &_heap };

	Main(Genode::Env &env) :
		_env(env)
	{
		Genode::log("parser: Hello!");
		_env.parent().announce(_env.ep().manage(parser_root));
	}
};

Genode::size_t Component::stack_size() { return 32*2048; }

void Component::construct(Genode::Env &env)
{
	static Parser::Main server(env);
}

void Libc::Component::construct(Libc::Env&)
{
	//Libc::with_libc([&] () {  });
}
