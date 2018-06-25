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
	Parser_root_component parser_root ;
	Libc::Env &_env;
	//Genode::Sliced_heap _sliced_heap { _env.ram(), _env.rm() };

	Genode::Heap _heap { _env.ram(), _env.rm() };

	Main(Libc::Env &env) :
		parser_root(_env, &_env.ep(), &_heap), _env(env)
	{
		Genode::log("parser: Hello!\n");
		_env.parent().announce(_env.ep().rpc_ep().manage(&parser_root));
	}
};

/************
 ** Server **
 ************/



	//char const *name()             { return "parser";      }
	//Genode::size_t Component::stack_size()            { return 64*1024*sizeof(long); }
//void Component::construct(Genode::Env &env) { static Parser::Main server(env);     }

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&] () { static Parser::Main main(env); });
}
