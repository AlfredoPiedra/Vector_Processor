# Regular expression library
import re

# List of the instructions with format F
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

# List of the instructions with format I
format_m_instructions = {

    'VLDR': 'a',
    'VSTR': 'b'
}

# List of the instructions with format I
format_i_instructions = {

    'ADD': 'c',
    'SET': 'd',
    'STR': 'e',
    'LDR': 'f'
}

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

def parse_pragma(user_program):

    only_instructions = []
    
    for line in user_program:

        # Check if the line is a blank space
        # or the line is a comment
        if (line.strip()
            and line[0:2] != '//'
            and line[0] != '#'):

            only_instructions += [line]
            
    return only_instructions

# Main function used for parse the assembly code
def parse_program(user_program):

    # Array for the codified instructions
    codified_instructions = []

    # Line counter for the syntax error message
    line_number = 1

    # Search for a pragma in order to expand the code
    # or eliminate the comments and blank spaces
    instructions = parse_pragma(user_program)

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
