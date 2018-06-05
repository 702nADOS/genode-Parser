#include <base/env.h>
#include <base/printf.h>
#include <base/rpc_server.h>
#include <base/sleep.h>
#include <os/server.h>

#include "parser_session_component.h"

struct Main
{
	Parser_root_component parser_root ;
	Genode::Env &_env;
	//Genode::Sliced_heap _sliced_heap { _env.ram(), _env.rm() };

	Genode::Heap _heap { _env.ram(), _env.rm() };

	Main(Genode::Env &env, Server::Entrypoint& ep) :
		parser_root(_env, &ep, &_heap), _env(env)
	{
		Genode::log("parser: Hello!\n");
		_env.parent().announce(ep.rpc_ep().manage(&parser_root));
	}
};

/************
 ** Server **
 ************/

namespace Server
{
	char const *name()             { return "parser";      }
	size_t stack_size()            { return 64*1024*sizeof(long); }
	void construct(Genode::Env &env, Entrypoint& ep) { static Main server(env, ep);     }
}
