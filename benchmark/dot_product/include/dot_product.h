#ifndef __dot_product_h__
#define __dot_product_h__

#include <iostream>


template < std :: size_t size >
void dot_product_task ();

void dot_product_omp (const std :: size_t & length, const unsigned & num_threads);



#endif // __dot_product_h__
