#pragma once

#include <parser/parser_client.h>
#include <base/connection.h>
namespace Parser {
struct Connection : Genode::Connection<Session>, Session_client
{
	Connection(Genode::Env &env) : Genode::Connection<Parser::Session>(env, session(env.parent(),
		                                                "ram_quota=6K, cap_quota=4")),
		               Session_client(cap()) { }
	};


}
