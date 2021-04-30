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

int grades_add_student(grades_t, const char *name, int id){
	struct iterator* it = list_begin(grades_t->students_list);
	for(;it!=list_end(grades_t->students_list);it=list_next(grades_t->students_list){
		if(id==it->id){
			printf("Error");
			return 1;
		}
	}
	list_push_back(grades_t->students_list, student_t);
	list_end(grades_t->students_list)->name=strcpy(name);
	list_end(grades_t->students_list)->id=id;
	student_t->courses = list_init(&clone_course, &destroy_course);                 
	return 0;
}
	
int grades_add_grade(grades_t,const char *name, int id, int grade){
	//checks if student.id exists
	int result=0;
	struct iterator* it = list_begin(grades_t->students_list);
	for(;it!=list_end(grades_t->students_list);it=list_next(grades_t->students_list){
		if(it->id==id){
			result ++;
			break;
		}
	}
    if(!result){
    	printf("Error");
    	return 1;
    }               
                   
                    

int clone_student(void* student, void **out){
    student_t clone = (student_t) malloc(sizeof(struct student));
    //TODO add malloc check
    clone->id = student_t->id; 
    clone->name = strcpy(student_t->name);
    
    struct iterator* it = list_begin(student_t->courses);
    for(; it!=list_end(student_t->courses);it=list_next(student_t->courses)) {
    	if(list_push_back(clone->courses, it)){
    		printf("ERROR");
    }
    *out = clone;
    return 0;
}

void destroy_student(void * student){
    free((student_t)student->name);
    list_destroy(student_t->courses);
    free(student_t);
}

int clone_course(void* course, void **out){
	course_t clone = (course_t) malloc(sizeof(struct course));
	//todo if malloc
	clone->grade = course_t->grade;
	clone->name = strcpy(course_t->name);
	*out=clone;
	return 0;
}

void destroy_course(void *course){
	free(course_t->name);
	free(course_t);
	}
