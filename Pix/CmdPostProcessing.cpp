#include "CmdPostProcessing.h"
#include "PostProcessing.h"

bool CmdPostProcessingBeginDraw::Execute(const std::vector<std::string>& params)
{
    PostProcessing::Get()->BeginDraw();
    return true;
}

bool CmdPostProcessingEndDraw::Execute(const std::vector<std::string>& params)
{
    PostProcessing::Get()->EndDraw();
    return true;
}

bool CmdPostProcessingSetEffectType::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
        return false;

    EffectType effectType = EffectType::None;
    if (params[0]=="none"){effectType=EffectType::None;}
    else if (params[0] == "monoChrome") { effectType = EffectType::MonoChrome; }
    else if (params[0] == "invert") { effectType = EffectType::Invert; }
    else if (params[0] == "mirror") { effectType = EffectType::Mirror; }
    else if (params[0] == "blur") { effectType = EffectType::Blur; }
    else if (params[0] == "colorMaskR") { effectType = EffectType::ColorMaskR; }
    else if (params[0] == "colorMaskG") { effectType = EffectType::ColorMaskG; }
    else if (params[0] == "colorMaskB") { effectType = EffectType::ColorMaskB; }
    else if (params[0] == "sepia") { effectType = EffectType::Sepia; }
    else if (params[0] == "wave") { effectType = EffectType::Wave; }
    else if (params[0] == "fishEye") { effectType = EffectType::FishEye; }
    else { return false; }

    PostProcessing::Get()->SetEffectType(effectType);
    return true;
}