####################################

This command creates test_grid
> grid_get 0 10 1 0 10 1 test_grid

if you can see something like this:
> grid: (0.00 <-> 10.00) / 1.00; (0.00 <-> 10.00) / 1.00.
then grid is created succesfully i.e. variable surfit_grid is initialized

to ask about surfit_grid existance type
> grid_check
if surfit_grid exisits you will see the answer:
> 1

Now try to check some grid properties 
> grid_getCountX
> 11
> grid_getCountY
> 11

> grid_getCoordNodeX 1
> 1.0
> grid_getCoordNodeX 5
> 5.0

> grid_getStepX
1.0
> grid_getStepY 
1.0 

###################################

Suppose we have file 3dpoints.txt:

>	3.2	10	7
>	5.1	-7	7
>	3.2	8	7
>	7.6	0.2	7
>	1.8	-6	7

We want to build grid, wich covers these points in XOY plane. 
First of all we must load these points:
> task_read 3dpoints.txt
> Reading task with name "my_points" from file 3dpoints.txt
> task_check
> 1
> task_size
> 5

Create grid 15x15 nodes, coverig all these points:
> grid_get_for_task 15 15
> grid: (1.80 <-> 7.60) / 0.41; (-7.00 <-> 10.00) / 1.21
> grid_check
> 1
> grid_getCountX
> 15
> grid_getCountY
> 15
