
#ifndef __surfit__vec__
#define __surfit__vec__

#include <stdio.h>

#ifdef _DEBUG
#define LSS_BOUNDS_CHECK
#else
#undef LSS_BOUNDS_CHECK
#endif

#ifdef XXL
#include "../../src_xxl/sstuff/vec_xxl.h"
#endif

namespace surfit {

class vec;
#ifndef XXL
/*! \typedef vec extvec 
    \brief vector that can be saved on hard drive (external vector)
*/
typedef vec extvec;
#endif

/*! \ingroup sstuff_internal
    \fn vec * create_vec(size_t size = 0, REAL default_value = REAL(0), bool fill_default = true, size_t grow_by = 250);
    \brief creates vec object

    \param size size of the vector
    \param default_value value for filling vector by default
    \param fill_default flag for perfoming filling vector with default value
    \param grow_by amount of elements for extending vector
*/
SSTUFF_EXPORT
vec * create_vec(size_t size = 0, REAL default_value = REAL(0), bool fill_default = true, size_t grow_by = 250);

/*! \ingroup sstuff_internal
    \fn vec * create_vec(const vec &in);
    \brief creates vec object

    This function is a copy constructor
*/
SSTUFF_EXPORT
vec * create_vec(const vec &in);

/*! \ingroup sstuff_internal
    \fn vec * create_vec(const extvec &in);
    \brief creates vec object

    This function is a copy constructor
*/
SSTUFF_EXPORT
vec * create_vec(const extvec &in);

/*! \ingroup sstuff_internal
    \fn extvec * create_extvec(size_t size = 0, REAL default_value = REAL(0), bool fill_default = true, size_t grow_by = 250);
    \brief creates extvec object

    \param size size of the vector
    \param default_value value for filling vector by default
    \param fill_default flag for perfoming filling vector with default value
    \param grow_by amount of elements for extending vector
*/
SSTUFF_EXPORT
extvec * create_extvec(size_t size = 0, REAL default_value = REAL(0), bool fill_default = true, size_t grow_by = 250);

/*! \ingroup sstuff_internal
    \fn extvec * create_extvec(const extvec &in);
    \brief creates extvec object

    This function is a copy constructor
*/
SSTUFF_EXPORT
extvec * create_extvec(const extvec &in);


/*! \class vec
    \brief vector of REAL's
*/
#ifdef XXL
#include "../../src_xxl/sstuff/vec_xxl.h"
#endif

#ifndef XXL
#define extvec vec
#define create_extvec create_vec
#endif

class SSTUFF_EXPORT vec 
{
public:

	//! iterator type for vec
	typedef         REAL*  iterator;
	//! reference type for vec
	typedef         REAL&  reference;

	//! const_iterator type for vec
	typedef const   REAL*  const_iterator;

	//! const_reference type for vec
	typedef const   REAL&  const_reference;

		
protected:

	/*! A consturtor
	    \param size vector size
            \param default_value initial value for fill vector
	    \param fill_default use initial value filling
	    \param grow_by value for resizing vector
    	*/
	vec (size_t size = 0, REAL default_value = REAL(0), bool fill_default = true, size_t grow_by = 250);
	
	//! Copy constructor
	vec(const vec &in);
#ifdef XXL
	//! Copy constructor
	vec(const extvec &in);
#endif
	
	//! Destructor
	~vec();
public:
	
	/*!
	\fn vec * create_vec(size_t size = 0, REAL default_value = REAL(0), bool fill_default = true, size_t grow_by = 250);
	\brief creates vec object

	\param size size of the vector
	\param default_value value for filling vector by default
	\param fill_default flag for perfoming filling vector with default value
	\param grow_by amount of elements for extending vector
	*/	
	friend SSTUFF_EXPORT
	vec * create_vec (size_t size, REAL default_value, bool fill_default, size_t grow_by);

	/*! 
	\fn vec * create_vec(const vec &in);
	\brief creates vec object

	This function is a copy constructor
	*/
	friend SSTUFF_EXPORT
	vec * create_vec(const vec &in);

#ifdef XXL
	friend SSTUFF_EXPORT
	//! copy constructor
	vec * create_vec(const extvec &in);
#endif

public:
	//! destructor
	void release();

	//! returns pointer to begin of REAL-array
	iterator begin() { return data; };

	//! returns const pointer to begin of REAL-array
	const_iterator const_begin() const { return data; };

	//! returns pointer to end of REAL-array
	iterator end() { return data+datasize; };

	//! returns const pointer to end of REAL-array
	const_iterator const_end() const { return data+datasize; };

	//! removes element by iterator
	void erase(iterator);

	//! removes element by index
	void erase(size_t index);
		
	//! changes vector size
	void resize(size_t newsize, REAL default_value = REAL(0), bool fill_default = true);

	//! returns vector size
	size_t size() const { return datasize; };

	//! returns reference to i'th element
	reference operator()(size_t i) {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
			
		return *(data+i);
	};
		
	//! returns const reference to i'th element
	const_reference operator()(size_t i) const {
#ifdef LSS_BOUNDS_CHECK
		if ((i < 0) || (i >= size()))
			throw "invalid argument";
#endif
		const REAL& res = *(data+i);
		return res;
	};

	//! copy operator
	vec& operator=(const vec & copy);

	//! adds one element at the end of array
	void push_back(const REAL&);

	//! adds array at the end of array
	void push_back(vec * v);

	//! sets currently allocated vector size to reserve_size
	void reserve(size_t reserve_size);

	//! sets vector's grow factor
	void set_grow(size_t grow_by);

	//! exchanges two elements
	void swap(size_t i, size_t j);

	//! forgets all allocated memory
	void drop_data();

	//! writes vector content to the file
	size_t write_file(int file, size_t size) const;
	//! reads vector content from the file
	size_t read_file(int file, size_t size);
	
private:
	//! pointer to vector-array
	REAL* data;

	//! real vector size in elements
	size_t datasize;

	//! size of allocated memory in elements
	size_t real_datasize;
	
	//! grow factor
	size_t grow_by;
};

}; // namespace surfit

#endif

