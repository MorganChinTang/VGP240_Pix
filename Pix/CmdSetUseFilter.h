#pragma once
#include "Command.h"
class CmdSetUseFilter: public Command
{
public:
        const char* GetName() override { return "SetUseFilter"; }

    const char* GetDescription() override 
    { 
        return "SetUseFilter(bool)"
            "\n"
            "- enable/ disable texture filtering";
    }
    bool Execute(const std::vector<std::string>& params) override;
};

