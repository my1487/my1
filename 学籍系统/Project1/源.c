#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT_COUNT 1000
#define MAX_CHANGE_COUNT 100
struct Change {
    char date[20]; // 变化日期
    char reason[50]; // 变化原因
};

struct Student {
    char id[20]; // 学号
    char name[20]; // 姓名
    char sex[10]; // 性别
    int age; // 年龄
    char birthplace[50]; // 籍贯
    char department[50]; // 系别
    char major[50]; // 专业
    char grade[20]; // 班级
    struct Change changes[20]; // 变化情况
    int change_count; // 变化情况数量
};
struct Student students[100];
int student_count = 0;


void register_student() {
    if (student_count >= MAX_STUDENT_COUNT) {
        printf("学生人数已满，无法注册\n");
        return;
    }
    printf("请输入学生信息：\n");
    printf("学号：");
    scanf("%s", students[student_count].id);
    printf("姓名：");
    scanf("%s", students[student_count].name);
    printf("性别：");
    scanf("%s", students[student_count].sex);
    printf("年龄：");
    scanf("%d", &students[student_count].age);
    printf("籍贯：");
    scanf("%s", students[student_count].birthplace);
    printf("系别：");
    scanf("%s", students[student_count].department);
    printf("专业：");
    scanf("%s", students[student_count].major);
    printf("班级：");
    scanf("%s", students[student_count].grade);
    students[student_count].change_count = 0;
    student_count++;
    printf("学生信息注册成功\n");
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
    printf("请输入要修改的学生学号：");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("未找到该学生\n");
        return;
    }
    printf("请输入学生信息：\n");
    printf("姓名：");
    scanf("%s", students[index].name);
    printf("性别：");
    scanf("%s", students[index].sex);
    printf("年龄：");
    scanf("%d", &students[index].age);
    printf("籍贯：");
    scanf("%s", students[index].birthplace);
    printf("系别：");
    scanf("%s", students[index].department);
    printf("专业：");
    scanf("%s", students[index].major);
    printf("班级：");
    scanf("%s", students[index].grade);
    printf("学生信息修改成功\n");
}

void delete_student() {
    char id[20];
    printf("请输入要删除的学生学号：");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("未找到该学生\n");
        return;
    }
    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;
    printf("学生信息删除成功\n");
}

void search_student() {
    char id[20];
    printf("请输入要查找的学生学号：");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("未找到该学生\n");
        return;
    }
    printf("学号：%s\n", students[index].id);
    printf("姓名：%s\n", students[index].name);
    printf("性别：%s\n", students[index].sex);
    printf("年龄：%d\n", students[index].age);
    printf("籍贯：%s\n", students[index].birthplace);
    printf("系别：%s\n", students[index].department);
    printf("专业：%s\n", students[index].major);
    printf("班级：%s\n", students[index].grade);
}

void print_birthplace_table() {
    char major[20];
    printf("请输入要输出籍贯表的专业：");
    scanf("%s", major);
    printf("学号\t\t籍贯\n");
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].major, major) == 0) {
            printf("%s\t%s\n", students[i].id, students[i].birthplace);
        }
    }
}

void add_change() {
    char id[20];
    printf("请输入要变更学籍的学生学号：");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("未找到该学生\n");
        return;
    }
    if (students[index].change_count >= MAX_CHANGE_COUNT) {
        printf("学籍变更次数已达上限，无法继续变更\n");
        return;
    }
    printf("请输入变更时间：");
    scanf("%s", students[index].changes[students[index].change_count].date);
    printf("请输入变更原因：");
    scanf("%s", students[index].changes[students[index].change_count].reason);
    students[index].change_count++;
    printf("学籍变更成功\n");
}

void print_changes() {
    char id[20];
    printf("请输入要查询学籍变化的学生学号：");
    scanf("%s", id);
    int index = find_student(id);
    if (index == -1) {
        printf("未找到该学生\n");
        return;
    }
    printf("该学生学籍变化如下：\n");
    printf("时间\t\t\t变化原因\n");
    for (int i = 0; i < students[index].change_count; i++) {
        printf("%s\t%s\n", students[index].changes[i].date, students[index].changes[i].reason);
    }
}

int main() {
    int choice;
    while (1) {
        printf("请选择要进行的操作：\n");
        printf("1. 注册学生学籍\n");
        printf("2. 修改学生学籍\n");
        printf("3. 删除学生学籍\n");
        printf("4. 查找学生学籍\n");
        printf("5. 输出学生籍贯表\n");
        printf("6. 查询学生学籍变化\n");
        printf("0. 退出程序\n");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            printf("感谢使用本程序\n");
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
            printf("无效的选项，请重新选择\n");
            break;
        }
    }
    return 0;
}


