#pragma once

#include "Command.h"
#include "MathHelper.h"
class CmdSetCameraPosition : public Command
{
public:
	const char* GetName() override { return "SetCameraPosition"; }

	const char* GetDescription() override { return "SetCameraPosition(x,y,z) \n Sets the position of the camera"; }

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraDirection : public Command
{
public:
	const char* GetName() override { return "SetCameraDirection"; }

	const char* GetDescription() override { return "SetCameraDirection(x,y,z) \n Sets the position of the camera"; }

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraNear : public Command
{
public:
	const char* GetName() override { return "SetCameraNear"; }

	const char* GetDescription() override { return "SetCameraNear(value)"; }

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraFar : public Command
{
public:
	const char* GetName() override { return "SetCameraFar"; }

	const char* GetDescription() override { return "SetCameraFar(value)"; }

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetCameraFov : public Command
{
public:
	const char* GetName() override { return "SetFov"; }

	const char* GetDescription() override { return "SetCameraFov(radians)"; }

	bool Execute(const std::vector<std::string>& params) override;
};