/******INCLUDE********/

#include "Graph.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Queue.h"
/******       VERTEX FUNCTIONS        ******/
void addStudent(tstGraph *g, 
                const char *name, 
                const char *PLastName, 
                const char *MLastName, 
                const char *ID, 
                tenStuStatus status);

void addCourse(tstGraph *g,
                char *CourseID,
                char *name);

void addProfessor(tstGraph *g,
                char *name,
                char *PLastName,
                char *MLastName,
                char *ID);

void addDegree(tstGraph *g,
                char *name,
                char *acronym);

void addArea(tstGraph *g,
                char *name);

void addCampus(tstGraph *g,
                char *name,
                char *location);

void addExtra(tstGraph *g,
                char *name);

/*           PRIVATE FUNCTIONS           */
tstQueue* searchNodes(tstGraph *g, char *s);
tstQueue* requestBasicQuery(tenEdgeType type, char *s);

void printGraph(tstGraph *g);
tenbool compString(char *str1, char *str2, uint8 n);
void printAdjElemQueue(tstQueue *q);
/*******          MAIN              ********/
void main(void){

    tstGraph* g;
    tstQueue *q_AdjElem;

    g=createGraph();

    addStudent(g,"Jordan Abel","Avalos","Bueno","A01227033",Active);
    addStudent(g,"Fabian","Galindo","Sanchez","A01226208",Active);
    addStudent(g,"Jorge Ernesto","Castaneda","Hernandez","A01225503",Active);
    addProfessor(g,"Martin","Sinsel","Gonzalez","L01227584");
    addCourse(g,"TC1207","Matematicas IV");

    printGraph(g);
    
    q_AdjElem = searchNodes(g,"A0122");
    printAdjElemQueue(q_AdjElem);
    q_AdjElem = requestBasicQuery(teaches,"Matematicas");
    printAdjElemQueue(q_AdjElem);
}

void printAdjElemQueue(tstQueue *q){

    
    tstQueueNode *tmp=q->head;
    tstAdjElem* node;

    while(tmp != NULL_PTR){

        node=(tstAdjElem*) tmp->pData;
        printf("|%s| ", getStudentVertex(node)->PLastName);
        tmp=tmp->next;
    }
    printf("\n");

}

void printGraph(tstGraph *g){


    tstAdjElem *tmp= g->adjListHead;
    printf("Number of V::%i\n",g->V);
    printf("Number of E::%i\n",g->E);

    while(tmp != NULL_PTR){
        switch(getNodeType(tmp)){

            case student:
                printf("Name of student is%s\n", getStudentVertex(tmp)->name );
                printf("ID of student is%s\n\n", getStudentVertex(tmp)->ID );
                break;

            case professor:
                printf("Name of professor is%s\n", getProfessorVertex(tmp)->name );
                printf("ID of professor is%s\n\n", getProfessorVertex(tmp)->ID );
                break;

            case course:
                printf("Name of course is:%s\n",getCourseVertex(tmp)->name);
                printf("Course ID is:%s\n\n",getCourseVertex(tmp)->CourseID);
                break;
        }

        tmp=tmp->next;

    }
}

tenbool compString(char *str1, char *str2, uint8 n){

    uint8 i;
    char tmp;
    printf("Comparing %s with %s\n",str1,str2);
    for(i=0;i<n;){
        
        if(str1[i]>='A' && str1[i]<='Z' || str1[i]>='a' && str1[i]<='z'){
            if(str2[i]>='A' && str2[i]<='Z' || str2[i]>='a' && str2[i]<='z'){
                
                if(str2[i]<str1[i])     tmp = str1[i] - str2[i];
                else                    tmp = str2[i] - str1[i];
                
                if(tmp == 0 || tmp == 0x20 || tmp == 0xE0) i++;
                else return FALSE;

            }else{
                return FALSE;
            }
        }else{
            tmp = str2[i]-str1[i];
            if( tmp == 0 ) i++;
            else return FALSE;
        }
    }
    return TRUE;
}

tstQueue* searchNodes(tstGraph *g, char *s){
    
    tstQueue *q;
    tstAdjElem *tmp=g->adjListHead;
    
    q=CreateQueue();
    

    while(tmp != NULL_PTR){
        switch(getNodeType(tmp)){

            case student:
                if(compString(s,getStudentVertex(tmp)->name,strlen(s))==TRUE
                || compString(s,getStudentVertex(tmp)->PLastName,strlen(s))==TRUE
                || compString(s,getStudentVertex(tmp)->MLastName,strlen(s))==TRUE
                || compString(s,getStudentVertex(tmp)->ID,strlen(s))==TRUE)
                {
                    printf("Result found... Enqueue...\n");
                    Enqueue(q,(void*)tmp);
                }
                break;
            case professor:
                printf("NOT IMPLEMENTED\n");
                break;
            case course:
                 printf("NOT IMPLEMENTED\n");
                 break;
            case degree:
                 printf("NOT IMPLEMENTED\n");
                 break;
            case area:
                 printf("NOT IMPLEMENTED\n");
                 break;
            case campus:
                 printf("NOT IMPLEMENTED\n");
                 break;
            case extra:
                 printf("NOT IMPLEMENTED\n");
                 break;
            default:
                 printf("NOT IMPLEMENTED\n");
                 break;
        }
        tmp = tmp->next;
    }
    return q;
}

tstQueue* requestBasicQuery(tenEdgeType type, char *s){
    
    tenNodeType filter;
    tstAdjNode *node;
    tstQueue *q;
    tstAdjElem *tmp=g->adjListHead;
    
    q=CreateQueue();
    
    if(type == courses || type == isPartTo ||
       type == studiesIn || type == coursesE){
        filter = student;
    }
    else if(type == teaches || type == teachesIn || type == teachesE){
        filter = professor;
    }
    else if(type == partOfPlan)
    {
        filter = course;
    }
    else if(type == belongsTo)
    {
        filter = extra;
    }
    
    
    while(tmp != NULL_PTR){
        if(getNodeType(tmp) == filter){
            node = tmp->first_adj;
            while(node != NULL){
                if(type == node->tenEdgeType){
                    switch(getNodeType(tmp)){
                        case student:
                            if(compString(s,getStudentVertex(tmp)->name,strlen(s))==TRUE
                               || compString(s,getStudentVertex(tmp)->PLastName,strlen(s))==TRUE
                               || compString(s,getStudentVertex(tmp)->MLastName,strlen(s))==TRUE
                               || compString(s,getStudentVertex(tmp)->ID,strlen(s))==TRUE){
                                printf("Result found... Enqueue...\n");
                                Enqueue(q,(void*)tmp);
                            }
                            break;
                        case professor:
                            printf("NOT IMPLEMENTED\n");
                            break;
                        case course:
                            printf("NOT IMPLEMENTED\n");
                            break;
                        case degree:
                            printf("NOT IMPLEMENTED\n");
                            break;
                        case area:
                            printf("NOT IMPLEMENTED\n");
                            break;
                        case campus:
                            printf("NOT IMPLEMENTED\n");
                            break;
                        case extra:
                            printf("NOT IMPLEMENTED\n");
                            break;
                        default:
                            printf("NOT IMPLEMENTED\n");
                            break;
                    }
                }
                node = node->next;
            }
        }
        tmp = tmp->next;
    }
    return q;
}

void* safeMalloc(size){

    void* tmp = malloc(size);
    if(tmp == NULL_PTR) exit(0);

    return tmp;
}

void addVertex(tstGraph *g, void *vertex){

    tstAdjElem *ptrVertex;
  
    //add Vertex to AdjList
    
    ptrVertex= (tstAdjElem*) safeMalloc(sizeof(tstAdjElem));
    printf("ptrVertex added:%p\n",ptrVertex);
    ptrVertex->vertex= vertex;
    ptrVertex->next=NULL_PTR;
    ptrVertex->first_adj=NULL_PTR;
    
    if(g->adjListHead==NULL_PTR){ //Empty graph
        g->adjListHead = g->adjListTail = ptrVertex;
    }else{
        (g->adjListTail)->next = ptrVertex;
        g->adjListTail = ptrVertex;
    }

    g->V++;
    
}

void addStudent(tstGraph *g, 
                const char *name, 
                const char *PLastName, 
                const char *MLastName, 
                const char *ID, 
                tenStuStatus status){
    
    tstStudentV *tmp;
    char* str;
    
    //Allocate memory
    tmp = (tstStudentV*) safeMalloc(sizeof(tstStudentV));
    str = (char*) safeMalloc(strlen(name) 
                    + strlen(PLastName) 
                    + strlen(MLastName) 
                    + strlen(ID) + 4);


    //add parameters to node
    tmp->NodeType=student;

    strncpy(str,name,strlen(name)+1);
    tmp->name=str;

    str +=strlen(name)+1;

    strncpy(str,PLastName,strlen(PLastName)+1);
    tmp->PLastName=str;

    str += strlen(PLastName)+1;

    strncpy(str,MLastName,strlen(MLastName)+1);
    tmp->MLastName=str;

    str += strlen(MLastName)+1;

    strncpy(str,ID,strlen(ID)+1);
    tmp->ID=str;

    tmp->Status=status;

    //add vertex to graph

    addVertex(g, (void*) tmp);
         
}

void addCourse(tstGraph *g,
                char *CourseID,
                char *name){
    tstCourseV *tmp;
    char* str;
    
    //Allocate memory
    tmp = (tstCourseV*) safeMalloc(sizeof(tstCourseV));
    
    str = (char*) safeMalloc(strlen(CourseID) 
                    + strlen(name)+2); 


    //add parameters to node
    tmp->NodeType=course;

    strncpy(str,CourseID,strlen(CourseID)+1);
    tmp->CourseID=str;

    str +=strlen(CourseID)+1;

    strncpy(str,name,strlen(name)+1);
    tmp->name=str;

    //add vertex to graph

    addVertex(g, (void*) tmp);
}

void addProfessor(tstGraph *g,
                char *name,
                char *PLastName,
                char *MLastName,
                char *ID){

    tstProfessorV *tmp;
    char* str;
    
    //Allocate memory
    tmp = (tstProfessorV*) safeMalloc(sizeof(tstProfessorV));
    
    str = (char*) safeMalloc(strlen(name) 
                    + strlen(PLastName) 
                    + strlen(MLastName) 
                    + strlen(ID) + 4);


    //add parameters to node
    tmp->NodeType=professor;

    strncpy(str,name,strlen(name)+1);
    tmp->name=str;

    str +=strlen(name)+1;

    strncpy(str,PLastName,strlen(PLastName)+1);
    tmp->PLastName=str;

    str += strlen(PLastName)+1;

    strncpy(str,MLastName,strlen(MLastName)+1);
    tmp->MLastName=str;

    str += strlen(MLastName)+1;

    strncpy(str,ID,strlen(ID)+1);
    tmp->ID=str;

    

    //add vertex to graph

    addVertex(g, (void*) tmp);
        
}

void addDegree(tstGraph *g,
                char *name,
                char *acronym){

    tstDegreeV *tmp;
    char* str;
    
    //Allocate memory
    tmp = (tstDegreeV*) safeMalloc(sizeof(tstDegreeV));
    
    str = (char*) safeMalloc(strlen(name) 
                    + strlen(acronym)+2); 


    //add parameters to node
    tmp->NodeType=degree;

    strncpy(str,name,strlen(name)+1);
    tmp->name=str;

    str +=strlen(name)+1;

    strncpy(str,acronym,strlen(acronym)+1);
    tmp->acronym=str;

    //add vertex to graph

    addVertex(g, (void*) tmp);
        
}

void addArea(tstGraph *g,
                char *name){
    tstAreaV *tmp;
    char* str;
    
    //Allocate memory
    tmp = (tstAreaV*) safeMalloc(sizeof(tstAreaV));
    
    str = (char*) safeMalloc(strlen(name) + 1); 


    //add parameters to node
    tmp->NodeType=area;

    strncpy(str,name,strlen(name)+1);
    tmp->name=str;

    //add vertex to graph

    addVertex(g, (void*) tmp);
}

void addCampus(tstGraph *g,
                char *name,
                char *location){
    
    tstCampusV *tmp;
    char* str;
    
    //Allocate memory
    tmp = (tstCampusV*) safeMalloc(sizeof(tstCampusV));
    
    str = (char*) safeMalloc(strlen(name) 
                    + strlen(location)+2); 


    //add parameters to node
    tmp->NodeType=campus;

    strncpy(str,name,strlen(name)+1);
    tmp->name=str;

    str +=strlen(name)+1;

    strncpy(str,location,strlen(location)+1);
    tmp->location=str;

    //add vertex to graph

    addVertex(g, (void*) tmp);
}

void addExtra(tstGraph *g,
                char *name){
    tstExtraV *tmp;
    char* str;
    
    //Allocate memory
    tmp = (tstExtraV*) safeMalloc(sizeof(tstExtraV));
    
    str = (char*) safeMalloc(strlen(name) + 1); 


    //add parameters to node
    tmp->NodeType=area;

    strncpy(str,name,strlen(name)+1);
    tmp->name=str;

    //add vertex to graph

    addVertex(g, (void*) tmp);

}

tstGraph* createGraph(void){

    tstGraph* tmp;

    //Allocate graph basic structure
    tmp= malloc(sizeof(tstGraph));
    
    //Allocation failed for graph structure
    if(tmp == NULL_PTR) return NULL_PTR; //can use: exit(0);

    //if memory allocation was sucessfull, initialize all structures and return pointer
    tmp->V=0;
    tmp->E=0;

    tmp->adjListHead=NULL_PTR;
    tmp->adjListTail=NULL_PTR;
    
    return tmp;
}
