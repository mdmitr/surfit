###################################

Suppose we have file 3dpoints.txt:

>	3.2	10	7
>	5.1	-7	7
>	3.2	8	7
>	7.6	0.2	7
>	1.8	-6	7

If file consists of 3 columns use command
> task_read 3dpoints.txt my_poinst
to read it.
> Reading task with name "my_points" from file 3dpoints.txt
> task_check
> 1
> task_size
> 5

######################################

Suppose we have file 3dpoints_names.txt:

> point1	3.2	10	7
> point2	5.1 	-7	7
> point3	13.2	8	7
> point4	7.6	0.2	7
> point5	1.8	-6	7

To read this file it is need to skip first column:

> task_read 3dpoints_names.txt my_points 4 2 3 4
> Reading task with name "my_points" from file 3dpoints_names.txt
> task_check
> 1
> task_size
> 5

######################################

To save task from memory to binary data file use command:

> task_save 3dpoints.dat
> Saving task to file 3dpoints.dat

To load task from binary datafile use command:

> task_load 3dpoints.dat my_points
> loading task "my_points" from file 3dpoints.dat

If you typed wrong task name, you will get error:

> task_load 3dpoints.dat wrong_name
> loading task "wrong_name" from file 3dpoints.dat
> Error! task_load : this file have no task with name wrong_name

#######################################

Here some examples to ask surfit about loaded task.

1. Task existance checking:
> task_check
> 1
If surfit_task does not exists, surfit returns 0.

2. Task name
> task_name
> surfit_task name is "my_points"

3. Amount of points in task
> task_size
> 5

4. Minimum and maximum values:
> task_minx
> 1.8
> task_maxx
> 13.2
> task_miny
> -7.0
> task_maxy
> 10.0
> task_minz
> 7.0
> task_maxz
> 7.0

###########################################