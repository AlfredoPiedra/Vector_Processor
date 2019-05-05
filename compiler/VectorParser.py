# Regular expression library
import re

###########################################################################
# Global dictionary used to associate the mnemonic of the instructions    #
# with format F to its corresponding operational code                     #
###########################################################################
format_f_instructions = {

    'VADD': '0',
    'VSUB': '1',
    'VXOR': '2',
    'VAND': '3',
    'VOR': '4',
    'VSHFR': '5',
    'VSHFL': '6',
    'VCSHFR': '7',
    'VCSHFL': '8',
    'VSET': '9'
}

###########################################################################
# Global dictionary used to associate the mnemonic of the instructions    #
# with format M to its corresponding operational code                     #
###########################################################################
format_m_instructions = {

    'VLDR': 'a',
    'VSTR': 'b'
}

###########################################################################
# Global dictionary used to associate the mnemonic of the instructions    #
# with format I to its corresponding operational code                     #
###########################################################################
format_i_instructions = {

    'ADD': 'c',
    'SET': 'd',
    'STR': 'e',
    'LDR': 'f'
}

###########################################################################
# Function that parse the operands of a instructions                      #
# following the format F                                                  #
#                                                                         #
# Inputs:                                                                 #
#       operands: string that contains the instruction without            #
#                 the mnemonic                                            #
#       use_va: boolean variable that indicates if the instruction        #
#               use three explicitly defined operands or only two         #
#                                                                         #
#                                                                         #
# Output: On success return a list with two elements, the first is        #
#         the integer uses as a code to indicate if the conversion        #
#         was successful or not and the second is a string with the       #
#         hexadecimal value of the codified instruction                   #
#                                                                         #  
#         On failure return a list with three elements, the first is      #
#         the error code, the second is the number of the line with       #
#         the error and the third element is the error message            #
###########################################################################
def parse_operands_format_f(operands,use_va):

    # Variable used to store the hexadecimal code of the instruction
    hex_code = ''

    # Search for a # and a numeric value
    has_immediate = re.search('(?<=#)\d+',operands)

    # Search for the number of the vector registers
    vector_ids = re.findall('(?<=V)\d+',operands)

    # Check if the instructions has at least two correctly
    # defined registers when using a explicitly defined Va register
    if use_va == True and len(vector_ids) < 2:

        # Return error code
        return [-1, "Missing operand"]

    # Check if the instruction has at least one correctly
    # defined register when using a implicitly defined Va register
    elif use_va == False and len(vector_ids) < 1:

        #Return error code
        return [-1, "Missing operand"]

    # Parse to int the register numbers
    Vd = int(vector_ids[0])

    # Implicit definition of Va
    Va = 0

    # Check if the instruction use Va explicitly
    if use_va:

        # Parse the Va register number        
        Va = int(vector_ids[1])
    

    # Check that the registers specified exists
    if Vd < 0 or Vd > 15 or Va < 0 or Va > 15:

        # Return error code
        return [-1, 'Register does not exist']

    # Convert to binary values
    Vd = format(Vd,'04b')
    Va = format(Va,'04b')

    if(has_immediate != None):

        # Obtain the numeric value in the instruction
        immediate_value = int(has_immediate.group())

        # Check if the immediate value is a 8 bit constant
        if immediate_value > 255:

            print(immediate_value)
            # Return error code
            return [-1,'Exceed 8 bit constant']

        # Convert the immediate to pair of hexadecimal values
        hex_code = format(immediate_value,'08b')

        # Add the I-bit, Vd, Va, Imm -> all in binary format
        hex_code = '1' + Vd + Va + '00000000000' + hex_code

    else:

        # Position in the register number list of Vb
        vb_pos = 0
        
        # Check if the instructions has three correctly
        # defined registers when using a explicitly Va register
        if  use_va and len(vector_ids) == 3:

            # Starting from zero, Vb must be in the third position
            vb_pos = 2

        # Check if the instructions has two correctly
        # defined registers when using a implicitly Va register
        elif use_va ==  False and len(vector_ids) == 2:

            # Starting from zero, Vb must be in the second position
            vb_pos = 1

        else:

            # Return error code
            return [-1,'Missing operand']

        # Get the number of the Vb register
        Vb = int(vector_ids[vb_pos])

        # Check that the register specified exist
        if Vb < 0 or Vb > 15:

            # Return error code
            return [-1, 'Register does not exist']

        # Get the binary value of the register number
        Vb = format(Vb,'04b')
            
        # Add the I-bit, Vd, Va, Vb -> all in binary format
        hex_code = '0' + Vd + Va + '000000000000000' + Vb

    # Convert the binary value to hexadecimal
    hex_code = format(int(hex_code,2),'07x')

    # Return success code and the hexadecimal code of the operands
    return [0,hex_code]
        
###########################################################################
# Function that parse the operands of a instructions                      #
# following the format I                                                  #
#                                                                         #
# Inputs:                                                                 #
#       operands: string that contains the instruction without            #
#                 the mnemonic                                            #
#       use_ra: boolean variable that indicates if the instruction        #
#               use three explicitly defined operands or only two         #
#                                                                         #
#                                                                         #
# Output: On success return a list with two elements, the first is        #
#         the integer uses as a code to indicate if the conversion        #
#         was successful or not and the second is a string with the       #
#         hexadecimal value of the codified instruction                   #
#                                                                         #  
#         On failure return a list with three elements, the first is      #
#         the error code, the second is the number of the line with       #
#         the error and the third element is the error message            #
###########################################################################
def parse_operands_format_i(operands, use_ra):

    # Variable used to store the hexadecimal code of the instruction
    hex_code = ''

    # Search for a # and a numeric value
    has_immediate = re.search('(?<=#)\d+',operands)

    # Search for the number of the scalar registers
    register_ids = re.findall('(?<=R)\d+',operands)

    # Check if the instructions has two correctly defined registers
    if use_ra == False  and len(register_ids) < 1:

        # Return error code
        return [-1, "Missing operand"]

    elif use_ra and len(register_ids) < 2:

        # Return error code
        return [-1, "Missing operand"]

    # Parse to int the register numbers
    Rd = int(register_ids[0])
    Ra = 0

    # Check if the instruction use Ra explicitly
    if use_ra:

        # Parse the Ra register number        
        Ra = int(register_ids[1])

    # Check that the registers specified exists
    if Rd < 0 or Rd > 6 or Ra < 0 or Ra > 6:

        # Return error code
        return [-1, 'Register doesnt exist']

    # Convert to binary values
    Rd = format(Rd,'03b')
    Ra = format(Ra,'03b')

    if(has_immediate != None):

        # Obtain the numeric value in the instruction
        immediate_value = int(has_immediate.group())

        # Check if the immediate value is a 21 bit constant
        if immediate_value > 2097151:

            # Return error code
            return [-1,'Exceed 21 bits constant']

        # Convert the immediate to pair of hexadecimal values
        hex_code = format(immediate_value,'021b')

        # Add the I-bit, Rd, Ra, Imm -> all in binary format
        hex_code = '1' + Rd + Ra + hex_code

    else:

        # Position in the register number list of Vb
        rb_pos = 0

        # Check if the instructions has two correctly
        # defined registers when using a implicitly Ra register
        if use_ra ==  False and len(register_ids) == 2:

            # Starting from zero, Rb must be in the second position
            rb_pos = 1
        
        # Check if the instructions has three correctly
        # defined registers when using a explicitly Ra register
        elif  use_ra and len(register_ids) == 3:

            # Starting from zero, Rb must be in the third position
            rb_pos = 2

        else:

            # Return error code
            return [-1,'Missing operand']

        # Get the number of the Rb register
        Rb = int(register_ids[rb_pos])

        # Check that the registers specified exists
        if Rb < 0 or Rb > 6:

            # Return error code
            return [-1, 'Register does not exist']

        # Get the binary value of the register number
        Rb = format(Rb,'03b')
            
        # Add the I-bit, Rd, Ra, Rb -> all in binary format
        hex_code = '0' + Rd + Ra + '000000000000000000' + Rb
           
    # Convert the binary value to hexadecimal
    hex_code = format(int(hex_code,2),'07x')

    # Return success code and the hexadecimal code of the operands
    return [0,hex_code]

###########################################################################
# Function that parse the operands of a instructions                      #
# following the format M                                                  #
#                                                                         #
# Inputs:                                                                 #
#       operands: string that contains the instruction without            #
#                 the mnemonic                                            #
#                                                                         #
# Output: On success return a list with two elements, the first is        #
#         the integer uses as a code to indicate if the conversion        #
#         was successful or not and the second is a string with the       #
#         hexadecimal value of the codified instruction                   #
#                                                                         #  
#         On failure return a list with three elements, the first is      #
#         the error code, the second is the number of the line with       #
#         the error and the third element is the error message            #
###########################################################################
def parse_operands_format_m(operands):

    # Variable used to store the hexadecimal code of the instruction
    hex_code = ''

    # Search for a # and a numeric value
    has_immediate = re.search('(?<=#)\d+',operands)

    # Search for the number of the vector register
    vector_id = re.search('(?<=V)\d+',operands)

    # Search for the number of the scalar register
    register_id = re.search('(?<=R)\d+',operands)

    # Check if the instructions has two correctly defined registers
    if( vector_id == None
        or register_id == None
        or len(re.findall('(?<=V)\d+',operands)) > 1
        or len(re.findall('(?<=R)\d+',operands)) > 1
      ):

        # Return error code
        return [-1,"Incorrect number of operands"]

    # Parse to int the register numbers
    Vd = int(vector_id.group())
    Rs = int(register_id.group())

    # Check that the registers specified exists
    if Vd < 0 or Vd > 15 or Rs < 0 or Rs > 6:

        # Return error code
        return [-1, 'Register does not exist']

    # Convert to binary values
    Vd = format(Vd,'04b')
    Rs = format(Rs,'03b')

    if(has_immediate != None):

        # Obtain the numeric value in the instruction
        immediate_value = int(has_immediate.group())

        # Check if the immediate value is a 20 bits constant
        if immediate_value > 1048575:

            # Return error code
            return [-1,'Exceed 20 bits constant']

        # Convert the immediate to pair of hexadecimal values
        hex_code = format(immediate_value,'020b')

        # Bit P that indicates the addressing mode used
        p_bit = ''

        # Check if the instructions use pre or post index
        if operands.find('#') < operands.find('R'):

            # Assign P bit to zero -> pre index
            p_bit = '0'

        else:

            # Assign P bit to one -> post index
            p_bit = '1'

        # Add the P-bit, Vd, Imm, Rs -> all in binary format
        hex_code = p_bit + Vd + hex_code + Rs

    else:
        
        # Add the P-bit, Vd, Imm, Rs -> all in binary format
        hex_code = '0' + Vd + '00000000000000000000' + Rs

    # Convert the binary value to hexadecimal
    hex_code = format(int(hex_code,2),'07x')    

    # Return success code and the hexadecimal code of the operands
    return [0,hex_code]

###########################################################################
# Function that parse one instruction depending on its format             #
#                                                                         # 
# Inputs:                                                                 #
#       line: string that contains the instruction in assembly syntax     #
#                                                                         #
# Output: On success return a list with two elements, the first is        #
#         the integer uses as a code to indicate if the conversion        #
#         was successful or not and the second is a string with the       #
#         hexadecimal value of the codified instruction                   #
#                                                                         #  
#         On failure return a list with three elements, the first is      #
#         the error code, the second is the number of the line with       #
#         the error and the third element is the error message            #
###########################################################################
def parse_instruction(line):

    # Separate the instruction mnemonic from the operands
    # The split is configure at the first whitespace
    instruction = re.split(' ',line,1)

    # Detect a syntax error
    if len(instruction) != 2:

        # Return -1 as a error code
        return [-1, "Expected space between mnemonic and operands"]

    # Check which format the instruction belongs to 
    if instruction[0] in format_f_instructions:

        # Flag use to indicate that the instructions
        # might use three register operands
        instruction_use_va = True

        # Compare with the only format F instruction
        # that does not use a explicitly defined Va register
        if instruction[0] == 'VSET':

            # Set the flag to false to indicate that
            # the instruction is VSET
            instruction_use_va = False

        # Get the codification of the operands
        result = parse_operands_format_f(instruction[1],
                                         instruction_use_va)

        # Check if the process was successful
        if result[0] == 0:

            # Add the operational code
            result[1] = format_f_instructions[instruction[0]] + result[1]

        # Return the success code and the codified instruction
        # or the failure code and error message
        return result

    elif instruction[0] in format_i_instructions:

        # Flag use to indicate that the instructions
        # might use three register operands
        instruction_use_ra = False

        # Compare with the only format I instruction
        # that use a explicitly defined Ra register
        if instruction[0] == 'ADD':

            # Set the flag to true to indicate that
            # the instruction is ADD
            instruction_use_ra = True

        # Get the codification of the operands
        result = parse_operands_format_i(instruction[1],
                                         instruction_use_ra)

        # Check if the process was successful
        if result[0] == 0:

            # Add the operational code
            result[1] = format_i_instructions[instruction[0]] + result[1]

        # Return the success code and the codified instruction
        # or the failure code and error message
        return result

    elif instruction[0] in format_m_instructions:

        # Get the codification of the operands
        result = parse_operands_format_m(instruction[1])

        # Check if the process was successful
        if result[0] == 0:

            # Add the operational code
            result[1] = format_m_instructions[instruction[0]] + result[1]

        # Return the success code and the codified instruction
        # or the failure code and error message
        return result

    else:
        
        return [-1, "Instruction not recognized"]

###########################################################################
# Function that reads all the user program and search for pragmas to      #
# resolved and comments and blank spaces to remove                        # 
#                                                                         #
# Inputs:                                                                 #
#       user_program: list with strings that contains all the             # 
#                     instructions of the user program                    #
#                                                                         #
# Output: On success return a list with two elements, the first is        #
#         the integer uses as a code to indicate if the conversion        #
#         was successful or not and the second is a string with the       #
#         hexadecimal value of the codified instruction                   #
#                                                                         #  
#         On failure return a list with three elements, the first is      #
#         the error code, the second is the number of the line with       #
#         the error and the third element is the error message            #
###########################################################################
def parse_pragma(user_program):

    # Save the pragma begin pattern for compare
    pragma_begin = re.compile("#pragma_for_begin\((\d+)\)")

    # Save the pragma end pattern for compare
    pragma_end = re.compile("#pragma_for_end")

    # List without blank spaces, comments or
    # unresolved pragmas
    only_instructions = []

    # Number of the line that is being analyzed
    line_number = 1

    # Instructions stack for deal with nested pragmas
    pragma_stack = []

    # Iterations values stack for deal with nested pragmas
    iterations_stack = []

    # Analyze all the user program looking for unresolved pragmas,
    # blank spaces or comments to remove
    for line in user_program:

        # Check if the line is not a blank space and begins with #
        if line.strip() and line[0] == '#':

            # Compare the line against the pragma begin pattern
            # if match the extract the number of iterations
            pragma_iterations = pragma_begin.findall(line)

            # Check if there is a match with the pragma begin pattern
            if len(pragma_iterations) == 1:

                # Add a list in top of the pragma instruction stack
                pragma_stack = [[]] + pragma_stack

                # Get the number of iterations associated with
                # the list in the top of the pragma instrucion stack
                copies = int(pragma_iterations[0])

                # Check that the number of iterations makes sense
                if(copies <= 1):

                    # Return error code and error message
                    return [-1,line_number,"Pragma iterations must be greater than 1"]

                # If the number of iterations makes sense
                # then is added to the top of the pragma iterations stack
                iterations_stack = [copies] + iterations_stack

            # Check if there is a match with the pragma end pattern
            elif len(pragma_end.findall(line)) > 0:

                # In this case the program find a pragma end and
                # the stack has not been initialized so this mean
                # the user end a pragma without begin it first
                if len(pragma_stack) == 0:
                    
                    # Return the error code and error message
                    return [-1,line_number,"Pragma end without begin"]
        
                # List to hold instructions that will be
                # repeated n times
                expand_instructions = []
                
                # Copy the same block n times using the value
                # in the top of the iterations stack
                for iteration in range(0, iterations_stack[0]):

                    # Copy the set of instruction of the pragma
                    # in top of the stack
                    expand_instructions += pragma_stack[0];

                # Check if the current pragma is not inside
                # another pragma block
                if len(pragma_stack) == 1:

                    # Copy the repeated block in the main instructions
                    # list that will be codified later
                    only_instructions += expand_instructions

                # Check if the current pragma is inside
                # another pragma block
                elif len(pragma_stack) > 1:

                    # Copy the repeated block inside the
                    # instruction block of the outer pragma
                    pragma_stack[1] += expand_instructions
                    
                # Remove the instruction block in top of the stack
                pragma_stack = pragma_stack[1:]

                # Remove the number of iterations in top of the stack
                # because this value has already been used
                iterations_stack = iterations_stack[1:]

            # Did not find a match with a pragma begin or end
            # so this means a syntax error
            else:

                # Return error code and error message
                return [-1,line_number,"Bad defined pragma"]
                
        # Check if the lines are not a blank space or a comment
        elif line.strip() and line[0:2] != "//":

            # If the instruction is inside a pragma block
            # then it must be stored in the top of the pragma stack
            if len(pragma_stack) > 0:

                # Save the instruction in the top of the stack
                pragma_stack[0] += [line +"\n"]

            # The instruction is not inside a pragma block
            else:

                # Add the instruction directly to the instruction list
                only_instructions += [line + "\n"]
                

        # Increment the line number
        line_number += 1

    # Check if all the pragma blocks have a correctly
    # defined begin and end sentences
    if ( len(pragma_stack) != 0
         or len(iterations_stack) != 0 ):

        # Return error code and error message
        return [-1,line_number,"Pragma without end"]

    # In case all succeed return a sucess code
    # and the list of the instructions
    return [0, only_instructions]

###########################################################################
# Main function that reads all the user program and codified all the      # 
# valid instructions ignoring comments and blank spaces                   # #                                                                         #
#                                                                         #
# This function is also in charge of resolving pragmas block that         #
# multiply blocks of code                                                 #
#                                                                         #
# Inputs:                                                                 #
#       user_program: list with strings that contains all the             #
#                     instructions of the user program                    #
#                                                                         #
# Output: On success return a list with two elements, the first is        #
#         the integer uses as a code to indicate if the conversion        #
#         was successful or not and the second is a string with the       #
#         hexadecimal value of the codified instruction                   #
#                                                                         #  
#         On failure return a list with three elements, the first is      #
#         the error code, the second is the number of the line with       #
#         the error and the third element is the error message            #
###########################################################################
def parse_program(user_program):

    # Array for the codified instructions
    codified_instructions = []

    # Line counter for the syntax error message
    line_number = 1

    # Search for a pragma in order to expand the code
    # or eliminate the comments and blank spaces
    instructions = parse_pragma(user_program)

    # Check if an error code is returned
    if instructions[0] != 0:

        # Return the error code for the editor to
        # display the error message
        return instructions

    # If the operation is successful then get
    # only the instructions without the success code
    instructions = instructions[1]

    # Encode the instructions one by one
    for line in instructions:

        # Get the codified instruction
        the_code = parse_instruction(line)

        # Check that the conversion was successful
        if the_code[0] == 0:

            # Add the codified instruction to the list
            codified_instructions += [the_code[1] + "\n"]

        else:

            # Return an error code, the number of the line
            # with the error and the corresponding
            # error message for the editor to display
            return [the_code[0],line_number, the_code[1]]

        # Increment the line counter
        line_number += 1

    # Return the success code and the codified instructions list
    return [0 , codified_instructions]
