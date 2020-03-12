#include "vecoperators.h"

int operator == (const std::vector<float>& l_vector, 
				 const std::vector<float>& r_vector)
{
	if(l_vector.size() != r_vector.size()){
		return 0;
	}
	else{
		for(size_t i = 0; i < l_vector.size(); i++){
			if (l_vector[i]!= r_vector[i]){
				return 0;
			}
		}
		return 1;
	}
}

int operator != (const std::vector<float>& l_vector, 
				 const std::vector<float>& r_vector)
{
	if(l_vector == r_vector){
		return 0;
	}
	else{
		return 1;
	}
}

int operator == (const std::vector<std::vector<float>>& l_matrix, 
				 const std::vector<std::vector<float>>& r_matrix)
{
	if(l_matrix.size() != r_matrix.size()){
		return 0;
	}
	else{
		for(size_t i = 0; i < l_matrix.size(); i++){
			if (l_matrix[i] != r_matrix[i]){
				return 0;
			}
		}
		return 1;
	}
}

int operator != (const std::vector<std::vector<float>>& l_matrix, 
				 const std::vector<std::vector<float>>& r_matrix)
{
	if(l_matrix == r_matrix){
		return 0;
	}
	else{
		return 1;
	}
}
