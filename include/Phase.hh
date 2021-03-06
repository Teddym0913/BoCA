/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/Identification.hh"

namespace boca
{

enum class Stage
{
    trainer,
    reader
};

std::string Name(Stage stage);

class Phase
{
public:
    Phase(boca::Stage stage, boca::Tag tag);
    boca::Stage Stage() const;
    boca::Tag Tag() const;
private:
    boca::Stage stage_;
    boca::Tag tag_;
};

}
