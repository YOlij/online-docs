---
layout: default
title: Design Decisions
parent: Documentation
nav_order: 4
---

# Design decisions

---
## 1. Design decisions prototype1

### 1-1. Data model decisions

 - File formats:
    - YAML (ASCII)
    - NetCDF  (Binary)
 - The Data Model implements file I/O to create the objects in the Domain Model. 
 - The Data Model contains readers for various file formats. Domain objects are created using data produced by one or more readers. 
 - If data from multiple types of input files is needed to create a domain object, intermediate 'data objects' are created by the readers, which are in turn used to create the domain object. 
 - If data from a single input file is needed to create a domain object, the domain object can be directly created by the reader.  Use of an intermediate data object is not necessary. 
 - Possible implementation: Domain object factories in the data model create domain objects. Methods in these factories call readers and create domain objects. 
 - Do we want to implement some form of lazy loading? This could be done by making domain objects maintain references to data objects to which the loading is lazily evaluated.
 - Initially focus on small YAML files. Optionally (future) convert (very big) external files to either YAML or NetCDF, during a preprocessor step.

### 1-2. Domain model decisions

 - Prototype scope:
 
    - Land
        - Topography: terrain height (Bed)
        - Bed roughness
        - Sediment characteristics
        - Vegetation

    - Water
        - Free-surface level / water depth
        - Velocity
        - Density
        - Viscosity
        - Temperature
        - Salinity

    - Atmosphere (heat flow, etc)
        - Wind (velocity + direction)
        - Air temperature
        - Air pressure
        - Air humidity
        - Cloudiness

    - Domain Boundaries
        - River (sink/source)
        - Open Sea

 - The properties described in the Land, Water and Atmosphere classes above, typically concern measured values/fields, which serve as initial conditions for the computational model.
 - Note: Turbulence is not a separate domain property. It is calculated in the mathematical model.
 - Perhaps we already need to think about how to separately handle surface water and groundwater (saturated and unsaturated zone), as part of the Domain Model class describing the "Water": or possibly two separate classes: Surface water and groundwater. Prototype1 then only contains surface water.
 - TODO: Define how we model sediments and tracers.


### 1-3. Mathemetical model decisions

 - Governing equations (e.g. shallow water, transport, Exner)
 - Physical terms (pressure gradient, advection, viscosity, bottom friction, couplings to external processes, etc.)
 - Boundary conditions
 - Initial conditions
 - Turbulence models
 - Parameters (child class?)
 - Dimensionality (1D, 2D, 3D)
 - Wetting and Drying
 - Couplings? (or are these just a representation of some physical term?)

 - Possible option:

     **First** Define operators:
        - Gradient
            - Applied to a scalar
            - Applied to a vector
        - Divergence
        - Laplace
        - Rotation/Curl
        - Dot-product
    
    **Then** define terms as composable functions of operators:
        - Advection (transport of a constituent)
        - Convection (transport of momentum)
        - Pressure
        - Viscous flux
        - Additionally there is a time derivative

### 1-4. Discretization model decisions

Key points:

 - Computational grid: for now: Structured, Cartesian grid
 - Finite volume
 - Collocated
 - Vertex centered
 - Explicit (but with mass-matrix due to vertex-based discretization), implicit bottom friction?
 - (without upwind) 2nd order (all quantities linearly varying with bilinear-interpolation on quad grids)
 - When upwind then with limiter?
 - Interpolation/extrapolation of input data to the grid
 - Integrate terms over control volumes
 - Bilinear interpolation

Notes: 

 - Are the grid and the solver separate classes in the discretization model or do they get their own layer in the architecture?
 - HPC / Parallellization (Here? Can it be a separate level?)
 
     - OpenMP
     - MPI
     - GPU

### 1-5. Testing

 - Acceptance tests 
 
     - Verify any inherited testcases for data-sources or analytical conclusions. 
     - i.e. it's not a goal or constraint to get the same results as a predecessor for the same model)
     - Mass conservation tests : Note: Method of Manufactured Solutions
     - Analytical solution tests (that verify the Mathematical Model), e.g.:
         - Simple channel flow (bottom friction, boundary conditions)
         - Dambreak cases: wet/dry (momentum conservation, wetting/drying)
         - Thacker case (Time integration, wetting/drying, mass conservation)
     - Grab and convert tests from the Delft3D4 and D-FlowFM validation testcases: Compare only to the original analytical or data-source.
     - Small SFINCS testcase
     - Big SFINCS testcase

---
## 2. Design decisions for the complete (long-term) architecture

### 2-1. Data model decisions

For now the same as for the prototype: Yaml and NetCDF.

### 2-2. Domain model decisions

#### 2-2-1. For follow-up prototypes:

    - Hydraulic Structures
    - Precipitation
    - Waves
    - Sediments (part of the bed?)
    - Mud
    - Soil constitution/stratigraphy
    - Bed forms

#### 2-2-2. For the future:

    - Ice (how to model phase transitions?)
    - Floating objects
        - Vegetation (floating in water)
        - Ships
        - Oil
        - Particles
    - Are buildings a part of the "land" class?
    - Active human-intervention: e.g. irrigation
    - Sewer system

 - For modelling water quality (inventory needed?):
    - Species/constituents, e.g.
        - Phytoplankton
        - Oxygen, Nitrogen, etc.
        - Animals/fish (or should this be a separate class in the Domain Model?)

#### 2-2-3. Towards a more complete domain model:

A possible more elaborate/complete domain model could for instance look as follows:

 - Atmosphere
     - Meteorology
         - Wind
             - HurricaneWind
                       
     - HeatFluxExchange
         - SolarRadiation
         - BackRadiation
         - Evaporation
         - Convection

 - Land
     - Topography
     - BedRoughness
     - BedComposition
     - Constructions
     - Buildings
         - Roads
     - Agriculture
     - Irrigation
     - Banks
     - BedloadTransport[^1]
     - Bedforms[^1]

 - Water
     - Flow
     - Waves
         - Tide
         - Tsunamis
         - Breaking waves
         - FloatingStructures
     - Particles
     - TransportedConstituents (are suspended sediments in here or should they be in a separate class?)
     - Oil
     - Ice

 - HydraulicStructures
     - Weirs
     - Groynes
     - Dams
     - Culverts
     - Gates
     - Pumps
     - Bridges
     - Powerstations
     - RealTimeControl

 - Vegetation[^2]
     - Rigid
     - Flexible

 - Chemical/WaterQuality?
     - OrganicMatter
     - NonOrganicMatter
     - Processes?

[^1]: Bedload and bedforms are under water. Are they part of land or water? Ask domain experts, e.g. Bert Jagers, Mohamed Yossef, Willem Ottevanger, coastal morphologists.
[^2]: Vegetation can be both on land and in water, ask domain experts what is logical.

### 2-3. Mathemetical model decisions

 - Sediment transport & morphology
     - Sediment transport formulas
     - Slope effects
     - Hiding & Exposure
     - Bank erosion
     - Fall velocity formulas
     - Flocculation
 - Equations of state 
 - Roughness formulations 
 - Hydraulic structure formulations 
 - Hydrological processes
 - Different (more elaborate) boundary conditions (e.g. absorbing BCs)
 - Different (slope/flux) limiters
 

### 2-4. Discretization model decisions

#### 2-4-1. Key attention points (brief)

 - Rectangular, cuvilinear, block-structured and/or unstructured grids
 - 1D, 2D, 3D
 - Explicit and/or (semi-)implicit
 - Higher order (2nd and higher)
 - (Multi-)GPU/multi-CPU (Here? Should it be a separate level?)
 
#### 2-4-2. Elaborate considerations
 
Starting points for a good discretization:
 1. Zero (or very few) options! The effect of numerical options is usually very application dependent and very difficult to assess for users. 
    Moreover, the 'correct' choice is often space- and time-dependennt, even within one simulation. 
    Options have far-reaching consequences for testing/validation, where any possible combinaton of options needs to be considered.
    Note: zero options particularly holds for the discretisations (in space and time). One or two possible options in the solver (e.g. specifying a convergence criterion) is acceptable, in case this has little to no effect on the solution (which needs to be verified). 
    Options for specifying things like under-relaxation should be avoided (or removed in a later stage). Necessity of such options will result in a solution algorithm that is difficult to comprehend, where the developer passed the responsibility to the user, which should be avoided.
 2. Have solutions only/mostly depend on grid resolution, not on grid structure or positioning of grid points.
 3. Make fit for a scala of relevant use cases (and display that this is the case by presenting defendable and/or verifiable argumentation, when a formal analysis is not yet available.
 4. No optimization for simple and possibly not-so-relevant applications (e.g. dam-break problem). Instead, optimalising for (to be expected) complex applications in rivers, lakes, estuaries, seas, ... (unless such functionality is not deemed necessary).
 5. Preferably have a numerical implementation that provides physical insight in the effect of numerical errors on the solution, for being able to assess whether grid grid was locally sufficiently fine, or needs to be refined, without having the need to perform such computations on twice finer grids (i.e. no necessity for expensive grid refinement studies).
 6. Be sufficiently accurate and flexible, very robust and efficiënt (in particular for problems with large time scales), be well-maintainable, extendible and exchangeable (within the chosen concept), be parallelisable, etc.
 
Based on present knowledge, there is only one numerical implementation that (as preliminary analyses have shown) - in time - can fulfill all these conditions: the fully-implicit, block-structured, central, vertex-centered, finite-volume discretisation of regularised (= locally sufficiently smoothed) fysics, based on piecewise-linear (higher-order is p.m.) approximations of all variables, with cut-cell method for modelling of (irregularly shaped) boundaries and interfaces (between water and hydraulic structures for example), for those situations where the use of boundary-fitted grids are not practicable or possible.
 
How about (classical) staggering? That works quite well for large-scale applications (e.g. tidal motions) with little dynamics on the smaller scales. 
In applications with (locally) more dynamics (lokally important convection and viscosity) a staggered-grid method performs less well, in particular on somewhat irregular grids. 
Since the aim is to have a generically applicable method, staggered-grid methods seem to not fulfill some of the criteria, also because of the orthogonality requirements, that considerably limit the flexibility. 
It should be noted that there are different types or flavours of staggering. The P1NC-P1 configuration is a considerable improvement in accuracy compared to the RT0 (Raviart-Thomas) method used in D-Flow FM.
It is considerably more accurate, less sensitive to the grid structure, and does not have an orthogonality requirement. It is an interesting method, but as shown from preliminary analyses, also has considerably less favourable properties than the P1-P1 method (= collocated and all piecewise linear apprximations). 
An important drawback of staggering is also the implementation of/near boundaries and Domain Decomposition (DD) interfaces.
For accuracy purposes and for clarity/simplicity/modularity of the software implementation it is of great advantantage when all variables are defined and stored in a single manner.
This particularly holds for boundaries and interfaces.

There are many more discretisation methods/approaches, e.g. Discontinuous Galerkin (DG) and WENO variants. 
We have/had little experience with these approaches in the past. 
Conjecture is that the better variants of these approaches are rather complex and are therefore often combined with explicit time integration methods.
This can be beneficial for parallel performance, but not for numerical performance, due to the severe time step restrictions for stability. 
Due to the broad computational stencils of WENO (the more accurate the method, the large the stencil (for Finite Volume type methods), the implementation of/near boundaries and interfaces is also more complex.
We should have more knowledge of DG and WENO methods, to be able better judge/compare them to the - to us - more familiar/conventional methods.
It can be noted that it should theoretically be possible to obtain a cell-based software implementation that can accommodate DG or WENO-type approaches.
Therefore, the applicability of such methods could/should also be considered.
 
How about unstructured/flexible-mesh versus block-structured? Piecewise linear P1-P1 allows both. 
It could be an idea to start with flexible meshes (mixed quadrilaterals and triangles, and ...), and to put the development of appropriate Domain Decomposition (DD) coupling methods (which is far from trivial!) on the longer-term agenda. 
Advantage of this approach is that - due to the fact that vertex-centered, piecewise linear P1-P1 scheme can be accurate on both quadrilateral and triangular grids - there is no large loss of accuracy on structured grids, that one would have for other special unstructured-grid methods, that have special measures to get the method to work on triangles (e.g. Perot averaging).
In such a case, the acquired flexibility is attained at the cost of a reduced accuracy on structured grids. 
This advantage also holds for the P1NC-P1 method and probably for all (collocated) cell-based space-discretisations. 
Point 5 above is then not reached, and consequently also point 6 is only partly achieved. 
Some form of upwind is probably required to acquire a certain level of robustness, with the consequency of deteriorated accuracy and efficiency and (temporarily) not achieving points 1 and 2 above.

How about semi-implicit versus fully implicit methods? Here the same reasoning holds as above. 
For simplicity, we could start with a semi-implicit/linearized implicit method and steadily extend towards a more nonlinearly implicit method.
For stability and robustness it is likely that some form of upwind will be necessary and the lack of implicitness will definitely hamper efficiency, which causes point 5 above to not be reached, it considerably reduces point 6, and removes points 1 and 2 weg (temporarily?).
It is recommended to perform some upfront analysis to gain some insight in certain properties of the methods (e.g. stability, accuracy). 
This will very likely involve two-dimensional, depth-avereaged (2DH) Fourier-mode analyses of the methods and of grid transitions (DD, quads-triangles, jumps in grid resolution, etc.).

### 2-5. Other

 - Possibilities for prototype 2:
 - Julia
 - Combine multiple external frameworks where possible
 - Implicit solver
 - Unstructured grid
 - Adaptive grids
 - GPU
 - Structures (weirs, thin dams, dry points etc.)
 - Meteo files, initial conditions, boundary conditions
 - Subgrid topography (as in SFINCS, Frank's PhD work)
 - Subgrid (or its own grid resolution) for any data source (roughness, precipitation, etc).
 - Restart files (full state dump)


