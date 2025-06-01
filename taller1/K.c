// https://vjudge.net/contest/713089#problem/K
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int custom_min(int a, int b) {
    return a < b ? a : b;
}

char actual_n1[25];
char actual_s1[25];
char actual_s2[25];
char n2_first_char_str[2]; 

char n1_prefix_buf[25];
char s2_prefix_buf[25];
char ldap_buf[100];      

int main() {
    char line_input[150]; 
    if (fgets(line_input, sizeof(line_input), stdin) == NULL) {
        return 1; 
    }
    
    line_input[strcspn(line_input, "\n")] = 0;


    char temp_w1[25], temp_w2[25], temp_w3[25], temp_w4[25];
    int num_words = sscanf(line_input, "%s %s %s %s", temp_w1, temp_w2, temp_w3, temp_w4);

    if (num_words == 3) {

        strcpy(actual_n1, temp_w1);
        strcpy(actual_s1, temp_w2);
        strcpy(actual_s2, temp_w3);
        n2_first_char_str[0] = '\0'; 
    } else if (num_words == 4) {

        strcpy(actual_n1, temp_w1); 
        strcpy(actual_s1, temp_w3); 
        strcpy(actual_s2, temp_w4); 
        
        if (strlen(temp_w2) > 0) { 
            n2_first_char_str[0] = temp_w2[0];
            n2_first_char_str[1] = '\0';
        } else {
             n2_first_char_str[0] = '\0'; 
        }
    } else {
        return 1; 
    }

    int len_n1 = strlen(actual_n1);
    int len_s2 = strlen(actual_s2);
    char query_response[5]; 

    for (int k = 1; k <= len_n1; k++) {
        strncpy(n1_prefix_buf, actual_n1, k);
        n1_prefix_buf[k] = '\0';

        for (int m = 0; m <= custom_min(k, len_s2); m++) { 
            if (m == 0) {
                s2_prefix_buf[0] = '\0'; 
            } else {
                strncpy(s2_prefix_buf, actual_s2, m);
                s2_prefix_buf[m] = '\0';
            }

            sprintf(ldap_buf, "%s%s%s%s", n1_prefix_buf, n2_first_char_str, actual_s1, s2_prefix_buf);
            printf("%s\n", ldap_buf);
            fflush(stdout);

            if (scanf("%s", query_response) != 1) return 1; // Read error
            if (query_response[0] == '0') {
                printf("! %s\n", ldap_buf);
                fflush(stdout);
                return 0; // Found unused LDAP
            }
        }
    }

    strcpy(n1_prefix_buf, actual_n1); 

    int start_m_for_part2 = custom_min(len_n1, len_s2) + 1;
    for (int m = start_m_for_part2; m <= len_s2; m++) {
        strncpy(s2_prefix_buf, actual_s2, m);
        s2_prefix_buf[m] = '\0';

        sprintf(ldap_buf, "%s%s%s%s", n1_prefix_buf, n2_first_char_str, actual_s1, s2_prefix_buf);
        printf("%s\n", ldap_buf);
        fflush(stdout);

        if (scanf("%s", query_response) != 1) return 1; 
        if (query_response[0] == '0') {
            printf("! %s\n", ldap_buf);
            fflush(stdout);
            return 0; 
        }
    }
    
    return 0; 
}