# Analysing Mission Data

The following files were part of my research with Prof. Anthony Chan, Rice University.

These files were written to analyse and preprocess data from a Van Allen Probes mission dataset, for use in setting up data-driven boundary conditions in a simulation. Specifcally, they add diffusion coefficients (and calculate their derivatives) for Upper Band and Lower Band Chorus waves (LBC and UBC) for the March 2013 geomagnetic storm and convert the coefficients into adiabatic invariant coordinates.

The header and template files include
1. Implementation of dipole field formulae for conversion of coordinates into adiabatic invariant coordinates.
2. Relevant formulae for a dipole magnetic field.

The LBC and UBC addition files:
1. Read in diffusion coefficients in one coordinate system.
2. Calculate derivatives.
3. Convert diffusion coefficients to simulation coordinate system.
4. Generate a masterfile containing the new data.

The files were extremely large, leading to the choice of using C++ for this data analysis to expedite time and be efficient in memory usage.

Due to the scientific nature and copyright, the datasets themselves and the simulation code cannot be shared.
