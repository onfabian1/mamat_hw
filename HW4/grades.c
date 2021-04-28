typedef struct student{
    char* name;
    int id;
} * student_t

int cloneStudent(void* student, void **out){
    student_t clone = (student_t) malloc(sizeof(struct student));
    clone->id = (student_t)student->id;
    clone->name = strcpy((student_t)student->name);
    *out = clone;
}

void destroyStudent(void * student){
    free((student_t)student->name);
    free(student);
}


typedef struct grades{
    list* 
} *grades_t

grades_t grades_init(){
    grades_t g = (grades_t)new malloc(sizeof(struct grades));
    grades_t->userList = list_init(&cloneStudent, &destroyStudent);
}
void grades_destroy(struct grades *grades){
    list_destroy(grade->studentList);
    free(grade);
}
