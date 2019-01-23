#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "numvector.h"
#include "Patch.h"
#include "Params.h"
#include <string>



class Boundary
{
public:

    //- Type of BC
    std::string type;

    const Patch& patch;



    //- Default constructor
    Boundary(const Patch& p) : type("not implemented"), patch(p) {};

    //- Apply boundary conditions
    virtual void applyBoundary(std::vector<numvector<double, dimS>>& coeffs) const = 0;
};

#endif // BOUNDARY_H