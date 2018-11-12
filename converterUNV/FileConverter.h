#ifndef FILECONVERTER_H
#define FILECONVERTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

/// Mesh converter from Ideas UNV format to RKDG2D format
///
/// IDEAS UNV mesh: the sequence of blocks like:
///     -1
/// universal dataset number according to IDEAS notation
/// (see more: http://www.sdrl.uc.edu/sdrl/referenceinfo/universalfileformats/file-format-storehouse)
/// content of section
///     -1
///
/// RKDG mesh: the sequence of blocks looks like .msh format
/// See more after class definition


//- Boundary between UNV sections
const std::string SEPARATOR("    -1");


class FileConverter
{

private:

    /// Variables

    //- fstream for UNV mesh
    std::ifstream reader;

    //- fstream for RKDG mesh
    std::ofstream writer;

    //- nodes
    std::vector<std::vector<double>> nodes;

    //- edges = numbers of nodes
    std::vector<std::vector<int>> edges;

    //- cells = numbers of edges
    std::vector<std::vector<int>> cellsAsEdges;
    std::vector<std::vector<int>> cellsAsNodes;

    //- cell centers
    std::vector<std::vector<double>> cellCenters;

    //- adjoint cells for edges
    std::vector<std::vector<int>> adjEdgeCells;

    //- edge normals
    std::vector<std::vector<double>> edgeNormals;

    //- patch names
    std::vector<std::string> patchNames;

    //- patch edge groups
    std::vector<std::vector<int>> patchEdgeGroups;


    /// Methods

    //- Read number of section
    int readTag();

    //- Skip section
    void skipSection();

    //- Read nodes
    void readNodes();

    //- Read elements (edges + cells)
    void readElements();

    //- Read patches
    void readPatches();

    //- Find edges for cell defined by nodes
    void getElementEdges(const std::vector<int>& nodeNumbers);

    //- Find center of cell vertices
    void getCellCenter(const std::vector<int>& nodes);

    //- Find normal vectors for edges
    void getEgdeNormals();

    //- Find ajoint cells for each edge
    void setAdjointCells();


public:

    //- Constructor
    FileConverter(std::string unvMeshFile, std::string rkdgMeshFile);

    //- Destructor
    ~FileConverter();

    //- Import UNV mesh
    void importUNV ();

    //- Export RKDG mesh
    void exportRKDG();
};


#endif // FILECONVERTER_H

/// RKDG mesh format
/// ----------------
///
/// $Nodes
///     number_of_nodes
///     x y
///     ...
/// $EndNodes
/// $Edges //at first - boundary edges, after - internal
///     number_of_boundary_edges
///     total_number_of_edges
///     is_edge_on_boundary node_1 node_2
///     ...
/// $EndEdges
/// $Cells
///     number_of_cells
///     number_of_edges_in_cell node1 node2 ... edge1 edge2 ... // number_of_nodes = number_of_edges
///     ...
/// $EndCells
/// $AdjointCellsForEdges
///     total_number_of_edges
///     number_of_adj_cells cell1 cell2 (or only cell1)
///     ...
/// $EndAdjointCellsForEdges
/// $EdgeNormals
///     total_number_of_edges
///     n_x n_y
/// /// ...
/// $EndEdgeNormals
/// $Patches
///     number_of_patches
///     patch_name1
///         number_of_edges_in_patch
///         edgenum1
///         edgenum2
///         ...
///     patch_name_2
///         ...
/// $EndPatches
