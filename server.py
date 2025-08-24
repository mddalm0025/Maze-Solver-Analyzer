from flask import Flask, render_template, jsonify
import subprocess
import os

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/generate')
def generate_maze():
    try:
        print("Running maze solver...")

        # Run the C++ program
        result = subprocess.run(
            ['./maze_solver'], 
            capture_output=True, 
            text=True, 
            cwd='.'
        )

        print("STDOUT:", result.stdout)
        if result.stderr:
            print("STDERR:", result.stderr)

        # Check if files were created
        if not os.path.exists('maze.json'):
            error_msg = "maze.json not found. "
            if result.stderr and "error" in result.stderr.lower():
                error_msg += "Compilation error detected."
            return jsonify({'error': error_msg}), 500

        if not os.path.exists('results.json'):
            return jsonify({'error': 'results.json not found'}), 500

        # Read the generated files
        with open('maze.json', 'r') as f:
            maze_data = f.read()
        with open('results.json', 'r') as f:
            results_data = f.read()

        print("Files read successfully")
        return jsonify({
            'maze': maze_data,
            'results': results_data
        })

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    # Get the port from Replit's environment variable, default to 5000
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port, debug=True)