typedef struct grades{
     struct list* students_list;
} *grades_t;

typedef struct student{
    char* name;
    int id;
    struct list* courses;
} *p_student_t, student_t;

typedef struct course{
	char* course_name;
	double grade;
} *p_course_t, course_t;



int checkIfStudentExists(struct list* students_list, int id) {
	struct iterator* it = list_begin(students_list);
	for(;it!=list_end(students_list);it=list_next(students_list)){
		p_student_t student = (p_student_t)list_get(it);
		if(student->id==id){
			return 1;
		}
	}
	return 0;
}

int checkIfCourseExists(struct list* courses, char* name) {
	struct iterator* it = list_begin(courses);
	for(;it!=list_end(courses);it=list_next(courses)){
		p_course_t course = (p_course_t)list_get(it);
		if(!strcmp(course->course_name,name)){
			return 1;
		}
	}
	return 0;
}


grades_t grades_init(){
    grades_t grades_sys = (grades_t)malloc(sizeof(struct grades));
    grades_sys->students_list = list_init(&clone_student, &destroy_student);
    return grades_sys;
}

void grades_destroy(grades_t grades){
    list_destroy(grades->students_list);
    free(grades);
}

int grades_add_student(grades_t grades, const char *name, int id){
	if(grades == NULL || checkIfStudentExists(grades->students_list, id) == 1) {
		return 1; // Fail
	}
	p_student_t new_student = (p_student_t)malloc(sizeof(student_t));
	new_student->name = malloc(sizeof(char)*(strlen(name)+1));
	strcpy(new_student->name,name);
	new_student->id = id;
	new_student->courses = list_init(&clone_course, &destroy_course);
	list_push_back(grades->students_list, new_student);
	destroy_student(new_student);
	return 0;
}
	
int grades_add_grade(grades_t grades,const char *name, int id, int grade){
	if(grade>100 || grade<0){ //checks grade
		return 1; //Fail
	}
	//checks if student.id exists
	int result=0;
	struct iterator* it = list_begin(grades->students_list);
	p_student_t student = (p_student_t)malloc(sizeof(student_t));
	for(;it!=list_end(grades->students_list);it=list_next(grades->students_list)){
		student = (p_student_t)list_get(it);
		if(student->id==id){
			result ++;
			break;
		}
	}
    if(!result){
    	return 1; //Fail
    }    //end of check student.id exists
    //checks name exists in courses 
    struct iterator* it_course = list_begin(student->courses);
    p_course_t course;
    for(;it_course!=list_end(student->courses);it_course=list_next(student->courses)){
    	course = (p_course_t)list_get(it_course);
		if(!strcpy(course->course_name, name)){
			return 1; //Fail
		}
	}
    p_course_t new_course = malloc(sizeof(new_course));
    new_course->course_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    new_course->grade = grade;
    list_push_back(student->courses, new_course);
    destroy_course(new_course);
    destroy_student(student);
    return 0;
}

float grades_calc_avg(grades_t grades, int id, char **out){
	struct iterator* it = list_begin(grades->students_list);
	int result=0;
	p_student_t student = (p_student_t)malloc(sizeof(student_t));
	for(;it!=list_end(grades->students_list);it=list_next(grades->students_list)){
		student = (p_student_t)list_get(it);
		if(student->id == id){
			result++;
			break;
		}
	}
	if(result){
		return 1;
	}
	double avg=0;
	struct iterator* it_course = list_begin(student->courses);
	p_course_t course = (p_course_t)malloc(sizeof(course_t));
	for(;it!=list_end(student->courses);it=list_next(student->courses)){
		course = (p_course_t)list_get(it_course);
		avg += course->grade;
	}
	*out = avg;
	destroy_course(course);
	return *out;
}
                    

int clone_student(void* student, void **out){
    p_student_t clone = (p_student_t) malloc(sizeof(student_t));
    p_student_t original = (p_student_t)student;
    clone->id = original->id;
    int nameSize = strlen(original->name);
    //TODO add malloc check
    clone->name = (char*)malloc(sizeof(char) * (nameSize + 1));
    strcpy(clone->name, original->name);
    p_course_t course;
    //dosent understand this line below
    ct(&clone->courses = list_iniclone_course, &destroy_course); // TODO add missing arguments
    struct iterator *it = list_begin(original->courses);
    for(; it != list_end(original->courses); it = list_next(it)) {
    	course = (p_course_t)list_get(it);
    	list_push_back(clone->courses, course);
    }
    *out = (void *)clone;
    return 0;
}


void destroy_student(void * student){
	p_student_t original = (p_student_t)student;
    free(original->name);
    list_destroy(original->courses);
    free(original);
}

int clone_course(void* course, void **out){
	p_course_t clone = (p_course_t) malloc(sizeof(course_t));
	//TODO if malloc
	p_course_t original = (p_course_t)course;
	clone->grade = original->grade;
	strcpy(clone->course_name, original->course_name);
	*out=(void *)clone;
	return 0;
}

void destroy_course(void *course){
	p_course_t original = (p_course_t)course;
	free(original->course_name);
	free(original);
	}
