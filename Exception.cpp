#include "Exception.h"



myException::myException() {
	error = 0;
	message = "";
}

myException::myException(int error) {
	this->error = error;
	message = "";
}

myException::myException(int error, std::string message) {
	this->error = error;
	this->message = message;
}

std::string myException::getErrorString() {
	if (error == name_not_in_file)
		return "Can't find name ' " + message + " ' in file.";
	else if (error == command_not_found)
		return "Can't find command ' " + message + " ' .";
	else if (error == bracket_error)
		return "Left bracket number are not equal to right bracket number.";
	else if (error == operand_not_found)
		return "Operand with operator '" + message + "' can't be found.";
	else if (error == parameter_error)
		return "Error parameter with function '" + message + "' .";
	else if (error == is_true)
		return "yes";
	else if (error == is_false)
		return "no";
	else if (error == bool_error)
		return "Bool function can't caculate with other operand.";
	else if (error == vector_size_not_same)
		return message + " size are different.";
	else if (error == denominator_is_zero)
		return "Denominator is zero.";
	else if (error == cross_error)
		return "Can't cross with the vector which size isn't three.";
	else if (error == zero_vector_error)
		return  message + " of the zero vector is undefined. ";
	else if (error == column_not_same)
		return "column are not same.";
	else if (error == row_not_same)
		return "row are not same.";
	else if (error == row_and_col_not_same)
		return "row and column are not same.";
	else if (error == det_is_zero)
		return "Determinant is zero.";
	else if (error == no_solution)
		return "There is not a solution in linear system.";
	else if (error == not_square_matrix)
		return "This matrix is not a square matrix.";
	else if (error == not_power_method)
		return "Please ues the power method to get eigen value and vector.";
	else if (error == complex_error)
		return "Have complex number in eigen value.";
	else
		return "...";
}
