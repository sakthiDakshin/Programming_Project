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

void link_parents(Person *child, Person *father, Person *mother);
void print_family_relationships(const Person *me);
void print_tree_visual(const Person *root, int level);

int main(void) {  
      Person *people[7];
    int person_count = 0;

    char name_buf[50];
    int age_buf;

    printf("=== ENTER FAMILY DETAILS ===\n\n");

    read_person_info("Paternal Grandfather", name_buf, &age_buf);
    Person *pat_gf = create_person(name_buf, age_buf); // Declare and create first
    people[person_count++] = pat_gf;

    read_person_info("Paternal Grandmother", name_buf, &age_buf);
    Person *pat_gm = create_person(name_buf, age_buf);
    people[person_count++] = pat_gm;

    read_person_info("Maternal Grandfather", name_buf, &age_buf);
    Person *mat_gf= create_person(name_buf, age_buf);
    people[person_count++] = mat_gf;

    read_person_info("Maternal Grandmother", name_buf, &age_buf);
    Person *mat_gm = create_person(name_buf, age_buf);
    people[person_count++] = mat_gm;

    read_person_info("Father", name_buf, &age_buf);
    Person *father = create_person(name_buf, age_buf);
    people[person_count++] = father;

    read_person_info("Mother", name_buf, &age_buf);
    Person *mother = create_person(name_buf, age_buf);
    people[person_count++] = mother;

    read_person_info("Yourself", name_buf, &age_buf);
    Person *me = create_person(name_buf, age_buf);
    people[person_count++] = me;


    link_parents(father, pat_gf, pat_gm);
    link_parents(mother, mat_gf, mat_gm);
    link_parents(me, father, mother);

    print_family_relationships(me);

    printf("\n=== VISUAL FAMILY TREE ===\n");
    print_tree_visual(me, 0);

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

void link_parents(Person *child, Person *father, Person *mother) {
    if (child != NULL) {
        child->father = father;
        child->mother = mother;
    }
}

void print_family_relationships(const Person *me) {
    if (me == NULL) return;

    printf("\n=== FAMILY TREE RELATIONSHIPS ===\n");

    printf("1. YOURSELF:\n");
    printf(" - Name: %s | Age: %d\n", me->name, me->age);

    printf("2. PARENTS:\n");
    if (me->father) {
        printf(" - Father: %s | Age: %d\n", me->father->name, me->father->age);
    }
    if (me->mother) {
        printf(" - Mother: %s | Age: %d\n", me->mother->name, me->mother->age);
    }

    printf("3. PATERNAL GRANDPARENTS (via Father's Pointers):\n");
    if (me->father && me->father->father) {
        printf(" - Grandfather: %s | Age: %d\n", me->father->father->name, me->father->father->age);
    }
    if (me->father && me->father->mother) {
        printf(" - Grandmother: %s | Age: %d\n", me->father->mother->name, me->father->mother->age);
    }

    printf("4. MATERNAL GRANDPARENTS (via Mother's Pointers):\n");
    if (me->mother && me->mother->father) {
        printf(" - Grandfather: %s | Age: %d\n", me->mother->father->name, me->mother->father->age);
    }
    if (me->mother && me->mother->mother) {
        printf(" - Grandmother: %s | Age: %d\n", me->mother->mother->name, me->mother->mother->age);
    }
}

void print_tree_visual(const Person *root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) printf(" ");

    if (level == 0) {
        printf("%s (Age: %d)\n", root->name, root->age);
    }

    if (root->father != NULL) {
        for (int i = 0; i < level + 1; i++) printf(" ");
        printf("Father: %s (Age: %d)\n", root->father->name, root->father->age);
        if (root->father->father != NULL) {
            for (int i = 0; i < level + 2; i++) printf(" ");
            printf("Grandfather: %s (Age: %d)\n", root->father->father->name, root->father->father->age);
        }
        if (root->father->mother != NULL) {
            for (int i = 0; i < level + 2; i++) printf(" ");
            printf("Grandmother: %s (Age: %d)\n", root->father->mother->name, root->father->mother->age);
        }
    }

    if (root->mother != NULL) {
        for (int i = 0; i < level + 1; i++) printf(" ");
        printf("Mother: %s (Age: %d)\n", root->mother->name, root->mother->age);
        if (root->mother->father != NULL) {
            for (int i = 0; i < level + 2; i++) printf(" ");
            printf("Grandfather: %s (Age: %d)\n", root->mother->father->name, root->mother->father->age);
        }
        if (root->mother->mother != NULL) {
            for (int i = 0; i < level + 2; i++) printf(" ");
            printf("Grandmother: %s (Age: %d)\n", root->mother->mother->name, root->mother->mother->age);
        }
    }
}