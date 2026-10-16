#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person* create_person(const char *name, int age);

int main(void) {
    // Basic memory allocation test
    Person *test = create_person("Test Person", 20);
    printf("Created: %s, Age: %d\n", test->name, test->age);
    free(test);
    return 0;
}

Person* create_person(const char *name, int age) {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
    p->age = age;
    p->father = NULL;
    p->mother = NULL;
    return p;
}
