import os
import re
import shutil
import argparse

def resolve_includes(glsl_content, root):
    # Find all "#include" statements in the GLSL file
    include_statements = re.findall(r'#include\s+"([^"]+)"', glsl_content)

    # Process each include statement
    for include_statement in include_statements:
        # Get the path of the included file
        included_file_path = os.path.join(root, include_statement)

        # Read the contents of the included file
        with open(included_file_path, 'r') as included_file:
            included_content = included_file.read()

        # Recursively resolve includes in the included content
        included_content = resolve_includes(included_content, os.path.dirname(included_file_path))

        # Replace the include statement with the included content
        glsl_content = glsl_content.replace(f'#include "{include_statement}"', included_content)

    return glsl_content

def process_glsl_files(glsl_path, result_path):
    # Create the result directory if it doesn't exist
    if not os.path.exists(result_path):
        os.makedirs(result_path)

    # Walk through the directory tree
    for root, dirs, files in os.walk(glsl_path):
        # Calculate the relative path from the root GLSL directory
        relative_path = os.path.relpath(root, glsl_path)
        # Create the corresponding directory in the result path
        result_dir = os.path.join(result_path, relative_path)
        if not os.path.exists(result_dir):
            os.makedirs(result_dir)

        # Process each file in the current directory
        for file in files:
            if file.endswith('.glsl') and not file.startswith('_'):
                glsl_file_path = os.path.join(root, file)
                result_file_path = os.path.join(result_dir, file)

                # Read the contents of the GLSL file
                with open(glsl_file_path, 'r') as glsl_file:
                    glsl_content = glsl_file.read()

                # Resolve all includes recursively
                glsl_content = resolve_includes(glsl_content, root)

                # Write the processed GLSL file to the result directory
                with open(result_file_path, 'w') as result_file:
                    result_file.write(glsl_content)

    print("GLSL files processed successfully!")

def main():
    parser = argparse.ArgumentParser(description="Process GLSL files.")
    parser.add_argument("glsl_path", help="Path to the directory containing GLSL files")
    parser.add_argument("result_path", help="Path to the directory where processed files will be saved")
    args = parser.parse_args()

    process_glsl_files(args.glsl_path, args.result_path)

if __name__ == "__main__":
    main()