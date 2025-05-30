def initialize_register_list():
	return list(range(1, number_of_registers+1))



def read_quadruples(file):
	f = open(file, "r")
	instructions = list()
	for i in f.readlines():
		instructions.append(i.split())
	return instructions


def remove_ifs_and_nots(instructions):

	to_be_removed = list()
	i = 0
	n = len(instructions)
	while(i < n):
		if (instructions[i][0] in ["+", "-", "*", "/", "&&", "||"]) and (i+2  < len(instructions)) and (instructions[i+2][0] == 'if'): 
			to_be_removed.append(i+1)
			i += 3
			continue
		try:
			if instructions[i][0] == "not":
				instructions[i-1][3] = instructions[i+1][3]
				to_be_removed.append(i)
			elif instructions[i][0] == "if":
				to_be_removed.append(i)
			i += 1
		except:
			continue

	to_be_removed.sort(reverse = True)	
	for index in to_be_removed:
		del instructions[index]

def LRU_Free_Register(value):
	global source_variable_lines_mapping
	global common_variable_lines_mapping
	global output_file

	reg = variable_register_mapping[value]
	if((value in common_variable_lines_mapping and value not in source_variable_lines_mapping) or (len(common_variable_lines_mapping[value]) >= len(source_variable_lines_mapping[value]))):
		print("ST", value, "R" + str(reg))
		output_file.write("ST " + value + " R" + str(reg) + "\n")

	variable_register_mapping.pop(value)
	available_registers.insert(0, reg)
	available_registers.sort()
	
	if(value in source_variable_lines_mapping):
		source_variable_lines_mapping.pop(value)
	common_variable_lines_mapping.pop(value)
	
	
def reg_alloc(value, to_be_loaded):
	global available_registers
	global variable_register_mapping
	global used_registers
	global output_file
	
	if(len(available_registers) == 0):
		if(value[0] != 'T'):
			reg = used_registers.pop(0)
			l = list(variable_register_mapping.keys())
			for i in l:
				if (variable_register_mapping[i] == reg):
					LRU_Free_Register(i)

	if(value.isnumeric()):
		return "#" + value
	else:
		if value in variable_register_mapping:
			used_registers.remove(variable_register_mapping[value])
			used_registers.append(variable_register_mapping[value])
			return "R" + str(variable_register_mapping[value])
		else:
			variable_register_mapping[value] = available_registers[0]
			if(to_be_loaded):
				print("LD", "R" + str(available_registers[0]), value)
				output_file.write("LD R" + str(available_registers[0]) + " " + value + "\n")
			to_return = "R" + str(available_registers[0])
			available_registers.pop(0)
			if (variable_register_mapping[value] not in used_registers):
				used_registers.append(variable_register_mapping[value])
			return to_return

def add_variable_to_line_mapping(variable, line, mapping):
	if(variable != "(null"):
		if variable not in mapping:
			mapping[variable] = []
		mapping[variable].append(line)

def map_variable_lines(instructions):
	global source_variable_lines_mapping
	global common_variable_lines_mapping
	for i in range(len(instructions)):
		if instructions[i][0] in ["Label", "goto"]:
			pass
		elif instructions[i][0] in ["<", "<=", ">", ">=", "==", "!="]: 
			add_variable_to_line_mapping(instructions[i][1], i, source_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][2], i, source_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][1], i, common_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][2], i, common_variable_lines_mapping)

		elif instructions[i][0] == "=":
			add_variable_to_line_mapping(instructions[i][1], i, source_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][1], i, common_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][3], i, common_variable_lines_mapping)
		
		else:
			add_variable_to_line_mapping(instructions[i][1], i, source_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][2], i, source_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][1], i, common_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][2], i, common_variable_lines_mapping)
			add_variable_to_line_mapping(instructions[i][3], i, common_variable_lines_mapping)

def initialize_register_list():
	return list(range(number_of_registers))

def reg_dealloc():
	global variable_register_mapping
	global available_registers
	global output_file

	variables_used = [i for i in variable_register_mapping if not i.isnumeric()]
	for i in variables_used:
		register = variable_register_mapping[i]
		if(i in common_variable_lines_mapping and i in source_variable_lines_mapping):
			if(len(common_variable_lines_mapping[i]) >= len(source_variable_lines_mapping[i])):
				print("ST ", i, "R" + str(register))
				output_file.write("ST " + i + " R" + str(register) + "\n")

	variable_register_mapping = {}
	available_registers = initialize_register_list()

def check_source(value, line):
	global output_file
	
	if(value in common_variable_lines_mapping and value in source_variable_lines_mapping):
		source_variable_lines_mapping[value].remove(line)
		common_variable_lines_mapping[value].remove(line)
		if(len(common_variable_lines_mapping[value]) == 0 and not value.isnumeric()):
			reg = variable_register_mapping[value]
			if(value[0] != 'T'):
				if(len(common_variable_lines_mapping[value]) >= len(source_variable_lines_mapping[value])):
					print("ST", value, "R" + str(reg))
					output_file.write("ST " + value + " R" + str(reg) + "\n")
			variable_register_mapping.pop(value)
			available_registers.insert(0, reg)
			available_registers.sort()


def check_destination(value, line):
	global output_file

	if(value in common_variable_lines_mapping):
		common_variable_lines_mapping[value].remove(line)
		if(len(common_variable_lines_mapping[value]) == 0 and not value.isnumeric()):
			reg = variable_register_mapping[value]
			if(value[0] != 'T'):
					print("ST", value, "R" + str(reg))
					output_file.write("ST " + value + " R" + str(reg) + "\n")
			variable_register_mapping.pop(value)
			available_registers.insert(0, reg)
			available_registers.sort()


def assembly_gen(instructions):
	global source_variable_lines_mapping
	global common_variable_lines_mapping
	global output_file

	remove_ifs_and_nots(instructions)
	map_variable_lines(instructions)
	
	print("Start:")
	output_file.write("Start:\n")

	for i in range(len(instructions)):
		
		if(instructions[i][0] == 'if'):
			continue

		if(instructions[i][0] == "Label"):
			reg_dealloc()		
			print(instructions[i][3] + ":")
			output_file.write(instructions[i][3] + ":\n")
		elif(instructions[i][0] == "goto"):
			reg_dealloc()
			print("BR " + instructions[i][3])
			output_file.write("BR " + instructions[i][3] + "\n")
		elif instructions[i][0] in ["<", "<=", ">", ">=", "==", "!="]: 
			reg1 = reg_alloc(instructions[i][1], 1)
			reg2 = reg_alloc(instructions[i][2], 1)
			print("CMP", reg1, reg2)
			output_file.write("CMP " + reg1 + " " + reg2 + "\n")
			
			if instructions[i][0] == "<":
				print("BGT", instructions[i][3])
				output_file.write("BGT " + instructions[i][3] + "\n")
			elif instructions[i][0] == "<=":
				print("BGE", instructions[i][3])
				output_file.write("BGE " + instructions[i][3] + "\n")
			elif instructions[i][0] == ">":
				print("BLT", instructions[i][3])
				output_file.write("BLT " + instructions[i][3] + "\n")
			elif instructions[i][0] == ">=":
				print("BLE", instructions[i][3])
				output_file.write("BLE " + instructions[i][3] + "\n")
			elif instructions[i][0] == "==":
				print("BNE", instructions[i][3])
				output_file.write("BNE " + instructions[i][3] + "\n")
			elif instructions[i][0] == "!=":
				print("BEQ", instructions[i][3])
				output_file.write("BEQ " + instructions[i][3] + "\n")

			source_variable_lines_mapping[instructions[i][1]].remove(i)
			source_variable_lines_mapping[instructions[i][2]].remove(i)
			common_variable_lines_mapping[instructions[i][1]].remove(i)
			common_variable_lines_mapping[instructions[i][2]].remove(i)

		elif instructions[i][0] in ["+", "-", "*", "/", "&&", "||"] and (i+1  < len(instructions)) and (instructions[i+1][0] == 'if'):
			reg1 = reg_alloc(instructions[i][1], 1)
			reg2 = reg_alloc(instructions[i][2], 1)
			reg3 = reg_alloc(instructions[i][3], 0)
			if instructions[i][0] == "+":
				print("ADD", reg3, reg1, reg2)
				output_file.write("ADD " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "-":
				print("SUB", reg3, reg1, reg2)
				output_file.write("SUB " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "*":
				print("MUL", reg3, reg1, reg2)
				output_file.write("MUL " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "/":
				print("DIV", reg3, reg1, reg2)
				output_file.write("DIV " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "&&":
				print("AND", reg3, reg1, reg2)
				output_file.write("AND " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "||":
				print("OR", reg3, reg1, reg2)
				output_file.write("OR " + reg3 + " " + reg1 + " " + reg2 + "\n")

			print("BGZ", instructions[i+1][3])
			output_file.write("BGZ " + instructions[i+1][3] + "\n")

		elif instructions[i][0] in ["+", "-", "*", "/", "&&", "||"]: 
			reg1 = reg_alloc(instructions[i][1], 1)
			reg2 = reg_alloc(instructions[i][2], 1)		
			reg3 = reg_alloc(instructions[i][3], 0)

			if instructions[i][0] == "+":
				print("ADD", reg3, reg1, reg2)
				output_file.write("ADD " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "-":
				print("SUB", reg3, reg1, reg2)
				output_file.write("SUB " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "*":
				print("MUL", reg3, reg1, reg2)
				output_file.write("MUL " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "/":
				print("DIV", reg3, reg1, reg2)
				output_file.write("DIV " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "&&":
				print("AND", reg3, reg1, reg2)
				output_file.write("AND " + reg3 + " " + reg1 + " " + reg2 + "\n")
			elif instructions[i][0] == "||":
				print("OR", reg3, reg1, reg2)
				output_file.write("OR " + reg3 + " " + reg1 + " " + reg2 + "\n")

			check_source(instructions[i][1], i)
			check_source(instructions[i][2], i)
			check_destination(instructions[i][3], i)

		else:
			reg1 = reg_alloc(instructions[i][3], 0)		
			reg2 = reg_alloc(instructions[i][1], 1)
			print("MOV", reg1, reg2)
			output_file.write("MOV " + reg1 + " " + reg2 + "\n")

			check_source(instructions[i][1], i)
			check_destination(instructions[i][3], i)

output_file = open("output.txt", "w")

instructions = read_quadruples("input.txt")

number_of_registers = 16
available_registers = initialize_register_list()
variable_register_mapping = {}	
source_variable_lines_mapping = {}	
common_variable_lines_mapping = {}	
used_registers = []

assembly_gen(instructions)

output_file.close()
print("\nMachine code has been written to output.txt")