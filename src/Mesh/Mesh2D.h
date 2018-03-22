#ifndef MESH2D_H
#define MESH2D_H

#include "numvector.h"
#include "Point.h"
#include "Patch.h"
#include "Cell.h"
#include "FluxLLF.h"
#include "EdgeInternal.h"
#include "EdgeBoundaryDiagProjection.h"

#include <fstream>
#include <memory>


class Mesh2D
{

private:

    //- File ofstream for mesh export
    mutable std::ofstream writer;

    //- File ifstream for mesh import
    mutable std::ifstream reader;

    int nx;
    int ny;
    double Lx;
    double Ly;

    //- Construct rectangular mesh in the source code
    void createRectangularMesh(const Problem &prb);

public:

    //- Number of cells
    int nCells;

    //- Coordinates of nodes (x,y)
    std::vector<Point> nodes;

    //- Internal edges (node1, node2)
    std::vector<std::shared_ptr<EdgeInternal>> edgesInternal;

    //- Boundary edges
    std::vector<std::shared_ptr<EdgeBoundary>> edgesBoundary;

    //- Mesh cells (edge1, ..., edgek counterclockwise)
    std::vector<std::shared_ptr<Cell>> cells;

    //- Groups of boundary edges
    std::vector<Patch> patches;

public:

    //- Construct uniform rectangular mesh by number of cells and size of flow domain
    Mesh2D(int nx, int ny, double Lx, double Ly, const Problem& prb);

    //- Construct mesh by import from UNV file
    Mesh2D(std::string fileName);

    //- Destructor
    ~Mesh2D();

    //- Import mesh
    void importMesh(std::string fileName) const;

    //- Export uniform rectangular mesh
    void exportUniformMesh() const;

    //- Export arbitrary 2D mesh in custom format like .msh
    void exportMesh() const;

};// end Mesh 2D

#endif // MESH2D_H

