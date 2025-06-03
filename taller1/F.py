import sys

def solve():
    full_name_parts = sys.stdin.readline().strip().split()
    first_name1 = ""
    first_name2 = ""
    last_name1 = ""
    last_name2 = ""

    if len(full_name_parts) == 3:
        first_name1 = full_name_parts[0]
        last_name1 = full_name_parts[1]
        last_name2 = full_name_parts[2]
    elif len(full_name_parts) == 4:
        first_name1 = full_name_parts[0]
        first_name2 = full_name_parts[1]
        last_name1 = full_name_parts[2]
        last_name2 = full_name_parts[3]

    f2_char_component = ""
    if first_name2:
        f2_char_component = first_name2[0]

    L = len(first_name1)
    M = len(last_name2)

    groups = []
    groups.append((1, 1, 1))  

    for a in range(2, L + 1):
        count = min(a + 1, M + 1)
        groups.append((a, 0, count))

    if M > L:
        groups.append((L, L + 1, M - L))

    total_indices = sum(g[2] for g in groups)

    def build_ldap(a, b):
        part1 = first_name1[:a]
        part2 = f2_char_component
        part3 = last_name1
        part4 = last_name2[:b] if b > 0 else ""
        return part1 + part2 + part3 + part4

    def get_ldap_by_index(index):
        count = 0
        for a, b_start, length in groups:
            if index < count + length:
                b_val = b_start + (index - count)
                return build_ldap(a, b_val)
            count += length
        return None

    def make_query(ldap_str):
        print(ldap_str)
        sys.stdout.flush()
        while True:
            response = sys.stdin.readline().strip()
            if response:
                return response

    left = 0
    right = total_indices - 1
    result_index = None

    while left <= right:
        mid = (left + right) // 2
        candidate = get_ldap_by_index(mid)
        response = make_query(candidate)
        if response == "1":
            left = mid + 1
        else:
            result_index = mid
            right = mid - 1

    if result_index is None:
        result_index = total_indices - 1

    final_ldap = get_ldap_by_index(result_index)
    print(f"! {final_ldap}")
    sys.stdout.flush()

if __name__ == "__main__":
    solve()
