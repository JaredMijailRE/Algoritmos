import subprocess
import os

# Test cases from the problem description
tests = [
    {
        "name": "Example 1",
        "input": """4 2
1 2
2 3
1 4
1 2""",
        "output": "1"
    },
    {
        "name": "Example 2",
        "input": """3 3
1 2
1 3
2 1""",
        "output": "13"
    },
    {
        "name": "Example 3",
        "input": """3 1
1 2
1 3
1 1""",
        "output": "0"
    }
]

def run_tests():
    """
    Compiles and runs the C++ solution against predefined test cases.
    """
    executable_name = 'M'
    cpp_file = 'M.cpp'

    # Compile the C++ file
    if not os.path.exists(executable_name) or os.path.getmtime(cpp_file) > os.path.getmtime(executable_name):
        print(f"Compiling {cpp_file}...")
        compile_command = ['g++', '-std=c++17', '-O2', cpp_file, '-o', executable_name]
        compile_process = subprocess.run(compile_command, capture_output=True, text=True)
        
        if compile_process.returncode != 0:
            print("--- COMPILATION FAILED ---")
            print(f"Error:\n{compile_process.stderr}")
            return
        print("Compilation successful.")

    # Run tests
    for i, test in enumerate(tests):
        print(f"\n--- Running Test Case {i+1}: {test['name']} ---")
        try:
            process = subprocess.run(
                [f'./{executable_name}'],
                input=test['input'],
                capture_output=True,
                text=True,
                timeout=5
            )
            
            output = process.stdout.strip()
            expected = test['output'].strip()

            if output == expected:
                print(f"✅ PASS: Expected '{expected}', Got '{output}'")
            else:
                print(f"❌ FAIL: Expected '{expected}', Got '{output}'")
                print(f"Input was:\n---\n{test['input']}\n---")
                if process.stderr:
                    print(f"Stderr:\n{process.stderr}")
        
        except subprocess.TimeoutExpired:
            print("❌ FAIL: Time Limit Exceeded")
        except Exception as e:
            print(f"❌ FAIL: An error occurred: {e}")

if __name__ == "__main__":
    run_tests()
