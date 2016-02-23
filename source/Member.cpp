/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Member.hh"
#include "physics/Particles.hh"
#include "Types.hh"

namespace boca
{

Member::Member()
{
    id_ = int(boca::Id::none);
}

Member::Member(int id)
{
    id_ = id;
}

Member::Member(int id, int position)
{
    id_ = id;
    position_ = position;
}
Member::Member(LorentzVector<boca::Momentum> const& momentum, int id, int position)
{
    id_ = id;
    position_ = position;
    momentum_ = momentum;
}
Member::Member(TLorentzVector const& momentum, int id, int position)
{
    id_ = id;
    position_ = position;
    momentum_ = momentum;
}
LorentzVector< Momentum >  const& Member::Momentum() const
{
    return momentum_;
}

int Member::Position() const
{
    return position_;
}

int Member::Id() const
{
    return id_;
}

void Member::Set(int id, int position)
{
    id_ = id;
    position_ = position;
}

int Member::EmptyPosition()
{
    return -1;
}

}
