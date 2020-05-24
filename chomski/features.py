import random

def list_sorting(number_list, number_of_iterations = None):

	if number_of_iterations == None:
		number_of_iterations = len(number_list) - 1

	if number_of_iterations != 0:
		
		for index in range(number_of_iterations):
			
			if len(number_list[index]) > len(number_list[index + 1]):
				number_list.insert(index + 2, number_list[index])
				number_list.pop(index)

		number_of_iterations -= 1

		return list_sorting(number_list, number_of_iterations)

	else:
		return number_list

def extra_variables_elimination(list_of_variable, new_appenders, letters):

	for index, var in enumerate(list_of_variable):
		if len(var[2]) == 3:
			separated_var = var[2][1] + var[2][2]
			letter, letters = generate_random_letter(letters, 72, 82)
			
			new_appenders.append([letter, separated_var])
			for item_index, item in enumerate(list_of_variable):
				if separated_var in item[2]:
					list_of_variable[item_index][2] = list_of_variable[item_index][2].replace(separated_var, letter)

		elif len(var[2]) == 4:
			separated_var = var[2][2] + var[2][3]
			letter, letters = generate_random_letter(letters, 72, 82)

			new_appenders.append([letter, separated_var])
			for item_index, item in enumerate(list_of_variable):
				if separated_var in item[2]:
					list_of_variable[item_index][2] = list_of_variable[item_index][2].replace(separated_var, letter)


	return list_of_variable, new_appenders

def generate_random_letter(letter_list, starting_index, final_index):

	letter = chr(random.randrange(starting_index, final_index))
	if letter in letter_list:

		return generate_random_letter(letter_list, starting_index, final_index)

	else:
		letter_list.append(letter)
		return letter, letter_list