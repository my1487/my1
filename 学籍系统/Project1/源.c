#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT_COUNT 1000
#define MAX_CHANGE_COUNT 100
struct Change {
    char date[20]; // �仯����
    char reason[50]; // �仯ԭ��
};

struct Student {
    char id[20]; // ѧ��
    char name[20]; // ����
    char sex[10]; // �Ա�
    int age; // ����
    char birthplace[50]; // ����
    char department[50]; // ϵ��
    char major[50]; // רҵ
    char grade[20]; // �༶
    struct Change changes[20]; // �仯���
    int change_count; // �仯�������
};
struct Student students[100];
int student_count = 0;


void register_student() {
    if (student_count >= MAX_STUDENT_COUNT) {
        printf("ѧ�������������޷�ע��\n");
        return;
    }
    printf("������ѧ����Ϣ��\n");
    printf("ѧ�ţ�");
    scanf("%s", students[student_count].id);
    printf("������");
    scanf("%s", students[student_count].name);
    printf("�Ա�");
    scanf("%s", students[student_count].sex);
    printf("���䣺");
    scanf("%d", &students[student_count].age);
    printf("���᣺");
    scanf("%s", students[student_count].birthplace);
    printf("ϵ��");
    scanf("%s", students[student_count].department);
    printf("רҵ��");
    scanf("%s", students[student_count].major);
    printf("�༶��");
    scanf("%s", students[student_count].grade);
    students[student_count].change_count = 0;
    student_count++;
    printf("ѧ����Ϣע��ɹ�\n");
}

int find_student(char* id) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void update_student() {
    char id[20];
    printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("δ�ҵ���ѧ��\n");
        return;
    }
    printf("������ѧ����Ϣ��\n");
    printf("������");
    scanf("%s", students[index].name);
    printf("�Ա�");
    scanf("%s", students[index].sex);
    printf("���䣺");
    scanf("%d", &students[index].age);
    printf("���᣺");
    scanf("%s", students[index].birthplace);
    printf("ϵ��");
    scanf("%s", students[index].department);
    printf("רҵ��");
    scanf("%s", students[index].major);
    printf("�༶��");
    scanf("%s", students[index].grade);
    printf("ѧ����Ϣ�޸ĳɹ�\n");
}

void delete_student() {
    char id[20];
    printf("������Ҫɾ����ѧ��ѧ�ţ�");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("δ�ҵ���ѧ��\n");
        return;
    }
    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;
    printf("ѧ����Ϣɾ���ɹ�\n");
}

void search_student() {
    char id[20];
    printf("������Ҫ���ҵ�ѧ��ѧ�ţ�");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("δ�ҵ���ѧ��\n");
        return;
    }
    printf("ѧ�ţ�%s\n", students[index].id);
    printf("������%s\n", students[index].name);
    printf("�Ա�%s\n", students[index].sex);
    printf("���䣺%d\n", students[index].age);
    printf("���᣺%s\n", students[index].birthplace);
    printf("ϵ��%s\n", students[index].department);
    printf("רҵ��%s\n", students[index].major);
    printf("�༶��%s\n", students[index].grade);
}

void print_birthplace_table() {
    char major[20];
    printf("������Ҫ���������רҵ��");
    scanf("%s", major);
    printf("ѧ��\t\t����\n");
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].major, major) == 0) {
            printf("%s\t%s\n", students[i].id, students[i].birthplace);
        }
    }
}

void add_change() {
    char id[20];
    printf("������Ҫ���ѧ����ѧ��ѧ�ţ�");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("δ�ҵ���ѧ��\n");
        return;
    }
    if (students[index].change_count >= MAX_CHANGE_COUNT) {
        printf("ѧ����������Ѵ����ޣ��޷��������\n");
        return;
    }
    printf("��������ʱ�䣺");
    scanf("%s", students[index].changes[students[index].change_count].date);
    printf("��������ԭ��");
    scanf("%s", students[index].changes[students[index].change_count].reason);
    students[index].change_count++;
    printf("ѧ������ɹ�\n");
}

void print_changes() {
    char id[20];
    printf("������Ҫ��ѯѧ���仯��ѧ��ѧ�ţ�");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("δ�ҵ���ѧ��\n");
        return;
    }
    printf("��ѧ��ѧ���仯���£�\n");
    printf("ʱ��\t\t\t�仯ԭ��\n");
    for (int i = 0; i < students[index].change_count; i++) {
        printf("%s\t%s\n", students[index].changes[i].date, students[index].changes[i].reason);
    }
}

int main() {
    int choice;
    while (1) {
        printf("��ѡ��Ҫ���еĲ�����\n");
        printf("1. ע��ѧ��ѧ��\n");
        printf("2. �޸�ѧ��ѧ��\n");
        printf("3. ɾ��ѧ��ѧ��\n");
        printf("4. ����ѧ��ѧ��\n");
        printf("5. ���ѧ�������\n");
        printf("6. ��ѯѧ��ѧ���仯\n");
        printf("0. �˳�����\n");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            printf("��лʹ�ñ�����\n");
            return 0;
        case 1:
            register_student();
            break;
        case 2:
            update_student();
            break;
        case 3:
            delete_student();
            break;
        case 4:
            search_student();
            break;
        case 5:
            print_birthplace_table();
            break;
        case 6:
            print_changes();
            break;
        default:
            printf("��Ч��ѡ�������ѡ��\n");
            break;
        }
    }
    return 0;
}


