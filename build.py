import os

# Define the paths to your project directory and the support directory
support_dir = os.path.dirname(os.path.realpath(__file__))
project_dir = os.path.dirname(os.path.realpath(support_dir))

# Move project.yml up to the project directory if it exists in the support directory
project_yml_src = os.path.join(support_dir, 'project.yml')
project_yml_dest = os.path.join(project_dir, 'project.yml')


def main():
    if os.path.exists(project_yml_src):
        os.rename(project_yml_src, project_yml_dest)
        print("Moved project.yml to the project directory.")

    # Check if the test directory exists, and create it if it doesn't
    test_dir = os.path.join(project_dir, 'test')
    if not os.path.exists(test_dir):
        os.mkdir(test_dir)
        print("Created 'test' directory.")

    # Check if the inc directory inside the test directory exists, and create it if it doesn't
    inc_dir = os.path.join(test_dir, 'inc')
    if not os.path.exists(inc_dir):
        os.mkdir(inc_dir)
        print("Created 'inc' directory inside 'test' directory.")

    # Define the path to the src directory
    src_dir = os.path.join(project_dir, 'src')

    # Iterate through the files in the src directory
    for filename in os.listdir(src_dir):
        if filename.endswith('.c'):
            # Construct the path to the test file
            test_file_path = os.path.join(test_dir, f'test_{filename}')

            # Create an empty test file
            with open(test_file_path, 'w'):
                pass
            print(f"Created empty test file: {test_file_path}")

if __name__ == '__main__':
    main()