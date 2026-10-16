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
void read_person_info(const char *role, char *name_out, int *age_out);

int main(void) {  
      Person *people[7];
    int person_count = 0;

    char name_buf[50];
    int age_buf;

    printf("=== ENTER FAMILY DETAILS ===\n\n");

    read_person_info("Paternal Grandfather", name_buf, &age_buf);
    people[person_count++] = create_person(name_buf, age_buf);

    read_person_info("Paternal Grandmother", name_buf, &age_buf);
    people[person_count++] = create_person(name_buf, age_buf);

    read_person_info("Maternal Grandfather", name_buf, &age_buf);
    people[person_count++] = create_person(name_buf, age_buf);

    read_person_info("Maternal Grandmother", name_buf, &age_buf);
    people[person_count++] = create_person(name_buf, age_buf);

    read_person_info("Father", name_buf, &age_buf);
    people[person_count++] = create_person(name_buf, age_buf);

    read_person_info("Mother", name_buf, &age_buf);
    people[person_count++] = create_person(name_buf, age_buf);

    read_person_info("Yourself", name_buf, &age_buf);
    people[person_count++] = create_person(name_buf, age_buf);
    for (int i = 0; i < person_count; i++) {
        free(people[i]);
    }

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

void read_person_info(const char *role, char *name_out, int *age_out) {
    printf("Enter name for %s: ", role);
    if (fgets(name_out, 50, stdin) != NULL) {
        size_t len = strlen(name_out);
        if (len > 0 && name_out[len - 1] == '\n') {
            name_out[len - 1] = '\0';
        }
    }

    printf("Enter age for %s: ", role);
    while (scanf("%d", age_out) != 1) {
        printf("Invalid input. Please enter an integer: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    printf("\n");
}
