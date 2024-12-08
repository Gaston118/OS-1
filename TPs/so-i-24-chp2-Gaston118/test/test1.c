#include "unity.h"
#include "commands.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>
#include <dirent.h>

#include "../src/commands.c"
#include "../include/commands.h"
#include "../src/monitor.c"

// Mock de la función exit() para evitar que termine el programa en los tests.
static jmp_buf env;

void test_open_help(void) {
    open_help();  
}

void test_quit(void) {
    if (setjmp(env) == 0) {
        quit();  // Esto debería llevar a llamar a exit, que es interceptado por setjmp
    }
}

void test_dir(void) {
    dir();
}



void setUp(void) {
    // Función vacía
}

void tearDown(void) {
    // Función vacía 
}


int main(void) {
    UNITY_BEGIN();
    
    // Ejecutar todas las pruebas
    RUN_TEST(test_open_help);
    
    RUN_TEST(test_dir);

    RUN_TEST(test_quit);

    return UNITY_END();
}
