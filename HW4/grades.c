typedef struct grades{
     struct list* students_list;
} *grades_t;

typedef struct student{
    char* name;
    int id;
    struct list* courses;
} *student_t;

typedef struct course{
	char* course_name;
	double grade;
} *course_t;



int checkIfStudentExists(struct list students_list, int id) {
	struct iterator* it = list_begin(students_list);
	for(;it!=list_end(students_list);it=list_next(students_list)){
		if(it->id==id){
			return 1;
		}
	}
	return 0;
}

int checkIfCourseExists(struct list courses, char* name) {
	struct iterator* it = list_begin(courses);
	for(;it!=list_end(courses);it=list_next(courses)){
		if(it->name==name){// change to strcmp
			return 1;
		}
	}
	return 0;
}


grades_t grades_init(){
    grades_t grades_sys = (grades_t)malloc(sizeof(struct grades));
    grades_sys->students_list = list_init(&clone_student, &destroy_student);
}

void grades_destroy(grades_t grades){
    list_destroy(grades->students_list);
    free(grades);
}

int grades_add_student(grades_t grades, const char *name, int id){
	if(checkIfStudentExists(grades->students_list, id) == 1) {
		printf("Error!");
	}
	student_t new_student = (student_t)malloc(sizeof(struct student));
	new_student->name = malloc(sizeof(char)*strlen(name)+1);
	new_student->name = name;//strcpy
	// same to id
	new_student->courses = list_init(&clone_course, &destroy_course);
	list_push_back(grades->students_list, new_student);
	destroy_student(new_student);

	return 0;
}
	
int grades_add_grade(grades_t grades,const char *name, int id, int grade){
	if(grade>100 || grade<0){ //checks grade
		printf("Error");
		return 1;
	}
	//checks if student.id exists
	int result=0;
	struct iterator* it = list_begin(grades->students_list);
	for(;it!=list_end(grades->students_list);it=list_next(grades->students_list)){
		if(it->id==id){
			result ++;
			break;
		}
	}
    if(!result){
    	printf("Student does not exists");
    	return 1; //end of check student.id exists
    }    
    //checks name exists in courses 
    struct iterator* it_course = list_begin(it->courses);          
    for(;it!=list_end(it->courses);it=list_next(it->courses)){
		if(strcpy(it_course->name, name)==0){
			printf("Course already exists");
			return 1;
		}
	}
    course_t new_course = malloc(sizeof(new_course));
    //add name
    //add grade
    list_push_back(it->courses, new_course);
                    

int clone_student(void* student, void **out){
    student_t clone = (student_t) malloc(sizeof(struct student));
    //TODO add malloc check
    clone->id = ((student_t)student)->id;
    //malloc name
    strcpy(clone->name, ((student_t)student)->name);
    
    struct iterator* it = list_begin(((student_t)student)->courses);
    for(; it!=list_end(((student_t)student)->courses);it=list_next(((student_t)student)->courses)) {
    	if(list_push_back(clone->courses, it)){
    		printf("ERROR");
    	}
    }
    *out = clone;
    return 0;
}

void destroy_student(void * student){
    free(((student_t)student)->name);
    list_destroy(((student_t)student)->courses);
    free(student);
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
