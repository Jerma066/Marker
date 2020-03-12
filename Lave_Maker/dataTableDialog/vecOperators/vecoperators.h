#ifndef VECOPERATORS_H
#define VECOPERATORS_H

#include <vector>

int operator == (const std::vector<float>& l_vector, 
				 const std::vector<float>& r_vector);

int operator != (const std::vector<float>& l_vector, 
				 const std::vector<float>& r_vector);

int operator == (const std::vector<std::vector<float>>& l_matrix, 
				 const std::vector<std::vector<float>>& r_matrix);

int operator != (const std::vector<std::vector<float>>& l_matrix, 
				 const std::vector<std::vector<float>>& r_matrix);

#endif // VECOPERATORS_H
