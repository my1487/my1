#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 100     // 最多可录入的课程数
#define MAX_NAME_LEN 20     // 课程名称最大长度
#define COURSE_FILE "courses.dat"  // 课程信息保存文件名
#define STUDENT_FILE "students.dat"  // 学生信息保存文件名

// 定义课程的结构体
typedef struct course {
    int id;                 // 课程编号
    char name[MAX_NAME_LEN];    // 课程名称
    char type[10];          // 课程性质（公共课、必修课、选修课等）
    int total_hours;        // 总学时
    int teach_hours;        // 授课学时
    int exp_hours;          // 实验/上机学时
    float credit;           // 学分
    int semester;           // 开课学期
} Course;

// 定义学生的结构体
typedef struct student {
    int id;                 // 学号
    char name[MAX_NAME_LEN];    // 姓名
    int course_ids[MAX_COURSES]; // 所选课程的编号数组
    int num_courses;        // 已选课程数
} Student;

// 定义课程信息保存的全局变量
Course courses[MAX_COURSES];
int num_courses = 0;

// 从文件中读取课程信息
void read_courses() {
    FILE* file = fopen(COURSE_FILE, "rb");
    if (file != NULL) {
        fread(&num_courses, sizeof(int), 1, file);
        fread(courses, sizeof(Course), num_courses, file);
        fclose(file);
    }
}

// 将课程信息保存到文件中
void save_courses() {
    FILE* file = fopen(COURSE_FILE, "wb");
    if (file != NULL) {
        fwrite(&num_courses, sizeof(int), 1, file);
        fwrite(courses, sizeof(Course), num_courses, file);
        fclose(file);
    }
}

// 添加一个新的课程
void add_course() {
    Course course;
    printf("请输入课程编号：");
    scanf("%d", &course.id);
    printf("请输入课程名称：");
    scanf("%s", course.name);
    printf("请输入课程性质：");
    scanf("%s", course.type);
    printf("请输入总学时：");
    scanf("%d", &course.total_hours);
    printf("请输入授课学时：");
    scanf("%d", &course.teach_hours);
    printf("请输入实验/上机学时：");
    scanf("%d", &course.exp_hours);
    printf("请输入学分：");
    scanf("%f", &course.credit);
    printf("请输入开课学期：");
    scanf("%d", &course.semester);
    courses[num_courses++] = course;
    save_courses();
    printf("课程添加成功！\n");
}

// 浏览所有课程信息
// 浏览所有课程信息
void view_courses() {
    printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验/上机学时\t学分\t开课学期\n");
    for (int i = 0; i < num_courses; i++) {
        Course course = courses[i];
        printf("%d\t%s\t%s\t%d\t%d\t%d\t%.1f\t%d\n", course.id, course.name, course.type, course.total_hours,
            course.teach_hours, course.exp_hours, course.credit, course.semester);
    }
}

// 按学分查询课程
void search_courses_by_credit() {
    float credit;
    printf("请输入学分：");
    scanf("%f", &credit);
    printf("查询结果如下：\n");
    for (int i = 0; i < num_courses; i++) {
        Course course = courses[i];
        if (course.credit == credit) {
            printf("%d\t%s\t%s\t%d\t%d\t%d\t%.1f\t%d\n", course.id, course.name, course.type, course.total_hours,
                course.teach_hours, course.exp_hours, course.credit, course.semester);
        }
    }
}

// 按课程性质查询课程
void search_by_type() {
    char search_type[20];
    printf("请输入要查询的课程性质（公共课、必修课、选修课）：");
    scanf("%s", search_type);

    printf("查询结果如下：\n");
    printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验/上机学时\t学分\t开课学期\n");
    printf("------------------------------------------------------------------------------------\n");

    int found = 0; // 是否找到符合条件的课程
    for (int i = 0; i < num_courses; i++) {
        Course course = courses[i];
        if (strcmp(course.type, search_type) == 0) {
            printf("%d\t%s\t%s\t%d\t%d\t%d\t%.1f\t%d\n", course.id, course.name, course.type, course.total_hours, course.teach_hours, course.exp_hours, course.credit, course.semester);
            found = 1;
        }
    }

    if (!found) {
        printf("没有找到符合条件的课程！\n");
    }
}


// 学生选修课程
void choose_courses() {
    int student_id;
    printf("请输入学生学号：");
    scanf("%d", &student_id);
    Student student;
    student.id = student_id;
    printf("请输入学生姓名：");
    scanf("%s", student.name);
    student.num_courses = 0;
    while (1) {
        int course_id;
        printf("请输入要选修的课程编号（输入0结束）：");
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
            printf("课程编号%d不存在，请重新输入！\n", course_id);
        }
    }
    FILE* file = fopen(STUDENT_FILE, "ab");
    if (file != NULL) {
        fwrite(&student, sizeof(Student), 1, file);
        fclose(file);
        printf("选课成功！\n");
    }
    else {
        printf("选课失败，请重试！\n");
    }
}

// 主菜单
void main_menu() {
    printf("\n==== 选修课程系统 ====\n");
    printf("1. 浏览所有课程信息\n");
    printf("2. 添加课程信息\n");
    printf("3. 按学分查询课程\n");
    printf("4. 按课程性质查询课程\n");
    printf("5. 学生选课\n");
    printf("0. 退出系统\n");
    printf("=======================\n");
    printf("请选择操作编号：");
}

int main() {
    int choice;
    do {
        main_menu();
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("谢谢使用，再见！\n");
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
            printf("无效的操作编号，请重新输入！\n");
            break;
        }
    } while (choice != 0);

    return 0;
}

