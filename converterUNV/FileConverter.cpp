#include "FileConverter.h"

#include <functional>
#include <algorithm>
#include <math.h>
#include <map>
#include <utility>

using namespace std;

// TODO: make it more flexible, may be, via templates!!!!
std::vector<int> parseStringInt(std::string str)
{
    std::vector<int> data;
    int num;

    std::istringstream sstreamer(str);

    while (sstreamer >> num)
        data.push_back(num);

    return data;
}

// TODO: make it more flexible, may be, via templates!!!!
std::vector<double> parseStringDouble(std::string str)
{
    std::vector<double> data;
    double num;

    std::istringstream sstreamer(str);

    while (sstreamer >> num)
        data.push_back(num);

    return data;
}

// -------------------- Constructors & Destructor -----------------------

FileConverter::FileConverter(std::string unvMeshFile, std::string rkdgMeshFile)
{
    reader.open(unvMeshFile.c_str());

    if (!reader.is_open())
    {
        cout << "File " << unvMeshFile << " is not found\n";
        exit(0);
    }

    writer.open(rkdgMeshFile.c_str());

    if (!writer.is_open())
    {
        cout << "File " << rkdgMeshFile << " could not be opened\n";
        exit(0);
    }

    //TODO: check if file format correct
}

FileConverter::~FileConverter()
{
    writer.close();
    reader.close();
}

// -------------------------- Private methods ----------------------------

int FileConverter::readTag()
{
    string str;

    do
    {
        getline(reader, str);
    } while (str != SEPARATOR);

    int num;

    reader >> num;
    getline(reader, str);

    return num;
}


void FileConverter::skipSection()
{
    string str;

    do
    {
        getline(reader, str);
    } while (str != SEPARATOR);

    cout << "skip\n";
}


void FileConverter::readNodes()
{
    string str;

    vector<int> nodeChar;
    vector<double> nodeCoord;

    int num;

    double x, y, z;

    do
    {
        getline(reader, str);

        nodeChar = parseStringInt(str);

        if (nodeChar[0] == -1) // end of section
            break;

        getline(reader, str);
        //cout << "rn str: " << str << endl;

        nodeCoord = parseStringDouble(str);
        nodes.push_back(nodeCoord);

    } while (str != SEPARATOR);

    cout << "OK\n";
}  // End readNodes


void FileConverter::readElements()
{

    string str = "";

    vector<int> elementProperties;
    vector<int> beamElementProperties;
    vector<int> elementNodeNumbers;

    int elementType = -100500;

    do
    {
        getline(reader, str);
        //cout << str << endl;

        elementProperties = parseStringInt(str);

        if (elementProperties[0] == -1)
            break;

        elementType = elementProperties[1];

        //cout << "elemType = " << elementType << endl;

        switch (elementType)
        {
            case 11:    // rod
            {
                getline(reader, str);
                beamElementProperties = parseStringInt(str);
                getline(reader, str);
                elementNodeNumbers = parseStringInt(str);

                edges.push_back(elementNodeNumbers);

                break;
            }
            case 41:    // plane triangular
            case 44:    // plane quadrilateral
            {
                getline(reader, str);
                elementNodeNumbers = parseStringInt(str);
                cellsAsNodes.push_back(elementNodeNumbers);

                getCellCenter(elementNodeNumbers);

                break;
            }
            default:
            {
                cout << "Element type " << elementType << " is not supported\n";
                break;
            }
        }

    } while (str != SEPARATOR);

    cout << "OK\n";

}  // End readElements


void FileConverter::readPatches()
{
    string str;

    do
    {
        vector<int> edgeGroup;
        vector<int> patchProperties;

        getline(reader, str);
        patchProperties = parseStringInt(str);

        if (patchProperties[0] == -1)
            break;

        int nEdgesInGroup = patchProperties.back();

        getline(reader, str);

        patchNames.push_back(str);

        //getline(reader, str);

        function<int()> getEdgeNumber = [&]()
        {
            int number;

            for (int j = 0; j < 2; ++j)
                reader >> number;

            int edgeNumber = number;

            for (int j = 0; j < 2; ++j)
                reader >> number;

            return edgeNumber;
        };

        for (int i = 0; i < nEdgesInGroup; ++i)
            edgeGroup.push_back(getEdgeNumber());

        patchEdgeGroups.push_back(edgeGroup);

        getline(reader, str);


    } while (str != SEPARATOR);

    cout << "OK\n";
}  // End readPatches


void FileConverter::getEdges()
{
    //int nEntities = nodes.size();
    map<pair<int, int>, int> isWritten;
    pair<int, int> key(0,0);

    for (int iEdge = 0; iEdge < edges.size(); ++iEdge)
    {
        key.first  = min(edges[iEdge][0],edges[iEdge][1]);
        key.second  = max(edges[iEdge][0],edges[iEdge][1]);
        isWritten[key] = iEdge + 1;
    }

    for (int iCell = 0; iCell < cellsAsNodes.size(); ++iCell)
    {
        //cout << "cell #" << iCell << endl;
        int n = cellsAsNodes[iCell].size();
        vector<int> elementEdges;
        //elementEdges.reserve(n);

        for (int i = 0; i < n - 1; ++i)
        {
            key.first  = min(cellsAsNodes[iCell][i],cellsAsNodes[iCell][i+1]);
            key.second = max(cellsAsNodes[iCell][i],cellsAsNodes[iCell][i+1]);

            //cout << key.first << ' ' << key.second << endl;

            if (isWritten[key] == 0)
            {
               //cout << isWritten[key] << endl;
               vector<int> newEdge = {key.first,key.second};
               edges.push_back(newEdge);
               elementEdges.push_back(edges.size());
               isWritten[key] = edges.size();
            }
            else
            {
                //cout << isWritten[key] << endl;
                elementEdges.push_back(isWritten[key]);
            }
        }

        key.first  = min(cellsAsNodes[iCell][0],cellsAsNodes[iCell][n-1]);
        key.second = max(cellsAsNodes[iCell][0],cellsAsNodes[iCell][n-1]);

        //cout << key.first << ' ' << key.second << endl;

        if (isWritten[key] == 0)
        {
           //cout << isWritten[key] << endl;
           vector<int> newEdge = {key.first,key.second};
           edges.push_back(newEdge);
           elementEdges.push_back(edges.size());
           isWritten[key] = edges.size();
        }
        else
        {
            //cout << isWritten[key] << endl;
            elementEdges.push_back(isWritten[key]);
        }

        cellsAsEdges.push_back(elementEdges);
    }

    cout << "OK" << endl;

} // End getEdges


void FileConverter::setAdjointCells()
{
    int nEdges = edges.size();

    adjEdgeCells.resize(nEdges);

    for (size_t iCell = 0; iCell < cellsAsEdges.size(); ++iCell)
        for (int iEdge : cellsAsEdges[iCell])
                adjEdgeCells[iEdge-1].push_back(iCell+1);

} // End setAdjointCells

void FileConverter::getCellCenter(const vector<int> &nodeNumbers)
{
    vector<double> center = {0.0, 0.0};

    for (int iNode : nodeNumbers )
    {
        center[0] += nodes[iNode - 1][0];
        center[1] += nodes[iNode - 1][1];
    }

    center[0] /= double(nodeNumbers.size());
    center[1] /= double(nodeNumbers.size());

    cellCenters.push_back(center);

} // End getCellCenter


void FileConverter::getEgdeNormals()
{
    cout << "Get edge normals... ";
    edgeNormals.reserve(edges.size());

    for (size_t i = 0; i < edges.size(); ++i)
    {
        vector<int> edge = edges[i];
        vector<double> edgeV = {nodes[edge[1]-1][0] - nodes[edge[0]-1][0], nodes[edge[1]-1][1] - nodes[edge[0]-1][1]};
        vector<double> centerV = {cellCenters[adjEdgeCells[i][0]-1][0] - nodes[edge[0]-1][0], cellCenters[adjEdgeCells[i][0]-1][1] - nodes[edge[0]-1][1]};
        vector<double> n = {edgeV[1], -edgeV[0]};
        if (n[0]*centerV[0] + n[1]*centerV[1] > 0)
        {
            n[0] *= -1;
            n[1] *= -1;
        }

        double ilen = 1.0/sqrt(n[0]*n[0] + n[1]*n[1]);

        n[0] *= ilen;
        n[1] *= ilen;

        edgeNormals.push_back(n);
    }

    cout << "OK" << endl;
} // End getEgdeNormals


// ------------------------------ Public methods ------------------------------


void FileConverter::importUNV ()
{
    int num = -1;

    while (reader.peek() != EOF)
    {
        num = readTag();

        cout << num << endl;

        switch (num)
        {
            case 164:
            {
                cout << "Processing units ... ";
                skipSection();
                break;
            }
            case 2420:
            {
                cout << "Processing coordinate system ... ";
                skipSection();
                break;
            }
            case 2411:
            {
                cout << "Processing nodes ... ";
                readNodes();
//                for (int i = 0; i < nodes.size(); ++i)
//                    cout << nodes[i][0] << ' ' << nodes[i][1] << endl;
                break;
            }
            case 2412:
            {
                cout << "Processing elements (boundary edges + cells) ... ";
                readElements();
                getEdges();
                setAdjointCells();
                getEgdeNormals();

                break;
            }
            case 2467:  //patches
            {
                cout << "Processing patches ... ";
                readPatches();

                cout << "patch names\n";
                for (size_t i = 0; i < patchNames.size(); ++i)
                    cout << i+1 << '|' << patchNames[i] << ", " << patchEdgeGroups[i].size() << " edges" << endl;

                break;
            }
            default:
            {
                cout << "Section " << num << "is not supported\n";
                skipSection();
                break;
            }
        };
    }
}

void FileConverter::exportRKDG()
{
    //renumerateEdges();
    cout << "Write RKDG mesh...";

    writer.precision(16);

    // --------------------------------------

    writer << "$Nodes\n";
    writer << nodes.size() << endl;

    for (int i = 0; i < nodes.size(); ++i)
        writer << i + 1 << ' ' << nodes[i][0] << ' ' << nodes[i][1] << endl;

    writer << "$EndNodes\n";

    // --------------------------------------

    int nEdgesBound = 0;

    for (int i = 0; i < patchNames.size(); ++i)
        nEdgesBound += patchEdgeGroups.size();

    writer << "$Edges\n";

    writer << edges.size() << endl;
    writer << edges.size() << endl;

    for (size_t i = 0; i < edges.size(); ++i)
        writer << i + 1 << ' ' << edges[i][0] << ' ' << edges[i][1] << endl;

    writer << "$EndEdges\n";

    // --------------------------------------

    writer << "$Cells\n";
    writer << cellsAsEdges.size() << endl;

    for (size_t i = 0; i < cellsAsEdges.size(); ++i)
    {
        writer << i + 1 << ' ' << cellsAsEdges[i].size() << ' ';
        for (size_t j = 0; j < cellsAsNodes[i].size(); ++j)
             writer << cellsAsNodes[i][j] << ' ';
        for (size_t j = 0; j < cellsAsEdges[i].size(); ++j)
             writer << cellsAsEdges[i][j] << ' ';
        writer << endl;
    }

    writer << "$EndCells\n";

   // --------------------------------------

    writer << "$NeibProcPatches\n";
    writer << 0 << endl;
    writer << "$EndNeibProcPatches\n";

    // --------------------------------------

    writer << "$AdjointCellsForEdges\n";
    writer << edges.size() << endl;

    for (size_t i = 0; i < adjEdgeCells.size(); ++i)
    {
        writer << adjEdgeCells[i].size() << ' ';

        for (size_t j = 0; j < adjEdgeCells[i].size(); ++j)
            writer << adjEdgeCells[i][j] << ' ' ;
        writer << endl;
    }

    writer << "$EndAdjointCellsForEdges\n";

    // --------------------------------------

    writer << "$EdgeNormals\n";
    writer << edges.size() << endl;

    for (size_t i = 0; i < edgeNormals.size(); ++i)
        writer << edgeNormals[i][0] << ' ' << edgeNormals[i][1] << endl;

    writer << "$EndEdgeNormals\n";

    // --------------------------------------

    writer << "$Patches\n";
    writer << patchNames.size() << endl;

    for (size_t i = 0; i < patchEdgeGroups.size(); ++i)
    {
        writer  << patchNames[i] << endl;
        writer  << patchEdgeGroups[i].size() << endl;

        for (size_t j = 0; j < patchEdgeGroups[i].size(); ++j)
            writer << patchEdgeGroups[i][j] << endl;
    }

    writer << "$EndPatches\n";

    cout << "Export OK\n";

}

// EOF