#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Question No 1:
PhD Genealogy Tree

A PhD Genealogy Tree represents professors and their advising relationships.
Each student is a child of their primary advisor.

Operations:
contains()          - Checks whether a professor exists.
size()              - Counts professors in a subtree.
findAdvisor()       - Finds the advisor of a professor.
numLeaves()         - Counts leaf nodes.
findProlificMentor()- Finds the advisor with maximum advisees.
findAcademicLineage() - Prints lineage from ancestor to student.
commonAncestor()    - Finds the most recent common academic ancestor.

A virtual root is used for professors who do not have an advisor,
or whose advisor has no record of their own in the CSV.
*/

#define MAX_CHILDREN 200
#define MAX_NODES    2000

typedef struct Node{
    char name[100];
    int year;
    struct Node *children[MAX_CHILDREN];
    int child_count;
    struct Node *parent;
}Node;

/* Registry of EVERY node ever created (real CSV rows + stub advisors),
   so any name can be looked up regardless of where it sits in the tree. */
Node* allNodes[MAX_NODES];
int nodeCount = 0;

Node* createNode(char name[],int year){
    Node *new = (Node*)malloc(sizeof(Node));
    if(new==NULL){
        printf("Memory allocation failed for %s\n",name);
        exit(1);
    }
    strcpy(new->name,name);
    new->year=year;
    new->child_count=0;
    new->parent=NULL;

    if(nodeCount<MAX_NODES){
        allNodes[nodeCount]=new;
        nodeCount++;
    } else {
        printf("Node registry full, increase MAX_NODES\n");
    }

    return new;
}

void addChild(Node *parent,Node *child){
    if(parent->child_count>=MAX_CHILDREN){
        printf("Too many children for %s, increase MAX_CHILDREN\n",parent->name);
        return;
    }
    int index=parent->child_count;
    parent->children[index]=child;
    parent->child_count++;
    child->parent=parent;
}

/* Turns a raw name/advisor string into a comparable "key":
   - strips a leading title ("Dr.", "Dr ", "Prof.", "Prof ") if present
   - removes all remaining spaces and periods
   - lowercases everything
   e.g. "Dr. A. K. Misra", "Prof.A.K.Misra", "A. K. Misra" -> "akmisra" */
void normalizeKey(const char *input, char *output){
    char buf[200];
    strncpy(buf,input,sizeof(buf)-1);
    buf[sizeof(buf)-1]='\0';

    int start=0;
    while(buf[start]==' ') start++;

    const char *titles[] = {"dr.", "dr ", "prof.", "prof "};
    for(int t=0;t<4;t++){
        int len=(int)strlen(titles[t]);
        if((int)strlen(buf+start) >= len){
            char tmp[10];
            strncpy(tmp,buf+start,len);
            tmp[len]='\0';
            for(int k=0;k<len;k++)
                tmp[k]=(char)tolower((unsigned char)tmp[k]);
            if(strcmp(tmp,titles[t])==0){
                start+=len;
                break;
            }
        }
    }

    int j=0;
    for(int i=start; buf[i]!='\0'; i++){
        char c=buf[i];
        if(c=='.'||c==' '||c=='\t')
            continue;
        output[j++]=(char)tolower((unsigned char)c);
    }
    output[j]='\0';
}

/* Look up a node by name, comparing normalized keys (title/spacing-insensitive) */
Node* findByName(char name[]){
    char key1[200];
    normalizeKey(name,key1);

    for(int i=0;i<nodeCount;i++){
        char key2[200];
        normalizeKey(allNodes[i]->name,key2);
        if(strcmp(key1,key2)==0)
            return allNodes[i];
    }
    return NULL;
}

/* Tree-relative containment check (exact match), still used for
   queries against a specific subtree/root. */
Node* contains(Node *root,char name[]){
    if(root==NULL||strcmp(root->name,name)==0)
        return root;
    for(int i=0;i<root->child_count;i++){
        Node *result=contains(root->children[i],name);
        if(result!=NULL)
            return result;
    }
    return NULL;
}

int size(Node *n){
    if(n==NULL)
        return 0;
    int count=1;
    for(int i=0;i<n->child_count;i++)
        count+=size(n->children[i]);
    return count;
}

Node* findAdvisor(Node *root,char name[]){
    Node *n=contains(root,name);
    return (n==NULL)?NULL:n->parent;
}

int numLeaves(Node *n){
    if(n==NULL)
        return 0;
    if(n->child_count==0)
        return 1;
    int count=0;
    for(int i=0;i<n->child_count;i++)
        count+=numLeaves(n->children[i]);
    return count;
}

/* Finds the node with the most DIRECT children within this subtree
   (including 'node' itself as a candidate). Kept general-purpose. */
Node* findProlificMentor(Node *node){
    if(node==NULL)
        return NULL;
    Node *best=node;
    for(int i=0;i<node->child_count;i++){
        Node *child=findProlificMentor(node->children[i]);
        if(child!=NULL&&best->child_count<child->child_count)
            best=child;
    }
    return best;
}

/* Wrapper used from main(): finds the most prolific REAL mentor by
   comparing the best candidate from each of root's subtrees.
   This prevents VirtualRoot itself (which only exists to hold
   stub/unknown advisors) from ever being reported as the answer. */
Node* findProlificMentorReal(Node *root){
    Node *best=NULL;
    for(int i=0;i<root->child_count;i++){
        Node *candidate=findProlificMentor(root->children[i]);
        if(candidate!=NULL && (best==NULL || candidate->child_count>best->child_count))
            best=candidate;
    }
    return best;
}

void findAcademicLineage(Node *n){
    if(n==NULL)
        return;
    findAcademicLineage(n->parent);
    if(n->parent!=NULL)
        printf(" -> ");
    printf("\"%s\"",n->name);
}

Node* commonAncestor(Node *root,char name1[],char name2[]){
    Node *node1=contains(root,name1);
    Node *node2=contains(root,name2);

    if(node1==NULL||node2==NULL)
        return NULL;

    Node *originalNode2=node2;

    while(node1!=NULL){
        node2=originalNode2;

        while(node2!=NULL){
            if(strcmp(node1->name,node2->name)==0)
                return node1;
            node2=node2->parent;
        }

        node1=node1->parent;
    }

    return NULL;
}

void printTree(Node *root, int level){
    if(root == NULL)
        return;

    for(int i=0;i<level;i++)
        printf("    ");

    printf("|-- %s (%d)\n",root->name,root->year);

    for(int i=0;i<root->child_count;i++)
        printTree(root->children[i],level+1);
}

/* Quote-aware CSV field reader.
   Treats commas inside "..." as part of the field, not a separator,
   so fields like "Computer Science, IT" don't throw off later columns.
   Also trims stray leading/trailing spaces left over from quoting. */
void getField(char line[], int field, char result[]){
    int i = 0, current = 0, j = 0;
    int inQuotes = 0;

    while (line[i] != '\0') {
        char c = line[i];

        if (c == '"') {
            inQuotes = !inQuotes;   /* toggle: entering/leaving a quoted field */
            i++;
            continue;
        }

        if (current == field) {
            if ((c == ',' && !inQuotes) || c == '\n' || c == '\r')
                break;
            result[j++] = c;
            i++;
            continue;
        }

        if (c == ',' && !inQuotes)
            current++;

        i++;
    }

    result[j] = '\0';

    /* trim leading spaces */
    int start = 0;
    while (result[start] == ' ') start++;
    if (start > 0) {
        int k = 0;
        while (result[start] != '\0') result[k++] = result[start++];
        result[k] = '\0';
    }

    /* trim trailing spaces */
    int len = (int)strlen(result);
    while (len > 0 && result[len-1] == ' ') {
        result[len-1] = '\0';
        len--;
    }
}

/* Parses a year out of a string that might have leading non-digit
   junk (e.g. "AY 2000"). Skips forward to the first digit before
   calling atoi. Returns 0 if no digit is found (genuinely missing). */
int parseYear(const char *s){
    while(*s && !isdigit((unsigned char)*s))
        s++;
    return atoi(s);
}

int main(){
    FILE *fp;
    char line[500];
    char name[100];
    char advisor[100];
    char yearString[20];
    int year;

    /* Create virtual root */
    Node *root=createNode("VirtualRoot",0);

    /* ---- First pass: create every professor listed as a "name",
       and attach any with a blank advisor field directly to root. ---- */
    fp=fopen("Ph.D. Thesis.csv","r");

    if(fp==NULL){
        printf("File not found\n");
        return 1;
    }

    printf("CSV opened successfully\n");

    fgets(line,sizeof(line),fp);

    while(fgets(line,sizeof(line),fp)){
        getField(line,1,yearString);
        getField(line,2,name);
        getField(line,4,advisor);

        if(strlen(name)==0)
            continue;

        if(strlen(yearString)==0)
            printf("DEBUG: blank year field for \"%s\" | raw line: %s", name, line);

        year=parseYear(yearString);

        Node *student=createNode(name,year);   /* always registered */

        printf("Creating: %s\n",name);

        if(strlen(advisor)==0)
            addChild(root,student);
    }

    fclose(fp);

    /* ---- Second pass: connect students to advisors.
       If an advisor has no record of their own in the CSV,
       create a stub node for them under VirtualRoot instead
       of dropping the student. ---- */
    fp=fopen("Ph.D. Thesis.csv","r");

    if(fp==NULL){
        printf("File not found\n");
        return 1;
    }

    fgets(line,sizeof(line),fp);

    while(fgets(line,sizeof(line),fp)){
        getField(line,1,yearString);
        getField(line,2,name);
        getField(line,4,advisor);

        if(strlen(name)==0)
            continue;

        if(strlen(advisor)==0)
            continue;

        /* If multiple advisors exist, use first advisor */
        char *p=strstr(advisor," & ");

        if(p!=NULL)
            *p='\0';

        Node *student=findByName(name);
        Node *parent=findByName(advisor);

        if(parent==NULL){
            /* No CSV row for this advisor -> create a stub and
               attach it under VirtualRoot. It gets registered by
               createNode(), so later rows citing the same advisor
               will find and reuse this same stub node. */
            parent=createNode(advisor,0);
            addChild(root,parent);
            printf("Note: advisor \"%s\" had no record of their own -- added as a root-level entry\n",advisor);
        }

        if(student!=NULL&&parent!=NULL)
            addChild(parent,student);
    }

    fclose(fp);

    /* ---- Safety sweep: attach any node that still has no parent
       (other than root itself) directly under VirtualRoot. Should
       rarely trigger now, but guards against any edge case. ---- */
    for(int i=0;i<nodeCount;i++){
        if(allNodes[i]!=root && allNodes[i]->parent==NULL){
            addChild(root,allNodes[i]);
        }
    }

    printf("Tree created successfully!\n");

    printf("\nPhD Genealogy Tree:\n");
    printTree(root,0);

    /* Test contains() */
    if(contains(root,"Suman Purwar")!=NULL)
        printf("Suman Purwar is present\n");
    else
        printf("Suman Purwar is not present\n");

    /* Test size() */
    printf("Size of tree = %d\n",size(root));

    /* Test findAdvisor() */
    Node *a=findAdvisor(root,"Suman Purwar");

    if(a!=NULL && a!=root)
        printf("Advisor of Suman Purwar = %s\n",a->name);
    else
        printf("Advisor not found\n");

    /* Test numLeaves() */
    printf("Number of leaves = %d\n",numLeaves(root));

    /* Test findProlificMentor() */
    Node *mentor=findProlificMentorReal(root);

    if(mentor!=NULL)
        printf("Most prolific mentor = %s\n",mentor->name);

    /* Test findAcademicLineage() */
    Node *student=contains(root,"Suman Purwar");

    if(student!=NULL){
        printf("Academic lineage: ");
        findAcademicLineage(student);
        printf("\n");
    }

    /* Test commonAncestor() */
    Node *ancestor=commonAncestor(root,"Suman Purwar","Lekhraj");

    if(ancestor!=NULL)
        printf("Common ancestor = %s\n",ancestor->name);
    else
        printf("Common ancestor not found\n");

    return 0;
}