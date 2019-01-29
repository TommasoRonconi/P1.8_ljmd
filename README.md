# P1.8_ljmd
# Jesus Espinoza, Herbert Nguruwe, Tommaso Ronconi, Matteo Zampieri

## MPI benchmarking

We test the performance of our MPI parallelization by collecting the time spent by the `force()` function (declared in [compute_force.h](include/compute_force.h) and defined in [compute_force.c](src/compute_force.c)) both with and without the communication part.
We then compute the **strong scaling** averaging between 10 runs per number of processors, the results are shown in the following plots, were we also show with a black dashed line the ideal linear scaling.

| ![](MPI-benchmark/strong_scaling_comm+comp.png)         | ![](MPI-benchmark/strong_scaling_comp.png)         |
| ------------------------------------------------------- | -------------------------------------------------- |
| [full size](MPI-benchmark/strong_scaling_comm+comp.png) | [full size](MPI-benchmark/strong_scaling_comp.png) |

It can be noticed that, even though the computation part scales better for the smaller system size (blue curve), the overall performance is better for larger size of the system, suggesting that the communication time depends less on the size of the system.