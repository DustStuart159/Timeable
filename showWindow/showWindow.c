#include"../header/CreatingTimeableLibrary.h"

extern v_observeTimeable(int i_Controller);

int i_showMainMenu(){
    system("@cls||clear");

    printf("1. Creating Timeable\n");
    printf("2. Observing Timeable\n");
    printf("0. Exit\n");

    return (getch() - '0');
}
