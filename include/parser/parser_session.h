#pragma once

#include <session/session.h>
#include <base/rpc.h>
#include <ram_session/ram_session.h>
//#include <string>
namespace Parser {
struct Session : Genode::Session
{
	static const char *service_name() { return "parser"; }
	enum { CAP_QUOTA = 2 };
	virtual Genode::Ram_dataspace_capability profile_data() = 0;

	virtual Genode::Ram_dataspace_capability live_data() = 0;

	GENODE_RPC(Rpc_profile_data, Genode::Ram_dataspace_capability, profile_data);

	GENODE_RPC(Rpc_live_data, Genode::Ram_dataspace_capability, live_data);

	GENODE_RPC_INTERFACE(Rpc_profile_data, Rpc_live_data);
};
}
