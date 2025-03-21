#pragma once

#include "Command.h"

class CmdSetMaterialEmissive : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialEmissive";
	}
	
	const char* GetDescription() override
	{
		return "SetMaterialEmissive (r, g, b)\n"
			"Set the emissive color of the current material";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetMaterialAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialAmbient";
	}

	const char* GetDescription() override
	{
		return "SetMaterialAmbient (r, g, b)\n"
			"Set the ambient color of the current material";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetMaterialDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialDiffuse";
	}
	const char* GetDescription() override
	{
		return "SetMaterialDiffuse (r, g, b)\n"
			"Set the diffuse color of the current material";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetMaterialSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialSpecular";
	}
	const char* GetDescription() override
	{
		return "SetMaterialSpecular (r, g, b)\n"
			"Set the specular color of the current material";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetMaterialShininess : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialShininess";
	}
	const char* GetDescription() override
	{
		return "SetMaterialShininess (shininess)\n"
			"Set the shininess of the current material";
	}
	bool Execute(const std::vector<std::string>& params) override;
};