<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="group">
    <name>freeflow_internal</name>
    <title>C/C++ functions and variables reference</title>
    <filename>group__freeflow__internal.html</filename>
    <subgroup>internal_pfunc</subgroup>
    <subgroup>internal_ptask</subgroup>
    <subgroup>internal_pcurv</subgroup>
    <subgroup>internal_lcm_simple</subgroup>
  </compound>
  <compound kind="group">
    <name>internal_pfunc</name>
    <title>func</title>
    <filename>group__internal__pfunc.html</filename>
    <member kind="function">
      <type>REAL</type>
      <name>_func_debit</name>
      <anchor>ga0</anchor>
      <arglist>(func *fnc, REAL x, REAL y)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>_func_debit_rect</name>
      <anchor>ga1</anchor>
      <arglist>(func *fnc, REAL x1, REAL y1, REAL x2, REAL y2)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_ptask</name>
    <title>ptask</title>
    <filename>group__internal__ptask.html</filename>
    <member kind="function">
      <type>ptask *</type>
      <name>_ptask_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *ptaskname, int columns, int col1, int col2, int col3, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>ptask *</type>
      <name>_ptask_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *ptaskname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>ptask *</type>
      <name>_ptask_load_df</name>
      <anchor>ga2</anchor>
      <arglist>(datafile *df, const char *ptaskname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_ptask_write</name>
      <anchor>ga3</anchor>
      <arglist>(ptask *ptsk, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_ptask_save</name>
      <anchor>ga4</anchor>
      <arglist>(ptask *ptsk, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_ptask_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(ptask *ptsk, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_ptask_check</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_sort_ptask</name>
      <anchor>ga7</anchor>
      <arglist>(ptask *ptsk, std::vector&lt; unsigned int &gt; *nums, REAL **&amp;sortx_begin, REAL **&amp;sortx_end, REAL **&amp;sorty_begin, REAL **&amp;sorty_end)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_ptask_info</name>
      <anchor>ga8</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_ptask_transform</name>
      <anchor>ga9</anchor>
      <arglist>(ptask *ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_inverse_ptask_transform</name>
      <anchor>ga10</anchor>
      <arglist>(ptask *ptsk, REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>ptask *</type>
      <name>_get_flow_ptask</name>
      <anchor>ga11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_flow_ptask</name>
      <anchor>ga12</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_flow_ptasks</name>
      <anchor>ga13</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_pcurv</name>
    <title>curves</title>
    <filename>group__internal__pcurv.html</filename>
    <subgroup>internal_parea</subgroup>
    <subgroup>internal_piso</subgroup>
    <subgroup>internal_pcntr</subgroup>
  </compound>
  <compound kind="group">
    <name>internal_parea</name>
    <title>parea</title>
    <filename>group__internal__parea.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_parea_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_parea_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>parea *</type>
      <name>_parea_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pareaname, REAL value, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_parea_write</name>
      <anchor>ga3</anchor>
      <arglist>(parea *parealine, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_parea_save</name>
      <anchor>ga4</anchor>
      <arglist>(parea *parealine, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_parea_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(parea *ar, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>parea *</type>
      <name>_parea_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *pareaname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>parea *</type>
      <name>_parea_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *pareaname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_parea_info</name>
      <anchor>ga8</anchor>
      <arglist>(parea *parealine)</arglist>
    </member>
    <member kind="function">
      <type>parea *</type>
      <name>_get_flow_parea</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_flow_parea</name>
      <anchor>ga10</anchor>
      <arglist>(parea *parealine)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_flow_pareas</name>
      <anchor>ga11</anchor>
      <arglist>(parea *parealine)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_piso</name>
    <title>piso</title>
    <filename>group__internal__piso.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_piso_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_piso_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>piso *</type>
      <name>_piso_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pisoname, REAL value, int columns, int col1, int col2, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_piso_write</name>
      <anchor>ga3</anchor>
      <arglist>(piso *pisoline, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_piso_save</name>
      <anchor>ga4</anchor>
      <arglist>(piso *pisoline, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_piso_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(piso *pisoline, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>piso *</type>
      <name>_piso_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *pisoname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>piso *</type>
      <name>_piso_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *pisoname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_piso_info</name>
      <anchor>ga8</anchor>
      <arglist>(piso *pisoline)</arglist>
    </member>
    <member kind="function">
      <type>piso *</type>
      <name>_get_flow_piso</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_flow_piso</name>
      <anchor>ga10</anchor>
      <arglist>(piso *pisoline)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_flow_pisos</name>
      <anchor>ga11</anchor>
      <arglist>(piso *pisoline)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_pcntr</name>
    <title>pcntr</title>
    <filename>group__internal__pcntr.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>_pcntr_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_pcntr_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>pcntr *</type>
      <name>_pcntr_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pcntrname, int columns, int col1, int col2, int col3, int grow_by, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_pcntr_write</name>
      <anchor>ga3</anchor>
      <arglist>(pcntr *pcntrline, const char *filename, const char *mask)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_pcntr_save</name>
      <anchor>ga4</anchor>
      <arglist>(pcntr *contour, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_pcntr_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(pcntr *contour, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>pcntr *</type>
      <name>_pcntr_load</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *pcntrname, int mode)</arglist>
    </member>
    <member kind="function">
      <type>pcntr *</type>
      <name>_pcntr_load_df</name>
      <anchor>ga7</anchor>
      <arglist>(datafile *df, const char *pcntrname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_pcntr_info</name>
      <anchor>ga8</anchor>
      <arglist>(pcntr *pcntrline)</arglist>
    </member>
    <member kind="function">
      <type>pcntr *</type>
      <name>_get_flow_pcntr</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_flow_pcntr</name>
      <anchor>ga10</anchor>
      <arglist>(pcntr *contour)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_add_flow_pcntrs</name>
      <anchor>ga11</anchor>
      <arglist>(pcntr *contour)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>internal_lcm_simple</name>
    <title>lcm_simple</title>
    <filename>group__internal__lcm__simple.html</filename>
    <member kind="function">
      <type>lcm_simple *</type>
      <name>_lcm_simple_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *lcm_simple_name)</arglist>
    </member>
    <member kind="function">
      <type>lcm_simple *</type>
      <name>_lcm_simple_load</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *lcm_simple_name, int mode)</arglist>
    </member>
    <member kind="function">
      <type>lcm_simple *</type>
      <name>_lcm_simple_load_df</name>
      <anchor>ga2</anchor>
      <arglist>(datafile *df, const char *lcm_simple_name)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_lcm_simple_write</name>
      <anchor>ga3</anchor>
      <arglist>(lcm_simple *lcm, const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_lcm_simple_save</name>
      <anchor>ga4</anchor>
      <arglist>(lcm_simple *lcm, const char *filename, int mode)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_lcm_simple_save_df</name>
      <anchor>ga5</anchor>
      <arglist>(lcm_simple *lcm, datafile *df)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>_lcm_simple_check</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>_lcm_simple_info</name>
      <anchor>ga7</anchor>
      <arglist>(lcm_simple *lcm)</arglist>
    </member>
    <member kind="function">
      <type>lcm_simple *</type>
      <name>_get_flow_lcm_simple</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>_set_flow_lcm_simple</name>
      <anchor>ga9</anchor>
      <arglist>(lcm_simple *lcm)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>flow_tcl</name>
    <title>Tcl commands and variables reference</title>
    <filename>group__flow__tcl.html</filename>
    <subgroup>flow_variables</subgroup>
    <subgroup>tcl_pfunc</subgroup>
    <subgroup>tcl_ptask</subgroup>
    <subgroup>tcl_pcurves</subgroup>
    <subgroup>tcl_lcm_simple</subgroup>
  </compound>
  <compound kind="group">
    <name>flow_variables</name>
    <title>freeflow variables</title>
    <filename>group__flow__variables.html</filename>
    <subgroup>flow_data_variables</subgroup>
  </compound>
  <compound kind="group">
    <name>flow_data_variables</name>
    <title>freeflow data variables</title>
    <filename>group__flow__data__variables.html</filename>
    <subgroup>flow_variables_collections</subgroup>
    <member kind="variable">
      <type>lcm_simple *</type>
      <name>flow_lcm_simple</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parea *</type>
      <name>flow_parea</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>pcntr *</type>
      <name>flow_pcntr</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>piso *</type>
      <name>flow_piso</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ptask *</type>
      <name>flow_ptask</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>flow_variables_collections</name>
    <title>collections of freeflow variables</title>
    <filename>group__flow__variables__collections.html</filename>
    <member kind="variable">
      <type>std::vector&lt; parea * &gt; *</type>
      <name>flow_pareas</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; pcntr * &gt; *</type>
      <name>flow_pcntrs</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; piso * &gt; *</type>
      <name>flow_pisos</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; ptask * &gt; *</type>
      <name>flow_ptasks</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pfunc</name>
    <title>operations with functions (func)</title>
    <filename>group__tcl__pfunc.html</filename>
    <member kind="function">
      <type>REAL</type>
      <name>func_debit</name>
      <anchor>ga0</anchor>
      <arglist>(REAL x, REAL y)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>func_debit_rect</name>
      <anchor>ga1</anchor>
      <arglist>(REAL x1, REAL y1, REAL x2, REAL y2)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_ptask</name>
    <title>scattered production points (ptask)</title>
    <filename>group__tcl__ptask.html</filename>
    <subgroup>tcl_ptask_save_load</subgroup>
    <subgroup>tcl_ptask_math</subgroup>
    <subgroup>tcl_ptask_conv</subgroup>
    <subgroup>tcl_ptask_other</subgroup>
    <subgroup>tcl_ptasks</subgroup>
    <subgroup>tcl_ptask_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_ptask_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__ptask__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>ptask_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *ptaskname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ptask_read</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *ptaskname, int columns, int col1, int col2, int col3, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ptask_unload</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_save</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *ptaskname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_write</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_ptask_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__ptask__math.html</filename>
    <member kind="function">
      <type>void</type>
      <name>ptask_transform</name>
      <anchor>ga0</anchor>
      <arglist>(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ptask_inverse_transform</name>
      <anchor>ga1</anchor>
      <arglist>(REAL shiftX, REAL scaleX, REAL shiftY, REAL scaleY)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_filter_by_defarea</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_filter_by_func</name>
      <anchor>ga3</anchor>
      <arglist>(REAL eps)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_update_by_func</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_minx</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_maxx</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_miny</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_maxy</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_minz</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_maxz</name>
      <anchor>ga10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_add_noise</name>
      <anchor>ga11</anchor>
      <arglist>(REAL std)</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_mean</name>
      <anchor>ga12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>ptask_std</name>
      <anchor>ga13</anchor>
      <arglist>(REAL mean)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_plus</name>
      <anchor>ga14</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_minus</name>
      <anchor>ga15</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_mult</name>
      <anchor>ga16</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_div</name>
      <anchor>ga17</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_set</name>
      <anchor>ga18</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_plus_real</name>
      <anchor>ga19</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_minus_real</name>
      <anchor>ga20</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_mult_real</name>
      <anchor>ga21</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_div_real</name>
      <anchor>ga22</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_set_real</name>
      <anchor>ga23</anchor>
      <arglist>(REAL val)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_ptask_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__ptask__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>ptask_to_task</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_to_tasks</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_to_ptask</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>task_to_ptasks</name>
      <anchor>ga3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_to_ptasks</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_ptask_other</name>
    <title>other operations</title>
    <filename>group__tcl__ptask__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>ptask_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ptask_size</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_ptasks</name>
    <title>operations with task collections</title>
    <filename>group__tcl__ptasks.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>ptasks_load</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *ptaskname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptasks_read</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *ptaskname, int columns, int col1, int col2, int col3, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptasks_delall</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptasks_del</name>
      <anchor>ga3</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>ptask *</type>
      <name>ptasks_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>ptask *</type>
      <name>ptasks_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ptask *</type>
      <name>ptasks_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ptask_concat</name>
      <anchor>ga7</anchor>
      <arglist>(ptask *ptsk)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ptasks_size</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ptasks_info</name>
      <anchor>ga9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_ptask_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__ptask__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>ptask_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ptask_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *ptaskname)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ptask_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ptask_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ptask_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ptask_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>draw_ptask</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pcurves</name>
    <title>curves</title>
    <filename>group__tcl__pcurves.html</filename>
    <subgroup>tcl_parea</subgroup>
    <subgroup>tcl_piso</subgroup>
    <subgroup>tcl_pcntr</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_parea</name>
    <title>production area (parea)</title>
    <filename>group__tcl__parea.html</filename>
    <subgroup>tcl_parea_save_load</subgroup>
    <subgroup>tcl_parea_conv</subgroup>
    <subgroup>tcl_parea_other</subgroup>
    <subgroup>tcl_pareas</subgroup>
    <subgroup>tcl_parea_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_parea_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__parea__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>parea_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *pareaname, REAL value, int columns, int col1, int col2, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pareaname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *pareaname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_parea_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__parea__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>parea_to_curv</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_to_curvs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_to_pareas</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_parea_other</name>
    <title>other operations</title>
    <filename>group__tcl__parea__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>parea_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_value</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_set</name>
      <anchor>ga2</anchor>
      <arglist>(parea *par)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parea_name</name>
      <anchor>ga3</anchor>
      <arglist>(const char *new_name, parea *parealine)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pareas</name>
    <title>operations with parea collections</title>
    <filename>group__tcl__pareas.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>pareas_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pareas_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pareas_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pareaname, REAL value, int columns, int col1, int col2, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pareas_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *pareaname)</arglist>
    </member>
    <member kind="function">
      <type>parea *</type>
      <name>pareas_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>parea *</type>
      <name>pareas_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>parea *</type>
      <name>pareas_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pareas_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pareas_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_parea_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__parea__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>parea_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parea_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *pareaname)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parea_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parea_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parea_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parea_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>draw_parea</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_piso</name>
    <title>constant production line (piso)</title>
    <filename>group__tcl__piso.html</filename>
    <subgroup>tcl_piso_save_load</subgroup>
    <subgroup>tcl_piso_conv</subgroup>
    <subgroup>tcl_piso_other</subgroup>
    <subgroup>tcl_pisos</subgroup>
    <subgroup>tcl_piso_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_piso_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__piso__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>piso_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *pisoname, REAL value, int columns, int col1, int col2, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pisoname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *pisoname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_piso_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__piso__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>piso_to_curv</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_to_curvs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_to_pisos</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_piso_other</name>
    <title>other operations</title>
    <filename>group__tcl__piso__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>piso_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_value</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_set</name>
      <anchor>ga2</anchor>
      <arglist>(piso *pisoline)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>piso_name</name>
      <anchor>ga3</anchor>
      <arglist>(const char *new_name, piso *pisoline)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pisos</name>
    <title>operations with piso collections</title>
    <filename>group__tcl__pisos.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>pisos_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pisos_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pisos_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pisoname, REAL value, int columns, int col1, int col2, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pisos_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *pisoname)</arglist>
    </member>
    <member kind="function">
      <type>piso *</type>
      <name>pisos_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>piso *</type>
      <name>pisos_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>piso *</type>
      <name>pisos_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pisos_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pisos_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_piso_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__piso__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>piso_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>piso_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *pisoname)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>piso_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>piso_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>piso_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>piso_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>draw_piso</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pcntr</name>
    <title>variable production line (pcntr)</title>
    <filename>group__tcl__pcntr.html</filename>
    <subgroup>tcl_pcntr_save_load</subgroup>
    <subgroup>tcl_pcntr_math</subgroup>
    <subgroup>tcl_pcntr_conv</subgroup>
    <subgroup>tcl_pcntr_other</subgroup>
    <subgroup>tcl_pcntrs</subgroup>
    <subgroup>tcl_pcntr_gl</subgroup>
  </compound>
  <compound kind="group">
    <name>tcl_pcntr_save_load</name>
    <title>saving and loading</title>
    <filename>group__tcl__pcntr__save__load.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_read</name>
      <anchor>ga0</anchor>
      <arglist>(const char *filename, const char *pcntrname, int columns, int col1, int col2, int col3, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_write</name>
      <anchor>ga1</anchor>
      <arglist>(const char *filename, const char *delimiter)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_save</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pcntrname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *pcntrname)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_unload</name>
      <anchor>ga4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pcntr_math</name>
    <title>mathematical operations</title>
    <filename>group__tcl__pcntr__math.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_plus_real</name>
      <anchor>ga0</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_minus_real</name>
      <anchor>ga1</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_mult_real</name>
      <anchor>ga2</anchor>
      <arglist>(REAL value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_div_real</name>
      <anchor>ga3</anchor>
      <arglist>(REAL value)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pcntr_conv</name>
    <title>converting to other objects</title>
    <filename>group__tcl__pcntr__conv.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_to_curv</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_to_curvs</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_to_pcntrs</name>
      <anchor>ga2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pcntr_other</name>
    <title>other operations</title>
    <filename>group__tcl__pcntr__other.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_check</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_set</name>
      <anchor>ga1</anchor>
      <arglist>(pcntr *pcontour)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntr_name</name>
      <anchor>ga2</anchor>
      <arglist>(const char *new_name, pcntr *contour)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pcntrs</name>
    <title>operations with pcntr collections</title>
    <filename>group__tcl__pcntrs.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>pcntrs_delall</name>
      <anchor>ga0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntrs_del</name>
      <anchor>ga1</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntrs_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *pcntrname, int columns, int col1, int col2, int col3, const char *delimiter, int grow_by)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>pcntrs_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *pcntrname)</arglist>
    </member>
    <member kind="function">
      <type>pcntr *</type>
      <name>pcntrs_at</name>
      <anchor>ga4</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>pcntr *</type>
      <name>pcntrs_first</name>
      <anchor>ga5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>pcntr *</type>
      <name>pcntrs_last</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pcntrs_size</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pcntrs_info</name>
      <anchor>ga8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_pcntr_gl</name>
    <title>OpenGL drawing</title>
    <filename>group__tcl__pcntr__gl.html</filename>
    <member kind="function">
      <type>void</type>
      <name>pcntr_color</name>
      <anchor>ga5</anchor>
      <arglist>(const char *color_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pcntr_show</name>
      <anchor>ga6</anchor>
      <arglist>(const char *filename, const char *cntrname)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pcntr_color_red</name>
      <anchor>ga0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pcntr_color_green</name>
      <anchor>ga1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pcntr_color_blue</name>
      <anchor>ga2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pcntr_color_alpha</name>
      <anchor>ga3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>draw_pcntr</name>
      <anchor>ga4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>tcl_lcm_simple</name>
    <title>simple law of conservation of mass (lcm_simple)</title>
    <filename>group__tcl__lcm__simple.html</filename>
    <member kind="function">
      <type>void</type>
      <name>lcm_simple_set</name>
      <anchor>ga0</anchor>
      <arglist>(REAL permeability, REAL viscosity, REAL multiplier)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lcm_simple_unload</name>
      <anchor>ga1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lcm_simple_read</name>
      <anchor>ga2</anchor>
      <arglist>(const char *filename, const char *lcm_simple_name)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lcm_simple_load</name>
      <anchor>ga3</anchor>
      <arglist>(const char *filename, const char *lcm_simple_name)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lcm_simple_write</name>
      <anchor>ga4</anchor>
      <arglist>(const char *filename)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lcm_simple_save</name>
      <anchor>ga5</anchor>
      <arglist>(const char *filename, const char *lcm_simple_name)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>lcm_simple_check</name>
      <anchor>ga6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>lcm_simple_info</name>
      <anchor>ga7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>D:/develop/surfit/surfit-1.0.0pre/freeflow/</name>
    <path>D:/develop/surfit/surfit-1.0.0pre/freeflow/</path>
    <filename>dir_000000.html</filename>
    <dir>D:/develop/surfit/surfit-1.0.0pre/freeflow/src/</dir>
  </compound>
  <compound kind="dir">
    <name>D:/develop/surfit/surfit-1.0.0pre/freeflow/src/interface/</name>
    <path>D:/develop/surfit/surfit-1.0.0pre/freeflow/src/interface/</path>
    <filename>dir_000002.html</filename>
    <file>flow_draw.i</file>
    <file>freeflow.i</file>
    <file>lcm.i</file>
  </compound>
  <compound kind="dir">
    <name>D:/develop/surfit/surfit-1.0.0pre/freeflow/src/</name>
    <path>D:/develop/surfit/surfit-1.0.0pre/freeflow/src/</path>
    <filename>dir_000001.html</filename>
    <dir>D:/develop/surfit/surfit-1.0.0pre/freeflow/src/interface/</dir>
    <file>flow.cpp</file>
    <file>flow.h</file>
    <file>flow_colors.cpp</file>
    <file>flow_colors.h</file>
    <file>flow_curv_show.cpp</file>
    <file>flow_curv_show.h</file>
    <file>flow_file_manager.cpp</file>
    <file>flow_file_manager.h</file>
    <file>flow_func_internal.cpp</file>
    <file>flow_func_internal.h</file>
    <file>flow_func_tcl.cpp</file>
    <file>flow_func_tcl.h</file>
    <file>flow_ie.h</file>
    <file>flow_variables.cpp</file>
    <file>flow_variables.h</file>
    <file>freeflow.cpp</file>
    <file>freeflow.h</file>
    <file>lcm_simple.cpp</file>
    <file>lcm_simple.h</file>
    <file>lcm_simple_internal.cpp</file>
    <file>lcm_simple_internal.h</file>
    <file>lcm_simple_tcl.cpp</file>
    <file>lcm_simple_tcl.h</file>
    <file>lcm_simple_user.cpp</file>
    <file>lcm_simple_user.h</file>
    <file>parea.cpp</file>
    <file>parea.h</file>
    <file>parea_internal.cpp</file>
    <file>parea_internal.h</file>
    <file>parea_show.cpp</file>
    <file>parea_show.h</file>
    <file>parea_tcl.cpp</file>
    <file>parea_tcl.h</file>
    <file>parea_user.cpp</file>
    <file>parea_user.h</file>
    <file>pareas.cpp</file>
    <file>pareas.h</file>
    <file>pcntr.cpp</file>
    <file>pcntr.h</file>
    <file>pcntr_internal.cpp</file>
    <file>pcntr_internal.h</file>
    <file>pcntr_show.cpp</file>
    <file>pcntr_show.h</file>
    <file>pcntr_tcl.cpp</file>
    <file>pcntr_tcl.h</file>
    <file>pcntr_user.cpp</file>
    <file>pcntr_user.h</file>
    <file>pcntrs.cpp</file>
    <file>pcntrs.h</file>
    <file>piso.cpp</file>
    <file>piso.h</file>
    <file>piso_internal.cpp</file>
    <file>piso_internal.h</file>
    <file>piso_show.cpp</file>
    <file>piso_show.h</file>
    <file>piso_tcl.cpp</file>
    <file>piso_tcl.h</file>
    <file>piso_user.cpp</file>
    <file>piso_user.h</file>
    <file>pisos.cpp</file>
    <file>pisos.h</file>
    <file>ptask.cpp</file>
    <file>ptask.h</file>
    <file>ptask_internal.cpp</file>
    <file>ptask_internal.h</file>
    <file>ptask_show.cpp</file>
    <file>ptask_show.h</file>
    <file>ptask_tcl.cpp</file>
    <file>ptask_tcl.h</file>
    <file>ptask_user.cpp</file>
    <file>ptask_user.h</file>
    <file>ptasks.cpp</file>
    <file>ptasks.h</file>
  </compound>
  <compound kind="class">
    <name>surfit::freeflow_manager</name>
    <filename>classsurfit_1_1freeflow__manager.html</filename>
    <base>surfit::manager</base>
    <member kind="function">
      <type>int</type>
      <name>load_tag</name>
      <anchor>surfit_1_1freeflow__managera0</anchor>
      <arglist>(datafile *df, char *tag_name) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>save</name>
      <anchor>surfit_1_1freeflow__managera1</anchor>
      <arglist>(datafile *df) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_data</name>
      <anchor>surfit_1_1freeflow__managera2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mem_info</name>
      <anchor>surfit_1_1freeflow__managera3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mem_show</name>
      <anchor>surfit_1_1freeflow__managera4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check_for_drawing</name>
      <anchor>surfit_1_1freeflow__managera5</anchor>
      <arglist>(const char *type) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1freeflow__managera6</anchor>
      <arglist>(REAL &amp;minZ, REAL &amp;maxZ) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1freeflow__managera7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>data_count</name>
      <anchor>surfit_1_1freeflow__managera8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const data *</type>
      <name>data_get</name>
      <anchor>surfit_1_1freeflow__managera9</anchor>
      <arglist>(int i) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>surfit::flow_garbage</name>
    <filename>structsurfit_1_1flow__garbage.html</filename>
    <base>surfit::binman</base>
    <member kind="function">
      <type></type>
      <name>~flow_garbage</name>
      <anchor>surfit_1_1flow__garbagea0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::lcm_simple</name>
    <filename>classsurfit_1_1lcm__simple.html</filename>
    <base>surfit::data</base>
    <member kind="function">
      <type></type>
      <name>lcm_simple</name>
      <anchor>surfit_1_1lcm__simplea0</anchor>
      <arglist>(REAL ipermeability, REAL iviscosity, REAL imultiplier, const char *name=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1lcm__simplea1</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>getMinMaxZ</name>
      <anchor>surfit_1_1lcm__simplea2</anchor>
      <arglist>(REAL &amp;minz, REAL &amp;maxz) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska26</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>permeability</name>
      <anchor>surfit_1_1lcm__simpleo0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>viscosity</name>
      <anchor>surfit_1_1lcm__simpleo1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>REAL</type>
      <name>multiplier</name>
      <anchor>surfit_1_1lcm__simpleo2</anchor>
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
    <name>surfit::lcm_simple_user</name>
    <filename>classsurfit_1_1lcm__simple__user.html</filename>
    <base>surfit::user</base>
    <base>surfit::modifier1</base>
    <member kind="function">
      <type></type>
      <name>lcm_simple_user</name>
      <anchor>surfit_1_1lcm__simple__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~lcm_simple_user</name>
      <anchor>surfit_1_1lcm__simple__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1lcm__simple__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1lcm__simple__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1lcm__simple__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1lcm__simple__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1lcm__simple__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1lcm__simple__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1lcm__simple__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1lcm__simple__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1lcm__simple__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1lcm__simple__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1lcm__simple__usera12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual vec *</type>
      <name>get_weights</name>
      <anchor>surfit_1_1lcm__simple__usera13</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual intvec *</type>
      <name>get_weights_cnt</name>
      <anchor>surfit_1_1lcm__simple__usera14</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_weights</name>
      <anchor>surfit_1_1lcm__simple__usera15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>remove_weights_cnt</name>
      <anchor>surfit_1_1lcm__simple__usera16</anchor>
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
    <name>surfit::parea</name>
    <filename>classsurfit_1_1parea.html</filename>
    <base>surfit::area</base>
    <member kind="function">
      <type></type>
      <name>parea</name>
      <anchor>surfit_1_1pareaa0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL ivalue, const char *parea_name=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa4</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska26</anchor>
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
  <compound kind="struct">
    <name>surfit::parea_garbage</name>
    <filename>structsurfit_1_1parea__garbage.html</filename>
    <base>surfit::binman</base>
    <member kind="function">
      <type></type>
      <name>~parea_garbage</name>
      <anchor>surfit_1_1parea__garbagea1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::parea_user</name>
    <filename>classsurfit_1_1parea__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>parea_user</name>
      <anchor>surfit_1_1parea__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~parea_user</name>
      <anchor>surfit_1_1parea__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1parea__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>init</name>
      <anchor>surfit_1_1parea__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>prepare</name>
      <anchor>surfit_1_1parea__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>begin</name>
      <anchor>surfit_1_1parea__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stage1</name>
      <anchor>surfit_1_1parea__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stage2</name>
      <anchor>surfit_1_1parea__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stage3</name>
      <anchor>surfit_1_1parea__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stage4</name>
      <anchor>surfit_1_1parea__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stage5</name>
      <anchor>surfit_1_1parea__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>finish</name>
      <anchor>surfit_1_1parea__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>release</name>
      <anchor>surfit_1_1parea__usera12</anchor>
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
    <name>surfit::pcntr</name>
    <filename>classsurfit_1_1pcntr.html</filename>
    <base>surfit::cntr</base>
    <member kind="function">
      <type></type>
      <name>pcntr</name>
      <anchor>surfit_1_1pcntra0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL *iZ_begin, REAL *iZ_end, const char *pcntr_name=NULL)</arglist>
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
      <name>bounds</name>
      <anchor>surfit_1_1wisoa4</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska26</anchor>
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
  <compound kind="struct">
    <name>surfit::pcntr_garbage</name>
    <filename>structsurfit_1_1pcntr__garbage.html</filename>
    <base>surfit::binman</base>
    <member kind="function">
      <type></type>
      <name>~pcntr_garbage</name>
      <anchor>surfit_1_1pcntr__garbagea1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::pcntr_user</name>
    <filename>classsurfit_1_1pcntr__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>pcntr_user</name>
      <anchor>surfit_1_1pcntr__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~pcntr_user</name>
      <anchor>surfit_1_1pcntr__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1pcntr__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1pcntr__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1pcntr__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1pcntr__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1pcntr__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1pcntr__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1pcntr__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1pcntr__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1pcntr__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1pcntr__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1pcntr__usera12</anchor>
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
    <name>surfit::piso</name>
    <filename>classsurfit_1_1piso.html</filename>
    <base>surfit::iso</base>
    <member kind="function">
      <type></type>
      <name>piso</name>
      <anchor>surfit_1_1pisoa0</anchor>
      <arglist>(REAL *iX_begin, REAL *iX_end, REAL *iY_begin, REAL *iY_end, REAL ivalue, const char *piso_name=NULL)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~piso</name>
      <anchor>surfit_1_1pisoa1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1wisoa4</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wisoa5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wisoa6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wisoa7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wisoa8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wisoa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>length_xy</name>
      <anchor>surfit_1_1wisoa10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska26</anchor>
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
  <compound kind="struct">
    <name>surfit::piso_garbage</name>
    <filename>structsurfit_1_1piso__garbage.html</filename>
    <base>surfit::binman</base>
    <member kind="function">
      <type></type>
      <name>~piso_garbage</name>
      <anchor>surfit_1_1piso__garbagea1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::piso_user</name>
    <filename>classsurfit_1_1piso__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1piso__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1piso__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1piso__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1piso__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1piso__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1piso__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1piso__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1piso__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1piso__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1piso__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1piso__usera12</anchor>
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
    <name>surfit::ptask</name>
    <filename>classsurfit_1_1ptask.html</filename>
    <base>surfit::task</base>
    <member kind="function">
      <type></type>
      <name>ptask</name>
      <anchor>surfit_1_1ptaska0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ptask</name>
      <anchor>surfit_1_1ptaska1</anchor>
      <arglist>(REAL *&amp;X_begin, REAL *X_end, REAL *&amp;Y_begin, REAL *Y_end, REAL *&amp;Z_begin, REAL *Z_end, const char *ptaskname=NULL)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ptask</name>
      <anchor>surfit_1_1ptaska2</anchor>
      <arglist>(task *tsk)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>bounds</name>
      <anchor>surfit_1_1taska3</anchor>
      <arglist>(REAL &amp;minx, REAL &amp;maxx, REAL &amp;miny, REAL &amp;maxy) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchor>surfit_1_1wtaska4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>mean</name>
      <anchor>surfit_1_1wtaska5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minx</name>
      <anchor>surfit_1_1wtaska6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxx</name>
      <anchor>surfit_1_1wtaska7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>miny</name>
      <anchor>surfit_1_1wtaska8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxy</name>
      <anchor>surfit_1_1wtaska9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>minz</name>
      <anchor>surfit_1_1wtaska10</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>maxz</name>
      <anchor>surfit_1_1wtaska11</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>REAL</type>
      <name>std</name>
      <anchor>surfit_1_1wtaska12</anchor>
      <arglist>(REAL mean) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska13</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>plus</name>
      <anchor>surfit_1_1wtaska14</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska15</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minus</name>
      <anchor>surfit_1_1wtaska16</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska17</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mult</name>
      <anchor>surfit_1_1wtaska18</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska19</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>div</name>
      <anchor>surfit_1_1wtaska20</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska21</anchor>
      <arglist>(const points *pnts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchor>surfit_1_1wtaska22</anchor>
      <arglist>(REAL val)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_priority</name>
      <anchor>surfit_1_1wtaska23</anchor>
      <arglist>(int prior)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>get_priority</name>
      <anchor>surfit_1_1wtaska24</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>surfit_1_1wtaska25</anchor>
      <arglist>(const char *newname)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getName</name>
      <anchor>surfit_1_1wtaska26</anchor>
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
  <compound kind="struct">
    <name>surfit::ptask_garbage</name>
    <filename>structsurfit_1_1ptask__garbage.html</filename>
    <base>surfit::binman</base>
    <member kind="function">
      <type></type>
      <name>~ptask_garbage</name>
      <anchor>surfit_1_1ptask__garbagea1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>surfit::ptask_user</name>
    <filename>classsurfit_1_1ptask__user.html</filename>
    <base>surfit::user</base>
    <member kind="function">
      <type></type>
      <name>ptask_user</name>
      <anchor>surfit_1_1ptask__usera0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ptask_user</name>
      <anchor>surfit_1_1ptask__usera1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>max_priority</name>
      <anchor>surfit_1_1ptask__usera2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>surfit_1_1ptask__usera3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prepare</name>
      <anchor>surfit_1_1ptask__usera4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>begin</name>
      <anchor>surfit_1_1ptask__usera5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage1</name>
      <anchor>surfit_1_1ptask__usera6</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage2</name>
      <anchor>surfit_1_1ptask__usera7</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage3</name>
      <anchor>surfit_1_1ptask__usera8</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage4</name>
      <anchor>surfit_1_1ptask__usera9</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stage5</name>
      <anchor>surfit_1_1ptask__usera10</anchor>
      <arglist>(int priority)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>finish</name>
      <anchor>surfit_1_1ptask__usera11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchor>surfit_1_1ptask__usera12</anchor>
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
