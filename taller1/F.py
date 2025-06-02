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
    
    def make_query(ldap_str):
        print(ldap_str, flush=True)
        response = sys.stdin.readline().strip()
        if response == "0":
            print(f"! {ldap_str}", flush=True)
            sys.exit(0)
    
    if not first_name1 or not last_name1 or not last_name2:
        sys.exit("Error: Partes del nombre faltantes para el LDAP inicial.")
        
    ldap_seq1 = first_name1[0] + f2_char_component + last_name1 + last_name2[0]
    make_query(ldap_seq1)
    
    for l_f1_len in range(2, len(first_name1) + 1):
        current_fn1_prefix = first_name1[:l_f1_len]
        
        limit_l_l2_len = min(l_f1_len, len(last_name2))
        for l_l2_len in range(limit_l_l2_len + 1):
            current_ln2_prefix = last_name2[:l_l2_len]
            ldap = current_fn1_prefix + f2_char_component + last_name1 + current_ln2_prefix
            make_query(ldap)
    
    if len(first_name1) > 0:
        fn1_full_prefix = first_name1
        
        start_l_l2_len_final = min(len(first_name1), len(last_name2)) + 1
        
        for l_l2_len in range(start_l_l2_len_final, len(last_name2) + 1):
            current_ln2_prefix = last_name2[:l_l2_len]
            ldap = fn1_full_prefix + f2_char_component + last_name1 + current_ln2_prefix
            make_query(ldap)

if __name__ == "__main__":
    solve()
