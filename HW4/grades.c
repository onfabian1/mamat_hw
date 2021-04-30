typedef struct grades{
     struct list* students_list;
} *grades_t

typedef struct student{
    char* name;
    int id;
    struct list* courses;
} *student_t

typedef struct course{
	char* course_name;
	double grade;
} *course_t

grades_t grades_init(){
    grades_t grades_sys = (grades_t)malloc(sizeof(struct grades));
    grades_t->students_list = list_init(&clone_student, &destroy_student);
}

void grades_destroy(struct grades *grades){
    list_destroy(grades_t->students_list);
    free(grades_t);
}

int clone_student(void* student, void **out){
    student_t clone = (student_t) malloc(sizeof(struct student));
    //todo add malloc check
    clone->id = (student_t)student->id; //maybe student_t->id;
    clone->name = strcpy((student_t)student->name);
    
    struct iterator it = list_begin(student->courses);
    for(; it!=list_end(student->courses);it=list_next(student->courses)) {
    	list_push_back(clone->courses, it);
    }
    *out = clone;
    return 0;
}

void destroy_student(void * student){
    free((student_t)student->name);
    free(student);
    //todo free courses by linked-list.h funcs
}

int clone_course(void* course, void **out){
	course_t clone = (course_t) malloc(sizeof(struct course));
	//todo if malloc
	clone->grade = (course_t)course->grade;
	clone->name = strcpy((course_t)course->name);
	*out=clone;
	return 0;
}
