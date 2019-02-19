#ifndef FLUXHLLC_H
#define FLUXHLLC_H

#include "Flux.h"


class FluxHLLC : public Flux
{
    /// Calculate Star Region velocity
    numvector<double, dimPh> getUStar (const numvector<double, dimPh>& sol, double pK, double SK, double cK, double SStar) const;

    numvector<double, dimPh> getFStar(const numvector<double, dimPh>& sol, const numvector<double, dimPh>& fK, double rhoL, double pK, double SK, double cK, double SStar) const;

public:

    /// Construct with problem
    FluxHLLC(const Physics& phs) : Flux(phs) {}

    /// Destructor
    ~FluxHLLC() {}

    /// Evaluate numerical flux through one point
    virtual numvector<double, dimPh> evaluate(
        const numvector<double, dimPh>& solLeft, 
        const numvector<double, dimPh>& solRight
    ) const override;

};

#endif // FLUXHLLC_H