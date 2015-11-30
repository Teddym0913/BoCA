/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <iomanip>
#include <iostream>

#include "Flag.hh"
#include "TreeReader.hh"

namespace boca
{

enum class Status
{
    none = 0,
    stable = 1,
    unstable = 2,
    generator = 3
};


/**
 * @brief flags defining to which level of detail jets should be analyzed
 *
 */
enum class JetDetail
{
    plain = 1 << 0,
    structure = 1 << 1,
    tagging = 1 << 2,
    isolation = 1 << 3,
};

template<>
struct Flag<JetDetail> {
    static const bool enable = true;
};

enum class Severity
{
    error,
    notification,
    information,
    debug,
    detailed
};

std::string Name(JetDetail jet_detail);

/**
 * @brief converts Clones to LorentzVectors and Jets
 *
 */
class FourVector
{

public:


protected:

    void NewEvent(TreeReader const& tree_reader);

    template<typename Data>
    void PrintCell(Data const data) const {
        std::cout << std::right << std::setw(9) << std::setfill(' ') << data;
    }

    void PrintTruthLevel(Severity severity) const;

    std::string PrintParticle(int Position) const;

    TreeReader const& tree_reader() const;

    const TreeReader* tree_reader_;

    int source_;

private:

};

}
