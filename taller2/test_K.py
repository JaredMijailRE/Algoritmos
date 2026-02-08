import unittest
import sys
from io import StringIO
from K import solve

class TestPacman(unittest.TestCase):

    def run_solve(self, R, C, maze, path):
        # This function remains the same as it tests the overall `solve` function's I/O
        input_str = f"{R} {C}\n"
        input_str += "\n".join(maze) + "\n"
        input_str += path + "\n"
        
        original_stdin = sys.stdin
        original_stdout = sys.stdout
        sys.stdin = StringIO(input_str)
        sys.stdout = captured_output = StringIO()

        solve()

        sys.stdin = original_stdin
        sys.stdout = original_stdout
        
        return captured_output.getvalue().strip()

    def setUp(self):
        # No changes needed here, as run_solve handles the string formatting
        self.test_case_1 = {
            "R": 7, "C": 7,
            "maze": [
                "....P..",
                "..#..#.",
                "..#..#.",
                "..####.",
                ".G.....",
                ".......",
                "......."
            ],
            "path": "RRRRRRDD",
            "expected": "Yes"
        }
        
        self.test_case_2 = {
            "R": 7, "C": 7,
            "maze": [
                "....P..",
                "..#..#.",
                "..#..#.",
                "..####.",
                ".......",
                ".......",
                ".G....."
            ],
            "path": "RRRRRRDD",
            "expected": "No"
        }

        self.multiple_visits_test = {
            "R": 5, "C": 5,
            "maze": [
                "P....",
                ".#.#.",
                ".....",
                ".#.#.",
                "G...."
            ],
            "path": "RRRRDDDDLLLLUUUU",
            "expected": "Yes"
        }

        self.trapped_ghost_test = {
            "R": 5, "C": 5,
            "maze": [
                "P....",
                ".....",
                "#####",
                "#G#.#",
                "#####"
            ],
            "path": "RRRRDDDD",
            "expected": "No"
        }

        self.pacman_wraps_test = {
            "R": 5, "C": 5,
            "maze": [
                "P#G#.",
                ".....",
                ".....",
                ".....",
                "....."
            ],
            "path": "L",
            "expected": "No"
        }

        self.pacman_trapped_test = {
            "R": 3, "C": 3,
            "maze": [
                "G.#",
                "#P#",
                "..."
            ],
            "path": "UDLR",
            "expected": "Yes"
        }
    # Test methods remain the same
    def test_example_1(self):
        """Test the first example."""
        case = self.test_case_1
        result = self.run_solve(case["R"], case["C"], case["maze"], case["path"])
        self.assertEqual(result, case["expected"])

    def test_example_2(self):
        """Test the second example."""
        case = self.test_case_2
        result = self.run_solve(case["R"], case["C"], case["maze"], case["path"])
        self.assertEqual(result, case["expected"])

    def test_multiple_visits(self):
        """Test interception on a subsequent visit."""
        case = self.multiple_visits_test
        result = self.run_solve(case["R"], case["C"], case["maze"], case["path"])
        self.assertEqual(result, case["expected"])

    def test_trapped_ghost(self):
        """Test a case where the ghost is trapped."""
        case = self.trapped_ghost_test
        result = self.run_solve(case["R"], case["C"], case["maze"], case["path"])
        self.assertEqual(result, case["expected"])

    def test_pacman_wraps(self):
        """Test a case where Pac-Man wraps around the border."""
        case = self.pacman_wraps_test
        result = self.run_solve(case["R"], case["C"], case["maze"], case["path"])
        self.assertEqual(result, case["expected"])
    
    def test_pacman_trapped(self):
        """Test a case where Pac-Man is trapped."""
        case = self.pacman_trapped_test
        result = self.run_solve(case["R"], case["C"], case["maze"], case["path"])
        self.assertEqual(result, case["expected"])

if __name__ == '__main__':
    unittest.main() 