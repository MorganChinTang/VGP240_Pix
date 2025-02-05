#pragma once
#include "Command.h"

class CmdPushTranslation: public Command
{
public:
	const char* GetName() override
	{
		return "PushTranslation";
	}
	const char* GetDescription() override
	{
		return "Pushes a translation matrix to the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationX";
	}
	const char* GetDescription() override
	{
		return "Pushes a RotationX matrix to the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}
	const char* GetDescription() override
	{
		return "Pushes a RotationY matrix to the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}
	const char* GetDescription() override
	{
		return "Pushes a RotationZ matrix to the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushScaling : public Command
{
public:
	const char* GetName() override
	{
		return "PushScaling";
	}
	const char* GetDescription() override
	{
		return "Pushes a Scaling matrix to the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}
	const char* GetDescription() override
	{
		return "Pops a matrix from the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};