#pragma once

#include <memory>
#include <string>
#include <vector>

//forward declaratiion

struct Variable;

class VariableCache
{
public:
	static VariableCache* Get();

public:
	void Clear();

	bool IsVarName(const std::string& name) const;

	void AddFloat(const std::string& name, float value, float speed = 0.01f, float min = -FLT_MAX, float max = FLT_MAX);
	float GetFloat(const std::string& param);

	void ShowEditor();

	void AddBool(const std::string& name, bool value);
	bool GetBool(const std::string& param);

private:

	std::vector<std::unique_ptr<Variable>> mVariables;
	std::vector<Variable*> mVars;
};
