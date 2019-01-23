#pragma once

//- Number of conservative variables
static const int PhysDim = 5;
static const int dimPh = 5;

//- Number of basis functions
static const int nShapes = 3;

// Coeffs vector size
static const int dimS = PhysDim * nShapes;

//- Initialisaton of tools for computations
//void Initialize() {}

//- list of all variables 
enum Variables 
{ 
    RHO  = 0,  
    RHOU = 1,  
    RHOV = 2, 
    RHOW = 3, 
    E    = 4
}; 
