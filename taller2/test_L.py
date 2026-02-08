import unittest
import sys
from io import StringIO
from L import solve

class TestCourseScheduling(unittest.TestCase):

    def run_test(self, input_data, expected_output):
        """Helper function to run a test case."""
        # Redirect stdin and stdout
        original_stdin = sys.stdin
        original_stdout = sys.stdout
        sys.stdin = StringIO(input_data)
        sys.stdout = captured_output = StringIO()

        solve()

        # Restore original stdin and stdout
        sys.stdin = original_stdin
        sys.stdout = original_stdout
        
        self.assertEqual(captured_output.getvalue().strip(), expected_output)

    def test_example_1(self):
        """Test the first example from the problem description."""
        input_data = "4 2\n3 3 4 0\n"
        expected_output = "3"
        self.run_test(input_data, expected_output)

    def test_example_2(self):
        """Test the second example from the problem description."""
        input_data = "3 3\n0 1 2\n"
        # The prerequisites form a chain: 3 -> 2 -> 1
        # Each course is in a new semester.
        expected_output = "3"
        self.run_test(input_data, expected_output)

    def test_long_chain(self):
        """Test a single long chain of prerequisites."""
        input_data = "5 1\n2 3 4 5 0\n"
        # Chain: 1 -> 2 -> 3 -> 4 -> 5
        expected_output = "5"
        self.run_test(input_data, expected_output)

    def test_multiple_sources_and_k(self):
        """Test with multiple starting courses and k > 1."""
        input_data = "6 2\n3 4 0 0 0 0\n"
        # Level 0: {1,2,5,6} -> needs 2 semesters (4/2)
        # Level 1: {3,4} -> needs 1 semester (2/2)
        expected_output = "3"
        self.run_test(input_data, expected_output)
        
    def test_complex_dependencies(self):
        """Test a case where a course has prerequisites of different depths."""
        # 1->3, 2->3, 3->4, 4->5, 5->6. Also, a separate chain 7->8
        # Level-based analysis with k=2:
        # L0: {1,2,7} -> 2 semesters, L1: {3,8} -> 1 semester
        # L2: {4} -> 1 semester, L3: {5} -> 1 semester, L4: {6} -> 1 semester
        input_data = "8 2\n3 3 4 5 6 0 8 0\n"
        expected_output = "6"
        self.run_test(input_data, expected_output)

    def test_no_prerequisites(self):
        """Test a case with no prerequisites at all."""
        input_data = "5 2\n0 0 0 0 0\n"
        # All 5 courses at level 0. Need ceil(5/2) = 3 semesters.
        expected_output = "3"
        self.run_test(input_data, expected_output)
        
    def test_critical_path_logic(self):
        """Test a case where a simple greedy choice is suboptimal."""
        # This tests the "critical path" problem.
        # We have k=1.
        # Courses available are {1, 3}.
        # Path 1: 1 -> 2 (length 1)
        # Path 2: 3 -> 4 -> 5 (length 2)
        # A simple greedy approach might take course 1 first (lower index).
        # Optimal is to take course 3, which is on the longer critical path.
        #
        # Simple Greedy (take 1):
        # Sem 1: take 1. (avail: {3})
        # Sem 2: take 3. (avail: {2, 4})
        # Sem 3: take 2. (avail: {4})
        # Sem 4: take 4. (avail: {5})
        # Sem 5: take 5.
        # Total: 5 semesters.
        #
        # Optimal (take 3):
        # Sem 1: take 3. (avail: {1, 4})
        # Sem 2: take 4. (avail: {1, 5})
        # Sem 3: take 5. (avail: {1})
        # Sem 4: take 1. (avail: {2})
        # Sem 5: take 2.
        # Total: 5 semesters.
        # Hmm, for k=1, the order doesn't change the total time.
        # Let's try k=2.
        #
        # k=2
        # Optimal:
        # Sem 1: take {1, 3}. (avail: {2,4})
        # Sem 2: take {2, 4}. (avail: {5})
        # Sem 3: take {5}.
        # Total: 3 semesters
        input_data = "5 2\n2 0 4 5 0\n"
        expected_output = "3"
        self.run_test(input_data, expected_output)

    def test_edge_case_timing(self):
        """Test a case that might expose timing issues in the current logic."""
        # This creates a scenario where course availability timing matters
        # Course 1 -> Course 3, Course 2 -> Course 3
        # Course 3 -> Course 4
        # With k=2, we should be able to take courses 1,2 in semester 1
        # Then course 3 in semester 2, then course 4 in semester 3
        # Total: 3 semesters
        input_data = "4 2\n3 3 4 0\n"
        expected_output = "3"
        self.run_test(input_data, expected_output)
        
    def test_another_edge_case(self):
        """Test another potential edge case."""
        # Let's try a case that might fail: courses with different prerequisite depths
        # 1->2->4, 3->4, with k=1
        # Should be: Sem1: take 1,3 (both available), Sem2: take 2, Sem3: take 4
        # Wait, with k=1: Sem1: take 1, Sem2: take 3, Sem3: take 2, Sem4: take 4
        # Actually let's make k=2: Sem1: take 1,3, Sem2: take 2, Sem3: take 4 = 3 sems
        input_data = "4 2\n2 4 4 0\n"
        expected_output = "3"
        self.run_test(input_data, expected_output)

if __name__ == '__main__':
    unittest.main(argv=['first-arg-is-ignored'], exit=False) 