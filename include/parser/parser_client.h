#pragma once

#include <base/printf.h>
#include <base/rpc_client.h>
#include <parser/parser_session.h>
namespace Parser {
struct Session_client : Genode::Rpc_client<Session>
{
	Session_client(Genode::Capability<Session> cap):
		Genode::Rpc_client<Session>(cap) {}


	Genode::Ram_dataspace_capability profile_data()
	{
		return call<Rpc_profile_data>();
	}

	Genode::Ram_dataspace_capability live_data()
	{
		return call<Rpc_live_data>();
	}

};
}
