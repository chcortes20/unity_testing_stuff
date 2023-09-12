import os
import re
import shutil


def remove_leading_path(unique_list: list[str]):

    for index, item in enumerate(unique_list):
        if '/' in item:
            temp = item.split("/")
            unique_list[index] = temp[-1]
    return unique_list


def collect_unique_includes(directory):
    unique_includes = set()
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.c', '.h')):
                file_path = os.path.join(root, file)
                with open(file_path, 'r') as f:
                    content = f.read()
                    includes = re.findall(r'#include\s+(?:"([^"]+(?:\/[^"]+)*)"|<([^>]+)>)', content)
                    for include in includes:
                        unique_includes.add(include[0] or include[1])
    unique_includes = list(unique_includes)
    remove_leading_path(unique_includes)
    # print(unique_includes)
    return set(unique_includes)

def copy_headers(unique_includes, source_directory, destination_directory):
    # print(unique_includes)
    copied_headers = set()
    os.makedirs(destination_directory, exist_ok=True) # look into this here
    for header in unique_includes:
        if header not in copied_headers:
            for root, _, files in os.walk(source_directory):
                for file in files:
                    if file == header:
                        header_path = os.path.join(root, file)
                        print(header_path)
                        extract_global_static_variables(header_path)
                        if os.path.exists(header_path) and os.path.isfile(header_path):
                            shutil.copy(header_path, destination_directory )
                            copied_headers.add(header)
        

def extract_global_static_variables(input_file_path):
    # Regular expression patterns for global and static variable declarations
    global_pattern = r'(\w+)\s+(\w+)\s*;'
    static_pattern = r'static\s+(\w+)\s+(\w+)\s*;'

    global_vars = []
    static_vars = []

    with open(input_file_path, 'r') as input_file:
        inside_function = False
        for line in input_file:
            # Check if we're inside a function
            if re.search(r'\w+\s+\w+\s*\([^)]*\)\s*{', line):
                inside_function = True
            elif re.search(r'}', line):
                inside_function = False

            # Search for global variable declarations
            if not inside_function:
                global_match = re.search(global_pattern, line)
                static_match = re.search(static_pattern, line)
                if global_match:
                    global_vars.append(global_match.group())
                elif static_match:
                    static_vars.append(static_match.group())

    print("globals:", global_vars)
    print("static:", static_vars)
    # return global_vars, static_vars



def generate_header_from_source(input_file_path, output_file_path):
    global_vars, static_vars = extract_global_static_variables(input_file_path)

    # Regular expression pattern to match C function definitions
    function_pattern = r'(.*?)\s+(\w+)\s*\([^)]*\)\s*{'

    try:
        # Open the output header file
        with open(output_file_path, 'w') as output_file:
            # Write global variables to the header
            for global_var in global_vars:
                output_file.write(f'{global_var}\n')

            # Write static variables to the header
            for static_var in static_vars:
                output_file.write(f'{static_var}\n')

            # Write function prototypes to the header
            with open(input_file_path, 'r') as input_file:
                inside_function = False
                for line in input_file:
                    # Check if we're inside a function
                    if re.search(r'\w+\s+\w+\s*\([^)]*\)\s*{', line):
                        inside_function = True
                    elif re.search(r'}', line):
                        inside_function = False

                    # Search for function definitions using the pattern
                    if not inside_function:
                        function_match = re.search(function_pattern, line)
                        if function_match:
                            return_type, function_name = function_match.groups()
                            # Write the function prototype to the output header file
                            output_file.write(f'{return_type} {function_name}();\n')

        print(f"Header file '{output_file_path}' generated with function prototypes, global, and static variables.")

    except FileNotFoundError:
        print(f"Error: File not found - {input_file_path}")
    except Exception as e:
        print(f"An error occurred: {str(e)}")



'''
def extract_function_signatures(input_file_path):
    # Regular expression pattern to match C function signatures
    function_pattern = r'(.*?)\s+(\w+)\s*\(([^)]*)\)\s*{'

    function_signatures = []

    with open(input_file_path, 'r') as input_file:
        inside_function = False
        for line in input_file:
            # Check if we're inside a function
            if re.search(r'\w+\s+\w+\s*\([^)]*\)\s*{', line):
                inside_function = True
            elif re.search(r'}', line):
                inside_function = False

            # Search for function signatures using the pattern
            if not inside_function:
                function_match = re.search(function_pattern, line)
                if function_match:
                    return_type, function_name, parameters = function_match.groups()
                    # Remove whitespace and newline characters from parameters
                    parameters = ' '.join(parameters.split())
                    # Write the function prototype to the list
                    function_signatures.append(f'{return_type} {function_name}({parameters});')

    return function_signatures

def generate_header_from_source(input_file_path, output_file_path):
    static_vars = extract_static_variables(input_file_path)
    function_signatures = extract_function_signatures(input_file_path)

    try:
        # Open the output header file
        with open(output_file_path, 'w') as output_file:
            # Write the #define TEST with STATIC inside and #define STATIC
            output_file.write("#define TEST\n")
            output_file.write("#ifdef TEST\n")
            output_file.write("#define STATIC static\n")
            output_file.write("#else\n")
            output_file.write("#define STATIC\n")
            output_file.write("#endif\n\n")

            # Write static variables to the header
            for static_var in static_vars:
                output_file.write(f'{static_var}\n')

            # Write the function prototypes to the header
            for signature in function_signatures:
                output_file.write(f'{signature}\n')

        print(f"Header file '{output_file_path}' generated with static variables and function prototypes.")

    except FileNotFoundError:
        print(f"Error: File not found - {input_file_path}")
    except Exception as e:
        print(f"An error occurred: {str(e)}")
'''

if __name__ == "__main__":
    source_directory = "unit3a/src"
    destination_directory = "testing/test"
    starting_location = "unit3a"

    unique_includes = collect_unique_includes(source_directory)
    # test = list(unique_includes)
    # unique_includes = get_includes(source_directory)
    # print(unique_includes, type(unique_includes))
    # extract_global_static_variables(test[0])
    copy_headers(unique_includes, starting_location, destination_directory)
