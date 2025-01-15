#pragma once
#include"Command.h"
class CmdSetFillMode:public Command
{
public:
	const char* GetName() override
	{
		return "SetFillMode";
	}

	const char* GetDescription() override
	{
		return "Set the fill mode\n"
			"\n"
			"- sets fill mode to Wireframe or Solid";
	}

	bool Execute(const std::vector<std::string>& params) override;

};

