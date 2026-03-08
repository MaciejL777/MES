# MES - Finite Element Method Solver

## Overview

MES (Metoda Elementów Skończonych - Finite Element Method) is a C++ application for solving transient heat transfer problems using the Finite Element Method. It implements a complete FEM pipeline including mesh generation, assembly of global system matrices, and numerical solution of nonlinear thermal equations.

## Key Features

### Core Functionalities

- **Heat Transfer Analysis**: Solves transient heat conduction problems with Dirichlet and Neumann boundary conditions
- **Finite Element Discretization**: Supports 4-node isoparametric quadrilateral elements
- **Nonlinear Problem Solving**: Handles temperature-dependent material properties
- **Gaussian Integration**: Numerical integration using Gauss quadrature (16 integration points per element)
- **Matrix Assembly**: Constructs local and global heat capacity matrices (H, C) and load vectors (P)
- **Jacobian Transformation**: Computes local-to-global coordinate transformations for arbitrary element geometries
- **Boundary Conditions**: Applies Dirichlet (fixed temperature) and Neumann (heat flux) boundary conditions
- **Parallel Processing**: OpenMP support for multi-threaded computation

### Input Parameters

The solver uses material and simulation parameters including:

- Thermal conductivity (k)
- Convection coefficient (α)
- Ambient temperature (T_∞)
- Material density (ρ)
- Specific heat capacity (c_p)
- Simulation time and time step

## Technologies Used

### Programming Language & Standards

- **C++11/14**: Modern C++ with standard library containers and algorithms
- **Visual Studio ecosystem**: Developed with MSVC compiler (MES.vcxproj)

### Libraries & Technologies

- **Standard Template Library (STL)**: Vectors, arrays for data structures
- **OpenMP**: Multi-threaded parallelization for performance optimization
- **File I/O**: Standard C++ streams for mesh and data input/output

### Numerical Methods

- **Gauss Quadrature Integration**: 16-point Gaussian quadrature for accurate element integration
- **Isoparametric Elements**: 4-node quadrilateral elements with Jacobian transformation
- **Finite Element Assembly**: Local-to-global matrix assembly operations

## Project Structure

```
├── main.cpp                 # Program entry point with OpenMP initialization
├── GlobalData.h/cpp         # Global simulation parameters and material properties
├── Grid.h/cpp              # Mesh structure and node management
├── Element.h/cpp           # Finite element definition and local matrix computation
├── ElemUniw.h/cpp          # Universal element class for shape functions
├── Jakobian.h/cpp          # Jacobian matrix computation and coordinate mapping
├── Equations.h/cpp         # System of equations assembly and solving
├── Test1_4_4.txt          # Test case: 4×4 mesh
├── Test2_4_4_MixGrid.txt  # Test case: 4×4 mixed grid
└── Test3_31_31_kwadrat.txt # Test case: 31×31 mesh (detailed verification)
```

## Building the Project

### Prerequisites

- Visual Studio 2015 or later
- OpenMP-compatible compiler (included with MSVC)

### Compilation

```
# Using Visual Studio
Open MES.sln and build the solution

# Or using command line
msbuild MES.sln /p:Configuration=Release
```

## Usage

### Running the Solver

```bash
# Basic execution
MES.exe

# With specified number of threads
MES.exe 4        # Run with 4 threads

# Using environment variable
set OMP_NUM_THREADS=8
MES.exe
```

### Input Format

The solver reads mesh data and parameters from text files. Test files are provided with the project for validation.

## Performance Characteristics

- **Parallelization**: Leverages multi-core processors via OpenMP for element-wise computations
- **Gaussian Integration**: 16 integration points ensure high accuracy for quadrilateral elements
- **Memory Efficiency**: Local element matrices assembled into global sparse system
- **Scalability**: Handles varying mesh densities from 4×4 to 31×31 elements and beyond

## Author Notes

This implementation demonstrates a complete FEM workflow suitable for educational purposes and engineering analysis of heat transfer problems. The code structure allows for extension to other PDE-based problems and advanced numerical techniques.

---

**Language**: C++ | **Method**: Finite Element Method | **Application Domain**: Heat Transfer Analysis
