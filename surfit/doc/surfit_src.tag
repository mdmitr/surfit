<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="group">
    <name>internal</name>
    <title>C/C++ functions and variables reference</title>
    <filename>group__internal.html</filename>
    <subgroup>internal_grid</subgroup>
    <subgroup>internal_points</subgroup>
    <subgroup>internal_curv</subgroup>
    <subgroup>internal_misc</subgroup>
    <member kind="function">
      <type>void</type>
      <name>writelog</name>
      <anchor>ga0</anchor>
      <arglist>(int errlevel, const char *tmplt,...)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Tcl_printf</name>
      <anchor>ga1</anchor>
      <arglist>(const char *tmplt,...)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>solver_name</name>
      <anchor>ga2</anchor>
      <arglist>(int code)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_rw_mode</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SURFIT_EXPORT void</type>
      <name>surfit_init_all</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SURFIT_EXPORT void</type>
      <name>surfit_init_variables</name>
      <anchor>ga8</anchor>
      <arglist>(Tcl_Interp *interp)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT Tcl_Interp *</type>
      <name>surfit_interp</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>rw_mode</name>
      <anchor>ga4</anchor>
      <arglist>[7]</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT color_scale *</type>
      <name>surfit_color_scale</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_grid</name>
    <title>grid</title>
    <filename>group__internal__grid.html</filename>
    <subgroup>internal_func</subgroup>
    <subgroup>internal_wfunc</subgroup>
    <subgroup>internal_trend</subgroup>
    <subgroup>internal_defarea</subgroup>
    <member kind="function">
      <type>bool</type>
      <name>_grid_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_grid_save</name>
      <anchor>ga1</anchor>
      <arglist>(grid *grd, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_grid_save_df</name>
      <anchor>ga2</anchor>
      <arglist>(grid *grd, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_grid_load_df_tag_readed</name>
      <anchor>ga3</anchor>
      <arglist>(datafile *df, grid *&amp;grd)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_load_df</name>
      <anchor>ga4</anchor>
      <arglist>(datafile *df, const char *grid_name)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_load</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename, const char *gridname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_get_for_task</name>
      <anchor>ga6</anchor>
      <arglist>(task *tsk, int Xnodes, int Ynodes, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_get_for_task_step</name>
      <anchor>ga7</anchor>
      <arglist>(task *tsk, REAL stepX, REAL stepY, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_get_for_task_and_geom</name>
      <anchor>ga8</anchor>
      <arglist>(const grid *grd, const task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_get_for_func</name>
      <anchor>ga9</anchor>
      <arglist>(func *fnc, int Xnodes, int Ynodes, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_get_for_func_step</name>
      <anchor>ga10</anchor>
      <arglist>(func *fnc, REAL stepX, REAL stepY, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_get</name>
      <anchor>ga11</anchor>
      <arglist>(REAL startX, REAL endX, REAL stepX, REAL startY, REAL endY, REAL stepY, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_grid_from_func</name>
      <anchor>ga12</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>grid *</type>
      <name>_get_surfit_grid</name>
      <anchor>ga13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_grid</name>
      <anchor>ga14</anchor>
      <arglist>(grid *grd)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_func</name>
    <title>func</title>
    <filename>group__internal__func.html</filename>
    <subgroup>int_func_wavan</subgroup>
    <member kind="function">
      <type>bool</type>
      <name>_func_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_func_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *funcname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_func_load_df</name>
      <anchor>ga2</anchor>
      <arglist>(datafile *df, const char *funcname)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_func_load_grd</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *funcname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_unload</name>
      <anchor>ga4</anchor>
      <arglist>(func *&amp;fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_save</name>
      <anchor>ga5</anchor>
      <arglist>(func *fnc, const char *filename, const char *funcname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_save_df</name>
      <anchor>ga6</anchor>
      <arglist>(func *fnc, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_save_grd</name>
      <anchor>ga7</anchor>
      <arglist>(func *fnc, const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_save_xyz</name>
      <anchor>ga8</anchor>
      <arglist>(func *fnc, const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_save_bmp</name>
      <anchor>ga9</anchor>
      <arglist>(func *fnc, const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>task *</type>
      <name>_func_to_task</name>
      <anchor>ga10</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_add_noise</name>
      <anchor>ga11</anchor>
      <arglist>(func *fnc, REAL std)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_func_info</name>
      <anchor>ga12</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_resid</name>
      <anchor>ga13</anchor>
      <arglist>(func *fnc, task *tsk, const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_func_project</name>
      <anchor>ga14</anchor>
      <arglist>(func *fnc, grid *grd)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_func_project</name>
      <anchor>ga15</anchor>
      <arglist>(func *fnc, grid *grd, grid_line *fault_line)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>_func_D1</name>
      <anchor>ga16</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>_func_D2</name>
      <anchor>ga17</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_get_surfit_func</name>
      <anchor>ga18</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_func</name>
      <anchor>ga19</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_funcs</name>
      <anchor>ga20</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_func_gradient</name>
      <anchor>ga21</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>_func_to_wfunc</name>
      <anchor>ga22</anchor>
      <arglist>(func *fnc, REAL weight)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>int_func_wavan</name>
    <title>wavelets section</title>
    <filename>group__int__func__wavan.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_func_decomp</name>
      <anchor>ga0</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_auto_decomp</name>
      <anchor>ga1</anchor>
      <arglist>(func *fnc, REAL eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_recons</name>
      <anchor>ga2</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_func_full_recons</name>
      <anchor>ga3</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_wfunc</name>
    <title>wfunc</title>
    <filename>group__internal__wfunc.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_wfunc_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wfunc_save</name>
      <anchor>ga1</anchor>
      <arglist>(wfunc *fnc, const char *filename, const char *wfuncname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wfunc_save_df</name>
      <anchor>ga2</anchor>
      <arglist>(wfunc *fnc, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>_wfunc_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *wfuncname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>_wfunc_load_df</name>
      <anchor>ga4</anchor>
      <arglist>(datafile *df, const char *wfuncname)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>_wfunc_load_grd</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename, REAL weight, const char *wfuncname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wfunc_unload</name>
      <anchor>ga6</anchor>
      <arglist>(wfunc *&amp;fnc)</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>_wfunc_to_wtask</name>
      <anchor>ga7</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_wfunc_info</name>
      <anchor>ga8</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>_wfunc_project</name>
      <anchor>ga9</anchor>
      <arglist>(wfunc *wfnc, grid *grd)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>_wfunc_project</name>
      <anchor>ga10</anchor>
      <arglist>(wfunc *wfnc, grid *grd, grid_line *fault_line)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_wfunc_to_func</name>
      <anchor>ga11</anchor>
      <arglist>(wfunc *wfnc)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>_get_surfit_wfunc</name>
      <anchor>ga12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_wfunc</name>
      <anchor>ga13</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_wfuncs</name>
      <anchor>ga14</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_trend</name>
    <title>trend</title>
    <filename>group__internal__trend.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_trend_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>_trend_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *funcname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>_trend_load_df</name>
      <anchor>ga2</anchor>
      <arglist>(datafile *df, const char *funcname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_trend_unload</name>
      <anchor>ga3</anchor>
      <arglist>(trend *&amp;fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_trend_save</name>
      <anchor>ga4</anchor>
      <arglist>(trend *fnc, const char *filename, const char *funcname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_trend_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(trend *fnc, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>_trend_load_grd</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, REAL D1, REAL D2, const char *trendname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_trend_info</name>
      <anchor>ga7</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>_trend_project</name>
      <anchor>ga8</anchor>
      <arglist>(trend *trnd, grid *grd)</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>_trend_project</name>
      <anchor>ga9</anchor>
      <arglist>(trend *trnd, grid *grd, grid_line *fault_line)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>_trend_to_func</name>
      <anchor>ga10</anchor>
      <arglist>(trend *trnd)</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>_get_surfit_trend</name>
      <anchor>ga11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_trend</name>
      <anchor>ga12</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_trends</name>
      <anchor>ga13</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_defarea</name>
    <title>defarea</title>
    <filename>group__internal__defarea.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_defarea_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_defarea_save</name>
      <anchor>ga1</anchor>
      <arglist>(defarea *def, const char *filename, const char *defname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_defarea_save_df</name>
      <anchor>ga2</anchor>
      <arglist>(defarea *def, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>_defarea_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *defname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>_defarea_load_df</name>
      <anchor>ga4</anchor>
      <arglist>(datafile *df, const char *defareaname)</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>_defarea_load_grd</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename, const char *defareaname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_defarea_unload</name>
      <anchor>ga6</anchor>
      <arglist>(defarea *&amp;def)</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>_get_surfit_defarea</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_defarea</name>
      <anchor>ga8</anchor>
      <arglist>(defarea *def)</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>_defarea_by_func</name>
      <anchor>ga9</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_defarea_apply_to_func</name>
      <anchor>ga10</anchor>
      <arglist>(defarea *def, func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_defarea_info</name>
      <anchor>ga11</anchor>
      <arglist>(defarea *def)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_points</name>
    <title>points</title>
    <filename>group__internal__points.html</filename>
    <subgroup>internal_task</subgroup>
    <subgroup>internal_wtask</subgroup>
    <member kind="function">
      <type>void</type>
      <name>_sort_points</name>
      <anchor>ga0</anchor>
      <arglist>(points *pnts, std::vector&lt; unsigned int &gt; *nums, REAL **&amp;sortx_begin, REAL **&amp;sortx_end, REAL **&amp;sorty_begin, REAL **&amp;sorty_end)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_points_transform</name>
      <anchor>ga1</anchor>
      <arglist>(points *pnts, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_inverse_points_transform</name>
      <anchor>ga2</anchor>
      <arglist>(points *pnts, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_task</name>
    <title>task</title>
    <filename>group__internal__task.html</filename>
    <member kind="function">
      <type>task *</type>
      <name>_task_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *taskname, int columns, int col1, int col2, int col3, const char *mask, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>task *</type>
      <name>_task_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *taskname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>task *</type>
      <name>_task_load_df</name>
      <anchor>ga2</anchor>
      <arglist>(datafile *df, const char *taskname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_task_write</name>
      <anchor>ga3</anchor>
      <arglist>(task *tsk, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_task_save</name>
      <anchor>ga4</anchor>
      <arglist>(task *tsk, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_task_check</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_task_info</name>
      <anchor>ga6</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>task *</type>
      <name>_get_surfit_task</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_task</name>
      <anchor>ga8</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_tasks</name>
      <anchor>ga9</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>_task_to_wtask</name>
      <anchor>ga10</anchor>
      <arglist>(task *tsk, REAL weight)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_wtask</name>
    <title>wtask</title>
    <filename>group__internal__wtask.html</filename>
    <member kind="function">
      <type>wtask *</type>
      <name>_wtask_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *taskname, int columns, int col1, int col2, int col3, int col4, const char *mask, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>_wtask_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *taskname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>_wtask_load_df</name>
      <anchor>ga2</anchor>
      <arglist>(datafile *df, const char *taskname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wtask_write</name>
      <anchor>ga3</anchor>
      <arglist>(wtask *wtsk, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wtask_save</name>
      <anchor>ga4</anchor>
      <arglist>(wtask *wtsk, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wtask_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(wtask *wtsk, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wtask_check</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_wtask_info</name>
      <anchor>ga7</anchor>
      <arglist>(wtask *wtsk)</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>_get_surfit_wtask</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>_collect_all_wtasks</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_curv</name>
    <title>curv</title>
    <filename>group__internal__curv.html</filename>
    <subgroup>internal_iso</subgroup>
    <subgroup>internal_flt</subgroup>
    <subgroup>internal_area</subgroup>
    <subgroup>internal_cntr</subgroup>
    <subgroup>internal_grid_line</subgroup>
    <member kind="function">
      <type>bool</type>
      <name>_curv_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_curv_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>curv *</type>
      <name>_curv_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *curvname, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_curv_write</name>
      <anchor>ga3</anchor>
      <arglist>(curv *contour, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_curv_save</name>
      <anchor>ga4</anchor>
      <arglist>(curv *contour, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_curv_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(curv *contour, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>curv *</type>
      <name>_curv_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *curvname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>curv *</type>
      <name>_curv_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *curvname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_curv_info</name>
      <anchor>ga8</anchor>
      <arglist>(curv *contour)</arglist>
    </member>
    <member kind="function">
      <type>curv *</type>
      <name>_get_surfit_curv</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_curv</name>
      <anchor>ga10</anchor>
      <arglist>(curv *contour)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_curvs</name>
      <anchor>ga11</anchor>
      <arglist>(curv *contour)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_iso</name>
    <title>iso</title>
    <filename>group__internal__iso.html</filename>
    <subgroup>internal_wiso</subgroup>
    <member kind="function">
      <type>bool</type>
      <name>_iso_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_iso_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iso *</type>
      <name>_iso_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *isoname, REAL value, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_iso_write</name>
      <anchor>ga3</anchor>
      <arglist>(iso *isoline, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_iso_save</name>
      <anchor>ga4</anchor>
      <arglist>(iso *isoline, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_iso_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(iso *isoline, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>iso *</type>
      <name>_iso_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *isoname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>iso *</type>
      <name>_iso_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *isoname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_iso_info</name>
      <anchor>ga8</anchor>
      <arglist>(iso *isoline)</arglist>
    </member>
    <member kind="function">
      <type>iso *</type>
      <name>_get_surfit_iso</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_iso</name>
      <anchor>ga10</anchor>
      <arglist>(iso *isoline)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_isos</name>
      <anchor>ga11</anchor>
      <arglist>(iso *isoline)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_wiso</name>
    <title>wiso</title>
    <filename>group__internal__wiso.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_wiso_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wiso_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wiso *</type>
      <name>_wiso_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *isoname, REAL value, REAL weight, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wiso_write</name>
      <anchor>ga3</anchor>
      <arglist>(wiso *wisoline, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wiso_save</name>
      <anchor>ga4</anchor>
      <arglist>(wiso *wisoline, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wiso_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(wiso *wisoline, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>wiso *</type>
      <name>_wiso_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *wisoname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>wiso *</type>
      <name>_wiso_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *wisoname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_wiso_info</name>
      <anchor>ga8</anchor>
      <arglist>(wiso *wisoline)</arglist>
    </member>
    <member kind="function">
      <type>wiso *</type>
      <name>_get_surfit_wiso</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_wiso</name>
      <anchor>ga10</anchor>
      <arglist>(wiso *wisoline)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_wisos</name>
      <anchor>ga11</anchor>
      <arglist>(wiso *wisoline)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_flt</name>
    <title>flt</title>
    <filename>group__internal__flt.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_flt_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_flt_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>flt *</type>
      <name>_flt_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *fltname, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_flt_write</name>
      <anchor>ga3</anchor>
      <arglist>(flt *fault, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_flt_save</name>
      <anchor>ga4</anchor>
      <arglist>(flt *fault, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_flt_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(flt *fault, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>flt *</type>
      <name>_flt_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *fltname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>flt *</type>
      <name>_flt_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *fltname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_flt_info</name>
      <anchor>ga8</anchor>
      <arglist>(flt *fault)</arglist>
    </member>
    <member kind="function">
      <type>flt *</type>
      <name>_get_surfit_flt</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_flt</name>
      <anchor>ga10</anchor>
      <arglist>(flt *fault)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_flts</name>
      <anchor>ga11</anchor>
      <arglist>(flt *fault)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_area</name>
    <title>area</title>
    <filename>group__internal__area.html</filename>
    <subgroup>internal_warea</subgroup>
    <member kind="function">
      <type>bool</type>
      <name>_area_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_area_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>area *</type>
      <name>_area_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *areaname, REAL value, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_area_write</name>
      <anchor>ga3</anchor>
      <arglist>(area *arealine, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_area_save</name>
      <anchor>ga4</anchor>
      <arglist>(area *arealine, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_area_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(area *ar, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>area *</type>
      <name>_area_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *areaname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>area *</type>
      <name>_area_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *areaname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_area_info</name>
      <anchor>ga8</anchor>
      <arglist>(area *arealine)</arglist>
    </member>
    <member kind="function">
      <type>area *</type>
      <name>_get_surfit_area</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_area</name>
      <anchor>ga10</anchor>
      <arglist>(area *arealine)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_areas</name>
      <anchor>ga11</anchor>
      <arglist>(area *arealine)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_warea</name>
    <title>warea</title>
    <filename>group__internal__warea.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_warea_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_warea_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>warea *</type>
      <name>_warea_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *wareaname, REAL value, REAL weight, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_warea_write</name>
      <anchor>ga3</anchor>
      <arglist>(warea *warealine, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_warea_save</name>
      <anchor>ga4</anchor>
      <arglist>(warea *warealine, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_warea_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(warea *ar, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>warea *</type>
      <name>_warea_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *wareaname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>warea *</type>
      <name>_warea_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *wareaname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_warea_info</name>
      <anchor>ga8</anchor>
      <arglist>(warea *warealine)</arglist>
    </member>
    <member kind="function">
      <type>warea *</type>
      <name>_get_surfit_warea</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_warea</name>
      <anchor>ga10</anchor>
      <arglist>(warea *warealine)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_wareas</name>
      <anchor>ga11</anchor>
      <arglist>(warea *warealine)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_cntr</name>
    <title>cntr</title>
    <filename>group__internal__cntr.html</filename>
    <subgroup>internal_wcntr</subgroup>
    <member kind="function">
      <type>bool</type>
      <name>_cntr_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_cntr_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>cntr *</type>
      <name>_cntr_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *cntrname, int columns, int col1, int col2, int col3, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_cntr_write</name>
      <anchor>ga3</anchor>
      <arglist>(cntr *contour, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_cntr_save</name>
      <anchor>ga4</anchor>
      <arglist>(cntr *contour, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_cntr_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(cntr *contour, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>cntr *</type>
      <name>_cntr_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *cntrname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>cntr *</type>
      <name>_cntr_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *cntrname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_cntr_info</name>
      <anchor>ga8</anchor>
      <arglist>(cntr *contour)</arglist>
    </member>
    <member kind="function">
      <type>cntr *</type>
      <name>_get_surfit_cntr</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_cntr</name>
      <anchor>ga10</anchor>
      <arglist>(cntr *contour)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_cntrs</name>
      <anchor>ga11</anchor>
      <arglist>(cntr *contour)</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>_cntr_to_wcntr</name>
      <anchor>ga12</anchor>
      <arglist>(cntr *contour, REAL weight)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_wcntr</name>
    <title>wcntr</title>
    <filename>group__internal__wcntr.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_wcntr_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wcntr_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>_wcntr_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *cntrname, REAL weight, int columns, int col1, int col2, int col3, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wcntr_save</name>
      <anchor>ga3</anchor>
      <arglist>(wcntr *wcnt, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_wcntr_save_df</name>
      <anchor>ga4</anchor>
      <arglist>(wcntr *wcontour, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>_wcntr_load</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename, const char *cntrname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>_wcntr_load_df</name>
      <anchor>ga6</anchor>
      <arglist>(datafile *df, const char *cntrname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_wcntr_info</name>
      <anchor>ga7</anchor>
      <arglist>(wcntr *wcontour)</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>_get_surfit_wcntr</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_wcntr</name>
      <anchor>ga9</anchor>
      <arglist>(wcntr *wcontour)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_surfit_wcntrs</name>
      <anchor>ga10</anchor>
      <arglist>(wcntr *wcontour)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_grid_line</name>
    <title>grid_line</title>
    <filename>group__internal__grid__line.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_grid_line_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_grid_line_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_grid_line_write</name>
      <anchor>ga2</anchor>
      <arglist>(grid_line *contour, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_grid_line_save</name>
      <anchor>ga3</anchor>
      <arglist>(grid_line *contour, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_grid_line_info</name>
      <anchor>ga4</anchor>
      <arglist>(grid_line *contour)</arglist>
    </member>
    <member kind="function">
      <type>grid_line *</type>
      <name>_get_surfit_grid_line</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_surfit_grid_line</name>
      <anchor>ga6</anchor>
      <arglist>(grid_line *contour)</arglist>
    </member>
    <member kind="function">
      <type>SURFIT_EXPORT curv *</type>
      <name>_grid_line_to_curv</name>
      <anchor>ga7</anchor>
      <arglist>(grid_line *gline)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_misc</name>
    <title>miscellaneous</title>
    <filename>group__internal__misc.html</filename>
  </compound>
  <compound kind="group">
    <name>tcl</name>
    <title>Tcl commands and variables reference</title>
    <filename>group__tcl.html</filename>
    <subgroup>surfit_variables</subgroup>
    <subgroup>tcl_grid</subgroup>
    <subgroup>tcl_opoints</subgroup>
    <subgroup>tcl_points</subgroup>
    <subgroup>tcl_curves</subgroup>
    <subgroup>tcl_whole</subgroup>
    <subgroup>tcl_dynamic</subgroup>
    <subgroup>tcl_log</subgroup>
    <subgroup>tcl_file</subgroup>
    <member kind="function">
      <type>void</type>
      <name>clear_data</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mem_info</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rw_mode_set</name>
      <anchor>ga3</anchor>
      <arglist>(const char *new_mode)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>rw_mode_get</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>surfit_variables</name>
    <title>surfit variables</title>
    <filename>group__surfit__variables.html</filename>
    <subgroup>surfit_data_variables</subgroup>
    <subgroup>surfit_gl_variables</subgroup>
    <member kind="variable">
      <type>SURFIT_EXPORT REAL</type>
      <name>undef_value</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT float</type>
      <name>tol</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>datafile_mode</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>priority</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>solver_code</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT REAL</type>
      <name>sor_omega</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT REAL</type>
      <name>ssor_omega</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT bool</type>
      <name>write_mat</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT char *</type>
      <name>map_name</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>surfit_data_variables</name>
    <title>surfit data variables</title>
    <filename>group__surfit__data__variables.html</filename>
    <subgroup>surfit_variables_collections</subgroup>
    <member kind="variable">
      <type>SURFIT_EXPORT area *</type>
      <name>surfit_area</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT cntr *</type>
      <name>surfit_cntr</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT completer *</type>
      <name>surfit_completer</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT curv *</type>
      <name>surfit_curv</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT defarea *</type>
      <name>surfit_defarea</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT dynamic *</type>
      <name>surfit_dynamic</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT fill_with *</type>
      <name>surfit_fill_with</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT flt *</type>
      <name>surfit_flt</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT func *</type>
      <name>surfit_func</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT grid_line *</type>
      <name>surfit_grid_line</name>
      <anchor>ga9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT grid *</type>
      <name>surfit_grid</name>
      <anchor>ga10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT iso *</type>
      <name>surfit_iso</name>
      <anchor>ga11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT task *</type>
      <name>surfit_task</name>
      <anchor>ga12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT trend *</type>
      <name>surfit_trend</name>
      <anchor>ga13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT warea *</type>
      <name>surfit_warea</name>
      <anchor>ga14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT wcntr *</type>
      <name>surfit_wcntr</name>
      <anchor>ga15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT wfunc *</type>
      <name>surfit_wfunc</name>
      <anchor>ga16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT wiso *</type>
      <name>surfit_wiso</name>
      <anchor>ga17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT wtask *</type>
      <name>surfit_wtask</name>
      <anchor>ga18</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>surfit_variables_collections</name>
    <title>collections of surfit variables</title>
    <filename>group__surfit__variables__collections.html</filename>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; area * &gt; *</type>
      <name>surfit_areas</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; cntr * &gt; *</type>
      <name>surfit_cntrs</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; curv * &gt; *</type>
      <name>surfit_curvs</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; defarea * &gt; *</type>
      <name>surfit_defareas</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; dynamic * &gt; *</type>
      <name>surfit_dynamics</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; flt * &gt; *</type>
      <name>surfit_flts</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; func * &gt; *</type>
      <name>surfit_funcs</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; iso * &gt; *</type>
      <name>surfit_isos</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; task * &gt; *</type>
      <name>surfit_tasks</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; trend * &gt; *</type>
      <name>surfit_trends</name>
      <anchor>ga9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; warea * &gt; *</type>
      <name>surfit_wareas</name>
      <anchor>ga10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; wcntr * &gt; *</type>
      <name>surfit_wcntrs</name>
      <anchor>ga11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; wfunc * &gt; *</type>
      <name>surfit_wfuncs</name>
      <anchor>ga12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; wiso * &gt; *</type>
      <name>surfit_wisos</name>
      <anchor>ga13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT std::vector&lt; wtask * &gt; *</type>
      <name>surfit_wtasks</name>
      <anchor>ga14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>surfit_gl_variables</name>
    <title>surfit variables for OpenGL drawing</title>
    <filename>group__surfit__gl__variables.html</filename>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>bg_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>bg_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>bg_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>bg_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>grid_amount_x</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>grid_amount_y</name>
      <anchor>ga5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>point_size</name>
      <anchor>ga6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT float</type>
      <name>x_shift</name>
      <anchor>ga7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT float</type>
      <name>y_shift</name>
      <anchor>ga8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT float</type>
      <name>scale</name>
      <anchor>ga9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT float</type>
      <name>z_scale</name>
      <anchor>ga10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>axis_labels</name>
      <anchor>ga11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>light</name>
      <anchor>ga12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>smooth</name>
      <anchor>ga13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>isoline</name>
      <anchor>ga14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_wtask</name>
      <anchor>ga15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_func</name>
      <anchor>ga16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_wfunc</name>
      <anchor>ga17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_trend</name>
      <anchor>ga18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_piso</name>
      <anchor>ga19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_pcntr</name>
      <anchor>ga20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_parea</name>
      <anchor>ga21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_grid</name>
      <anchor>ga22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_defarea</name>
      <anchor>ga23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>use_projections</name>
      <anchor>ga24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>fix_axes</name>
      <anchor>ga25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT double</type>
      <name>minx</name>
      <anchor>ga26</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT double</type>
      <name>maxx</name>
      <anchor>ga27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT double</type>
      <name>miny</name>
      <anchor>ga28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT double</type>
      <name>maxy</name>
      <anchor>ga29</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT double</type>
      <name>minz</name>
      <anchor>ga30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT double</type>
      <name>maxz</name>
      <anchor>ga31</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_grid</name>
    <title>equidistant grid (grid)</title>
    <filename>group__tcl__grid.html</filename>
    <subgroup>tcl_grid_save_load</subgroup>
    <subgroup>tcl_grid_create</subgroup>
    <subgroup>tcl_grid_other</subgroup>
    <subgroup>tcl_grid_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_grid_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__grid__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>grid_save</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *gridname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>grid_unload</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_grid_create</name>
    <title>constructing grid</title>
    <filename>group__tcl__grid__create.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>grid_auto</name>
      <anchor>ga0</anchor>
      <arglist>(REAL stepX=0, REAL stepY=0, REAL percent=2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_auto2</name>
      <anchor>ga1</anchor>
      <arglist>(REAL stepX, REAL stepY, REAL percent=2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_get</name>
      <anchor>ga2</anchor>
      <arglist>(REAL startX, REAL endX, REAL stepX, REAL startY, REAL endY, REAL stepY, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_get2</name>
      <anchor>ga3</anchor>
      <arglist>(REAL startX, REAL endX, REAL stepX, REAL startY, REAL endY, REAL stepY, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_get_for_task</name>
      <anchor>ga4</anchor>
      <arglist>(int Xnodes, int Ynodes, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_get_for_task_step</name>
      <anchor>ga5</anchor>
      <arglist>(REAL stepX, REAL stepY, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_get_from_func</name>
      <anchor>ga6</anchor>
      <arglist>(const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_get_for_func</name>
      <anchor>ga7</anchor>
      <arglist>(int Xnodes, int Ynodes, const char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_get_for_func_step</name>
      <anchor>ga8</anchor>
      <arglist>(REAL stepX, REAL stepY, const char *name=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_grid_other</name>
    <title>other operations</title>
    <filename>group__tcl__grid__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>grid_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>grid_info</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>grid_getCountX</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>grid_getCountY</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>grid_getCoordNodeX</name>
      <anchor>ga4</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>grid_getCoordNodeY</name>
      <anchor>ga5</anchor>
      <arglist>(int j)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>grid_getStepX</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>grid_getStepY</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_grid_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__grid__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>grid_show</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename=NULL, const char *gridname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>grid_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>grid_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>grid_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>grid_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_opoints</name>
    <title>ordered points</title>
    <filename>group__tcl__opoints.html</filename>
    <subgroup>tcl_func</subgroup>
    <subgroup>tcl_wfunc</subgroup>
    <subgroup>tcl_trend</subgroup>
    <subgroup>tcl_defarea</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_func</name>
    <title>function for interpolation (func)</title>
    <filename>group__tcl__func.html</filename>
    <subgroup>tcl_func_save_load</subgroup>
    <subgroup>tcl_func_math</subgroup>
    <subgroup>tcl_func_wavan</subgroup>
    <subgroup>tcl_func_conv</subgroup>
    <subgroup>tcl_func_other</subgroup>
    <subgroup>tcl_funcs</subgroup>
    <subgroup>tcl_func_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_func_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__func__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>func_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_load_grd</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>func_unload</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_save</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_save_grd</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_save_xyz</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_save_bmp</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_func_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__func__math.html</filename>
    <member kind="function">
      <type>REAL</type>
      <name>func_getValue</name>
      <anchor>ga0</anchor>
      <arglist>(REAL x, REAL y)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_resid</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_D1</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_D2</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_gradient</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_project</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_add_noise</name>
      <anchor>ga6</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_minz</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_maxz</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_mean</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_std</name>
      <anchor>ga10</anchor>
      <arglist>(REAL mean)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_sum</name>
      <anchor>ga11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_plus</name>
      <anchor>ga12</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_minus</name>
      <anchor>ga13</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_minus_undef</name>
      <anchor>ga14</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_mult</name>
      <anchor>ga15</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_div</name>
      <anchor>ga16</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_set</name>
      <anchor>ga17</anchor>
      <arglist>(func *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_plus_real</name>
      <anchor>ga18</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_mult_real</name>
      <anchor>ga19</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_div_real</name>
      <anchor>ga20</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_set_real</name>
      <anchor>ga21</anchor>
      <arglist>(REAL val)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_func_wavan</name>
    <title>wavelet analysis</title>
    <filename>group__tcl__func__wavan.html</filename>
    <member kind="function">
      <type>int</type>
      <name>func_get_details_level</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_decomp</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_auto_decomp</name>
      <anchor>ga2</anchor>
      <arglist>(REAL eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_recons</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_full_recons</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wfunc_get_details_level</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_func_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__func__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>func_to_task</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_to_defarea</name>
      <anchor>ga1</anchor>
      <arglist>(REAL true_from, REAL true_to)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_to_defareas</name>
      <anchor>ga2</anchor>
      <arglist>(REAL true_from, REAL true_to)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_to_trend</name>
      <anchor>ga3</anchor>
      <arglist>(REAL D1, REAL D2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_to_trends</name>
      <anchor>ga4</anchor>
      <arglist>(REAL D1, REAL D2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_to_wfunc</name>
      <anchor>ga5</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_to_wfuncs</name>
      <anchor>ga6</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_to_funcs</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_func_other</name>
    <title>other operations</title>
    <filename>group__tcl__func__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>func_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>func_getCountX</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>func_getCountY</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_getStepX</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_getStepY</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_undef</name>
      <anchor>ga5</anchor>
      <arglist>(REAL new_undef_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>func_info</name>
      <anchor>ga6</anchor>
      <arglist>(func *fnc=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>func_name</name>
      <anchor>ga7</anchor>
      <arglist>(const char *new_name, func *fnc=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_funcs</name>
    <title>operations with func collections</title>
    <filename>group__tcl__funcs.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>funcs_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>funcs_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>funcs_load</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>funcs_load_grd</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *funcname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>funcs_unload</name>
      <anchor>ga4</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>funcs_at</name>
      <anchor>ga5</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>funcs_first</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>func *</type>
      <name>funcs_last</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>funcs_size</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>funcs_info</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_func_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__func__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>func_show</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename=NULL, const char *funcname=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wfunc</name>
    <title>function for approximation (wfunc)</title>
    <filename>group__tcl__wfunc.html</filename>
    <subgroup>tcl_wfunc_save_load</subgroup>
    <subgroup>tcl_wfunc_math</subgroup>
    <subgroup>tcl_wfunc_wavan</subgroup>
    <subgroup>tcl_wfunc_conv</subgroup>
    <subgroup>tcl_wfunc_other</subgroup>
    <subgroup>tcl_wfuncs</subgroup>
    <subgroup>tcl_wfunc_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_wfunc_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__wfunc__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *wfuncname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_load_grd</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, REAL weight, const char *wfuncname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wfunc_unload</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_save</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *wfuncname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_save_grd</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_save_xyz</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_save_bmp</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wfunc_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__wfunc__math.html</filename>
    <member kind="function">
      <type>REAL</type>
      <name>wfunc_getValue</name>
      <anchor>ga0</anchor>
      <arglist>(REAL x, REAL y)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_add_noise</name>
      <anchor>ga1</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wfunc_minz</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wfunc_maxz</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wfunc_mean</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wfunc_std</name>
      <anchor>ga5</anchor>
      <arglist>(REAL mean)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_plus</name>
      <anchor>ga6</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_minus</name>
      <anchor>ga7</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_mult</name>
      <anchor>ga8</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_div</name>
      <anchor>ga9</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_set</name>
      <anchor>ga10</anchor>
      <arglist>(wfunc *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_plus_real</name>
      <anchor>ga11</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_mult_real</name>
      <anchor>ga12</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_div_real</name>
      <anchor>ga13</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_set_real</name>
      <anchor>ga14</anchor>
      <arglist>(REAL val)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wfunc_wavan</name>
    <title>wavelet analysis</title>
    <filename>group__tcl__wfunc__wavan.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_decomp</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_auto_decomp</name>
      <anchor>ga1</anchor>
      <arglist>(REAL eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_recons</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_full_recons</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wfunc_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__wfunc__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_to_wtask</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_to_func</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_to_funcs</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_to_wfuncs</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wfunc_other</name>
    <title>other operations</title>
    <filename>group__tcl__wfunc__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wfunc_getCountX</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wfunc_getCountY</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wfunc_getStepX</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wfunc_getStepY</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_undef</name>
      <anchor>ga5</anchor>
      <arglist>(REAL new_undef_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wfunc_info</name>
      <anchor>ga6</anchor>
      <arglist>(wfunc *fnc=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfunc_name</name>
      <anchor>ga7</anchor>
      <arglist>(const char *new_name, wfunc *wfnc=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wfuncs</name>
    <title>operations with wfunc collections</title>
    <filename>group__tcl__wfuncs.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wfuncs_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfuncs_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfuncs_load</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *wfuncname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfuncs_load_grd</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, REAL weight, const char *wfuncname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wfuncs_unload</name>
      <anchor>ga4</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>wfuncs_at</name>
      <anchor>ga5</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>wfuncs_first</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wfunc *</type>
      <name>wfuncs_last</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wfuncs_size</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wfuncs_info</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wfunc_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__wfunc__gl.html</filename>
  </compound>
  <compound kind="group">
    <name>tcl_trend</name>
    <title>trend function (trend)</title>
    <filename>group__tcl__trend.html</filename>
    <subgroup>tcl_trend_save_load</subgroup>
    <subgroup>tcl_trend_math</subgroup>
    <subgroup>tcl_trend_wavan</subgroup>
    <subgroup>tcl_trend_conv</subgroup>
    <subgroup>tcl_trend_other</subgroup>
    <subgroup>tcl_trends</subgroup>
    <subgroup>tcl_trend_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_trend_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__trend__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>trend_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_load_grd</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, REAL D1=1, REAL D2=0, const char *trendname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trend_unload</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_save</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_save_grd</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_save_xyz</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_save_bmp</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_trend_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__trend__math.html</filename>
    <member kind="function">
      <type>REAL</type>
      <name>trend_getValue</name>
      <anchor>ga0</anchor>
      <arglist>(REAL x, REAL y)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_resid</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_project</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>trend_minz</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>trend_maxz</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>trend_mean</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>trend_std</name>
      <anchor>ga6</anchor>
      <arglist>(REAL mean)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_plus</name>
      <anchor>ga7</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_minus</name>
      <anchor>ga8</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_minus_undef</name>
      <anchor>ga9</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_mult</name>
      <anchor>ga10</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_div</name>
      <anchor>ga11</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_set</name>
      <anchor>ga12</anchor>
      <arglist>(trend *fnc)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_plus_real</name>
      <anchor>ga13</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_minus_real</name>
      <anchor>ga14</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_mult_real</name>
      <anchor>ga15</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_div_real</name>
      <anchor>ga16</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_set_real</name>
      <anchor>ga17</anchor>
      <arglist>(REAL val)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_trend_wavan</name>
    <title>wavelet analysis</title>
    <filename>group__tcl__trend__wavan.html</filename>
    <member kind="function">
      <type>int</type>
      <name>trend_get_details_level</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_decomp</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_auto_decomp</name>
      <anchor>ga2</anchor>
      <arglist>(REAL eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_recons</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_full_recons</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_trend_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__trend__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>trend_to_func</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_to_funcs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_to_trends</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_trend_other</name>
    <title>other operations</title>
    <filename>group__tcl__trend__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>trend_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trend_getCountX</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trend_getCountY</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>trend_getStepX</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>trend_getStepY</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_undef</name>
      <anchor>ga5</anchor>
      <arglist>(REAL new_undef_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trend_info</name>
      <anchor>ga6</anchor>
      <arglist>(trend *fnc=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trend_name</name>
      <anchor>ga7</anchor>
      <arglist>(const char *new_name, trend *trnd=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_trends</name>
    <title>operations with trend collections</title>
    <filename>group__tcl__trends.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>trends_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trends_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trends_load</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *trendname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trends_load_grd</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, REAL D1, REAL D2, const char *trendname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trends_unload</name>
      <anchor>ga4</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>trends_at</name>
      <anchor>ga5</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>trends_first</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>trend *</type>
      <name>trends_last</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trends_size</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trends_info</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_trend_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__trend__gl.html</filename>
  </compound>
  <compound kind="group">
    <name>tcl_defarea</name>
    <title>definition area (defarea)</title>
    <filename>group__tcl__defarea.html</filename>
    <subgroup>tcl_defarea_save_load</subgroup>
    <subgroup>tcl_defarea_math</subgroup>
    <subgroup>tcl_defarea_conv</subgroup>
    <subgroup>tcl_defarea_other</subgroup>
    <subgroup>tcl_defareas</subgroup>
    <subgroup>tcl_defarea_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_defarea_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__defarea__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>defarea_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *defname=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>defarea_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *defname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_save_grd</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_save_xyz</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_defarea_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__defarea__math.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>defarea_getValue</name>
      <anchor>ga0</anchor>
      <arglist>(REAL x, REAL y)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_and</name>
      <anchor>ga1</anchor>
      <arglist>(defarea *def)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_not</name>
      <anchor>ga2</anchor>
      <arglist>(defarea *def=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_or</name>
      <anchor>ga3</anchor>
      <arglist>(defarea *def)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_xor</name>
      <anchor>ga4</anchor>
      <arglist>(defarea *def)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_defarea_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__defarea__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>defarea_to_func</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_to_funcs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_to_defareas</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_defarea_other</name>
    <title>other operations</title>
    <filename>group__tcl__defarea__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>defarea_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_by_func</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_apply_to_func</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defarea_name</name>
      <anchor>ga3</anchor>
      <arglist>(const char *new_name, defarea *def=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_defareas</name>
    <title>operations with defarea collections</title>
    <filename>group__tcl__defareas.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>defareas_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defareas_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defareas_load</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *defareaname=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defareas_load_grd</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *defareaname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>defareas_unload</name>
      <anchor>ga4</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>defareas_at</name>
      <anchor>ga5</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>defareas_first</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>defarea *</type>
      <name>defareas_last</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>defareas_size</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>defareas_info</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_defarea_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__defarea__gl.html</filename>
  </compound>
  <compound kind="group">
    <name>tcl_points</name>
    <title>scattered points</title>
    <filename>group__tcl__points.html</filename>
    <subgroup>tcl_task</subgroup>
    <subgroup>tcl_wtask</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_task</name>
    <title>scattered data-points for interpolation (task)</title>
    <filename>group__tcl__task.html</filename>
    <subgroup>tcl_task_save_load</subgroup>
    <subgroup>tcl_task_math</subgroup>
    <subgroup>tcl_task_conv</subgroup>
    <subgroup>tcl_task_other</subgroup>
    <subgroup>tcl_tasks</subgroup>
    <subgroup>tcl_task_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_task_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__task__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>task_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_read</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *taskname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_unload</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_save</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_write</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename, const char *delimiter=&quot;\t&quot;)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_task_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__task__math.html</filename>
    <member kind="function">
      <type>void</type>
      <name>task_transform</name>
      <anchor>ga0</anchor>
      <arglist>(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_inverse_transform</name>
      <anchor>ga1</anchor>
      <arglist>(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_filter_by_defarea</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_filter_by_func</name>
      <anchor>ga3</anchor>
      <arglist>(REAL eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_update_by_func</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_minx</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_maxx</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_miny</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_maxy</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_minz</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_maxz</name>
      <anchor>ga10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_add_noise</name>
      <anchor>ga11</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_mean</name>
      <anchor>ga12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>task_std</name>
      <anchor>ga13</anchor>
      <arglist>(REAL mean)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_plus</name>
      <anchor>ga14</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_minus</name>
      <anchor>ga15</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_mult</name>
      <anchor>ga16</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_div</name>
      <anchor>ga17</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_set</name>
      <anchor>ga18</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_plus_real</name>
      <anchor>ga19</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_minus_real</name>
      <anchor>ga20</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_mult_real</name>
      <anchor>ga21</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_div_real</name>
      <anchor>ga22</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_set_real</name>
      <anchor>ga23</anchor>
      <arglist>(REAL val)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_task_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__task__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>task_to_wtask</name>
      <anchor>ga0</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_to_wtasks</name>
      <anchor>ga1</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_to_tasks</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_task_other</name>
    <title>other operations</title>
    <filename>group__tcl__task__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>task_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>task_size</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name, task *tsk=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_tasks</name>
    <title>operations with task collections</title>
    <filename>group__tcl__tasks.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>tasks_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>tasks_read</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *taskname=NULL, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>tasks_delall</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>tasks_del</name>
      <anchor>ga3</anchor>
      <arglist>(int pos=-1)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_concat</name>
      <anchor>ga4</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function">
      <type>task *</type>
      <name>tasks_at</name>
      <anchor>ga5</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>task *</type>
      <name>tasks_first</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>task *</type>
      <name>tasks_last</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>tasks_size</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>tasks_info</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_task_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__task__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>task_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>task_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename=NULL, const char *taskname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>task_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>task_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>task_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>task_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_task</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wtask</name>
    <title>scattered data-points for approximation (wtask)</title>
    <filename>group__tcl__wtask.html</filename>
    <subgroup>tcl_wtask_save_load</subgroup>
    <subgroup>tcl_wtask_math</subgroup>
    <subgroup>tcl_wtask_conv</subgroup>
    <subgroup>tcl_wtask_other</subgroup>
    <subgroup>tcl_wtasks</subgroup>
    <subgroup>tcl_wtask_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_wtask_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__wtask__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wtask_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wtask_read</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *taskname, int columns, int col1, int col2, int col3, int col4, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wtask_unload</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_save</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_write</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename, const char *delimiter=&quot;\t&quot;)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wtask_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__wtask__math.html</filename>
    <member kind="function">
      <type>void</type>
      <name>wtask_transform</name>
      <anchor>ga0</anchor>
      <arglist>(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wtask_inverse_transform</name>
      <anchor>ga1</anchor>
      <arglist>(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_filter_by_defarea</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_filter_by_func</name>
      <anchor>ga3</anchor>
      <arglist>(REAL eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_update_by_func</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_minx</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_maxx</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_miny</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_maxy</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_minz</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_maxz</name>
      <anchor>ga10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_add_noise</name>
      <anchor>ga11</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_mean</name>
      <anchor>ga12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>wtask_std</name>
      <anchor>ga13</anchor>
      <arglist>(REAL mean)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_plus</name>
      <anchor>ga14</anchor>
      <arglist>(wtask *wtsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_minus</name>
      <anchor>ga15</anchor>
      <arglist>(wtask *wtsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_mult</name>
      <anchor>ga16</anchor>
      <arglist>(wtask *wtsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_div</name>
      <anchor>ga17</anchor>
      <arglist>(wtask *wtsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_set</name>
      <anchor>ga18</anchor>
      <arglist>(wtask *wtsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_plus_real</name>
      <anchor>ga19</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_minus_real</name>
      <anchor>ga20</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_mult_real</name>
      <anchor>ga21</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_div_real</name>
      <anchor>ga22</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_set_real</name>
      <anchor>ga23</anchor>
      <arglist>(REAL val)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wtask_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__wtask__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wtask_to_task</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_to_tasks</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_to_wtasks</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wtask_other</name>
    <title>other operations</title>
    <filename>group__tcl__wtask__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wtask_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wtask_size</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name, wtask *wtsk=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wtasks</name>
    <title>operations with wtask collections</title>
    <filename>group__tcl__wtasks.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wtasks_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtasks_read</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *taskname=NULL, int columns=4, int col1=1, int col2=2, int col3=3, int col4=4, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtasks_delall</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtasks_del</name>
      <anchor>ga3</anchor>
      <arglist>(int pos=-1)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wtask_concat</name>
      <anchor>ga4</anchor>
      <arglist>(wtask *wtsk)</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>wtasks_at</name>
      <anchor>ga5</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>wtasks_first</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wtask *</type>
      <name>wtasks_last</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wtasks_size</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wtasks_info</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wtask_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__wtask__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>wtask_color</name>
      <anchor>ga4</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wtask_show</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename=NULL, const char *wtaskname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wtask_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wtask_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wtask_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wtask_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_curves</name>
    <title>curves</title>
    <filename>group__tcl__curves.html</filename>
    <subgroup>tcl_curv</subgroup>
    <subgroup>tcl_iso</subgroup>
    <subgroup>tcl_wiso</subgroup>
    <subgroup>tcl_flt</subgroup>
    <subgroup>tcl_area</subgroup>
    <subgroup>tcl_warea</subgroup>
    <subgroup>tcl_cntr</subgroup>
    <subgroup>tcl_wcntr</subgroup>
    <subgroup>tcl_grid_line</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_curv</name>
    <title>curve (curv)</title>
    <filename>group__tcl__curv.html</filename>
    <subgroup>tcl_curv_save_load</subgroup>
    <subgroup>tcl_curv_conv</subgroup>
    <subgroup>tcl_curv_other</subgroup>
    <subgroup>tcl_curvs</subgroup>
    <subgroup>tcl_curv_gl</subgroup>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>curv_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_curv_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__curv__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>curv_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *curvname=NULL, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *curvname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *curvname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_curv_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__curv__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_iso</name>
      <anchor>ga0</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_isos</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_wiso</name>
      <anchor>ga2</anchor>
      <arglist>(REAL value, REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_wisos</name>
      <anchor>ga3</anchor>
      <arglist>(REAL value, REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_flt</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_flts</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_area</name>
      <anchor>ga6</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_areas</name>
      <anchor>ga7</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_warea</name>
      <anchor>ga8</anchor>
      <arglist>(REAL value, REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_to_wareas</name>
      <anchor>ga9</anchor>
      <arglist>(REAL value, REAL weight)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_curv_other</name>
    <title>other operations</title>
    <filename>group__tcl__curv__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>curv_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_set</name>
      <anchor>ga1</anchor>
      <arglist>(curv *contour)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curv_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *name=NULL, curv *crv=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_curvs</name>
    <title>operations with curv collections</title>
    <filename>group__tcl__curvs.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>curvs_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curvs_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curvs_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *curvname, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>curvs_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *curvname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>curv *</type>
      <name>curvs_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>curv *</type>
      <name>curvs_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>curv *</type>
      <name>curvs_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>curvs_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>curvs_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_curv_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__curv__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>curv_color</name>
      <anchor>ga4</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>curv_show</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename=NULL, const char *curvname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>curv_color_green</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>curv_color_blue</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>curv_color_alpha</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_curv</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_iso</name>
    <title>isoline for interpolation (iso)</title>
    <filename>group__tcl__iso.html</filename>
    <subgroup>tcl_iso_save_load</subgroup>
    <subgroup>tcl_iso_conv</subgroup>
    <subgroup>tcl_iso_other</subgroup>
    <subgroup>tcl_isos</subgroup>
    <subgroup>tcl_iso_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_iso_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__iso__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>iso_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *isoname, REAL value, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *isoname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *isoname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_iso_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__iso__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>iso_to_wiso</name>
      <anchor>ga0</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_to_wisos</name>
      <anchor>ga1</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_to_curv</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_to_curvs</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_to_isos</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_iso_other</name>
    <title>other operations</title>
    <filename>group__tcl__iso__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>iso_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_value</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_set</name>
      <anchor>ga2</anchor>
      <arglist>(iso *isoline)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>iso_name</name>
      <anchor>ga3</anchor>
      <arglist>(const char *new_name=NULL, iso *isoline=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_isos</name>
    <title>operations with iso collections</title>
    <filename>group__tcl__isos.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>isos_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isos_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isos_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *isoname, REAL value, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isos_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *isoname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>iso *</type>
      <name>isos_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>iso *</type>
      <name>isos_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>iso *</type>
      <name>isos_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>isos_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>isos_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_iso_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__iso__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>iso_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iso_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename=NULL, const char *isoname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>iso_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>iso_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>iso_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>iso_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_iso</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wiso</name>
    <title>isoline for approximation (wiso)</title>
    <filename>group__tcl__wiso.html</filename>
    <subgroup>tcl_wiso_save_load</subgroup>
    <subgroup>tcl_wiso_conv</subgroup>
    <subgroup>tcl_wiso_other</subgroup>
    <subgroup>tcl_wisos</subgroup>
    <subgroup>tcl_wiso_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_wiso_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__wiso__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wiso_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *isoname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *isoname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *isoname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wiso_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__wiso__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wiso_to_iso</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_to_isos</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_to_curv</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_to_curvs</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_to_wisos</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wiso_other</name>
    <title>other operations</title>
    <filename>group__tcl__wiso__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wiso_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_value</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_weight</name>
      <anchor>ga2</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_set</name>
      <anchor>ga3</anchor>
      <arglist>(wiso *wisoline)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wiso_name</name>
      <anchor>ga4</anchor>
      <arglist>(const char *name=NULL, wiso *wisoline=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wisos</name>
    <title>operations with wiso collections</title>
    <filename>group__tcl__wisos.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wisos_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wisos_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wisos_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *wisoname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wisos_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *wisoname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>wiso *</type>
      <name>wisos_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>wiso *</type>
      <name>wisos_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wiso *</type>
      <name>wisos_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wisos_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wisos_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wiso_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__wiso__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>wiso_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wiso_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename=NULL, const char *wisoname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wiso_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wiso_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wiso_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wiso_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_wiso</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_flt</name>
    <title>tectonical fault line (flt)</title>
    <filename>group__tcl__flt.html</filename>
    <subgroup>tcl_flt_save_load</subgroup>
    <subgroup>tcl_flt_conv</subgroup>
    <subgroup>tcl_flt_other</subgroup>
    <subgroup>tcl_flts</subgroup>
    <subgroup>tcl_flt_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_flt_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__flt__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>flt_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *fltname, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *fltname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *fltname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_flt_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__flt__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>flt_to_curv</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_to_curvs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_to_grid_line</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_to_flts</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_flt_other</name>
    <title>other operations</title>
    <filename>group__tcl__flt__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>flt_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_set</name>
      <anchor>ga1</anchor>
      <arglist>(flt *fault)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flt_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name=NULL, flt *fault=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_flts</name>
    <title>operations with flt collections</title>
    <filename>group__tcl__flts.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>flts_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flts_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flts_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *fltname, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>flts_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *fltname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>flt *</type>
      <name>flts_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>flt *</type>
      <name>flts_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>flt *</type>
      <name>flts_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>flts_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>flts_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_flt_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__flt__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>flt_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>flt_show</name>
      <anchor>ga6</anchor>
      <arglist>(REAL value=0, const char *filename=NULL, const char *fltname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>flt_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>flt_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>flt_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>flt_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_flt</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_area</name>
    <title>area for interpolation (area)</title>
    <filename>group__tcl__area.html</filename>
    <subgroup>tcl_area_save_load</subgroup>
    <subgroup>tcl_area_conv</subgroup>
    <subgroup>tcl_area_other</subgroup>
    <subgroup>tcl_areas</subgroup>
    <subgroup>tcl_area_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_area_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__area__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>area_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *areaname, REAL value=undef_value, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter=&quot; &quot;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *areaname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *areaname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_area_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__area__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>area_to_curv</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_to_curvs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_to_areas</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_area_other</name>
    <title>other operations</title>
    <filename>group__tcl__area__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>area_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_value</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_value_undef</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_set</name>
      <anchor>ga3</anchor>
      <arglist>(area *arealine)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>area_name</name>
      <anchor>ga4</anchor>
      <arglist>(const char *new_name=NULL, area *arealine=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_areas</name>
    <title>operations with area collections</title>
    <filename>group__tcl__areas.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>areas_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>areas_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>areas_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *areaname, REAL value=undef_value, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>areas_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *areaname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>area *</type>
      <name>areas_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>area *</type>
      <name>areas_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>area *</type>
      <name>areas_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>areas_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>areas_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_area_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__area__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>area_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>area_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename=NULL, const char *areaname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>area_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>area_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>area_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>area_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_area</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_warea</name>
    <title>area for approximation (warea)</title>
    <filename>group__tcl__warea.html</filename>
    <subgroup>tcl_warea_save_load</subgroup>
    <subgroup>tcl_warea_conv</subgroup>
    <subgroup>tcl_warea_other</subgroup>
    <subgroup>tcl_wareas</subgroup>
    <subgroup>tcl_warea_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_warea_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__warea__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>warea_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *wareaname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *wareaname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *wareaname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_set</name>
      <anchor>ga5</anchor>
      <arglist>(warea *warealine)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_name</name>
      <anchor>ga6</anchor>
      <arglist>(const char *new_name=NULL, warea *warealine=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_warea_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__warea__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>warea_to_area</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_to_areas</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_to_curv</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_to_curvs</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_to_wareas</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_warea_other</name>
    <title>other operations</title>
    <filename>group__tcl__warea__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>warea_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_value</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>warea_weight</name>
      <anchor>ga2</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wareas</name>
    <title>operations with warea collections</title>
    <filename>group__tcl__wareas.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wareas_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wareas_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wareas_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *wareaname, REAL value, REAL weight, int columns=2, int col1=1, int col2=2, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wareas_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *wareaname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>warea *</type>
      <name>wareas_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>warea *</type>
      <name>wareas_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>warea *</type>
      <name>wareas_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wareas_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wareas_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_warea_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__warea__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>warea_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warea_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename=NULL, const char *wareaname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>warea_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>warea_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>warea_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>warea_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_warea</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_cntr</name>
    <title>contour for interpolation (cntr)</title>
    <filename>group__tcl__cntr.html</filename>
    <subgroup>tcl_cntr_save_load</subgroup>
    <subgroup>tcl_cntr_math</subgroup>
    <subgroup>tcl_cntr_conv</subgroup>
    <subgroup>tcl_cntr_other</subgroup>
    <subgroup>tcl_cntrs</subgroup>
    <subgroup>tcl_cntr_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_cntr_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__cntr__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>cntr_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *cntrname, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *cntrname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *cntrname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_cntr_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__cntr__math.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>cntr_plus_real</name>
      <anchor>ga0</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_minus_real</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_mult_real</name>
      <anchor>ga2</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_div_real</name>
      <anchor>ga3</anchor>
      <arglist>(REAL value)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_cntr_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__cntr__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>cntr_to_wcntr</name>
      <anchor>ga0</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_to_wcntrs</name>
      <anchor>ga1</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_to_curv</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_to_curvs</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_to_cntrs</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_cntr_other</name>
    <title>other operations</title>
    <filename>group__tcl__cntr__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>cntr_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_set</name>
      <anchor>ga1</anchor>
      <arglist>(cntr *contour)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntr_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name=NULL, cntr *contour=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_cntrs</name>
    <title>operations with cntr collections</title>
    <filename>group__tcl__cntrs.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>cntrs_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntrs_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntrs_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *cntrname, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntrs_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *cntrname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>cntr *</type>
      <name>cntrs_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>cntr *</type>
      <name>cntrs_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>cntr *</type>
      <name>cntrs_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>cntrs_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>cntrs_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cntrs_to_wcntrs</name>
      <anchor>ga9</anchor>
      <arglist>(REAL weight)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_cntr_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__cntr__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>cntr_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cntr_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename=NULL, const char *cntrname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>cntr_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>cntr_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>cntr_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>cntr_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_cntr</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wcntr</name>
    <title>contour for approximation (wcntr)</title>
    <filename>group__tcl__wcntr.html</filename>
    <subgroup>tcl_wcntr_save_load</subgroup>
    <subgroup>tcl_wcntr_math</subgroup>
    <subgroup>tcl_wcntr_conv</subgroup>
    <subgroup>tcl_wcntr_other</subgroup>
    <subgroup>tcl_wcntrs</subgroup>
    <subgroup>tcl_wcntr_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_wcntr_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__wcntr__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *cntrname, REAL weight, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *cntrname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *cntrname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wcntr_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__wcntr__math.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_plus_real</name>
      <anchor>ga0</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_minus_real</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_mult_real</name>
      <anchor>ga2</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_div_real</name>
      <anchor>ga3</anchor>
      <arglist>(REAL value)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wcntr_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__wcntr__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_to_cntr</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_to_cntrs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_to_curv</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_to_curvs</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_to_wcntrs</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wcntr_other</name>
    <title>other operations</title>
    <filename>group__tcl__wcntr__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_set</name>
      <anchor>ga1</anchor>
      <arglist>(wcntr *wcontour)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntr_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name=NULL, wcntr *wcontour=NULL)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wcntrs</name>
    <title>operations with wcntr collections</title>
    <filename>group__tcl__wcntrs.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>wcntrs_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntrs_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntrs_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *cntrname, REAL weight, int columns=3, int col1=1, int col2=2, int col3=3, const char *delimiter=&quot; &quot;, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wcntrs_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *cntrname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>wcntrs_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>wcntrs_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>wcntr *</type>
      <name>wcntrs_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wcntrs_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>wcntrs_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_wcntr_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__wcntr__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>wcntr_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wcntr_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename=NULL, const char *wcntrname=NULL)</arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wcntr_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wcntr_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wcntr_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>wcntr_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SURFIT_EXPORT int</type>
      <name>draw_wcntr</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_grid_line</name>
    <title>grid based line (grid_line)</title>
    <filename>group__tcl__grid__line.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>grid_line_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_line_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_line_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *grid_linename=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>grid_line_unload</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_whole</name>
    <title>data for whole domain</title>
    <filename>group__tcl__whole.html</filename>
    <subgroup>tcl_completer</subgroup>
    <subgroup>tcl_fill_with</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_completer</name>
    <title>completer</title>
    <filename>group__tcl__completer.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>completer_set</name>
      <anchor>ga0</anchor>
      <arglist>(REAL D1, REAL D2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>completer_info</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_fill_with</name>
    <title>fill_with</title>
    <filename>group__tcl__fill__with.html</filename>
    <member kind="function">
      <type>void</type>
      <name>fill_with_set</name>
      <anchor>ga0</anchor>
      <arglist>(REAL value=undef_value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>fill_with_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>fill_with_check</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_dynamic</name>
    <title>dynamically loadable data</title>
    <filename>group__tcl__dynamic.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>dynamic_unload</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dynamic_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *load_proc_name, const char *unload_proc_name)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dynamic_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name, dynamic *dynam)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dynamics_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *load_proc_name, const char *unload_proc_name)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>dynamics_delall</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dynamics_info</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_log</name>
    <title>log file operations</title>
    <filename>group__tcl__log.html</filename>
    <member kind="function">
      <type>int</type>
      <name>log_open</name>
      <anchor>ga0</anchor>
      <arglist>(int level=3, const char *logname=NULL)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>log_clear</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>putlog</name>
      <anchor>ga2</anchor>
      <arglist>(const char *str)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_file</name>
    <title>ROFF file operations</title>
    <filename>group__tcl__file.html</filename>
    <member kind="function">
      <type>void</type>
      <name>file_info</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>file_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>file_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>D:/develop/surfit/surfit-1.0.0pre/surfit/src/interface/</name>
    <path>D:/develop/surfit/surfit-1.0.0pre/surfit/src/interface/</path>
    <filename>dir_000002.html</filename>
    <file>curv.i</file>
    <file>draw.i</file>
    <file>fileio.i</file>
    <file>func.i</file>
    <file>geom.i</file>
    <file>mrf.i</file>
    <file>solve.i</file>
    <file>surfit.i</file>
    <file>task.i</file>
  </compound>
  <compound kind="dir">
    <name>D:/develop/surfit/surfit-1.0.0pre/surfit/src/</name>
    <path>D:/develop/surfit/surfit-1.0.0pre/surfit/src/</path>
    <filename>dir_000001.html</filename>
    <dir>D:/develop/surfit/surfit-1.0.0pre/surfit/src/interface/</dir>
    <file>area.h</file>
    <file>area_internal.h</file>
    <file>area_show.h</file>
    <file>area_tcl.h</file>
    <file>area_user.h</file>
    <file>areas.h</file>
    <file>bitvec.h</file>
    <file>bitvec_alg.h</file>
    <file>boolvec.h</file>
    <file>cg.h</file>
    <file>cg2.h</file>
    <file>cntr.h</file>
    <file>cntr_internal.h</file>
    <file>cntr_show.h</file>
    <file>cntr_tcl.h</file>
    <file>cntr_user.h</file>
    <file>cntrs.h</file>
    <file>color_scale.h</file>
    <file>colors.h</file>
    <file>completer.h</file>
    <file>completer_tcl.h</file>
    <file>completer_user.h</file>
    <file>config.h</file>
    <file>curv.h</file>
    <file>curv_internal.h</file>
    <file>curv_show.h</file>
    <file>curv_tcl.h</file>
    <file>curv_user.h</file>
    <file>curvs.h</file>
    <file>data.h</file>
    <file>datafile.h</file>
    <file>defarea.h</file>
    <file>defarea_internal.h</file>
    <file>defarea_show.h</file>
    <file>defarea_tcl.h</file>
    <file>defarea_user.h</file>
    <file>defareas.h</file>
    <file>draw.h</file>
    <file>draw_object.h</file>
    <file>dynamic.h</file>
    <file>dynamic_internal.h</file>
    <file>dynamic_tcl.h</file>
    <file>dynamic_user.h</file>
    <file>dynamics.h</file>
    <file>file_manager.h</file>
    <file>fileio.h</file>
    <file>fill_with.h</file>
    <file>fill_with_tcl.h</file>
    <file>fill_with_user.h</file>
    <file>flt.h</file>
    <file>flt_internal.h</file>
    <file>flt_show.h</file>
    <file>flt_tcl.h</file>
    <file>flt_user.h</file>
    <file>flts.h</file>
    <file>free_elements.h</file>
    <file>func.h</file>
    <file>func_internal.h</file>
    <file>func_show.h</file>
    <file>func_tcl.h</file>
    <file>func_user.h</file>
    <file>funcs.h</file>
    <file>geom_alg.h</file>
    <file>grid.h</file>
    <file>grid_internal.h</file>
    <file>grid_line.h</file>
    <file>grid_line_internal.h</file>
    <file>grid_line_tcl.h</file>
    <file>grid_line_user.h</file>
    <file>grid_show.h</file>
    <file>grid_tcl.h</file>
    <file>grid_user.h</file>
    <file>ie.h</file>
    <file>intvec.h</file>
    <file>iso.h</file>
    <file>iso_internal.h</file>
    <file>iso_show.h</file>
    <file>iso_tcl.h</file>
    <file>iso_user.h</file>
    <file>isos.h</file>
    <file>jacobi.h</file>
    <file>license.h</file>
    <file>main_method.h</file>
    <file>matfile.h</file>
    <file>matlab.h</file>
    <file>mrf.h</file>
    <file>oper.h</file>
    <file>oper_points.h</file>
    <file>operD1.h</file>
    <file>operD2.h</file>
    <file>points.h</file>
    <file>projector.h</file>
    <file>read_txt.h</file>
    <file>real.h</file>
    <file>rnd.h</file>
    <file>simpiter.h</file>
    <file>simpiter2.h</file>
    <file>solvers.h</file>
    <file>sor.h</file>
    <file>sort_alg.h</file>
    <file>ssor.h</file>
    <file>surfit.h</file>
    <file>task.h</file>
    <file>task_internal.h</file>
    <file>task_show.h</file>
    <file>task_tcl.h</file>
    <file>task_user.h</file>
    <file>tasks.h</file>
    <file>trackball.h</file>
    <file>trend.h</file>
    <file>trend_internal.h</file>
    <file>trend_show.h</file>
    <file>trend_tcl.h</file>
    <file>trend_user.h</file>
    <file>trends.h</file>
    <file>user.h</file>
    <file>variables.h</file>
    <file>variables_internal.h</file>
    <file>variables_tcl.h</file>
    <file>vec.h</file>
    <file>vec_alg.h</file>
    <file>warea.h</file>
    <file>warea_internal.h</file>
    <file>warea_show.h</file>
    <file>warea_tcl.h</file>
    <file>warea_user.h</file>
    <file>wareas.h</file>
    <file>wcntr.h</file>
    <file>wcntr_internal.h</file>
    <file>wcntr_show.h</file>
    <file>wcntr_tcl.h</file>
    <file>wcntr_user.h</file>
    <file>wcntrs.h</file>
    <file>wfunc.h</file>
    <file>wfunc_internal.h</file>
    <file>wfunc_show.h</file>
    <file>wfunc_tcl.h</file>
    <file>wfunc_user.h</file>
    <file>wfuncs.h</file>
    <file>wiso.h</file>
    <file>wiso_internal.h</file>
    <file>wiso_show.h</file>
    <file>wiso_tcl.h</file>
    <file>wiso_user.h</file>
    <file>wisos.h</file>
    <file>wtask.h</file>
    <file>wtask_internal.h</file>
    <file>wtask_show.h</file>
    <file>wtask_tcl.h</file>
    <file>wtask_user.h</file>
    <file>wtasks.h</file>
  </compound>
  <compound kind="dir">
    <name>D:/develop/surfit/surfit-1.0.0pre/surfit/</name>
    <path>D:/develop/surfit/surfit-1.0.0pre/surfit/</path>
    <filename>dir_000000.html</filename>
    <dir>D:/develop/surfit/surfit-1.0.0pre/surfit/src/</dir>
  </compound>
  <compound kind="class">
    <name>surfit::area</name>
    <filename>classsurfit_1_1area.html</filename>
    <base>surfit::curv</base>
    <member kind="function">
      <type></type>
      <name>area</name>
      <anchor>surfit_1_1areaa0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL ivalue, const char *area_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>area</name>
      <anchor>surfit_1_1areaa1</anchor>
      <arglist>(curv *crv, REAL ivalue)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~area</name>
      <anchor>surfit_1_1areaa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wareaa3</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>value</name>
      <anchor>surfit_1_1wareao1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::area_user</name>
    <filename>classsurfit_1_1area__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>area_user</name>
      <anchor>surfit_1_1area__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~area_user</name>
      <anchor>surfit_1_1area__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1area__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1area__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1area__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1area__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1area__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1area__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1area__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1area__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1area__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1area__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1area__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::bitvec</name>
    <filename>classsurfit_1_1bitvec.html</filename>
    <member kind="function">
      <type></type>
      <name>bitvec</name>
      <anchor>surfit_1_1bitveca0</anchor>
      <arglist>(int size=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>bitvec</name>
      <anchor>surfit_1_1bitveca1</anchor>
      <arglist>(const bitvec *src)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~bitvec</name>
      <anchor>surfit_1_1bitveca2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get</name>
      <anchor>surfit_1_1bitveca3</anchor>
      <arglist>(int pos) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_true</name>
      <anchor>surfit_1_1bitveca4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_false</name>
      <anchor>surfit_1_1bitveca5</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy</name>
      <anchor>surfit_1_1bitveca6</anchor>
      <arglist>(const bitvec *src)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_false</name>
      <anchor>surfit_1_1bitveca7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_true</name>
      <anchor>surfit_1_1bitveca8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1bitveca9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>true_size</name>
      <anchor>surfit_1_1bitveca10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write4</name>
      <anchor>surfit_1_1bitveca11</anchor>
      <arglist>(int pos, bool b1, bool b2, bool b3, bool b4)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get4</name>
      <anchor>surfit_1_1bitveca12</anchor>
      <arglist>(int pos, bool &amp;b1, bool &amp;b2, bool &amp;b3, bool &amp;b4)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write10</name>
      <anchor>surfit_1_1bitveca13</anchor>
      <arglist>(int pos, bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, bool b9, bool b10)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get10</name>
      <anchor>surfit_1_1bitveca14</anchor>
      <arglist>(int pos, bool &amp;b1, bool &amp;b2, bool &amp;b3, bool &amp;b4, bool &amp;b5, bool &amp;b6, bool &amp;b7, bool &amp;b8, bool &amp;b9, bool &amp;b10)</arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>data</name>
      <anchor>surfit_1_1bitveco0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>bits_per_byte</name>
      <anchor>surfit_1_1bitveco1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>offset</name>
      <anchor>surfit_1_1bitveco2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>datasize</name>
      <anchor>surfit_1_1bitveco3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>byte_size</name>
      <anchor>surfit_1_1bitveco4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::boolvec</name>
    <filename>classsurfit_1_1boolvec.html</filename>
    <member kind="typedef">
      <type>bool *</type>
      <name>iterator</name>
      <anchor>surfit_1_1boolvecw0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bool &amp;</type>
      <name>reference</name>
      <anchor>surfit_1_1boolvecw1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const bool *</type>
      <name>const_iterator</name>
      <anchor>surfit_1_1boolvecw2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const bool &amp;</type>
      <name>const_reference</name>
      <anchor>surfit_1_1boolvecw3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>boolvec</name>
      <anchor>surfit_1_1boolveca0</anchor>
      <arglist>(int size=0, bool default_value=false, int fill_default=1, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>boolvec</name>
      <anchor>surfit_1_1boolveca1</anchor>
      <arglist>(bool *boolvec_begin, bool *boolvec_end)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>boolvec</name>
      <anchor>surfit_1_1boolveca2</anchor>
      <arglist>(const boolvec &amp;in)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~boolvec</name>
      <anchor>surfit_1_1boolveca3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool *</type>
      <name>begin</name>
      <anchor>surfit_1_1boolveca4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool *&amp;</type>
      <name>ref_begin</name>
      <anchor>surfit_1_1boolveca5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const bool *</type>
      <name>begin</name>
      <anchor>surfit_1_1boolveca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool *</type>
      <name>end</name>
      <anchor>surfit_1_1boolveca7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const bool *</type>
      <name>end</name>
      <anchor>surfit_1_1boolveca8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>erase</name>
      <anchor>surfit_1_1boolveca9</anchor>
      <arglist>(bool *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>erase</name>
      <anchor>surfit_1_1boolveca10</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchor>surfit_1_1boolveca11</anchor>
      <arglist>(int newsize, bool default_value=false, int fill_default=1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1boolveca12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool &amp;</type>
      <name>operator()</name>
      <anchor>surfit_1_1boolveca13</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>const bool &amp;</type>
      <name>operator()</name>
      <anchor>surfit_1_1boolveca14</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>push_back</name>
      <anchor>surfit_1_1boolveca15</anchor>
      <arglist>(const bool &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reserve</name>
      <anchor>surfit_1_1boolveca16</anchor>
      <arglist>(int reserve_size)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_grow</name>
      <anchor>surfit_1_1boolveca17</anchor>
      <arglist>(int grow_by)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>swap</name>
      <anchor>surfit_1_1boolveca18</anchor>
      <arglist>(int i, int j)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drop_data</name>
      <anchor>surfit_1_1boolveca19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>getPointer</name>
      <anchor>surfit_1_1boolveca20</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>bool *</type>
      <name>data</name>
      <anchor>surfit_1_1boolveco0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>datasize</name>
      <anchor>surfit_1_1boolveco1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>bool_datasize</name>
      <anchor>surfit_1_1boolveco2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>grow_by</name>
      <anchor>surfit_1_1boolveco3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::cntr</name>
    <filename>classsurfit_1_1cntr.html</filename>
    <base>surfit::curv</base>
    <member kind="function">
      <type></type>
      <name>cntr</name>
      <anchor>surfit_1_1cntra0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL *iZ_begin, REAL *iZ_end, const char *cntr_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>plus</name>
      <anchor>surfit_1_1wcntra2</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minus</name>
      <anchor>surfit_1_1wcntra3</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1wcntra4</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>div</name>
      <anchor>surfit_1_1wcntra5</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~cntr</name>
      <anchor>surfit_1_1cntra5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minz</name>
      <anchor>surfit_1_1wcntra6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxz</name>
      <anchor>surfit_1_1wcntra7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wcntra8</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_begin</name>
      <anchor>surfit_1_1wcntro1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_end</name>
      <anchor>surfit_1_1wcntro2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::cntr_user</name>
    <filename>classsurfit_1_1cntr__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>cntr_user</name>
      <anchor>surfit_1_1cntr__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~cntr_user</name>
      <anchor>surfit_1_1cntr__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1cntr__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1cntr__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1cntr__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1cntr__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1cntr__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1cntr__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1cntr__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1cntr__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1cntr__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1cntr__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1cntr__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::color_scale</name>
    <filename>classsurfit_1_1color__scale.html</filename>
    <member kind="function">
      <type></type>
      <name>color_scale</name>
      <anchor>surfit_1_1color__scalea0</anchor>
      <arglist>(REAL from, REAL to, REAL step, int r_from, int g_from, int b_from, int r_to, int g_to, int b_to)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~color_scale</name>
      <anchor>surfit_1_1color__scalea1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchor>surfit_1_1color__scalea2</anchor>
      <arglist>(REAL from, REAL to, REAL step, int r_from, int g_from, int b_from, int r_to, int g_to, int b_to)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchor>surfit_1_1color__scalea3</anchor>
      <arglist>(REAL from, REAL to, REAL step, int r_from, int g_from, int b_from, int r_to, int g_to, int b_to)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_value</name>
      <anchor>surfit_1_1color__scalea4</anchor>
      <arglist>(REAL value, int &amp;r, int &amp;g, int &amp;b) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>get_value</name>
      <anchor>surfit_1_1color__scalea5</anchor>
      <arglist>(int pos) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1color__scalea6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_color</name>
      <anchor>surfit_1_1color__scalea7</anchor>
      <arglist>(int pos, int &amp;r, int &amp;g, int &amp;b) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_color_from</name>
      <anchor>surfit_1_1color__scalea8</anchor>
      <arglist>(int r, int g, int b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_color_to</name>
      <anchor>surfit_1_1color__scalea9</anchor>
      <arglist>(int r, int g, int b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_min</name>
      <anchor>surfit_1_1color__scalea10</anchor>
      <arglist>(REAL min_val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_max</name>
      <anchor>surfit_1_1color__scalea11</anchor>
      <arglist>(REAL max_val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_step</name>
      <anchor>surfit_1_1color__scalea12</anchor>
      <arglist>(REAL step_val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_params</name>
      <anchor>surfit_1_1color__scalea13</anchor>
      <arglist>(REAL &amp;from, REAL &amp;to, REAL &amp;step, int &amp;r_from, int &amp;g_from, int &amp;b_from, int &amp;r_to, int &amp;g_to, int &amp;b_to)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_default</name>
      <anchor>surfit_1_1color__scalea14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_default</name>
      <anchor>surfit_1_1color__scalea15</anchor>
      <arglist>(bool val)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; int &gt; *</type>
      <name>r_values</name>
      <anchor>surfit_1_1color__scaler0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; int &gt; *</type>
      <name>g_values</name>
      <anchor>surfit_1_1color__scaler1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; int &gt; *</type>
      <name>b_values</name>
      <anchor>surfit_1_1color__scaler2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; REAL &gt; *</type>
      <name>values</name>
      <anchor>surfit_1_1color__scaler3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>default_cs</name>
      <anchor>surfit_1_1color__scaler4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::completer</name>
    <filename>classsurfit_1_1completer.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>completer</name>
      <anchor>surfit_1_1completera0</anchor>
      <arglist>(REAL iD1=1, REAL iD2=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1completera1</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1completera2</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>D1</name>
      <anchor>surfit_1_1completero0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>D2</name>
      <anchor>surfit_1_1completero1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::completer_user</name>
    <filename>classsurfit_1_1completer__user.html</filename>
    <base>surfit::user</base>
    <base>surfit::modifier1</base>
    <member kind="function">
      <type></type>
      <name>completer_user</name>
      <anchor>surfit_1_1completer__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~completer_user</name>
      <anchor>surfit_1_1completer__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1completer__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1completer__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1completer__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1completer__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1completer__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1completer__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1completer__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1completer__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1completer__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1completer__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1completer__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec *</type>
      <name>get_weights</name>
      <anchor>surfit_1_1completer__usera13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual intvec *</type>
      <name>get_weights_cnt</name>
      <anchor>surfit_1_1completer__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_weights</name>
      <anchor>surfit_1_1completer__usera15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_weights_cnt</name>
      <anchor>surfit_1_1completer__usera16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::curv</name>
    <filename>classsurfit_1_1curv.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>curv</name>
      <anchor>surfit_1_1curva0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, const char *curv_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~curv</name>
      <anchor>surfit_1_1curva1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1curva9</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::data</name>
    <filename>classsurfit_1_1data.html</filename>
    <member kind="function">
      <type></type>
      <name>data</name>
      <anchor>surfit_1_1dataa0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~data</name>
      <anchor>surfit_1_1dataa1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1dataa6</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1dataa7</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const =0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::datafile</name>
    <filename>classsurfit_1_1datafile.html</filename>
    <member kind="function">
      <type></type>
      <name>datafile</name>
      <anchor>surfit_1_1datafilea0</anchor>
      <arglist>(const char *filename, int mode, int iomode)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~datafile</name>
      <anchor>surfit_1_1datafilea1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeTag</name>
      <anchor>surfit_1_1datafilea2</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeEndTag</name>
      <anchor>surfit_1_1datafilea3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeEof</name>
      <anchor>surfit_1_1datafilea4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeString</name>
      <anchor>surfit_1_1datafilea5</anchor>
      <arglist>(const char *name, const char *string)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeInt</name>
      <anchor>surfit_1_1datafilea6</anchor>
      <arglist>(const char *name, const int &amp;i)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeReal</name>
      <anchor>surfit_1_1datafilea7</anchor>
      <arglist>(const char *name, const REAL &amp;d)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeChar</name>
      <anchor>surfit_1_1datafilea8</anchor>
      <arglist>(const char *name, const char *c)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeRealArray</name>
      <anchor>surfit_1_1datafilea9</anchor>
      <arglist>(const char *name, const REAL *ptr, unsigned int size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeBoolArray</name>
      <anchor>surfit_1_1datafilea10</anchor>
      <arglist>(const char *name, const bool *ptr, unsigned int size)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readWord</name>
      <anchor>surfit_1_1datafilea11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readBool</name>
      <anchor>surfit_1_1datafilea12</anchor>
      <arglist>(bool &amp;b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readByte</name>
      <anchor>surfit_1_1datafilea13</anchor>
      <arglist>(unsigned char &amp;c)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readInt</name>
      <anchor>surfit_1_1datafilea14</anchor>
      <arglist>(int &amp;i)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readReal</name>
      <anchor>surfit_1_1datafilea15</anchor>
      <arglist>(REAL &amp;d)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readRealArray</name>
      <anchor>surfit_1_1datafilea16</anchor>
      <arglist>(REAL *&amp;begin, REAL *&amp;end)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readBoolArray</name>
      <anchor>surfit_1_1datafilea17</anchor>
      <arglist>(bool *&amp;begin, bool *&amp;end)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>condition</name>
      <anchor>surfit_1_1datafilea18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>findTag</name>
      <anchor>surfit_1_1datafilea19</anchor>
      <arglist>(const char *tagname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>findTagEof</name>
      <anchor>surfit_1_1datafilea20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipTagName</name>
      <anchor>surfit_1_1datafilea21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isWord</name>
      <anchor>surfit_1_1datafilea22</anchor>
      <arglist>(const char *testword) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skip</name>
      <anchor>surfit_1_1datafilea23</anchor>
      <arglist>(bool print_name, char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipToEndTag</name>
      <anchor>surfit_1_1datafilea24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipByte</name>
      <anchor>surfit_1_1datafilea25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipBool</name>
      <anchor>surfit_1_1datafilea26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipInt</name>
      <anchor>surfit_1_1datafilea27</anchor>
      <arglist>(bool skip_name=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipReal</name>
      <anchor>surfit_1_1datafilea28</anchor>
      <arglist>(bool skip_name=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipChar</name>
      <anchor>surfit_1_1datafilea29</anchor>
      <arglist>(bool print_name=false, bool skip_name=true, char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipArray</name>
      <anchor>surfit_1_1datafilea30</anchor>
      <arglist>(bool skip_type=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipByteArray</name>
      <anchor>surfit_1_1datafilea31</anchor>
      <arglist>(bool skip_name=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipBoolArray</name>
      <anchor>surfit_1_1datafilea32</anchor>
      <arglist>(bool skip_name=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipIntArray</name>
      <anchor>surfit_1_1datafilea33</anchor>
      <arglist>(bool skip_name=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipRealArray</name>
      <anchor>surfit_1_1datafilea34</anchor>
      <arglist>(bool skip_name=true)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>readNextTag</name>
      <anchor>surfit_1_1datafilea35</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getWord</name>
      <anchor>surfit_1_1datafilea36</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>file_info</name>
      <anchor>surfit_1_1datafilea37</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>file_info_fill</name>
      <anchor>surfit_1_1datafilea38</anchor>
      <arglist>(char **&amp;contents)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isVariableType</name>
      <anchor>surfit_1_1datafilea39</anchor>
      <arglist>(const char *type_name, bool &amp;read_ok)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ReadChar</name>
      <anchor>surfit_1_1datafilea40</anchor>
      <arglist>(const char *variable_name, char *&amp;result, bool &amp;read_ok)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ReadInt</name>
      <anchor>surfit_1_1datafilea41</anchor>
      <arglist>(const char *variable_name, int &amp;result, bool &amp;read_ok)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ReadReal</name>
      <anchor>surfit_1_1datafilea42</anchor>
      <arglist>(const char *variable_name, REAL &amp;result, bool &amp;read_ok)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ReadRealArray</name>
      <anchor>surfit_1_1datafilea43</anchor>
      <arglist>(const char *variable_name, REAL *&amp;begin, REAL *&amp;end, bool &amp;read_ok)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>writeBinaryString</name>
      <anchor>surfit_1_1datafilea44</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeString</name>
      <anchor>surfit_1_1datafilea45</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeTextString</name>
      <anchor>surfit_1_1datafilea46</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeHeader</name>
      <anchor>surfit_1_1datafilea47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>checkHeader</name>
      <anchor>surfit_1_1datafilea48</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>readTagName</name>
      <anchor>surfit_1_1datafilea49</anchor>
      <arglist>(char *string)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>byteswaptest</name>
      <anchor>surfit_1_1datafilea50</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ungetString</name>
      <anchor>surfit_1_1datafilea51</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipBytes</name>
      <anchor>surfit_1_1datafilea52</anchor>
      <arglist>(long how_much)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>skipHeader</name>
      <anchor>surfit_1_1datafilea53</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>skipTag</name>
      <anchor>surfit_1_1datafilea54</anchor>
      <arglist>(bool print_name, char *name=NULL)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>get_filename</name>
      <anchor>surfit_1_1datafilea55</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>file</name>
      <anchor>surfit_1_1datafileo0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>FILE *</type>
      <name>File</name>
      <anchor>surfit_1_1datafileo1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>word</name>
      <anchor>surfit_1_1datafileo2</anchor>
      <arglist>[TAG_WORD_SIZE]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>mode</name>
      <anchor>surfit_1_1datafileo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>zero</name>
      <anchor>surfit_1_1datafileo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>datafile_filename</name>
      <anchor>surfit_1_1datafileo5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::defarea</name>
    <filename>classsurfit_1_1defarea.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>defarea</name>
      <anchor>surfit_1_1defareaa0</anchor>
      <arglist>(boolvec *icoeff, grid *igrd, const char *funcname=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~defarea</name>
      <anchor>surfit_1_1defareaa1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1defareaa2</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1defareaa3</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getValue</name>
      <anchor>surfit_1_1defareaa4</anchor>
      <arglist>(REAL x, REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinX</name>
      <anchor>surfit_1_1defareaa5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxX</name>
      <anchor>surfit_1_1defareaa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinY</name>
      <anchor>surfit_1_1defareaa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxY</name>
      <anchor>surfit_1_1defareaa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getQuadsCount</name>
      <anchor>surfit_1_1defareaa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getQuad</name>
      <anchor>surfit_1_1defareaa10</anchor>
      <arglist>(int qe_number, float &amp;x0, float &amp;y0, float &amp;x1, float &amp;y1, float &amp;x2, float &amp;y2, float &amp;x3, float &amp;y3) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountX</name>
      <anchor>surfit_1_1defareaa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountY</name>
      <anchor>surfit_1_1defareaa12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getCoordNode</name>
      <anchor>surfit_1_1defareaa13</anchor>
      <arglist>(int i, int j, REAL &amp;x, REAL &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>getCoordNodeX</name>
      <anchor>surfit_1_1defareaa14</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>getCoordNodeY</name>
      <anchor>surfit_1_1defareaa15</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_i</name>
      <anchor>surfit_1_1defareaa16</anchor>
      <arglist>(REAL x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_j</name>
      <anchor>surfit_1_1defareaa17</anchor>
      <arglist>(REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>writeTags</name>
      <anchor>surfit_1_1defareaa18</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>compare_grid</name>
      <anchor>surfit_1_1defareaa19</anchor>
      <arglist>(const defarea *defarea) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>AND</name>
      <anchor>surfit_1_1defareaa20</anchor>
      <arglist>(const defarea *def)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>NOT</name>
      <anchor>surfit_1_1defareaa21</anchor>
      <arglist>(const defarea *def)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OR</name>
      <anchor>surfit_1_1defareaa22</anchor>
      <arglist>(const defarea *def)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>XOR</name>
      <anchor>surfit_1_1defareaa23</anchor>
      <arglist>(const defarea *def)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>grid *</type>
      <name>grd</name>
      <anchor>surfit_1_1defareao0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boolvec *</type>
      <name>coeff</name>
      <anchor>surfit_1_1defareao1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>show_smooth</name>
      <anchor>surfit_1_1defareao2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::defarea_user</name>
    <filename>classsurfit_1_1defarea__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>defarea_user</name>
      <anchor>surfit_1_1defarea__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~defarea_user</name>
      <anchor>surfit_1_1defarea__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1defarea__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1defarea__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1defarea__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1defarea__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1defarea__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1defarea__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1defarea__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1defarea__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1defarea__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1defarea__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1defarea__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::draw_object</name>
    <filename>classsurfit_1_1draw__object.html</filename>
    <member kind="function">
      <type></type>
      <name>draw_object</name>
      <anchor>surfit_1_1draw__objecta0</anchor>
      <arglist>(const char *name, const char *type, const char *filename, int listNo, REAL iminx, REAL imaxx, REAL iminy, REAL imaxy, REAL iminz, REAL imaxz)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~draw_object</name>
      <anchor>surfit_1_1draw__objecta1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>callList</name>
      <anchor>surfit_1_1draw__objecta2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setListNumber</name>
      <anchor>surfit_1_1draw__objecta3</anchor>
      <arglist>(int number)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getListNumber</name>
      <anchor>surfit_1_1draw__objecta4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1draw__objecta5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getType</name>
      <anchor>surfit_1_1draw__objecta6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getFileName</name>
      <anchor>surfit_1_1draw__objecta7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1draw__objecto0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1draw__objecto1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1draw__objecto2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1draw__objecto3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>minz</name>
      <anchor>surfit_1_1draw__objecto4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>maxz</name>
      <anchor>surfit_1_1draw__objecto5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>object_name</name>
      <anchor>surfit_1_1draw__objectp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>object_type</name>
      <anchor>surfit_1_1draw__objectp1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>object_filename</name>
      <anchor>surfit_1_1draw__objectp2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>listNumber</name>
      <anchor>surfit_1_1draw__objectp3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::dynamic</name>
    <filename>classsurfit_1_1dynamic.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>dynamic</name>
      <anchor>surfit_1_1dynamica0</anchor>
      <arglist>(const char *iload_proc_name, const char *iunload_proc_name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~dynamic</name>
      <anchor>surfit_1_1dynamica1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1dynamica2</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1dynamica3</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>load</name>
      <anchor>surfit_1_1dynamica4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>unload</name>
      <anchor>surfit_1_1dynamica5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>load_proc_name</name>
      <anchor>surfit_1_1dynamico0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>unload_proc_name</name>
      <anchor>surfit_1_1dynamico1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::dynamic_user</name>
    <filename>classsurfit_1_1dynamic__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>dynamic_user</name>
      <anchor>surfit_1_1dynamic__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~dynamic_user</name>
      <anchor>surfit_1_1dynamic__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1dynamic__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1dynamic__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1dynamic__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1dynamic__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1dynamic__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1dynamic__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1dynamic__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1dynamic__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1dynamic__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1dynamic__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1dynamic__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::manager</name>
    <filename>classsurfit_1_1manager.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>load_tag</name>
      <anchor>surfit_1_1managera0</anchor>
      <arglist>(datafile *df, char *tag_name) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>save</name>
      <anchor>surfit_1_1managera1</anchor>
      <arglist>(datafile *df) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>clear_data</name>
      <anchor>surfit_1_1managera2</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>mem_info</name>
      <anchor>surfit_1_1managera3</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>release</name>
      <anchor>surfit_1_1managera4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>data_count</name>
      <anchor>surfit_1_1managera5</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const data *</type>
      <name>data_get</name>
      <anchor>surfit_1_1managera6</anchor>
      <arglist>(int i) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>mem_show</name>
      <anchor>surfit_1_1managera7</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>check_for_drawing</name>
      <anchor>surfit_1_1managera8</anchor>
      <arglist>(const char *type) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1managera9</anchor>
      <arglist>(REAL &amp;minZ, REAL &amp;maxZ) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::surfit_manager</name>
    <filename>classsurfit_1_1surfit__manager.html</filename>
    <base>surfit::manager</base>
    <member kind="function">
      <type>int</type>
      <name>load_tag</name>
      <anchor>surfit_1_1surfit__managera0</anchor>
      <arglist>(datafile *df, char *tag_name) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>save</name>
      <anchor>surfit_1_1surfit__managera1</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_data</name>
      <anchor>surfit_1_1surfit__managera2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mem_info</name>
      <anchor>surfit_1_1surfit__managera3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1surfit__managera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>data_count</name>
      <anchor>surfit_1_1surfit__managera5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const data *</type>
      <name>data_get</name>
      <anchor>surfit_1_1surfit__managera6</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mem_show</name>
      <anchor>surfit_1_1surfit__managera7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check_for_drawing</name>
      <anchor>surfit_1_1surfit__managera8</anchor>
      <arglist>(const char *type) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1surfit__managera9</anchor>
      <arglist>(REAL &amp;minZ, REAL &amp;maxZ) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::data_manager</name>
    <filename>classsurfit_1_1data__manager.html</filename>
    <member kind="function">
      <type></type>
      <name>data_manager</name>
      <anchor>surfit_1_1data__managera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~data_manager</name>
      <anchor>surfit_1_1data__managera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>load</name>
      <anchor>surfit_1_1data__managera2</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>save</name>
      <anchor>surfit_1_1data__managera3</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_data</name>
      <anchor>surfit_1_1data__managera4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mem_info</name>
      <anchor>surfit_1_1data__managera5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mem_show</name>
      <anchor>surfit_1_1data__managera6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check_for_drawing</name>
      <anchor>surfit_1_1data__managera7</anchor>
      <arglist>(const char *type) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1data__managera8</anchor>
      <arglist>(REAL &amp;minZ, REAL &amp;maxZ) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>data_count</name>
      <anchor>surfit_1_1data__managera9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const data *</type>
      <name>data_get</name>
      <anchor>surfit_1_1data__managera10</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; manager * &gt; *</type>
      <name>managers</name>
      <anchor>surfit_1_1data__managero0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::fill_with</name>
    <filename>classsurfit_1_1fill__with.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>fill_with</name>
      <anchor>surfit_1_1fill__witha0</anchor>
      <arglist>(REAL ivalue)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1fill__witha1</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1fill__witha2</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>value</name>
      <anchor>surfit_1_1fill__witho0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::fill_with_user</name>
    <filename>classsurfit_1_1fill__with__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>fill_with_user</name>
      <anchor>surfit_1_1fill__with__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~fill_with_user</name>
      <anchor>surfit_1_1fill__with__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1fill__with__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1fill__with__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1fill__with__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1fill__with__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1fill__with__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1fill__with__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1fill__with__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1fill__with__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1fill__with__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1fill__with__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1fill__with__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::flt</name>
    <filename>classsurfit_1_1flt.html</filename>
    <base>surfit::curv</base>
    <member kind="function">
      <type></type>
      <name>flt</name>
      <anchor>surfit_1_1flta0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, const char *flt_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>flt</name>
      <anchor>surfit_1_1flta1</anchor>
      <arglist>(curv *crv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~flt</name>
      <anchor>surfit_1_1flta2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1flta3</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::flt_user</name>
    <filename>classsurfit_1_1flt__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>flt_user</name>
      <anchor>surfit_1_1flt__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~flt_user</name>
      <anchor>surfit_1_1flt__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1flt__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1flt__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1flt__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1flt__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1flt__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1flt__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1flt__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1flt__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1flt__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1flt__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1flt__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::func</name>
    <filename>classsurfit_1_1func.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>func</name>
      <anchor>surfit_1_1funca0</anchor>
      <arglist>(vec *icoeff, grid *igrd, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>func</name>
      <anchor>surfit_1_1funca1</anchor>
      <arglist>(defarea *def)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~func</name>
      <anchor>surfit_1_1funca2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getValue</name>
      <anchor>surfit_1_1wfunca4</anchor>
      <arglist>(REAL x, REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinX</name>
      <anchor>surfit_1_1wfunca5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxX</name>
      <anchor>surfit_1_1wfunca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinY</name>
      <anchor>surfit_1_1wfunca7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxY</name>
      <anchor>surfit_1_1wfunca8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>mean</name>
      <anchor>surfit_1_1wfunca9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>std</name>
      <anchor>surfit_1_1wfunca10</anchor>
      <arglist>(REAL mean) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>sum</name>
      <anchor>surfit_1_1wfunca11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wfunca12</anchor>
      <arglist>(REAL &amp;minZ, REAL &amp;maxZ) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getTrianglesCount</name>
      <anchor>surfit_1_1wfunca13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getTrianglesCount</name>
      <anchor>surfit_1_1wfunca14</anchor>
      <arglist>(const REAL &amp;show_x_from, const REAL &amp;show_x_to, const REAL &amp;show_y_from, const REAL &amp;show_y_to)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getTriangle</name>
      <anchor>surfit_1_1wfunca15</anchor>
      <arglist>(int triangle_number, REAL &amp;x0, REAL &amp;y0, REAL &amp;z0, REAL &amp;x1, REAL &amp;y1, REAL &amp;z1, REAL &amp;x2, REAL &amp;y2, REAL &amp;z2) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getTriangle</name>
      <anchor>surfit_1_1wfunca16</anchor>
      <arglist>(int triangle_number, REAL &amp;x0, REAL &amp;y0, REAL &amp;z0, REAL &amp;x1, REAL &amp;y1, REAL &amp;z1, REAL &amp;x2, REAL &amp;y2, REAL &amp;z2, const REAL &amp;show_x_from, const REAL &amp;show_x_to, const REAL &amp;show_y_from, const REAL &amp;show_y_to) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountX</name>
      <anchor>surfit_1_1wfunca17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountY</name>
      <anchor>surfit_1_1wfunca18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getStepX</name>
      <anchor>surfit_1_1wfunca19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getStepY</name>
      <anchor>surfit_1_1wfunca20</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getCoordNode</name>
      <anchor>surfit_1_1wfunca21</anchor>
      <arglist>(int i, int j, REAL &amp;x, REAL &amp;y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getCoordNodeX</name>
      <anchor>surfit_1_1wfunca22</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getCoordNodeY</name>
      <anchor>surfit_1_1wfunca23</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_i</name>
      <anchor>surfit_1_1wfunca24</anchor>
      <arglist>(REAL x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_j</name>
      <anchor>surfit_1_1wfunca25</anchor>
      <arglist>(REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>defined</name>
      <anchor>surfit_1_1wfunca26</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>writeTags</name>
      <anchor>surfit_1_1funca26</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>compare_grid</name>
      <anchor>surfit_1_1wfunca27</anchor>
      <arglist>(const func *fnc) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>plus</name>
      <anchor>surfit_1_1wfunca28</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus</name>
      <anchor>surfit_1_1wfunca30</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus_undef</name>
      <anchor>surfit_1_1wfunca32</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>mult</name>
      <anchor>surfit_1_1wfunca33</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>div</name>
      <anchor>surfit_1_1wfunca35</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set</name>
      <anchor>surfit_1_1wfunca37</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>plus</name>
      <anchor>surfit_1_1wfunca29</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus</name>
      <anchor>surfit_1_1wfunca31</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>mult</name>
      <anchor>surfit_1_1wfunca34</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>div</name>
      <anchor>surfit_1_1wfunca36</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set</name>
      <anchor>surfit_1_1wfunca38</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>add_noise</name>
      <anchor>surfit_1_1wfunca39</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wfunca40</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>decompose</name>
      <anchor>surfit_1_1wfunca41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>auto_decompose</name>
      <anchor>surfit_1_1wfunca42</anchor>
      <arglist>(REAL eps, int norm=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>reconstruct</name>
      <anchor>surfit_1_1wfunca43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>full_reconstruct</name>
      <anchor>surfit_1_1wfunca44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>details_size</name>
      <anchor>surfit_1_1wfunca45</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>calc_approx_norm</name>
      <anchor>surfit_1_1wfunca46</anchor>
      <arglist>(int norm_type) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>grid *</type>
      <name>grd</name>
      <anchor>surfit_1_1wfunco1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vec *</type>
      <name>coeff</name>
      <anchor>surfit_1_1wfunco2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>show_smooth</name>
      <anchor>surfit_1_1wfunco3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>undef_value</name>
      <anchor>surfit_1_1wfunco4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_h</name>
      <anchor>surfit_1_1wfunco5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_v</name>
      <anchor>surfit_1_1wfunco6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_d</name>
      <anchor>surfit_1_1wfunco7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; bool &gt; *</type>
      <name>enlarges_X</name>
      <anchor>surfit_1_1wfunco8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; bool &gt; *</type>
      <name>enlarges_Y</name>
      <anchor>surfit_1_1wfunco9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_i_from</name>
      <anchor>surfit_1_1wfuncp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_i_to</name>
      <anchor>surfit_1_1wfuncp1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_j_from</name>
      <anchor>surfit_1_1wfuncp2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_j_to</name>
      <anchor>surfit_1_1wfuncp3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::func_user</name>
    <filename>classsurfit_1_1func__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>func_user</name>
      <anchor>surfit_1_1func__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~func_user</name>
      <anchor>surfit_1_1func__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1func__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1func__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1func__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1func__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1func__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1func__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1func__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1func__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1func__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1func__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1func__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::grid</name>
    <filename>classsurfit_1_1grid.html</filename>
    <member kind="function">
      <type></type>
      <name>grid</name>
      <anchor>surfit_1_1grida0</anchor>
      <arglist>(REAL startX, REAL endX, REAL stepX, REAL startY, REAL endY, REAL stepY, const char *iname=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>grid</name>
      <anchor>surfit_1_1grida1</anchor>
      <arglist>(const grid *igrid)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~grid</name>
      <anchor>surfit_1_1grida2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCountX</name>
      <anchor>surfit_1_1grida3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCountY</name>
      <anchor>surfit_1_1grida4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getCoordNode</name>
      <anchor>surfit_1_1grida5</anchor>
      <arglist>(int i, int j, REAL &amp;x, REAL &amp;y) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>getCoordNodeX</name>
      <anchor>surfit_1_1grida6</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>getCoordNodeY</name>
      <anchor>surfit_1_1grida7</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getCoordPoint</name>
      <anchor>surfit_1_1grida8</anchor>
      <arglist>(REAL x, REAL y, int &amp;i, int &amp;j) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_i</name>
      <anchor>surfit_1_1grida9</anchor>
      <arglist>(REAL x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_j</name>
      <anchor>surfit_1_1grida10</anchor>
      <arglist>(REAL y) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeTags</name>
      <anchor>surfit_1_1grida11</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1grida12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1grida13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getLinesCount</name>
      <anchor>surfit_1_1grida14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getLine</name>
      <anchor>surfit_1_1grida15</anchor>
      <arglist>(int line_number, float &amp;x0, float &amp;y0, float &amp;x1, float &amp;y1) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchor>surfit_1_1grida16</anchor>
      <arglist>(const grid *test) const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>startX</name>
      <anchor>surfit_1_1grido0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>endX</name>
      <anchor>surfit_1_1grido1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>stepX</name>
      <anchor>surfit_1_1grido2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>startY</name>
      <anchor>surfit_1_1grido3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>endY</name>
      <anchor>surfit_1_1grido4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>stepY</name>
      <anchor>surfit_1_1grido5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>gridname</name>
      <anchor>surfit_1_1gridp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::grid_line</name>
    <filename>classsurfit_1_1grid__line.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>grid_line</name>
      <anchor>surfit_1_1grid__linea0</anchor>
      <arglist>(int *ifirst_begin, int *ifirst_end, int *isecond_begin, int *isecond_end)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~grid_line</name>
      <anchor>surfit_1_1grid__linea1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1grid__linea2</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1grid__linea3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchor>surfit_1_1grid__linea4</anchor>
      <arglist>(int *&amp;ifirst_begin, int *&amp;ifirst_end, int *&amp;isecond_begin, int *&amp;isecond_end)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchor>surfit_1_1grid__linea5</anchor>
      <arglist>(grid_line *line)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1grid__linea6</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sort</name>
      <anchor>surfit_1_1grid__linea7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compress</name>
      <anchor>surfit_1_1grid__linea8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>first_begin</name>
      <anchor>surfit_1_1grid__lineo0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>first_end</name>
      <anchor>surfit_1_1grid__lineo1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>second_begin</name>
      <anchor>surfit_1_1grid__lineo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>second_end</name>
      <anchor>surfit_1_1grid__lineo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int **</type>
      <name>sort_by_first_begin</name>
      <anchor>surfit_1_1grid__lineo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int **</type>
      <name>sort_by_first_end</name>
      <anchor>surfit_1_1grid__lineo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int **</type>
      <name>sort_by_second_begin</name>
      <anchor>surfit_1_1grid__lineo6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int **</type>
      <name>sort_by_second_end</name>
      <anchor>surfit_1_1grid__lineo7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::grid_user</name>
    <filename>classsurfit_1_1grid__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>grid_user</name>
      <anchor>surfit_1_1grid__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~grid_user</name>
      <anchor>surfit_1_1grid__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1grid__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1grid__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1grid__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1grid__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1grid__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1grid__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1grid__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1grid__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1grid__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1grid__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1grid__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::intvec</name>
    <filename>classsurfit_1_1intvec.html</filename>
    <member kind="typedef">
      <type>int *</type>
      <name>iterator</name>
      <anchor>surfit_1_1intvecw0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int &amp;</type>
      <name>reference</name>
      <anchor>surfit_1_1intvecw1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const int *</type>
      <name>const_iterator</name>
      <anchor>surfit_1_1intvecw2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const int &amp;</type>
      <name>const_reference</name>
      <anchor>surfit_1_1intvecw3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>intvec</name>
      <anchor>surfit_1_1intveca0</anchor>
      <arglist>(int size=0, int default_value=int(0), int fill_default=1, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>intvec</name>
      <anchor>surfit_1_1intveca1</anchor>
      <arglist>(int *vec_begin, int *vec_end)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>intvec</name>
      <anchor>surfit_1_1intveca2</anchor>
      <arglist>(const intvec &amp;in)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~intvec</name>
      <anchor>surfit_1_1intveca3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>begin</name>
      <anchor>surfit_1_1intveca4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *&amp;</type>
      <name>ref_begin</name>
      <anchor>surfit_1_1intveca5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const int *</type>
      <name>begin</name>
      <anchor>surfit_1_1intveca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int *</type>
      <name>end</name>
      <anchor>surfit_1_1intveca7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const int *</type>
      <name>end</name>
      <anchor>surfit_1_1intveca8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>erase</name>
      <anchor>surfit_1_1intveca9</anchor>
      <arglist>(int *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>erase</name>
      <anchor>surfit_1_1intveca10</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchor>surfit_1_1intveca11</anchor>
      <arglist>(int newsize, int default_value=int(0), int fill_default=1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1intveca12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int &amp;</type>
      <name>operator()</name>
      <anchor>surfit_1_1intveca13</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>const int &amp;</type>
      <name>operator()</name>
      <anchor>surfit_1_1intveca14</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>push_back</name>
      <anchor>surfit_1_1intveca15</anchor>
      <arglist>(const int &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reserve</name>
      <anchor>surfit_1_1intveca16</anchor>
      <arglist>(int reserve_size)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_grow</name>
      <anchor>surfit_1_1intveca17</anchor>
      <arglist>(int grow_by)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>swap</name>
      <anchor>surfit_1_1intveca18</anchor>
      <arglist>(int i, int j)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drop_data</name>
      <anchor>surfit_1_1intveca19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>getPointer</name>
      <anchor>surfit_1_1intveca20</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>data</name>
      <anchor>surfit_1_1intveco0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>datasize</name>
      <anchor>surfit_1_1intveco1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>int_datasize</name>
      <anchor>surfit_1_1intveco2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>grow_by</name>
      <anchor>surfit_1_1intveco3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::iso</name>
    <filename>classsurfit_1_1iso.html</filename>
    <base>surfit::curv</base>
    <member kind="function">
      <type></type>
      <name>iso</name>
      <anchor>surfit_1_1isoa0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL ivalue, const char *iso_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>iso</name>
      <anchor>surfit_1_1isoa1</anchor>
      <arglist>(curv *crv, REAL ivalue)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~iso</name>
      <anchor>surfit_1_1isoa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wisoa4</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>value</name>
      <anchor>surfit_1_1wisoo1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::iso_user</name>
    <filename>classsurfit_1_1iso__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1iso__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1iso__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1iso__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1iso__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1iso__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1iso__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1iso__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1iso__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1iso__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1iso__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1iso__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::matlabVector</name>
    <filename>classsurfit_1_1matlabVector.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1matlabVectora0</anchor>
      <arglist>(int i) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual long</type>
      <name>size</name>
      <anchor>surfit_1_1matlabVectora1</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1matlabVectora2</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::matlabSparseMatrix</name>
    <filename>classsurfit_1_1matlabSparseMatrix.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1matlabSparseMatrixa0</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1matlabSparseMatrixa1</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1matlabSparseMatrixa2</anchor>
      <arglist>(int i, int j, int *next_i=NULL) const =0</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::oper</name>
    <filename>classsurfit_1_1oper.html</filename>
    <base>surfit::matlabSparseMatrix</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~oper</name>
      <anchor>surfit_1_1opera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1opera1</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual REAL</type>
      <name>at</name>
      <anchor>surfit_1_1opera2</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1opera3</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1opera4</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual REAL</type>
      <name>mult_line</name>
      <anchor>surfit_1_1opera5</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual REAL</type>
      <name>mult_transposed_line</name>
      <anchor>surfit_1_1opera6</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1operD2__recta9</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult_transposed</name>
      <anchor>surfit_1_1operD2__recta10</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual REAL</type>
      <name>norm</name>
      <anchor>surfit_1_1opera9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::oper_complex</name>
    <filename>classsurfit_1_1oper__complex.html</filename>
    <base>surfit::oper</base>
    <member kind="function">
      <type></type>
      <name>oper_complex</name>
      <anchor>surfit_1_1oper__complexa0</anchor>
      <arglist>(REAL iw1, oper *iT1, REAL iw2=0, oper *iT2=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~oper_complex</name>
      <anchor>surfit_1_1oper__complexa1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1oper__complexa2</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>at</name>
      <anchor>surfit_1_1oper__complexa3</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>mult_line</name>
      <anchor>surfit_1_1oper__complexa4</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>mult_transposed_line</name>
      <anchor>surfit_1_1oper__complexa5</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>norm</name>
      <anchor>surfit_1_1oper__complexa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1oper__complexa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1oper__complexa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1operD2__recta9</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult_transposed</name>
      <anchor>surfit_1_1operD2__recta10</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>w1</name>
      <anchor>surfit_1_1oper__complexo0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>oper *</type>
      <name>T1</name>
      <anchor>surfit_1_1oper__complexo1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>w2</name>
      <anchor>surfit_1_1oper__complexo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>oper *</type>
      <name>T2</name>
      <anchor>surfit_1_1oper__complexo3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::oper_points</name>
    <filename>classsurfit_1_1oper__points.html</filename>
    <base>surfit::oper</base>
    <member kind="function">
      <type></type>
      <name>oper_points</name>
      <anchor>surfit_1_1oper__pointsa0</anchor>
      <arglist>(vec *iweights, intvec *iweights_cnt, bitvec *imask_solved, bitvec *imask_undefined, int iN)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~oper_points</name>
      <anchor>surfit_1_1oper__pointsa1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1oper__pointsa2</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>at</name>
      <anchor>surfit_1_1oper__pointsa3</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_line</name>
      <anchor>surfit_1_1oper__pointsa4</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_transposed_line</name>
      <anchor>surfit_1_1oper__pointsa5</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1oper__pointsa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1oper__pointsa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>norm</name>
      <anchor>surfit_1_1oper__pointsa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1operD2__recta9</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult_transposed</name>
      <anchor>surfit_1_1operD2__recta10</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N</name>
      <anchor>surfit_1_1oper__pointsp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_solved</name>
      <anchor>surfit_1_1oper__pointsp1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_undefined</name>
      <anchor>surfit_1_1oper__pointsp2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec *</type>
      <name>weights</name>
      <anchor>surfit_1_1oper__pointsp3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>intvec *</type>
      <name>weights_cnt</name>
      <anchor>surfit_1_1oper__pointsp4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::operD1</name>
    <filename>classsurfit_1_1operD1.html</filename>
    <base>surfit::oper</base>
    <member kind="function">
      <type></type>
      <name>operD1</name>
      <anchor>surfit_1_1operD1a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operD1</name>
      <anchor>surfit_1_1operD1a1</anchor>
      <arglist>(int iN, int iNN, REAL ihx, REAL ihy, bitvec *imask_solved, bitvec *imask_undefined, grid_line *ifault)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~operD1</name>
      <anchor>surfit_1_1operD1a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1operD1a3</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>at</name>
      <anchor>surfit_1_1operD1a4</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_line</name>
      <anchor>surfit_1_1operD1a5</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_transposed_line</name>
      <anchor>surfit_1_1operD1a6</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1operD1a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1operD1a8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>norm</name>
      <anchor>surfit_1_1operD1__recta8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1operD2__recta9</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult_transposed</name>
      <anchor>surfit_1_1operD2__recta10</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_mask</name>
      <anchor>surfit_1_1operD1b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>REAL</type>
      <name>operator_serve</name>
      <anchor>surfit_1_1operD1__rectb1</anchor>
      <arglist>(int i, int j, bool first_x, bool second_x, bool first_y, bool second_y, int *next_j) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N</name>
      <anchor>surfit_1_1operD1__rectp8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NN</name>
      <anchor>surfit_1_1operD1__rectp9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MM</name>
      <anchor>surfit_1_1operD1__rectp10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hx2</name>
      <anchor>surfit_1_1operD1__rectp11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hy2</name>
      <anchor>surfit_1_1operD1__rectp12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hx2</name>
      <anchor>surfit_1_1operD1__rectp13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hy2</name>
      <anchor>surfit_1_1operD1__rectp14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_solved</name>
      <anchor>surfit_1_1operD1__rectp15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_undefined</name>
      <anchor>surfit_1_1operD1__rectp16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>grid_line *</type>
      <name>fault</name>
      <anchor>surfit_1_1operD1__rectp17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask</name>
      <anchor>surfit_1_1operD1__rectp18</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::operD1_rect</name>
    <filename>classsurfit_1_1operD1__rect.html</filename>
    <base>surfit::operD1</base>
    <member kind="function">
      <type></type>
      <name>operD1_rect</name>
      <anchor>surfit_1_1operD1__recta0</anchor>
      <arglist>(int iN, int iNN, REAL ihx, REAL ihy, int x_from, int x_to, int y_from, int y_to, bitvec *imask_solved, bitvec *imask_undefined, grid_line *ifault)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~operD1_rect</name>
      <anchor>surfit_1_1operD1__recta1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1operD1__recta2</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>at</name>
      <anchor>surfit_1_1operD1__recta3</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_line</name>
      <anchor>surfit_1_1operD1__recta4</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_transposed_line</name>
      <anchor>surfit_1_1operD1__recta5</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1operD1__recta6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1operD1__recta7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>norm</name>
      <anchor>surfit_1_1operD1__recta8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1operD2__recta9</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult_transposed</name>
      <anchor>surfit_1_1operD2__recta10</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_mask</name>
      <anchor>surfit_1_1operD1__rectb0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>REAL</type>
      <name>operator_serve</name>
      <anchor>surfit_1_1operD1__rectb1</anchor>
      <arglist>(int i, int j, bool first_x, bool second_x, bool first_y, bool second_y, int *next_j) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N_cols</name>
      <anchor>surfit_1_1operD1__rectp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N_rows</name>
      <anchor>surfit_1_1operD1__rectp1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>matrNN</name>
      <anchor>surfit_1_1operD1__rectp2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>matrMM</name>
      <anchor>surfit_1_1operD1__rectp3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>x_from</name>
      <anchor>surfit_1_1operD1__rectp4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>x_to</name>
      <anchor>surfit_1_1operD1__rectp5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>y_from</name>
      <anchor>surfit_1_1operD1__rectp6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>y_to</name>
      <anchor>surfit_1_1operD1__rectp7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N</name>
      <anchor>surfit_1_1operD1__rectp8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NN</name>
      <anchor>surfit_1_1operD1__rectp9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MM</name>
      <anchor>surfit_1_1operD1__rectp10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hx2</name>
      <anchor>surfit_1_1operD1__rectp11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hy2</name>
      <anchor>surfit_1_1operD1__rectp12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hx2</name>
      <anchor>surfit_1_1operD1__rectp13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hy2</name>
      <anchor>surfit_1_1operD1__rectp14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_solved</name>
      <anchor>surfit_1_1operD1__rectp15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_undefined</name>
      <anchor>surfit_1_1operD1__rectp16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>grid_line *</type>
      <name>fault</name>
      <anchor>surfit_1_1operD1__rectp17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask</name>
      <anchor>surfit_1_1operD1__rectp18</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::operD2</name>
    <filename>classsurfit_1_1operD2.html</filename>
    <base>surfit::oper</base>
    <member kind="function">
      <type></type>
      <name>operD2</name>
      <anchor>surfit_1_1operD2a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operD2</name>
      <anchor>surfit_1_1operD2a1</anchor>
      <arglist>(int iN, int iNN, REAL ihx, REAL ihy, bitvec *imask_solved, bitvec *imask_undefined, grid_line *ifault)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1operD2a3</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>at</name>
      <anchor>surfit_1_1operD2a4</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_line</name>
      <anchor>surfit_1_1operD2a5</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_transposed_line</name>
      <anchor>surfit_1_1operD2a6</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1operD2a7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1operD2a8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>norm</name>
      <anchor>surfit_1_1operD2__recta8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1operD2__recta9</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult_transposed</name>
      <anchor>surfit_1_1operD2__recta10</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_mask</name>
      <anchor>surfit_1_1operD2b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>REAL</type>
      <name>operator_serve</name>
      <anchor>surfit_1_1operD2__rectb1</anchor>
      <arglist>(int i, int j, bool first_x, bool second_x, bool third_x, bool first_xx, bool second_xx, bool first_yy, bool second_yy, bool first_y, bool second_y, bool third_y, int *next_j) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N</name>
      <anchor>surfit_1_1operD2__rectp8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NN</name>
      <anchor>surfit_1_1operD2__rectp9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MM</name>
      <anchor>surfit_1_1operD2__rectp10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hx4</name>
      <anchor>surfit_1_1operD2__rectp11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hy4</name>
      <anchor>surfit_1_1operD2__rectp12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hx4</name>
      <anchor>surfit_1_1operD2__rectp13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hy4</name>
      <anchor>surfit_1_1operD2__rectp14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hxy4</name>
      <anchor>surfit_1_1operD2__rectp15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_solved</name>
      <anchor>surfit_1_1operD2__rectp16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_undefined</name>
      <anchor>surfit_1_1operD2__rectp17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>grid_line *</type>
      <name>fault</name>
      <anchor>surfit_1_1operD2__rectp18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask</name>
      <anchor>surfit_1_1operD2__rectp19</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::operD2_rect</name>
    <filename>classsurfit_1_1operD2__rect.html</filename>
    <base>surfit::operD2</base>
    <member kind="function">
      <type></type>
      <name>operD2_rect</name>
      <anchor>surfit_1_1operD2__recta0</anchor>
      <arglist>(int iN, int iNN, REAL ihx, REAL ihy, int x_from, int x_to, int y_from, int y_to, bitvec *imask_solved, bitvec *imask_undefined, grid_line *ifault)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~operD2_rect</name>
      <anchor>surfit_1_1operD2__recta1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>operator()</name>
      <anchor>surfit_1_1operD2__recta2</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>at</name>
      <anchor>surfit_1_1operD2__recta3</anchor>
      <arglist>(int i, int j, int *next_j=NULL) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_line</name>
      <anchor>surfit_1_1operD2__recta4</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mult_transposed_line</name>
      <anchor>surfit_1_1operD2__recta5</anchor>
      <arglist>(int J, const REAL *b_begin, const REAL *b_end) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>cols</name>
      <anchor>surfit_1_1operD2__recta6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual long</type>
      <name>rows</name>
      <anchor>surfit_1_1operD2__recta7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>norm</name>
      <anchor>surfit_1_1operD2__recta8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1operD2__recta9</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult_transposed</name>
      <anchor>surfit_1_1operD2__recta10</anchor>
      <arglist>(vec *b, vec *r)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeMAT</name>
      <anchor>surfit_1_1operD2__recta11</anchor>
      <arglist>(const char *filename, const char *name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_mask</name>
      <anchor>surfit_1_1operD2__rectb0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>REAL</type>
      <name>operator_serve</name>
      <anchor>surfit_1_1operD2__rectb1</anchor>
      <arglist>(int i, int j, bool first_x, bool second_x, bool third_x, bool first_xx, bool second_xx, bool first_yy, bool second_yy, bool first_y, bool second_y, bool third_y, int *next_j) const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N_cols</name>
      <anchor>surfit_1_1operD2__rectp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N_rows</name>
      <anchor>surfit_1_1operD2__rectp1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>matrNN</name>
      <anchor>surfit_1_1operD2__rectp2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>matrMM</name>
      <anchor>surfit_1_1operD2__rectp3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>x_from</name>
      <anchor>surfit_1_1operD2__rectp4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>x_to</name>
      <anchor>surfit_1_1operD2__rectp5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>y_from</name>
      <anchor>surfit_1_1operD2__rectp6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>y_to</name>
      <anchor>surfit_1_1operD2__rectp7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>N</name>
      <anchor>surfit_1_1operD2__rectp8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>NN</name>
      <anchor>surfit_1_1operD2__rectp9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>MM</name>
      <anchor>surfit_1_1operD2__rectp10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hx4</name>
      <anchor>surfit_1_1operD2__rectp11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>hy4</name>
      <anchor>surfit_1_1operD2__rectp12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hx4</name>
      <anchor>surfit_1_1operD2__rectp13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hy4</name>
      <anchor>surfit_1_1operD2__rectp14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REAL</type>
      <name>_hxy4</name>
      <anchor>surfit_1_1operD2__rectp15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_solved</name>
      <anchor>surfit_1_1operD2__rectp16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask_undefined</name>
      <anchor>surfit_1_1operD2__rectp17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>grid_line *</type>
      <name>fault</name>
      <anchor>surfit_1_1operD2__rectp18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bitvec *</type>
      <name>mask</name>
      <anchor>surfit_1_1operD2__rectp19</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::points</name>
    <filename>classsurfit_1_1points.html</filename>
    <member kind="function">
      <type></type>
      <name>points</name>
      <anchor>surfit_1_1pointsa0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>points</name>
      <anchor>surfit_1_1pointsa1</anchor>
      <arglist>(REAL *&amp;X_begin, REAL *X_end, REAL *&amp;Y_begin, REAL *Y_end, REAL *&amp;Z_begin, REAL *Z_end, const char *points_name=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~points</name>
      <anchor>surfit_1_1pointsa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wtaska5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mean</name>
      <anchor>surfit_1_1wtaska6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wtaska7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wtaska8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wtaska9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wtaska10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minz</name>
      <anchor>surfit_1_1wtaska11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxz</name>
      <anchor>surfit_1_1wtaska12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>std</name>
      <anchor>surfit_1_1wtaska13</anchor>
      <arglist>(REAL mean) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska14</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska16</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska18</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska20</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska22</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska15</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska17</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska19</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska21</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wtasko2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wtasko3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wtasko4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wtasko5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_begin</name>
      <anchor>surfit_1_1wtasko6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_end</name>
      <anchor>surfit_1_1wtasko7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::sub_points</name>
    <filename>classsurfit_1_1sub__points.html</filename>
    <member kind="function">
      <type></type>
      <name>sub_points</name>
      <anchor>surfit_1_1sub__pointsa0</anchor>
      <arglist>(int icell_number, std::vector&lt; unsigned int &gt; *ipoint_numbers)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~sub_points</name>
      <anchor>surfit_1_1sub__pointsa1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>value</name>
      <anchor>surfit_1_1sub__pointsa2</anchor>
      <arglist>(const points *pnts) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>sum_value</name>
      <anchor>surfit_1_1sub__pointsa3</anchor>
      <arglist>(const points *pnts) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>value</name>
      <anchor>surfit_1_1sub__pointsa4</anchor>
      <arglist>(const wtask *wtsk) const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>weight</name>
      <anchor>surfit_1_1sub__pointsa5</anchor>
      <arglist>(const wtask *wtsk) const </arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>cell_number</name>
      <anchor>surfit_1_1sub__pointso0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; unsigned int &gt; *</type>
      <name>point_numbers</name>
      <anchor>surfit_1_1sub__pointso1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::task</name>
    <filename>classsurfit_1_1task.html</filename>
    <base>surfit::points</base>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>task</name>
      <anchor>surfit_1_1taska0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>task</name>
      <anchor>surfit_1_1taska1</anchor>
      <arglist>(REAL *&amp;X_begin, REAL *X_end, REAL *&amp;Y_begin, REAL *Y_end, REAL *&amp;Z_begin, REAL *Z_end, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1taska3</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wtaska4</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wtaska5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mean</name>
      <anchor>surfit_1_1wtaska6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wtaska7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wtaska8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wtaska9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wtaska10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minz</name>
      <anchor>surfit_1_1wtaska11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxz</name>
      <anchor>surfit_1_1wtaska12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>std</name>
      <anchor>surfit_1_1wtaska13</anchor>
      <arglist>(REAL mean) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska14</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska15</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska16</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska17</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska18</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska19</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska20</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska21</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska22</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wtasko2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wtasko3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wtasko4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wtasko5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_begin</name>
      <anchor>surfit_1_1wtasko6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_end</name>
      <anchor>surfit_1_1wtasko7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::task_user</name>
    <filename>classsurfit_1_1task__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>task_user</name>
      <anchor>surfit_1_1task__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~task_user</name>
      <anchor>surfit_1_1task__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1task__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1task__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1task__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1task__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1task__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1task__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1task__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1task__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1task__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1task__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1task__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::trend</name>
    <filename>classsurfit_1_1trend.html</filename>
    <base>surfit::func</base>
    <member kind="function">
      <type></type>
      <name>trend</name>
      <anchor>surfit_1_1trenda0</anchor>
      <arglist>(vec *icoeff, grid *igrd, REAL D1, REAL D2, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>trend</name>
      <anchor>surfit_1_1trenda1</anchor>
      <arglist>(func *&amp;fnc, REAL D1, REAL D2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>writeTags</name>
      <anchor>surfit_1_1trenda2</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getValue</name>
      <anchor>surfit_1_1wfunca4</anchor>
      <arglist>(REAL x, REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinX</name>
      <anchor>surfit_1_1wfunca5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxX</name>
      <anchor>surfit_1_1wfunca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinY</name>
      <anchor>surfit_1_1wfunca7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxY</name>
      <anchor>surfit_1_1wfunca8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>mean</name>
      <anchor>surfit_1_1wfunca9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>std</name>
      <anchor>surfit_1_1wfunca10</anchor>
      <arglist>(REAL mean) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>sum</name>
      <anchor>surfit_1_1wfunca11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wfunca12</anchor>
      <arglist>(REAL &amp;minZ, REAL &amp;maxZ) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getTrianglesCount</name>
      <anchor>surfit_1_1wfunca13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getTrianglesCount</name>
      <anchor>surfit_1_1wfunca14</anchor>
      <arglist>(const REAL &amp;show_x_from, const REAL &amp;show_x_to, const REAL &amp;show_y_from, const REAL &amp;show_y_to)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getTriangle</name>
      <anchor>surfit_1_1wfunca15</anchor>
      <arglist>(int triangle_number, REAL &amp;x0, REAL &amp;y0, REAL &amp;z0, REAL &amp;x1, REAL &amp;y1, REAL &amp;z1, REAL &amp;x2, REAL &amp;y2, REAL &amp;z2) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getTriangle</name>
      <anchor>surfit_1_1wfunca16</anchor>
      <arglist>(int triangle_number, REAL &amp;x0, REAL &amp;y0, REAL &amp;z0, REAL &amp;x1, REAL &amp;y1, REAL &amp;z1, REAL &amp;x2, REAL &amp;y2, REAL &amp;z2, const REAL &amp;show_x_from, const REAL &amp;show_x_to, const REAL &amp;show_y_from, const REAL &amp;show_y_to) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountX</name>
      <anchor>surfit_1_1wfunca17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountY</name>
      <anchor>surfit_1_1wfunca18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getStepX</name>
      <anchor>surfit_1_1wfunca19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getStepY</name>
      <anchor>surfit_1_1wfunca20</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getCoordNode</name>
      <anchor>surfit_1_1wfunca21</anchor>
      <arglist>(int i, int j, REAL &amp;x, REAL &amp;y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getCoordNodeX</name>
      <anchor>surfit_1_1wfunca22</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getCoordNodeY</name>
      <anchor>surfit_1_1wfunca23</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_i</name>
      <anchor>surfit_1_1wfunca24</anchor>
      <arglist>(REAL x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_j</name>
      <anchor>surfit_1_1wfunca25</anchor>
      <arglist>(REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>defined</name>
      <anchor>surfit_1_1wfunca26</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>compare_grid</name>
      <anchor>surfit_1_1wfunca27</anchor>
      <arglist>(const func *fnc) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>plus</name>
      <anchor>surfit_1_1wfunca28</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>plus</name>
      <anchor>surfit_1_1wfunca29</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus</name>
      <anchor>surfit_1_1wfunca30</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus</name>
      <anchor>surfit_1_1wfunca31</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus_undef</name>
      <anchor>surfit_1_1wfunca32</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>mult</name>
      <anchor>surfit_1_1wfunca33</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>mult</name>
      <anchor>surfit_1_1wfunca34</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>div</name>
      <anchor>surfit_1_1wfunca35</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>div</name>
      <anchor>surfit_1_1wfunca36</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set</name>
      <anchor>surfit_1_1wfunca37</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set</name>
      <anchor>surfit_1_1wfunca38</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>add_noise</name>
      <anchor>surfit_1_1wfunca39</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wfunca40</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>decompose</name>
      <anchor>surfit_1_1wfunca41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>auto_decompose</name>
      <anchor>surfit_1_1wfunca42</anchor>
      <arglist>(REAL eps, int norm=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>reconstruct</name>
      <anchor>surfit_1_1wfunca43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>full_reconstruct</name>
      <anchor>surfit_1_1wfunca44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>details_size</name>
      <anchor>surfit_1_1wfunca45</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>calc_approx_norm</name>
      <anchor>surfit_1_1wfunca46</anchor>
      <arglist>(int norm_type) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>D1</name>
      <anchor>surfit_1_1trendo0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>D2</name>
      <anchor>surfit_1_1trendo1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>grid *</type>
      <name>grd</name>
      <anchor>surfit_1_1wfunco1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vec *</type>
      <name>coeff</name>
      <anchor>surfit_1_1wfunco2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>show_smooth</name>
      <anchor>surfit_1_1wfunco3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>undef_value</name>
      <anchor>surfit_1_1wfunco4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_h</name>
      <anchor>surfit_1_1wfunco5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_v</name>
      <anchor>surfit_1_1wfunco6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_d</name>
      <anchor>surfit_1_1wfunco7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; bool &gt; *</type>
      <name>enlarges_X</name>
      <anchor>surfit_1_1wfunco8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; bool &gt; *</type>
      <name>enlarges_Y</name>
      <anchor>surfit_1_1wfunco9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_i_from</name>
      <anchor>surfit_1_1wfuncp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_i_to</name>
      <anchor>surfit_1_1wfuncp1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_j_from</name>
      <anchor>surfit_1_1wfuncp2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_j_to</name>
      <anchor>surfit_1_1wfuncp3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::trend_user</name>
    <filename>classsurfit_1_1trend__user.html</filename>
    <base>surfit::user</base>
    <base>surfit::modifier1</base>
    <member kind="function">
      <type></type>
      <name>trend_user</name>
      <anchor>surfit_1_1trend__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~trend_user</name>
      <anchor>surfit_1_1trend__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1trend__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1trend__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1trend__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1trend__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1trend__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1trend__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1trend__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1trend__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1trend__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1trend__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1trend__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec *</type>
      <name>get_weights</name>
      <anchor>surfit_1_1trend__usera13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual intvec *</type>
      <name>get_weights_cnt</name>
      <anchor>surfit_1_1trend__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_weights</name>
      <anchor>surfit_1_1trend__usera15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_weights_cnt</name>
      <anchor>surfit_1_1trend__usera16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::binman</name>
    <filename>classsurfit_1_1binman.html</filename>
  </compound>
  <compound kind="class">
    <name>surfit::modifier1</name>
    <filename>classsurfit_1_1modifier1.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual vec *</type>
      <name>get_weights</name>
      <anchor>surfit_1_1modifier1a0</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual intvec *</type>
      <name>get_weights_cnt</name>
      <anchor>surfit_1_1modifier1a1</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>remove_weights</name>
      <anchor>surfit_1_1modifier1a2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>remove_weights_cnt</name>
      <anchor>surfit_1_1modifier1a3</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::user</name>
    <filename>classsurfit_1_1user.html</filename>
    <member kind="function">
      <type></type>
      <name>user</name>
      <anchor>surfit_1_1usera0</anchor>
      <arglist>(const char *iname)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~user</name>
      <anchor>surfit_1_1usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1usera4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>init</name>
      <anchor>surfit_1_1usera5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>prepare</name>
      <anchor>surfit_1_1usera6</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>begin</name>
      <anchor>surfit_1_1usera7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stage1</name>
      <anchor>surfit_1_1usera8</anchor>
      <arglist>(int priority)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stage2</name>
      <anchor>surfit_1_1usera9</anchor>
      <arglist>(int priority)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stage3</name>
      <anchor>surfit_1_1usera10</anchor>
      <arglist>(int priority)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stage4</name>
      <anchor>surfit_1_1usera11</anchor>
      <arglist>(int priority)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stage5</name>
      <anchor>surfit_1_1usera12</anchor>
      <arglist>(int priority)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>finish</name>
      <anchor>surfit_1_1usera13</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>release</name>
      <anchor>surfit_1_1usera14</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::vec</name>
    <filename>classsurfit_1_1vec.html</filename>
    <member kind="typedef">
      <type>REAL *</type>
      <name>iterator</name>
      <anchor>surfit_1_1vecw0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>REAL &amp;</type>
      <name>reference</name>
      <anchor>surfit_1_1vecw1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const REAL *</type>
      <name>const_iterator</name>
      <anchor>surfit_1_1vecw2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>const REAL &amp;</type>
      <name>const_reference</name>
      <anchor>surfit_1_1vecw3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>vec</name>
      <anchor>surfit_1_1veca0</anchor>
      <arglist>(int size=0, REAL default_value=REAL(0), int fill_default=1, int grow_by=250)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>vec</name>
      <anchor>surfit_1_1veca1</anchor>
      <arglist>(REAL *vec_begin, REAL *vec_end)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>vec</name>
      <anchor>surfit_1_1veca2</anchor>
      <arglist>(const vec &amp;in)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~vec</name>
      <anchor>surfit_1_1veca3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL *</type>
      <name>begin</name>
      <anchor>surfit_1_1veca4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL *&amp;</type>
      <name>ref_begin</name>
      <anchor>surfit_1_1veca5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const REAL *</type>
      <name>begin</name>
      <anchor>surfit_1_1veca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL *</type>
      <name>end</name>
      <anchor>surfit_1_1veca7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const REAL *</type>
      <name>end</name>
      <anchor>surfit_1_1veca8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>erase</name>
      <anchor>surfit_1_1veca9</anchor>
      <arglist>(REAL *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>erase</name>
      <anchor>surfit_1_1veca10</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchor>surfit_1_1veca11</anchor>
      <arglist>(int newsize, REAL default_value=REAL(0), int fill_default=1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1veca12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL &amp;</type>
      <name>operator()</name>
      <anchor>surfit_1_1veca13</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>const REAL &amp;</type>
      <name>operator()</name>
      <anchor>surfit_1_1veca14</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>vec &amp;</type>
      <name>operator=</name>
      <anchor>surfit_1_1veca15</anchor>
      <arglist>(const vec &amp;copy)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>push_back</name>
      <anchor>surfit_1_1veca16</anchor>
      <arglist>(const REAL &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reserve</name>
      <anchor>surfit_1_1veca17</anchor>
      <arglist>(int reserve_size)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_grow</name>
      <anchor>surfit_1_1veca18</anchor>
      <arglist>(int grow_by)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>swap</name>
      <anchor>surfit_1_1veca19</anchor>
      <arglist>(int i, int j)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drop_data</name>
      <anchor>surfit_1_1veca20</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>getPointer</name>
      <anchor>surfit_1_1veca21</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>data</name>
      <anchor>surfit_1_1veco0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>datasize</name>
      <anchor>surfit_1_1veco1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>real_datasize</name>
      <anchor>surfit_1_1veco2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>grow_by</name>
      <anchor>surfit_1_1veco3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::warea</name>
    <filename>classsurfit_1_1warea.html</filename>
    <base>surfit::area</base>
    <member kind="function">
      <type></type>
      <name>warea</name>
      <anchor>surfit_1_1wareaa0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL ivalue, REAL iweight, const char *warea_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>warea</name>
      <anchor>surfit_1_1wareaa1</anchor>
      <arglist>(curv *crv, REAL ivalue, REAL iweight)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~warea</name>
      <anchor>surfit_1_1wareaa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wareaa3</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>weight</name>
      <anchor>surfit_1_1wareao0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>value</name>
      <anchor>surfit_1_1wareao1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::warea_user</name>
    <filename>classsurfit_1_1warea__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>warea_user</name>
      <anchor>surfit_1_1warea__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~warea_user</name>
      <anchor>surfit_1_1warea__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1warea__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1warea__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1warea__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1warea__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1warea__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1warea__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1warea__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1warea__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1warea__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1warea__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1warea__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wcntr</name>
    <filename>classsurfit_1_1wcntr.html</filename>
    <base>surfit::cntr</base>
    <member kind="function">
      <type></type>
      <name>wcntr</name>
      <anchor>surfit_1_1wcntra0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL *iZ_begin, REAL *iZ_end, REAL iweight, const char *cntr_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~wcntr</name>
      <anchor>surfit_1_1wcntra1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>plus</name>
      <anchor>surfit_1_1wcntra2</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minus</name>
      <anchor>surfit_1_1wcntra3</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1wcntra4</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>div</name>
      <anchor>surfit_1_1wcntra5</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minz</name>
      <anchor>surfit_1_1wcntra6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxz</name>
      <anchor>surfit_1_1wcntra7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wcntra8</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>weight</name>
      <anchor>surfit_1_1wcntro0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_begin</name>
      <anchor>surfit_1_1wcntro1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_end</name>
      <anchor>surfit_1_1wcntro2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wcntr_user</name>
    <filename>classsurfit_1_1wcntr__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>wcntr_user</name>
      <anchor>surfit_1_1wcntr__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~wcntr_user</name>
      <anchor>surfit_1_1wcntr__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1wcntr__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1wcntr__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1wcntr__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1wcntr__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1wcntr__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1wcntr__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1wcntr__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1wcntr__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1wcntr__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1wcntr__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1wcntr__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wfunc</name>
    <filename>classsurfit_1_1wfunc.html</filename>
    <base>surfit::func</base>
    <member kind="function">
      <type></type>
      <name>wfunc</name>
      <anchor>surfit_1_1wfunca0</anchor>
      <arglist>(vec *icoeff, grid *igrd, REAL iweight, const char *funcname=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wfunc</name>
      <anchor>surfit_1_1wfunca1</anchor>
      <arglist>(func *fnc, REAL iweight, const char *funcname=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~wfunc</name>
      <anchor>surfit_1_1wfunca2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>writeTags</name>
      <anchor>surfit_1_1wfunca3</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getValue</name>
      <anchor>surfit_1_1wfunca4</anchor>
      <arglist>(REAL x, REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinX</name>
      <anchor>surfit_1_1wfunca5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxX</name>
      <anchor>surfit_1_1wfunca6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMinY</name>
      <anchor>surfit_1_1wfunca7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getMaxY</name>
      <anchor>surfit_1_1wfunca8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>mean</name>
      <anchor>surfit_1_1wfunca9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>std</name>
      <anchor>surfit_1_1wfunca10</anchor>
      <arglist>(REAL mean) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>sum</name>
      <anchor>surfit_1_1wfunca11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wfunca12</anchor>
      <arglist>(REAL &amp;minZ, REAL &amp;maxZ) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getTrianglesCount</name>
      <anchor>surfit_1_1wfunca13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getTrianglesCount</name>
      <anchor>surfit_1_1wfunca14</anchor>
      <arglist>(const REAL &amp;show_x_from, const REAL &amp;show_x_to, const REAL &amp;show_y_from, const REAL &amp;show_y_to)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getTriangle</name>
      <anchor>surfit_1_1wfunca15</anchor>
      <arglist>(int triangle_number, REAL &amp;x0, REAL &amp;y0, REAL &amp;z0, REAL &amp;x1, REAL &amp;y1, REAL &amp;z1, REAL &amp;x2, REAL &amp;y2, REAL &amp;z2) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getTriangle</name>
      <anchor>surfit_1_1wfunca16</anchor>
      <arglist>(int triangle_number, REAL &amp;x0, REAL &amp;y0, REAL &amp;z0, REAL &amp;x1, REAL &amp;y1, REAL &amp;z1, REAL &amp;x2, REAL &amp;y2, REAL &amp;z2, const REAL &amp;show_x_from, const REAL &amp;show_x_to, const REAL &amp;show_y_from, const REAL &amp;show_y_to) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountX</name>
      <anchor>surfit_1_1wfunca17</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>getCountY</name>
      <anchor>surfit_1_1wfunca18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getStepX</name>
      <anchor>surfit_1_1wfunca19</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getStepY</name>
      <anchor>surfit_1_1wfunca20</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>getCoordNode</name>
      <anchor>surfit_1_1wfunca21</anchor>
      <arglist>(int i, int j, REAL &amp;x, REAL &amp;y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getCoordNodeX</name>
      <anchor>surfit_1_1wfunca22</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>getCoordNodeY</name>
      <anchor>surfit_1_1wfunca23</anchor>
      <arglist>(int j) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_i</name>
      <anchor>surfit_1_1wfunca24</anchor>
      <arglist>(REAL x) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_j</name>
      <anchor>surfit_1_1wfunca25</anchor>
      <arglist>(REAL y) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>defined</name>
      <anchor>surfit_1_1wfunca26</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>compare_grid</name>
      <anchor>surfit_1_1wfunca27</anchor>
      <arglist>(const func *fnc) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>plus</name>
      <anchor>surfit_1_1wfunca28</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>plus</name>
      <anchor>surfit_1_1wfunca29</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus</name>
      <anchor>surfit_1_1wfunca30</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus</name>
      <anchor>surfit_1_1wfunca31</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>minus_undef</name>
      <anchor>surfit_1_1wfunca32</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>mult</name>
      <anchor>surfit_1_1wfunca33</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>mult</name>
      <anchor>surfit_1_1wfunca34</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>div</name>
      <anchor>surfit_1_1wfunca35</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>div</name>
      <anchor>surfit_1_1wfunca36</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set</name>
      <anchor>surfit_1_1wfunca37</anchor>
      <arglist>(const func *fnc)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set</name>
      <anchor>surfit_1_1wfunca38</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>add_noise</name>
      <anchor>surfit_1_1wfunca39</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wfunca40</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>decompose</name>
      <anchor>surfit_1_1wfunca41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>auto_decompose</name>
      <anchor>surfit_1_1wfunca42</anchor>
      <arglist>(REAL eps, int norm=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>reconstruct</name>
      <anchor>surfit_1_1wfunca43</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>full_reconstruct</name>
      <anchor>surfit_1_1wfunca44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>details_size</name>
      <anchor>surfit_1_1wfunca45</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual REAL</type>
      <name>calc_approx_norm</name>
      <anchor>surfit_1_1wfunca46</anchor>
      <arglist>(int norm_type) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>weight</name>
      <anchor>surfit_1_1wfunco0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>grid *</type>
      <name>grd</name>
      <anchor>surfit_1_1wfunco1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vec *</type>
      <name>coeff</name>
      <anchor>surfit_1_1wfunco2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>show_smooth</name>
      <anchor>surfit_1_1wfunco3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>undef_value</name>
      <anchor>surfit_1_1wfunco4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_h</name>
      <anchor>surfit_1_1wfunco5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_v</name>
      <anchor>surfit_1_1wfunco6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; vec * &gt; *</type>
      <name>details_d</name>
      <anchor>surfit_1_1wfunco7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; bool &gt; *</type>
      <name>enlarges_X</name>
      <anchor>surfit_1_1wfunco8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; bool &gt; *</type>
      <name>enlarges_Y</name>
      <anchor>surfit_1_1wfunco9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_i_from</name>
      <anchor>surfit_1_1wfuncp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_i_to</name>
      <anchor>surfit_1_1wfuncp1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_j_from</name>
      <anchor>surfit_1_1wfuncp2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>show_j_to</name>
      <anchor>surfit_1_1wfuncp3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wfunc_user</name>
    <filename>classsurfit_1_1wfunc__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>wfunc_user</name>
      <anchor>surfit_1_1wfunc__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~wfunc_user</name>
      <anchor>surfit_1_1wfunc__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1wfunc__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1wfunc__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1wfunc__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1wfunc__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1wfunc__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1wfunc__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1wfunc__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1wfunc__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1wfunc__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1wfunc__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1wfunc__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wiso</name>
    <filename>classsurfit_1_1wiso.html</filename>
    <base>surfit::iso</base>
    <member kind="function">
      <type></type>
      <name>wiso</name>
      <anchor>surfit_1_1wisoa0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL ivalue, REAL iweight, const char *iso_name=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wiso</name>
      <anchor>surfit_1_1wisoa1</anchor>
      <arglist>(curv *crv, REAL ivalue, REAL iweight)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wiso</name>
      <anchor>surfit_1_1wisoa2</anchor>
      <arglist>(iso *crv, REAL iweight)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~wiso</name>
      <anchor>surfit_1_1wisoa3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wisoa4</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>weight</name>
      <anchor>surfit_1_1wisoo0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>value</name>
      <anchor>surfit_1_1wisoo1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wisoo2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wisoo3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wisoo4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wisoo5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wiso_user</name>
    <filename>classsurfit_1_1wiso__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1wiso__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1wiso__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1wiso__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1wiso__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1wiso__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1wiso__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1wiso__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1wiso__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1wiso__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1wiso__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1wiso__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wtask</name>
    <filename>classsurfit_1_1wtask.html</filename>
    <base>surfit::task</base>
    <member kind="function">
      <type></type>
      <name>wtask</name>
      <anchor>surfit_1_1wtaska0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>wtask</name>
      <anchor>surfit_1_1wtaska1</anchor>
      <arglist>(REAL *&amp;X_begin, REAL *X_end, REAL *&amp;Y_begin, REAL *Y_end, REAL *&amp;Z_begin, REAL *Z_end, REAL *&amp;W_begin, REAL *W_end, const char *taskname=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~wtask</name>
      <anchor>surfit_1_1wtaska2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wtaska3</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1wtaska4</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wtaska5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mean</name>
      <anchor>surfit_1_1wtaska6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wtaska7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wtaska8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wtaska9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wtaska10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minz</name>
      <anchor>surfit_1_1wtaska11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxz</name>
      <anchor>surfit_1_1wtaska12</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>std</name>
      <anchor>surfit_1_1wtaska13</anchor>
      <arglist>(REAL mean) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska14</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska15</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska16</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska17</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska18</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska19</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska20</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska21</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska22</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska27</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>W_begin</name>
      <anchor>surfit_1_1wtasko0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>W_end</name>
      <anchor>surfit_1_1wtasko1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_begin</name>
      <anchor>surfit_1_1wtasko2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>X_end</name>
      <anchor>surfit_1_1wtasko3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_begin</name>
      <anchor>surfit_1_1wtasko4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Y_end</name>
      <anchor>surfit_1_1wtasko5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_begin</name>
      <anchor>surfit_1_1wtasko6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL *</type>
      <name>Z_end</name>
      <anchor>surfit_1_1wtasko7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>priority</name>
      <anchor>surfit_1_1wtaskp0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtaskp1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::wtask_user</name>
    <filename>classsurfit_1_1wtask__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>wtask_user</name>
      <anchor>surfit_1_1wtask__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~wtask_user</name>
      <anchor>surfit_1_1wtask__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1wtask__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1wtask__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1wtask__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1wtask__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1wtask__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1wtask__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1wtask__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1wtask__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1wtask__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1wtask__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1wtask__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtask__usera13</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtask__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>name</name>
      <anchor>surfit_1_1wtask__userp0</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
