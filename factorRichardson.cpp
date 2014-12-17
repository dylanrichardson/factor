#include <iostream>
#include <fstream>
#include <windows.h>
#include <math.h>
#include "dric.h"

using namespace std;

const int STR_LEN = 200;
const int ARR_LEN = 30;
void factor(float, float, float, char * * );
void quadratic(float, float, float, char * * );
void equation(void);
void writeHtml(float, float, float, char * * , char * * );
void fillEmptyStr(char * * , int, int);
void writeFraction(int, int, char * );
void gcf3(int * , int * , int * );
void writeLinEq(float, float, char * * , int * );
void writeQuadEq(float, float, float, char * * , int * );
void writeFacEq(int, int, int, char * * , int * );
char FILEPATH[] = "answer.html";

int main() {
    menu main(2, "Quadratic Equation Solver");
    optionList options = {
        "New equation",
        "Exit"
    };

    function functions[] = {
        equation,
        EXIT
    };
    main.setOptions(options);
    main.setFunctions(functions);
    main.open();
    return 0;
}

void equation(void) {
    char * * quadHtml;
    quadHtml = new char * [ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
        quadHtml[i] = new char[STR_LEN];
    char * * factorHtml;
    factorHtml = new char * [ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++)
        factorHtml[i] = new char[STR_LEN];
    fillArr2(quadHtml, ARR_LEN, STR_LEN);
    fillArr2(factorHtml, ARR_LEN, STR_LEN);

    system("cls");
    float a, b, c;
    cout << "ax^2+bx+c=0\n\n";
    cout << "Enter a: ";
    input( & a, 6, FLOAT_);
    cout << "Enter b: ";
    input( & b, 6, FLOAT_);
    cout << "Enter c: ";
    input( & c, 6, FLOAT_);

    quadratic(a, b, c, quadHtml);
    factor(a, b, c, factorHtml);
    writeHtml(a, b, c, quadHtml, factorHtml);

    ShellExecute(NULL, "open", FILEPATH, NULL, NULL, SW_SHOWNORMAL);
    Sleep(1000);
    system("pause");
    remove(FILEPATH);
}

void factor(float A, float B, float C, char * * html) {
    int line = 0;
    if (A == 0) {
        strcat(html[line], "Cannot factor linear equation");
        line++;
    } else if (A != floor(A) || B != floor(B) || C != floor(C)) {
        strcat(html[line], "Non integer coeffecients");
        line++;
    } else {
        char temp[11];
        int a = A, b = B, c = C;
        float n = (-b + sqrt(b * b - 4 * a * c)) / -2;
        float m = (-b - sqrt(b * b - 4 * a * c)) / -2;
        if (n != floor(n) || m != floor(m)) {
            //check fractions
            strcat(html[line], "Not factorable");
            line++;
        } else {
            //write equation and sub
            writeFacEq(a, n, m, html, & line);
            if (n == 0) {
                char temp[11];
                itoa(a, temp, 10);
                strcat(html[line], temp);
                strcat(html[line], "x = 0");
                line++;
                line++;
            } else if (n != m) {
                //split into two equations
                strcat(html[line], "<span style='width:50%;float:left'>");
                if (a != 1) {
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                }
                strcat(html[line], "x");
                if (n > 0)
                    strcat(html[line], "+");
                itoa(n, temp, 10);
                strcat(html[line], temp);
                strcat(html[line], " = 0");
                line++;
                if (a != 1) {
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                }
                strcat(html[line], "x = ");
                itoa(-n, temp, 10);
                strcat(html[line], temp);
                line++;
                if (a != 1) {
                    strcat(html[line], "x = ");
                    itoa(-n, temp, 10);
                    strcat(html[line], temp);
                    strcat(html[line], "/");
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                    line++;
                }
                strcat(html[line], "</span>");
                strcat(html[line], "<span style='width:50%;float:left'>");
                if (a != 1) {
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                }
                strcat(html[line], "x");
                if (m > 0)
                    strcat(html[line], "+");
                itoa(m, temp, 10);
                strcat(html[line], temp);
                strcat(html[line], " = 0");
                line++;
                if (a != 1) {
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                }
                strcat(html[line], "x = ");
                itoa(-m, temp, 10);
                strcat(html[line], temp);
                line++;
                if (a != 1) {
                    strcat(html[line], "x = ");
                    itoa(-m, temp, 10);
                    strcat(html[line], temp);
                    strcat(html[line], "/");
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                    line++;
                }
                line++;
                strcat(html[line], "</span>");
                line++;
            } else {
                //ax+n=0
                //ax=-n
                //x=-n/a
                if (a != 1) {
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                }
                strcat(html[line], "x");
                if (n > 0)
                    strcat(html[line], "+");
                itoa(n, temp, 10);
                strcat(html[line], temp);
                strcat(html[line], " = 0");
                line++;
                if (a != 1) {
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                }
                strcat(html[line], "x = ");
                itoa(-n, temp, 10);
                strcat(html[line], temp);
                line++;
                if (a != 1) {
                    strcat(html[line], "x = ");
                    itoa(-n, temp, 10);
                    strcat(html[line], temp);
                    strcat(html[line], "/");
                    itoa(a, temp, 10);
                    strcat(html[line], temp);
                    line++;
                }
                line++;
            }
            //solution
            strcat(html[line], "Solution");
            line++;
            line++;
            strcat(html[line], "x = ");
            writeFraction(-n, a, html[line]);
            line++;
            if (n != m) {
                strcat(html[line], "x = ");
                writeFraction(-m, a, html[line]);
                line++;
            }
            line++;
        }
    }
}

void quadratic(float A, float B, float C, char * * html) {
    int line = 0;
    //linear
    if (A == 0) {
        writeLinEq(B, C, html, & line);
        strcat(html[line], "Solution");
        line++;
        line++;
        strcat(html[line], "x = ");
        if (C == floor(C) && B == floor(B))
            writeFraction(-C, B, html[line]);
        else {
            char temp[11];
            ftoa(-C / B, temp, 10);
            strcat(html[line], temp);
        }
    }
    //integer
    else if (A == floor(A) && B == floor(B) && C == floor(C)) {
        int a = A, b = B, c = C;
        writeQuadEq(a, b, c, html, & line);
        strcat(html[line], "Solution");
        line++;
        line++;
        //square root
        int discriminant = b * b - 4 * a * c;
        int denominator = 2 * a;
        float discSqrt = sqrt(discriminant);
        //square discriminant
        if (discSqrt == floor(discSqrt)) {
            if (discSqrt == 0) {
                //one answer
                strcat(html[line], "x = ");
                writeFraction(-b, denominator, html[line]);
            } else {
                int n1 = -b + discSqrt;
                int n2 = -b - discSqrt;
                if ((float) n1 / denominator == (float) n2 / denominator) {
                    //one answer
                    strcat(html[line], "x = ");
                    writeFraction(n1, denominator, html[line]);
                } else {
                    //first answer
                    strcat(html[line], "x = ");
                    writeFraction(n1, denominator, html[line]);
                    //second answer
                    line++;
                    strcat(html[line], "x = ");
                    writeFraction(n2, denominator, html[line]);
                }
            }
        }
        //not square discriminant
        else {
            //get prime factors
            bool negDisc = false;
            if (discriminant < 0) {
                discriminant = -discriminant;
                negDisc = true;
            }
            int out = simplifySqrt(discriminant);
            int in = discriminant / out / out;
            if (b == 0) {
                //square root divided by denominator
                simplifyFrac( & out, & denominator);
                char temp[10];
                strcat(html[line], "x = ");
                //plus-minus
                strcat(html[line], "&plusmn;");
                if (abs(out) != 1) {
                    //number outside sqrt
                    itoa(abs(out), temp, 10);
                    strcat(html[line], temp);
                }
                if ( in != 1) {
                    //inside sqrt
                    strcat(html[line], "&radic;<span style=\"text-decoration:overline\">&nbsp;");
                    itoa( in , temp, 10);
                    strcat(html[line], temp);
                    strcat(html[line], "&nbsp;</span>");
                }
                if (negDisc)
                    strcat(html[line], "i");
                if (denominator != 1) {
                    //denominator
                    strcat(html[line], "/");
                    itoa(denominator, temp, 10);
                    strcat(html[line], temp);
                }
                if (abs(out) != 1 && in != 1 && denominator != 1 && !negDisc)
                //everything equals 1
                    strcat(html[line], "1");
            } else {
                //-b and square root divided by denominator
                char temp[10];
                gcf3( & b, & out, & denominator);
                strcat(html[line], "x = ");
                bool parentheses = denominator != 1 && (abs(out) != 1 || in != 1);
                if (parentheses)
                    strcat(html[line], "(");
                //-b
                itoa(-b, temp, 10);
                strcat(html[line], temp);
                //plus-minus
                strcat(html[line], "&plusmn;");
                if (abs(out) != 1) {
                    //number outside sqrt
                    itoa(abs(out), temp, 10);
                    strcat(html[line], temp);
                }
                if (negDisc)
                    strcat(html[line], "i");
                if ( in != 1) {
                    //inside sqrt
                    strcat(html[line], "&radic;<span style=\"text-decoration:overline\">&nbsp;");
                    itoa( in , temp, 10);
                    strcat(html[line], temp);
                    strcat(html[line], "&nbsp;</span>");
                }
                if (parentheses)
                    strcat(html[line], ")");
                if (denominator != 1) {
                    //denominator
                    strcat(html[line], "/");
                    itoa(denominator, temp, 10);
                    strcat(html[line], temp);
                }
                if (abs(out) != 1 && in != 1 && denominator != 1 && !negDisc)
                //everything equals 1
                    strcat(html[line], "1");
            }
        }
    }
    //decimal
    else {
        writeQuadEq(A, B, C, html, & line);
        strcat(html[line], "Solution");
        line++;
        line++;
        float x1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
        float x2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
        char ans1[15] = "x = ";
        char ans2[15] = "x = ";
        char x[11];
        ftoa(x1, x, 10);
        strncat(ans1, x, 10);
        strncpy(html[line], ans1, STR_LEN);
        line++;
        ftoa(x2, x, 10);
        strncat(ans2, x, 10);
        strncpy(html[line], ans2, STR_LEN);
    }
}

void writeHtml(float a, float b, float c, char * * quadHtml, char * * factorHtml) {
    fstream html;
    html.open(FILEPATH, ios::out);
    if (!html) {
        cout << "Could not open file";
        return;
    }
    html << "<!DOCTYPE html>";
    html << "<html>";
    html << "<head><title>Quadratic Equation Solver</title>";
    html << "<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js'></script>";
    html << "<script>$.ajax({url:'http://www.14test14.co.nf/api/quadratic.php',type:'GET',data:{input:'";
    html << a << "x^2+" << b << "x+" << c << "=0'}}).done(function(ret){$('#wa').append('<h3>WolframAlpha</h3><p>'+ret+'<p>')})</script></head>";
    html << "<body>";
    html << "<div style='text-align:center'><h3>Input</h3><p>";
    if (a != 0) {
        if (a == -1)
            html << "-";
        else if (a != 1)
            html << a;
        html << "x<sup>2</sup> ";
    }
    if (b != 0) {
        if (a != 0) {
            if (b > 0)
                html << "+";
            else
                html << "-";
            html << " ";
            if (abs(b) != 1)
                html << abs(b);
            html << "x ";
        } else {
            if (abs(b) != 1)
                html << b;
            html << "x ";
        }
    }
    if (c != 0) {
        if (a != 0 || b != 0) {
            if (c > 0)
                html << "+";
            else
                html << "-";
            html << " ";
            html << abs(c) << " ";
        } else
            html << c << " ";
    }
    html << "= 0</p></div>";
    html << "<div id='quad' style='width:50%;float:left;overflow:hidden'>";
    html << "<h3>Quadratic Formula Method</h3>";
    html << "<p>";
    for (int i = 0; i < ARR_LEN; i++)
        html << quadHtml[i] << "<br>";
    html << "</p>";
    html << "</div>";
    html << "<div id='factor' style='width:50%;float:left;overflow:hidden'>";
    html << "<h3>Factoring Method</h3>";
    html << "<p>";
    for (int i = 0; i < ARR_LEN; i++)
        html << factorHtml[i] << "<br>";
    html << "</p>";
    html << "</div>";
    html << "<div id='wa' style='clear:both'></div>";
    html << "</body>";
    html << "</html>";
    html.close();
}

void writeFraction(int n, int d, char * dest) {
    if (d == 0) {
        strcat(dest, "undefined");
        return;
    } else if (n == 0) {
        strcat(dest, "0");
        return;
    }
    simplifyFrac( & n, & d);
    char temp[10];
    //numerator
    itoa(n, temp, 10);
    strcat(dest, temp);
    if (d != 1) {
        strcat(dest, "/");
        //denominator
        itoa(d, temp, 10);
        strcat(dest, temp);
    }
}

void writeLinEq(float b, float c, char * * destp, int * line) {
    strcat(destp[ * line], "Equation");
    ( * line) ++;
    ( * line) ++;
    char temp[11];
    strcat(destp[ * line], "x = -c/b");
    ( * line) ++;
    ( * line) ++;
    strcat(destp[ * line], "Substitution");
    ( * line) ++;
    ( * line) ++;
    strcat(destp[ * line], "x = -(");
    ftoa(c, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")/");
    ftoa(b, temp, 10);
    strcat(destp[ * line], temp);
    ( * line) ++;
    ( * line) ++;
}

void writeQuadEq(float a, float b, float c, char * * destp, int * line) {
    strcat(destp[ * line], "Equation");
    ( * line) ++;
    ( * line) ++;
    char temp[11];
    strcat(destp[ * line], "x = (-b&plusmn;&radic;<span style=\"text-decoration:overline\">&nbsp;b</span><sup>2</sup><span style=\"text-decoration:overline\">-4ac&nbsp;</span>)/(2a)");
    ( * line) ++;
    ( * line) ++;
    strcat(destp[ * line], "Substitution");
    ( * line) ++;
    ( * line) ++;
    strcat(destp[ * line], "x = [-(");
    ftoa(b, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")&plusmn;&radic;<span style=\"text-decoration:overline\">&nbsp;(");
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")</span><sup>2</sup><span style=\"text-decoration:overline\">-4(");
    ftoa(a, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")(");
    ftoa(c, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")&nbsp;</span>]/[2(");
    ftoa(a, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")]");
    ( * line) ++;
    ( * line) ++;
}

void writeFacEq(int a, int n, int m, char * * destp, int * line) {
    strcat(destp[ * line], "Equation");
    ( * line) ++;
    ( * line) ++;
    char temp[11];
    strcat(destp[ * line], "a*c = n*m");
    ( * line) ++;
    strcat(destp[ * line], "n+m = b");
    ( * line) ++;
    strcat(destp[ * line], "(ax+n)(ax+m) = 0");
    ( * line) ++;
    ( * line) ++;
    strcat(destp[ * line], "Substitution");
    ( * line) ++;
    ( * line) ++;
    strcat(destp[ * line], "[(");
    itoa(a, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")x+(");
    itoa(n, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")][(");
    itoa(a, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")x+(");
    itoa(m, temp, 10);
    strcat(destp[ * line], temp);
    strcat(destp[ * line], ")]");
    strcat(destp[ * line], " = 0");
    ( * line) ++;
    ( * line) ++;
}
