#pragma once
#include "Command.h"

class CmdSetCullMode: public Command
{
public:
	const char* GetName() override { return "SetCullMode"; }
	const char* GetDescription()
	{
		return "SetCullMode(mode)"
			"\n" "None: Not use any face culling"
			"\n" "Front: will only render facing awy from camera"
			"\n" "Back: will only render facing towards the camera";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

