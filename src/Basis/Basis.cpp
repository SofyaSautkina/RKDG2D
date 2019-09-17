#include "Basis.h"
#include <vector>
#include <compService.h>
 
using namespace std;

Basis::Basis(const std::vector<shared_ptr<Cell>>& cls) : cells(cls)
{
    initBasisFunctions();
    initGramian();
}

void Basis::initBasisFunctions()
{
    for (const shared_ptr<Cell> cell : cells)
    {
        numvector<double,nShapes> curCoeffs =
        {
            1.0 / sqrt(cell->getArea()),
            2.0 * sqrt(3) / cell->getArea(),
            2.0 * sqrt(3) / cell->getArea()
        };

        if (nShapes == 6)
        {
            //curCoeffs.push_back(TODO)
        }

        phiCoeffs.push_back(curCoeffs);
    }



    phi.reserve(nShapes);
    gradPhi.reserve(nShapes);

    phi.emplace_back([&](int iCell, const Point& r){ return phiCoeffs[iCell][0]; });
    phi.emplace_back([&](int iCell, const Point& r){ return (r.x() - cells[iCell]->getCellCenter().x()) * phiCoeffs[iCell][1]; });
    phi.emplace_back([&](int iCell, const Point& r){ return (r.y() - cells[iCell]->getCellCenter().y()) * phiCoeffs[iCell][2]; });

    gradPhi.emplace_back([&](int iCell, const Point& r)->Point { return Point({ 0.0                , 0.0 }); });
    gradPhi.emplace_back([&](int iCell, const Point& r)->Point { return Point({ phiCoeffs[iCell][1], 0.0 }); });
    gradPhi.emplace_back([&](int iCell, const Point& r)->Point { return Point({ 0.0                , phiCoeffs[iCell][2] }); });

    if (nShapes == 6)
    {
        // CHECK FOR UNSTRUCTURED MESHES!!!
        //just for compilation, not used!!!
        double hx = 1.0;
        double hy = 1.0;

/*

        phi.emplace_back([&](const Point& r)
            { return sqrt(180.0 / pow(hx, 5) / hy) * ( sqr(r.x() - center.x()) - sqr(hx) / 12.0); });
        phi.emplace_back([&](const Point& r)
            { return sqrt(144.0 / pow(hx, 3) / pow(hy, 3)) * (r.x() - center.x()) * (r.y() - center.y()); });
        phi.emplace_back([&](const Point& r)
            { return sqrt(180.0 / pow(hy, 5) / hx) * ( sqr(r.y() - center.y()) - sqr(hy) / 12.0); });

        gradPhi.emplace_back([&](const Point& r)->Point
            { return Point({ sqrt(180.0 / pow(hx, 5) / hy) * 2 * (r.x() - center.x()) , 0.0}); });
        gradPhi.emplace_back([&](const Point& r)->Point
            { return Point({ sqrt(144.0 / pow(hx, 3) / pow(hy, 3)) * (r.y() - center.y()), \
                             sqrt(144.0 / pow(hx, 3) / pow(hy, 3)) * (r.x() - center.x()) }); });
        gradPhi.emplace_back([&](const Point& r)->Point
            { return Point({ 0.0, sqrt(180.0 / pow(hy, 5) / hx) * 2.0 * (r.y() - center.y()) }); });
*/
    }
}


void Basis::initGramian()
{
    gramian.reserve(cells.size());

    std::function<double(const Point&)> f;

    for (int iCell = 0; iCell < cells.size(); ++iCell)
    {
        std::vector<std::vector<double>> curGram(nShapes - 1);

        for (int i = 1; i < nShapes; ++i)
        {
            for (int j = 1; j <= i; ++j)
            {

                f = [&](const Point& p) {  return phi[i](iCell,p) * phi[j](iCell,p); };
                curGram[i-1].push_back(integrate(*cells[iCell], f));
            }

        }

        gramian.push_back(curGram);
    }
}

numvector<double, dimS> Basis::projection(const std::function<numvector<double, dimPh>(const Point& point)>& foo, int iCell) const
{
    numvector<double, dimS> alpha;    
    numvector<double, dimPh> buffer;

    for (int q = 0; q < nShapes; ++q)
    {
        std::function<numvector<double, dimPh>(const Point&)> f = \
            [&](const Point& p) 
            { 
                return phi[q](iCell, p) * foo(p); 
            };

        buffer = integrate(*(cells[iCell]), f);
        for (int p = 0; p < dimPh; ++p)
        {
            alpha[p*nShapes + q] = buffer[p];
        }// for p
    }// for shapes

    return correctNonOrthoCell(alpha, iCell);
} // end projection



numvector<double, dimS> Basis::correctNonOrthoCell(const numvector<double, dimS>& rhs, int iCell) const
{
    numvector<double, dimS> alphaCorr;
    const vector<vector<double>>& cellGramian = gramian[iCell];

    numvector<double, nShapes> solution(0.0); //for 3 ff!!!

    for (int iSol = 0; iSol < dimPh; ++iSol)
    {
        // solve slae
        solution[0] = rhs[iSol*nShapes];

        if (nShapes == 3)
        {
            solution[2] = (rhs[iSol*nShapes + 2] * cellGramian[0][0] - rhs[iSol*nShapes + 1] * cellGramian[1][0]) \
                / (cellGramian[1][1] * cellGramian[0][0] - cellGramian[1][0] * cellGramian[1][0]);
            solution[1] = (rhs[iSol*nShapes + 1] - solution[2] * cellGramian[1][0]) \
                  / (cellGramian[0][0]);
        }

        //set solution to appropriate positions 
        for (int i = 0; i < nShapes; ++i)
        {
            alphaCorr[i + iSol*nShapes] = solution[i];
        }
    }

    return alphaCorr;
}

numvector<double, dimS> Basis::correctPrevIterCell(const numvector<double, dimS>& alphaCorr, int iCell) const
{
    numvector<double, dimS> alpha(0.0);
    const vector<vector<double>>& cellGramian = gramian[iCell];

    for (int iSol = 0; iSol < dimPh; ++iSol)
    {
        alpha[iSol*nShapes] += alphaCorr[iSol*nShapes];

        for (int i = 1; i < nShapes; ++i)
        {
    ////#pragma omp simd
            for (int j = 1; j <=i; ++j)
                alpha[i + iSol*nShapes] += cellGramian[i-1][j-1] * alphaCorr[iSol*nShapes + j];

            for (int j = i + 1; j < nShapes; ++j)
                alpha[i + iSol*nShapes] += cellGramian[j-1][i-1] * alphaCorr[iSol*nShapes + j];

        }
    }// for variables

    return alpha;
}


