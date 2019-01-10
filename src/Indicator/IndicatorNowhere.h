#ifndef INDICATORNOWHERE_H
#define INDICATORNOWHERE_H

#include "Indicator.h"

class IndicatorNowhere : public Indicator
{
public:
    //- Constructor
    //IndicatorNowhere (const Mesh2D& msh, const Problem& prb): Indicator(msh, prb) {}
    IndicatorNowhere(const Mesh& msh) : Indicator(msh) {}

    //- Check discontinuities
    virtual std::vector<int> checkDiscontinuities() const override;
};

#endif // INDICATORNOWHERE_H
