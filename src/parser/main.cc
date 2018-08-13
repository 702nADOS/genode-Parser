#include <base/env.h>
#include <base/printf.h>
#include <base/rpc_server.h>
#include <base/sleep.h>
#include <base/component.h>
#include <libc/component.h>
#include <parser/parser.h>
#include <base/heap.h>

namespace Parser {
	struct Main;
	struct Session_component;
	struct Root_component;
}

struct Parser::Session_component : Genode::Rpc_object<Session>
{
	private:
		Parser* _parser=nullptr;
	public:
		enum { CAP_QUOTA = 2 };
		
		Genode::Ram_dataspace_capability profile_data()
		{
			return _parser->profile_data();
		}

		Genode::Ram_dataspace_capability live_data()
		{
			return _parser->live_data();
		}

		Session_component(Parser *parser)
		: Genode::Rpc_object<Session>()
		{
			_parser = parser;
		}
	Session_component(const Session_component&);
	Session_component& operator = (const Session_component&);	
};

class Parser::Root_component : public Genode::Root_component<Session_component>
{
	private:
		Parser* _parser { };
	protected:

		Session_component *_create_session(const char*)
		{
			return new (md_alloc()) Session_component(_parser);
		}

	public:

		Root_component(Genode::Entrypoint &ep,
		               Genode::Allocator &alloc,
		               Parser *parser)
		:
			Genode::Root_component<Session_component>(ep, alloc)
		{
			_parser=parser;
		}
	Root_component(const Root_component&);
	Root_component& operator = (const Root_component&);	
};

struct Parser::Main
{
	enum { ROOT_STACK_SIZE = 16*1024 };
	Genode::Env	&_env;
	Genode::Heap	heap	{ _env.ram(), _env.rm() };
	Parser parser { _env };
	Root_component Parser_root { _env.ep(), heap , &parser};

	Main(Libc::Env &env_) : _env(env_)
	{
		_env.parent().announce(_env.ep().manage(Parser_root));
	}
};

Genode::size_t Component::stack_size() { return 32*1024; }

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&] () { static Parser::Main main(env); });
}
