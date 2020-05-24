import re
import random
import features
from tabulate import tabulate


def from_file_to_list(file_name):
	nfa_file = open(file_name , 'r')
	rules = nfa_file.readlines()

	cfg_list = []
	for line in rules:
		cfg_list.append(line.split())

	return cfg_list


def S_in_RHS_checker():

	cfg_list = from_file_to_list('context_free_grammar.txt')

	starting_point = cfg_list[0][0]
	for elem in cfg_list:
		if starting_point in elem[1]:
			cfg_list.insert(0, [starting_point + '*', starting_point])
			break

	return cfg_list


def remove_null_production():

	cfg_list = S_in_RHS_checker()

	null_production_list = []
	for elem in cfg_list:
		if "eps." in elem[1]:
			null_production_list.append(elem)

	for null_product in null_production_list:
		for elem in cfg_list:
			if null_product[0] in elem[1]:
				letter_indexes = [pos for pos, char in enumerate(elem[1]) if char == null_product[0]]


				for index in letter_indexes:
					right_part = elem[1][:index] + elem[1][index + 1:]
					if [elem[0], right_part] not in cfg_list:
						cfg_list.append([elem[0], right_part])

				if len(letter_indexes) > 1:
					right_part = elem[1].replace(null_product[0], '')
					cfg_list.append([elem[0], right_part])

				if null_product in cfg_list:
					cfg_list.remove(null_product)

	return cfg_list

def remove_unit_production():
	cfg_list = remove_null_production()

	unit_production = []
	for elem in cfg_list:
		if len(elem[1]) == 1 and elem[1].isupper():
			unit_production.append(elem)

	for unit in unit_production:
		for elem in cfg_list:
			if unit[1] == elem[0] and len(elem[1]) == 1 and elem[1].islower():
				required_elem = elem[0]

	for counter in range(len(unit_production)):
		for unit in unit_production:
			if required_elem in unit:
				second_elem = unit[0]
				for elem in cfg_list:

					if required_elem == elem[0]:

						cfg_list.append([second_elem, elem[1]])

				required_elem = second_elem
			if unit in cfg_list:
				cfg_list.remove(unit)

	right_side_unique = []
	for elem in cfg_list:
		if "*" in elem[0]:
			right_side_unique.append(elem[0])
			break
		elif any('*' in sublist for sublist in cfg_list):
			right_side_unique.append(cfg_list[0][0])
			break

	for elem in cfg_list:
		for letter in elem[1]:
			if letter.isupper() and letter not in right_side_unique:
				right_side_unique.append(letter)


	for unit in right_side_unique:
		for elem in cfg_list:
			if elem[0] not in right_side_unique:
				cfg_list.remove(elem)

	return cfg_list

def maximum_2_var_in_RHS():

	cfg_list = remove_unit_production()

	more_than_2_var_list = []
	for elem in cfg_list:
		if len(elem[1]) > 2 and elem[1] not in more_than_2_var_list:
			more_than_2_var_list.append(elem[1])

	more_than_2_var_list = features.list_sorting(more_than_2_var_list)

	temp_list = []

	for item in more_than_2_var_list:
		temp_list.append([item, "*", item])

	more_than_2_var_list = temp_list 

	new_appenders = []
	letters = []
	for item in more_than_2_var_list:
		while len(item[2]) > 2:
			more_than_2_var_list, new_appenders = features.extra_variables_elimination(more_than_2_var_list, new_appenders, letters)
	
	for index, item in enumerate(cfg_list):
		for var_index, var in enumerate(more_than_2_var_list):
			if item[1] == var[0]:
				cfg_list[index][1] = cfg_list[index][1].replace(var[0], var[2]) 

	for item in new_appenders:
		cfg_list.append(item)


	return cfg_list


def change_production():

	cfg_list =  maximum_2_var_in_RHS()

	lowercase_container = []
	for item in cfg_list:
		if len(item[1]) > 1:
			for char in item[1]:
				if char.islower():
					if char not in lowercase_container:
						lowercase_container.append(char)

	temp_container = []
	letters = []
	for item in lowercase_container:
		letter, letters = features.generate_random_letter(letters, 86, 90)
		temp_container.append([letter, item])

	lowercase_container = temp_container

	# print(cfg_list)
	for item_index, item in enumerate(lowercase_container):
		for value_index, value in enumerate(cfg_list):
			if len(value[1]) > 1:
				for char in value[1]:

					if char.islower() and char == item[1]:
						cfg_list[value_index][1] = cfg_list[value_index][1].replace(char, item[0])

	for item in lowercase_container:
		cfg_list.append(item)

	return cfg_list

def main():

	cfg_list = change_production()
	for item in cfg_list:
		item.insert(1, '->')

	# print(cfg_list)
	print(tabulate(cfg_list))

main()