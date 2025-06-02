#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 25

int custom_min(int a, int b) {
    return a < b ? a : b;
}

void leer_nombre_completo(char *line_input, char *n1, char *n2_first_char, char *s1, char *s2) {
    char temp_w1[MAX_LEN], temp_w2[MAX_LEN], temp_w3[MAX_LEN], temp_w4[MAX_LEN];
    int num_words = sscanf(line_input, "%s %s %s %s", temp_w1, temp_w2, temp_w3, temp_w4);
    if (num_words == 3) {
        strcpy(n1, temp_w1);
        n2_first_char[0] = '\0';
        strcpy(s1, temp_w2);
        strcpy(s2, temp_w3);
    } else if (num_words == 4) {
        strcpy(n1, temp_w1);
        n2_first_char[0] = temp_w2[0];
        n2_first_char[1] = '\0';
        strcpy(s1, temp_w3);
        strcpy(s2, temp_w4);
    } else {
        exit(1);
    }
}

int consultar_ldap(const char *ldap_buf) {
    char respuesta[5];
    printf("%s\n", ldap_buf);
    fflush(stdout);
    if (scanf("%s", respuesta) != 1) exit(1);
    return respuesta[0] == '1';
}

void imprimir_ldap_final(const char *ldap_buf) {
    printf("! %s\n", ldap_buf);
    fflush(stdout);
}

void generar_y_verificar_ldap(const char *n1, const char *n2_first_char, const char *s1, const char *s2) {
    char n1_prefix[MAX_LEN], s2_prefix[MAX_LEN], ldap_buf[100];
    int len_n1 = strlen(n1);
    int len_s2 = strlen(s2);
    for (int k = 1; k <= len_n1; ++k) {
        strncpy(n1_prefix, n1, k);
        n1_prefix[k] = '\0';
        int max_m = custom_min(k, len_s2);
        int start_m = (k == 1 ? 1 : 0);
        for (int m = start_m; m <= max_m; ++m) {
            if (m == 0) {
                s2_prefix[0] = '\0';
            } else {
                strncpy(s2_prefix, s2, m);
                s2_prefix[m] = '\0';
            }
            sprintf(ldap_buf, "%s%s%s%s", n1_prefix, n2_first_char, s1, s2_prefix);
            if (!consultar_ldap(ldap_buf)) {
                imprimir_ldap_final(ldap_buf);
                exit(0);
            }
        }
    }
    for (int m = custom_min(len_n1, len_s2) + 1; m <= len_s2; ++m) {
        strncpy(s2_prefix, s2, m);
        s2_prefix[m] = '\0';
        sprintf(ldap_buf, "%s%s%s%s", n1, n2_first_char, s1, s2_prefix);
        if (!consultar_ldap(ldap_buf)) {
            imprimir_ldap_final(ldap_buf);
            exit(0);
        }
    }
}

int main() {
    char linea[150], n1[MAX_LEN], n2_first_char[2], s1[MAX_LEN], s2[MAX_LEN];
    if (fgets(linea, sizeof(linea), stdin) == NULL) return 1;
    linea[strcspn(linea, "\n")] = 0;
    leer_nombre_completo(linea, n1, n2_first_char, s1, s2);
    generar_y_verificar_ldap(n1, n2_first_char, s1, s2);
    return 0;
}
