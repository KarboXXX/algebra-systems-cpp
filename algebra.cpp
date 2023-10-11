#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <string.h>
#include <array>
#include <regex>
#include <gtk-3.0/gtk/gtk.h>
#include <bits/types.h>

float det(float matrix[][2]) {
    return (matrix[0][0] * matrix[1][1]) - ((matrix[0][1] * matrix[1][0]));
}

/*
    ax + by = c
    dx + ey = f
*/
std::array<float, 2> solve_cramer(float a, float b, float c, float d, float e, float f) {
    float coeficientsM[][2] = { {a, b}, 
                                {d, e} };
    float ansM[] = {c, f};

    float xM[][2] = { {ansM[0], coeficientsM[0][1]}, 
                      {ansM[1], coeficientsM[1][1]} };

    float yM[][2] = { {coeficientsM[0][0], ansM[0]},
                      {coeficientsM[1][0], ansM[1]} };

    float detCoeM = det(coeficientsM);

    float x,y;
    float detX = det(xM);
    float detY = det(yM);

    x = detX/detCoeM;
    y = detY/detCoeM;

    std::array<float, 2> S = {x, y};
    // S[0] = x;
    // S[1] = y;

    return S;
}

/*
    ax + by = c
    dx + ey = f
*/
std::array<float, 2> solve_substitution(float a, float b, float c, float d, float e, float f) {
    float x, y;

    // y = (f * a - d * c) / (a * e - d * b);
    // x = (c - b * y) / a;

    float dn = ((e*a) - (b*d));
    x = ((e*c) - (b*f)) / (dn);
    y = ((a*f) - (c*d)) / (dn);

    std::array<float, 2> S = {x, y};
    // S[0] = x;
    // S[1] = y;

    return S;

    /*
        EXPLICAÇÃO:

        Vamos usar um exemplo aleatorio, para demonstrar a resolução.

        7x+5y = 12
        7x = 12-5y

        Isole o x na primeira linha
        x = (12-5y)/7

        Substitua x na segunda linha por (12-5y)/7 
        4x + 9y = 13
        4(12-5y)/7 +9y = 13 multiplicando os dois menbros da igualdade por 7
        4*12-4*5y +7*9y = 7*13
        -4*5y +7*9y = 7*13 - 4*12
        y(7*9-4*5) = (7*13-4*12)

        y = (7*13-4*12)/(7*9-4*5)
        y = 43/43 
        y = 1

        Substitua y em x = (12-5y)/7 
        x = (12-5*1)/7
        x = 7/7
        x = 1

        Etapa 2: reformular o problema utilizando dados genéricos (parâmetros, letras ou palavras);

        Encontrar o valor de x e y do sistema a seguir:

        ax+by=c
        dx+ey=f

        Etapa 3: resolver o problema formulado no item 3 registrando todos os passos da resolução; 
        - Isolar x na primeira linha.
        ax+by = c
        ax = c-by
        x = (c-by)/a      (1)

        Substituir x na segunda linha por (c-by)/a  para isolar y
        dx+ey=f
        d(c-by)/a +ey = f          (multiplicando os dois menbros da igualdade por a)
        d*c-d*by +a*ey = a*f    
        -d*by +a*ey = a*f - d*c 
        y(a*e-d*b) = (a*f-d*c)   
            
        y = (a*f-d*c))/(a*e-d*b) <- Fórmula do y em função das variáveis de entrada


        Após encontrando o valor de y o valor de y será substituido em (1)
        x = (c-by)/a <-Fórmula de x em funçÃo de y
    
    */
}

void erase_char(std::string *original_string, std::string character) {
    std::string::size_type i = original_string->find(character);

    if (i != std::string::npos)
        original_string->erase(i, i);
}

std::array<std::string, 3> coeficient_matching(std::string equ) {
    std::array<std::string, 3> S = {"", "", ""};

    // std::regex coefficient_regex("([+-]?\\d*)[a-z].*?([+-]?\\d*)[a-z].*?=\\s*([+-]?\\d+)");
    std::regex coefficient_regex("([+-]?\\s*\\d*)[a-z].*?([+-]?\\s*\\d*)[a-z].*?=\\s*([+-]?\\s*\\d+)");

    std::smatch matches;
    if (std::regex_search(equ, matches, coefficient_regex)) {
        if (matches.size() == 4) {
            std::string x_coefficient = matches[1].str();
            std::string y_coefficient = matches[2].str();
            std::string ans_str = matches[3].str();

            std::string spaces = " ";

            erase_char(&x_coefficient, spaces);
            erase_char(&y_coefficient, spaces);
            erase_char(&ans_str, spaces);

            std::cout << x_coefficient << '\n' << y_coefficient << '\n' << ans_str << std::endl;

            S = { x_coefficient, y_coefficient, ans_str };

            // Converter os coeficientes para inteiros
            // x = (x_coefficient.empty() ? 1 : std::stoi(x_coefficient));
            // y = (y_coefficient.empty() ? 1 : std::stoi(y_coefficient));
            // ans = (ans_str.empty() ? 1 : std::stoi(ans_str));
        }
    }

    return S;
}

std::array<int, 4> read_variables_from_equation(std::string equ) {
    int x,y,ans;

    int error = 0;
    int i = 0;
    std::array<int, 3> coefs_int;

    if (equ == "") {
        x = 0;
        y = 0;
        ans = 0;
        error = 2;

        std::array<int, 4> S = {x, y, ans, error};
        return S;
    }

    std::array<std::string, 3> coefs = coeficient_matching(equ);
    for (const auto& s : coefs) {
        if (s.length() >= 10) {
            error = 1;
            break;
        }

        if (s.empty() || s == "+" || s == "-") {
            coefs_int[i] = 1;
        } else {
            coefs_int[i] = std::stoi(s);
        }

        // coefs_int[i] = (s.empty() ? 1 : std::stoi(s));
        i++;
    }

    x = coefs_int[0];
    y = coefs_int[1];
    ans = coefs_int[2];

    if (error != 0) { x = 0; y = 0; ans = 0; }

    std::array<int, 4> S = {x, y, ans, error};
    // S[0] = x;
    // S[1] = y;
    // S[2] = ans;

    return S;
}




// GUI

void on_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

GtkWidget *result_button;
GtkWidget *label1;
GtkWidget *entry1;
GtkWidget *entry2;

void result_button_clickevent(GtkWidget *button, gpointer data);


int main(int argc, char *argv[]) {
    std::array<float, 2> s_s;
    std::array<float, 2> s_c;

    /*
        x + 2y = 18
        3x + y = 90
    */

    // s_s = solve_substitution(1, 2, 18, 3, 1, 18);
    // s_c = solve_cramer(1, 2, 18, 3, 1, 90);

    // printf("x = %f\ny = %f\n\n", s_s[0], s_s[1]);
    // printf("x = %f\ny = %f\n\n", s_c[0], s_c[1]);

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Criar a janela principal
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Algebra Linear (Duas Icógnitas) [KARBOX]");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 400, 150);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Layout vertical
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Adicionar widgets à caixa vertical
    // Entradas de texto
    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();

    // Rótulos
    label1 = gtk_label_new("...");

    // Botão
    result_button = gtk_button_new_with_label("Results");
    gtk_widget_set_name(result_button, "results");
    g_signal_connect(entry2, "activate", G_CALLBACK(result_button_clickevent), NULL);
    g_signal_connect(result_button, "clicked", G_CALLBACK(result_button_clickevent), NULL);

    // Adicionar widgets à caixa vertical
    gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), result_button, FALSE, FALSE, 0);

    // Exibir todos os widgets
    gtk_widget_show_all(window);

    // Iniciar loop principal GTK
    gtk_main();
    
    return 0;
}

void result_button_clickevent(GtkWidget *button, gpointer data) {
    if (button != result_button) return;

    const gchar *input1 = gtk_entry_get_text(GTK_ENTRY(entry1));
    const gchar *input2 = gtk_entry_get_text(GTK_ENTRY(entry2));

    std::array<int, 4> eq1 = read_variables_from_equation((std::string)input1);
    std::array<int, 4> eq2 = read_variables_from_equation((std::string)input2);

    if (eq1[3] == 2 || eq2[3] == 2) {
        return gtk_label_set_text(GTK_LABEL(label1), "Uma das equações é inválida");
    }
    if (eq1[3] == 1 || eq2[3] == 1) {
        return gtk_label_set_text(GTK_LABEL(label1), "Uma das equações ultrapassou o limite de tamanho permitido para um coeficiente");
    }

    int a,b,c,d,e,f;
    std::string message;
    a = eq1[0]; b = eq1[1]; c = eq1[2];
    d = eq2[0]; e = eq2[1]; f = eq2[2];

    const std::array<float, 2> sol = solve_cramer(a, b, c, d, e, f);

    const std::string solution = (std::to_string(sol[0]) + ", " + std::to_string(sol[1]));
    message = "S = {" + solution + "}";

    if (isinf(sol[0]) || isinf(sol[1])) { message = "S = SPI"; }
    if (isnan(sol[0]) || isnan(sol[1])) { message = "S = SI"; }
    
    
    gtk_label_set_text(GTK_LABEL(label1), message.c_str());



    // g_print("entry1: %s\n", text1);

}

// g++ algebra.cpp -o al `pkg-config --cflags --libs gtk+-3.0`
