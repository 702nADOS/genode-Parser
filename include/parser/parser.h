#pragma once

#include <base/signal.h>
#include <parser/parser_session.h>
//#include <os/attached_ram_dataspace.h>
#include <base/attached_ram_dataspace.h>
//#include <os/server.h>
#include <root/component.h>
#include <timer_session/connection.h>
#include <util/string.h>
//#include <cap_session/connection.h>
#include "mon_manager/mon_manager_connection.h"
#include "mon_manager/mon_manager.h"
namespace Parser {
class Parser
{
public:
	//Parser_session_component(Genode::Env &_env, Server::Entrypoint& ep);
	Parser(Genode::Env &env);
	// Get profiling data as an XML file.
	Genode::Ram_dataspace_capability profile_data();

	//live monitoring data
	Genode::Ram_dataspace_capability live_data();

protected:
	Genode::Env &_env;
	Genode::Entrypoint& _ep;
	//Genode::Cap_connection _cap;
	Genode::Number_of_bytes _profile_ds_size();

	Genode::Attached_ram_dataspace _profile_data;
	Genode::Attached_ram_dataspace _live_data;

	Mon_manager::Connection _mon_manager{_env};
	Genode::Ram_dataspace_capability mon_ds_cap{};
	Genode::Ram_dataspace_capability dead_ds_cap{};
};
}
