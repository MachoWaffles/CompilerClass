/* SYMBOL TABLE IMPLEMENTATION
 * Manages variable declarations and lookups
 * Essential for semantic analysis (checking if variables are declared)
 * Provides memory layout information for code generation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Global symbol table instance */
SymbolTable symtab;

/* Initialize an empty symbol table */
void initSymTab() {
    symtab.count = 0;       /* No variables yet */
    symtab.nextOffset = 0;  /* Start at stack offset 0 */
    printf("SYMBOL TABLE: Initialized\n");
    printSymTab();
}

/* Add a new variable to the symbol table */
int addVar(char* name, char* type) {
    /* Check for duplicate declaration */
    if (isVarDeclared(name)) {
        /* Error: duplicate — goes to stderr since this is a real error condition */
        fprintf(stderr, "SYMBOL TABLE ERROR: Cannot add '%s' — variable already declared\n", name);
        return -1;
    }

    /* Add new symbol entry */
    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].type = strdup(type);
    symtab.vars[symtab.count].offset = symtab.nextOffset;

    /* Advance offset by 4 bytes (size of int in MIPS) */
    symtab.nextOffset += 4;
    symtab.count++;

    printf("SYMBOL TABLE: Added variable '%s' at offset %d\n", name, symtab.vars[symtab.count - 1].offset);
    printSymTab();

    /* Return the offset for this variable */
    return symtab.vars[symtab.count - 1].offset;
}

/* Look up a variable's stack offset
 * NOTE: This function is a pure lookup — it prints nothing.
 * It is called both by callers that need the offset AND by isVarDeclared()
 * for existence checks. Printing here would produce false "not found" noise
 * during normal isVarDeclared() calls, so error messages are left to the callers. */
int getVarOffset(char* name) {
    /* Linear search through symbol table */
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0) {
            return symtab.vars[i].offset;  /* Found it */
        }
    }
    return -1;  /* Variable not found — caller decides how to handle this */
}

/* Check if a variable has been declared */
int isVarDeclared(char* name) {
    return getVarOffset(name) != -1;  /* True if found, false otherwise */
}

/* Print current symbol table contents for debugging/tracing */
void printSymTab() {
    printf("\n=== SYMBOL TABLE STATE ===\n");
    printf("Count: %d, Next Offset: %d\n", symtab.count, symtab.nextOffset);
    if (symtab.count == 0) {
        printf("(empty)\n");
    } else {
        printf("Variables:\n");
        for (int i = 0; i < symtab.count; i++) {
            printf("  [%d] %s %s -> offset %d\n", i, symtab.vars[i].type, symtab.vars[i].name, symtab.vars[i].offset);
        }
    }
    printf("==========================\n\n");
}

/* --- Read-only accessors used by codegen for error/warning checks ---
 * These expose existing symbol table data without modifying any state. */

/* Returns the total number of declared variables */
int getVarCount() {
    return symtab.count;
}

/* Returns the name of the variable at the given index, or NULL if out of range */
char* getVarNameAt(int index) {
    if (index < 0 || index >= symtab.count) return NULL;
    return symtab.vars[index].name;
}

/* Returns the total bytes of stack space used by all declared variables */
int getStackUsage() {
    return symtab.nextOffset;
}