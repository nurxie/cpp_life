#include <iostream>
using namespace std;

const int x_define = 4; //10
const int y_define = 4; //10

const int b1 = 3;
const int s1 = 2;
const int s2 = 3;

const char FILL = '#';
const char UNFILL = '*';

int neighbors_counter(char mass[][x_define], int y_outside, int x_outside) {
    int number_of_neighbors = 0;
    int y = y_outside;
    int x = x_outside;

    if ((y - 1) >= 0 && mass[y - 1][x] == FILL) number_of_neighbors++;

    if ((y - 1) >= 0 && (x + 1) <= x_define && mass[y - 1][x + 1] == FILL) number_of_neighbors++;
    if ((x + 1) <= x_define && mass[y][x + 1] == FILL) number_of_neighbors++;

    if ((y + 1) <= y_define && (x + 1) <= x_define && mass[y + 1][x + 1] == FILL) number_of_neighbors++;
    if ((y + 1) <= y_define && mass[y + 1][x] == FILL) number_of_neighbors++;

    if ((y + 1) <= y_define && (x - 1) >= 0 && mass[y + 1][x - 1] == FILL) number_of_neighbors++;
    if ((x - 1) >= 0 && mass[y][x - 1] == FILL) number_of_neighbors++;

    if ((y - 1) >= 0 && (x - 1) >= 0 && mass[y - 1][x - 1] == FILL) number_of_neighbors++;

    return number_of_neighbors;
}

bool cell_death(char mass_outcome[][x_define], int y_outside, int x_outside) {
    mass_outcome[y_outside][x_outside] = UNFILL;
    return 1;
}

bool cell_remains(char mass_outcome[][x_define], int y_outside, int x_outside) {
    mass_outcome[y_outside][x_outside] = FILL;
    return 1;
}

bool cell_survival(char mass_income[][x_define], char mass_outcome[][x_define], int y_outside, int x_outside){
    if (neighbors_counter(mass_income, y_outside, x_outside) == s1 || neighbors_counter(mass_income, y_outside, x_outside) == s2)
    {
        cell_remains(mass_outcome, y_outside, x_outside);
        //noting to do, may be + to score?
    }
    if (neighbors_counter(mass_income, y_outside, x_outside) > s2)
    {
        cell_death(mass_outcome, y_outside, x_outside);
    }
    if (neighbors_counter(mass_income, y_outside, x_outside) < s1)
    {
        cell_death(mass_outcome, y_outside, x_outside);
    }
    return 1;
}

bool cell_birth(char mass_income[][x_define], char mass_outcome[][x_define], int y_outside, int x_outside) {
    if (neighbors_counter(mass_income, y_outside, x_outside) >= b1) {
        mass_outcome[y_outside][x_outside] = FILL;
    }
    return 1;
}

bool life_period(char mass_income[][x_define], char mass_outcome[][x_define]) {
    for (int y = 0; y < y_define; y++) {
        for (int x = 0; x < x_define; x++) {
            if (mass_income[y][x] == FILL) {
                cell_survival(mass_income, mass_outcome, y, x);
            } else {
                cell_birth(mass_income, mass_outcome, y, x);
            }
        }
    }
    return 1;
}

bool cout_mass(char mass_outcome[][x_define]) {
    for (int y = 0; y < y_define; y++) {
        for (int x = 0; x < x_define; x++) {
            cout << mass_outcome[y][x];
        }
        cout << endl;
    }
    return 1;
}

bool fill_mass_with_unfill(char mass[][x_define]) {
    for (int y = 0; y < y_define; y++) {
        for (int x = 0; x < x_define; x++) {
            mass[y][x] = UNFILL;
        }
    }
    return 1;
}

bool appropriation_mass(char mass_income[][x_define], char mass_outcome[][x_define]) {
    for (int y = 0; y < y_define; y++) {
        for (int x = 0; x < x_define; x++) {
            mass_income[y][x] = mass_outcome[y][x];
        }
    }
    return 1;
}

int main()
{
    char mass_income[y_define][x_define] = { UNFILL, FILL, UNFILL, UNFILL, 
                                             FILL, UNFILL, FILL, UNFILL, 
                                             UNFILL, FILL, UNFILL, UNFILL, 
                                             UNFILL, UNFILL, UNFILL, UNFILL, };
    char mass_outcome[y_define][x_define];
    fill_mass_with_unfill(mass_outcome);

        cout_mass(mass_income);
        cout << "========================" << endl;
    for (int i = 0; i < 50; i++) {
        //cin >> i;
        life_period(mass_income, mass_outcome);
        cout_mass(mass_outcome);
        appropriation_mass(mass_income, mass_outcome);
        fill_mass_with_unfill(mass_outcome);
        cout << "========================" << endl;
    }

  
    return 1;
}
