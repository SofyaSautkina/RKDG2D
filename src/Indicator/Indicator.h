#ifndef INDICATOR_H
#define INDICATOR_H

#include <vector>
#include "Mesh2D.h"
#include "numvector.h"


class Indicator
{
protected:

    //- Mesh
    const Mesh2D& mesh;
    
public:

    //- Constructor
    Indicator(const Mesh2D& msh) : mesh(msh) {}

    //- Destructor
    virtual ~Indicator() {}
    
    //- Check discontinuities
    virtual std::vector<double> checkDiscontinuities() const = 0;

};




#endif
