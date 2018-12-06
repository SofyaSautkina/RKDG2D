#ifndef BASIS_H
#define BASIS_H

#include <vector>
#include <functional>
#include "Point.h"

#include "Mesh.h"
#include "Params.h"



/// Form functions for mesh cells

class Basis
{
    //- Constant reference to mesh
    const std::vector<Cell>& cells;

    //- Init basis functions
    void initBasisFunctions();

    //- Init gramian matrices
    void initGramian();

public:
    //Basis(int nF) { nShapes = nF;};

    Basis(const std::vector<Cell>& cells);
    
    //- Coefficients for form functions
    std::vector<numvector<double, nShapes>> phiCoeffs;
    
    //- List of form functions as is
    std::vector<std::function<double(int iCell, const Point&)>> phi;
	//std::vector<std::function<double(const Point&)>> phi;

    //- List of form functions' gradients
    std::vector<std::function<double(int iCell, const Point&)>> gradPhi;
    
    //- Gramian matrix
    /// Typical look for my basis:
    /// 1     0         0
    /// 0 phi1*phi1 phi1*phi2
    /// 0 phi2*phi1 phi2*phi2
    ///
    /// The good idea is to save only three elements for linear BF
    /// and six elements for quadratic BF. Therefore, it will be an array
    /// which length is equal to nShapes.
    /// NOTE: in case of constant functions will be empty.
	numvector< numvector<double, nShapes>, nShapes> gramian;

};

#endif // BASIS_H
