#pragma once
#include<string>
class myException
{
public:
	myException();
	myException(int);
	myException(int, std::string);
	std::string getErrorString();
private:
	int error;
	std::string message;
};
enum error_type
{
	name_not_in_file = 1,
	command_not_found = 2,
	bracket_error = 3,
	operand_not_found = 4,
	parameter_error = 5,
	is_true = 6,
	is_false = 7,
	bool_error = 8,
	vector_size_not_same = 9,
	denominator_is_zero = 10,
	cross_error = 11,
	zero_vector_error = 12,
	column_not_same = 13,
	row_not_same = 14,
	row_and_col_not_same = 15,
	det_is_zero = 16,
	no_solution = 17,
	not_square_matrix = 18,
	not_power_method = 19,
	complex_error = 20,
};
