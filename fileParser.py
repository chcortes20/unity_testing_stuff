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
    print(unique_includes)
    copied_headers = set()
    os.makedirs(destination_directory, exist_ok=True) # look into this here
    for header in unique_includes:
        if header not in copied_headers:
            for root, _, files in os.walk(source_directory):
                for file in files:
                    if file == header:
                        header_path = os.path.join(root, file)
                        print(header_path)
                        if os.path.exists(header_path) and os.path.isfile(header_path):
                            shutil.copy(header_path, destination_directory )
                            copied_headers.add(header)
        

if __name__ == "__main__":
    source_directory = "unit3a/src"
    destination_directory = "testing/test"
    starting_location = "unit3a"

    unique_includes = collect_unique_includes(source_directory)
    # print(unique_includes, type(unique_includes))
    copy_headers(unique_includes, starting_location, destination_directory)
