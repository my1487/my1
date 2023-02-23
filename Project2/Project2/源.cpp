#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 100     // ����¼��Ŀγ���
#define MAX_NAME_LEN 20     // �γ�������󳤶�
#define COURSE_FILE "courses.dat"  // �γ���Ϣ�����ļ���
#define STUDENT_FILE "students.dat"  // ѧ����Ϣ�����ļ���

// ����γ̵Ľṹ��
typedef struct course {
    int id;                 // �γ̱��
    char name[MAX_NAME_LEN];    // �γ�����
    char type[10];          // �γ����ʣ������Ρ����޿Ρ�ѡ�޿εȣ�
    int total_hours;        // ��ѧʱ
    int teach_hours;        // �ڿ�ѧʱ
    int exp_hours;          // ʵ��/�ϻ�ѧʱ
    float credit;           // ѧ��
    int semester;           // ����ѧ��
} Course;

// ����ѧ���Ľṹ��
typedef struct student {
    int id;                 // ѧ��
    char name[MAX_NAME_LEN];    // ����
    int course_ids[MAX_COURSES]; // ��ѡ�γ̵ı������
    int num_courses;        // ��ѡ�γ���
} Student;

// ����γ���Ϣ�����ȫ�ֱ���
Course courses[MAX_COURSES];
int num_courses = 0;

// ���ļ��ж�ȡ�γ���Ϣ
void read_courses() {
    FILE* file = fopen(COURSE_FILE, "rb");
    if (file != NULL) {
        fread(&num_courses, sizeof(int), 1, file);
        fread(courses, sizeof(Course), num_courses, file);
        fclose(file);
    }
}

// ���γ���Ϣ���浽�ļ���
void save_courses() {
    FILE* file = fopen(COURSE_FILE, "wb");
    if (file != NULL) {
        fwrite(&num_courses, sizeof(int), 1, file);
        fwrite(courses, sizeof(Course), num_courses, file);
        fclose(file);
    }
}

// ���һ���µĿγ�
void add_course() {
    Course course;
    printf("������γ̱�ţ�");
    scanf("%d", &course.id);
    printf("������γ����ƣ�");
    scanf("%s", course.name);
    printf("������γ����ʣ�");
    scanf("%s", course.type);
    printf("��������ѧʱ��");
    scanf("%d", &course.total_hours);
    printf("�������ڿ�ѧʱ��");
    scanf("%d", &course.teach_hours);
    printf("������ʵ��/�ϻ�ѧʱ��");
    scanf("%d", &course.exp_hours);
    printf("������ѧ�֣�");
    scanf("%f", &course.credit);
    printf("�����뿪��ѧ�ڣ�");
    scanf("%d", &course.semester);
    courses[num_courses++] = course;
    save_courses();
    printf("�γ���ӳɹ���\n");
}

// ������пγ���Ϣ
// ������пγ���Ϣ
void view_courses() {
    printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��/�ϻ�ѧʱ\tѧ��\t����ѧ��\n");
    for (int i = 0; i < num_courses; i++) {
        Course course = courses[i];
        printf("%d\t%s\t%s\t%d\t%d\t%d\t%.1f\t%d\n", course.id, course.name, course.type, course.total_hours,
            course.teach_hours, course.exp_hours, course.credit, course.semester);
    }
}

// ��ѧ�ֲ�ѯ�γ�
void search_courses_by_credit() {
    float credit;
    printf("������ѧ�֣�");
    scanf("%f", &credit);
    printf("��ѯ������£�\n");
    for (int i = 0; i < num_courses; i++) {
        Course course = courses[i];
        if (course.credit == credit) {
            printf("%d\t%s\t%s\t%d\t%d\t%d\t%.1f\t%d\n", course.id, course.name, course.type, course.total_hours,
                course.teach_hours, course.exp_hours, course.credit, course.semester);
        }
    }
}

// ���γ����ʲ�ѯ�γ�
void search_by_type() {
    char search_type[20];
    printf("������Ҫ��ѯ�Ŀγ����ʣ������Ρ����޿Ρ�ѡ�޿Σ���");
    scanf("%s", search_type);

    printf("��ѯ������£�\n");
    printf("�γ̱��\t�γ�����\t�γ�����\t��ѧʱ\t�ڿ�ѧʱ\tʵ��/�ϻ�ѧʱ\tѧ��\t����ѧ��\n");
    printf("------------------------------------------------------------------------------------\n");

    int found = 0; // �Ƿ��ҵ����������Ŀγ�
    for (int i = 0; i < num_courses; i++) {
        Course course = courses[i];
        if (strcmp(course.type, search_type) == 0) {
            printf("%d\t%s\t%s\t%d\t%d\t%d\t%.1f\t%d\n", course.id, course.name, course.type, course.total_hours, course.teach_hours, course.exp_hours, course.credit, course.semester);
            found = 1;
        }
    }

    if (!found) {
        printf("û���ҵ����������Ŀγ̣�\n");
    }
}


// ѧ��ѡ�޿γ�
void choose_courses() {
    int student_id;
    printf("������ѧ��ѧ�ţ�");
    scanf("%d", &student_id);
    Student student;
    student.id = student_id;
    printf("������ѧ��������");
    scanf("%s", student.name);
    student.num_courses = 0;
    while (1) {
        int course_id;
        printf("������Ҫѡ�޵Ŀγ̱�ţ�����0��������");
        scanf("%d", &course_id);
        if (course_id == 0) {
            break;
        }
        int found = 0;
        for (int i = 0; i < num_courses; i++) {
            if (courses[i].id == course_id) {
                found = 1;
                student.course_ids[student.num_courses++] = course_id;
                break;
            }
        }
        if (!found) {
            printf("�γ̱��%d�����ڣ����������룡\n", course_id);
        }
    }
    FILE* file = fopen(STUDENT_FILE, "ab");
    if (file != NULL) {
        fwrite(&student, sizeof(Student), 1, file);
        fclose(file);
        printf("ѡ�γɹ���\n");
    }
    else {
        printf("ѡ��ʧ�ܣ������ԣ�\n");
    }
}

// ���˵�
void main_menu() {
    printf("\n==== ѡ�޿γ�ϵͳ ====\n");
    printf("1. ������пγ���Ϣ\n");
    printf("2. ��ӿγ���Ϣ\n");
    printf("3. ��ѧ�ֲ�ѯ�γ�\n");
    printf("4. ���γ����ʲ�ѯ�γ�\n");
    printf("5. ѧ��ѡ��\n");
    printf("0. �˳�ϵͳ\n");
    printf("=======================\n");
    printf("��ѡ�������ţ�");
}

int main() {
    int choice;
    do {
        main_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("ллʹ�ã��ټ���\n");
            break;
        case 1:
            view_courses();
            break;
        case 2:
            add_course();
            break;
        case 3:
            search_courses_by_credit();
            break;
        case 4:
            search_by_type();
            break;
        case 5:
            choose_courses();
            break;
        default:
            printf("��Ч�Ĳ�����ţ����������룡\n");
            break;
        }
    } while (choice != 0);

    return 0;
}

