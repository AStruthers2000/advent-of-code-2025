#include "string_from.h"

SimpleString StringFrom(AoC::NumericAnswer const& inst)
{
    std::string str = inst.to_string();
    return SimpleString(str.c_str());
}

SimpleString StringFrom(AoC::BigNumericAnswer const& inst)
{
    return SimpleString(inst.to_string().c_str());
}

SimpleString StringFrom(AoC::StringAnswer const& inst)
{
    return SimpleString(inst.to_string().c_str());
}

SimpleString StringFrom(AoC::NumericAnswer *inst)
{
    return StringFrom(*inst);
}

SimpleString StringFrom(AoC::BigNumericAnswer *inst)
{
    return StringFrom(*inst);
}

SimpleString StringFrom(AoC::StringAnswer *inst)
{
    return StringFrom(*inst);
}
