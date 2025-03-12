#pragma once
#include "Command.h"
class CmdPostProcessingBeginDraw : public Command
{
public:
    const char* GetName() override { return "PostProcessingBeginDraw"; }
    const char* GetDescription() override { return "PostProcessingBeginDraw()"; }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPostProcessingEndDraw : public Command
{
public:
    const char* GetName() override { return "PostProcessingEndDraw"; }
    const char* GetDescription() override { return "PostProcessingEndDraw()"; }
    bool Execute(const std::vector<std::string>& params) override;
};

class CmdPostProcessingSetEffectType : public Command
{
public:
    const char* GetName() override { return "PostProcessingSetEffectType"; }
    const char* GetDescription() override { return "PostProcessingSetEffectType()"; }
    bool Execute(const std::vector<std::string>& params) override;
};