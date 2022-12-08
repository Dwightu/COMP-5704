# COMP-5704: Parallel Algorithms and Applications in Data Science
This repository is the final project for course <a href="https://www.dehne.ca/comp5704">COMP-5704</a>, supervised by Prof F.Dehne.

## Introduction
OpenMP provides a high-level abstract description of parallel algorithms. Programmers specify their intentions by adding specialized pragmas to their source code, so that the compiler can automatically parallelize programs and add synchronous mutex and communication where necessary. However, as a high-level abstraction, OpenMP is not suitable for situations that require complex inter-thread synchronization and mutual exclusion. Another disadvantage of OpenMP is that it cannot be used on non-shared memory systems, such as computer clusters, where MPI is heavily used.

CPUs are now generally 4 or more cores, which is good news for computationally intensive programs. In the absence of GPU acceleration, consider using CPU multithreading for acceleration. This has great value in areas such as image processing. OpenMP is such a concurrent programming framework. It supports C language, C++ and Fortran, and compilers that support OpenMP include Sun Studio, Intel Compiler, Microsoft Visual Studio, and GCC.

Our project is to explore how much more efficient parallelism using OpenMP can be compared to traditional serial computing. The example we use is the Monte Carlo method. Using C++ programming language, explore the effectiveness of using OpenMP parallel computing.

## Test Enviornment
- AWS EC2
- Instance Type: c4.4xlarge
- 16 vCPU
- Maximum thread: 16
- Price: 0.796 USD per hour

## Useful links
<a href="https://mpitutorial.com/tutorials/launching-an-amazon-ec2-mpi-cluster/">Launching an Amazon EC2 MPI Cluster</a>

## Project website
<a href="https://dwightu.github.io/COMP-5704/">Explore how the OpenMP can improve application performance
</a>
