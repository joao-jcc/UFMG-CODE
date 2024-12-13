import subprocess
import os

# Path to the binary file
binary_path = "./bin/tp2"

# Directory containing input files
input_dir = "testCases/inputs/"

# Get all files in the input directory
input_files = sorted([os.path.join(input_dir, f) for f in os.listdir(input_dir)])

# Loop through each input file and execute the binary
for input_file in input_files:
    
    # Construct the Bash command
    bash_command = f"{binary_path} < {input_file}"
    
    try:
        print(f"Executing: {bash_command}")
        
        # Run the Bash command
        result = subprocess.run(
            bash_command,
            shell=True,  # Enable shell to execute the Bash command
            text=True,   # Ensure text output instead of bytes
            capture_output=True  # Capture stdout and stderr
        )
        
        # Print the output
        print(f"Output for {input_file}:\n{result.stdout}")
        if result.stderr:
            print(f"Error for {input_file}:\n{result.stderr}")
    except Exception as e:
        print(f"Error executing {binary_path} with {input_file}: {e}")
