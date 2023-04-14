#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int numStudents;

    printf("Enter how many students: ");
    scanf("%d", &numStudents);

    char** students = students = malloc(sizeof(char*) * numStudents);

    int i = 0;
    for(; i < numStudents; i++) {
        char* buf = malloc(sizeof(char) * 100);
        printf("Enter student %d: ", i + 1);
        scanf(" %[^\n]", buf);
        buf = realloc(buf, strlen(buf) + 1);
        students[i] = buf;
    }

    printf("\nYou Entered:\n");
    for (i = 0; i < numStudents; i++) {
        printf("Student %d: %s\n", i + 1, students[i]);
    }

    for(i = 0; i < numStudents; i++) {
        free(students[i]);
    }
    free(students);
}
