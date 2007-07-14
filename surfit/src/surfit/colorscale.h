
/*------------------------------------------------------------------------------
 *	$Id: color_scale.h 284 2006-03-25 09:09:26Z mvd $
 *	Copyright (c) 2002-2006 by M. V. Dmitrievsky 
 *----------------------------------------------------------------------------*/

#ifndef __color_scale_included__
#define __color_scale_included__

#include <vector>

namespace surfit {

#define DEFAULT_COLORS 89, 138, 237, 227, 46, 32

/*!
	\class color_scale
	\brief class of color scale for \ref d_surf
*/
class SURFIT_EXPORT color_scale {
public:
	//! default constructor
	color_scale();
	
	//! constructor 
	color_scale(double from, double to, double step,
		    int r_from, int g_from, int b_from,
		    int r_to, int g_to, int b_to);

	color_scale(const color_scale & cs);

	//! destructor
	~color_scale();

public:
	//! destructor
	void release();

	//! sets color_scale (like constructor)
	void set(double from, double to, double step,
		 int r_from, int g_from, int b_from,
		 int r_to, int g_to, int b_to);

	//! returns color for value
	void get_value(double value, int & r, int & g, int & b) const;

	void set_value(int pos, double value, int r, int g, int b);
	void add_value(double value, int r, int g, int b);
	
	//! returns value for specified position
	virtual double get_value(int pos) const;

	//! returns color_scale size (amount of colors)
	int size() const;

	void resize(int new_size);

	//! returs color for specified position
	bool get_color(int pos, int & r, int & g, int &b) const;
	
	//! returns false if color_scale is not default
	bool is_default() const { return default_cs; };
	//! sets color_scale to default
	void set_default(bool val) { default_cs = val; };

	bool operator==(const color_scale& cs) const;
	void operator=(const color_scale& cs);

	const std::vector<int> * get_r_values() const;
	const std::vector<int> * get_g_values() const;
	const std::vector<int> * get_b_values() const;
	const std::vector<double> * get_values() const;

	bool LoadCLR(const char * filename);
	bool SaveCLR(const char * filename) const;
	bool LoadLVL(const char * filename);
	bool SaveLVL(const char * filename) const;
	
private:

	//! array of red-colors
	std::vector<int>  * r_values;
	//! array of green-colors
	std::vector<int>  * g_values;
	//! array of blue-colors
	std::vector<int>  * b_values;
	//! array of values
	std::vector<double> * values;
	//! flag for checking defaultness
	bool default_cs;

};

SURFIT_EXPORT
color_scale * create_color_scale(double from, double to, double step,
			         int r_from, int g_from, int b_from,
			         int r_to, int g_to, int b_to);

}; // namespace surift

#endif

