typedef struct student{
    char* name;
    int id;
    struct list* courses;
} *student_t

typedef struct course{
	char* course_name;
	double grade;
} *course_t


int cloneStudent(void* student, void **out){
    student_t clone = (student_t) malloc(sizeof(struct student));
    //TODO add malloc check
    clone->id = (student_t)student->id;
    clone->name = strcpy((student_t)student->name);
    
    struct iterator it = list_begin(student->courses);
    for(; it!=list_end(student->courses);it=list_next(student->courses)) {
    	list_push_back(clone->courses, it);
    }
    *out = clone;
    return 0;
}

void destroyStudent(void * student){
    free((student_t)student->name);
    free(student);
    //TODO free courses by list funcs
}



typedef struct grades{
     list students_list;
} *grades_t

grades_t grades_init(){
    grades_t grades_sys = (grades_t)malloc(sizeof(struct grades));
    grades_t->students_list = list_init(&cloneStudent, &destroyStudent);
}
void grades_destroy(struct grades *grades){
    list_destroy(grade->studentList);
    free(grade);
}
