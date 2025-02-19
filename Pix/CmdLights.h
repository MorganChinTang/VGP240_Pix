#pragma once
#include "Command.h"

class CmdSetLightAmbient : public Command
{
public:
	const char* GetName() override { return "SetLightAmbient"; }

	const char* GetDescription() override
	{
		return
			"SetLightAmbient (r, g, b)\n"
			"Sets the light ambient color";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightDiffuse : public Command
{
public:
	const char* GetName() override {
		return "SetLightDiffuse";
	}

	const char* GetDescription() override
	{
		return
			"SetLightDiffuse (r, g, b)\n"
			"Sets the light diffuse color";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightSpecular : public Command
{
public:
	const char* GetName() override {
		return "SetLightSpecular";
	}

	const char* GetDescription() override
	{
		return
			"SetLightSpecular (r, g, b)\n"
			"Sets the light specular color";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddDirectionalLight : public Command
{
public:
	const char* GetName() override {
		return "AddDirectionalLight";
	}

	const char* GetDescription() override
	{
		return
			"AddDirectionalLight (x, y, z)\n"
			"Adds a directional light to the scene.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddPointLight : public Command
{
public:
	const char* GetName() override {
		return "AddPointLight";
	}

	const char* GetDescription() override
	{
		return
			"AddPointLight (x, y, z, <constant>, <linear>, <quadratic>)\n"
			"Adds a point light to the scene.";
	}
	bool Execute(const std::vector<std::string>& params) override;
};