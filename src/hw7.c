#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    // Regular binary search implementation 

    if(root == NULL){
        bst_sf *newNode = malloc(sizeof(bst_sf));
        if (!newNode){
            exit(1);
        }
        else{ // valid 
            newNode-> mat = mat;
            newNode-> left_child = NULL;
            newNode-> right_child = NULL;
            return newNode;
        }
    }

    if(mat-> name < root -> mat -> name){
        root->left_child = insert_bst_sf(mat,root -> left_child);

    }
    else if(mat -> name > root -> mat -> name){
        root->right_child = insert_bst_sf(mat,root -> right_child);
    }

    return root;//
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    // again just another regular bst algo 
    if(root == NULL){
        return NULL;
    }
    if(name == root -> mat -> name){
        return root -> mat;
    }
    
    if(name < root ->left_child){
        return find_bst_sf(name, root -> left_child);
    }
    else{
        return find_bst_sf(name, root -> right_child);
    }

}

void free_bst_sf(bst_sf *root) {
    // Steps: Traverse tree -> reach child and free first. THEN free what the pointer points to
    if(root == NULL){
        return NULL; //TODO remove NUll?
    }
    free_bst_sf(root -> left_child);
    free_bst_sf(root -> right_child);
    free(root -> mat);
    free(root);
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    // Steps: Need variable to store the sum of the matrix (another matrix). Calculate and store -> then return sum
    unsigned int rows = mat1 -> num_rows;
    unsigned int cols = mat1 -> num_cols;
    size_t sizeOfData = rows*cols* sizeof(int);

    matrix_sf *sumMatrix = malloc(sizeof(matrix_sf) + sizeOfData);
    if(!sumMatrix){
        exit(1);
    }
    else{
        sumMatrix -> name = "#";
        sumMatrix -> num_rows = rows;
        sumMatrix -> num_cols = cols;

        for(int i = 0; i < rows*cols; i++){// calculate 
            sumMatrix -> values[i] = mat1 -> values[i] * mat2 -> values[i];
        }
    }
    return sumMatrix;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
// Steps: Need to check dimensions fist then compute -> Return NEW MATRIX (Will need a new matrix)
    unsigned int m1Rows = mat1 -> num_rows;
    unsigned int m2Cols = mat2 -> num_cols;
    unsigned int compare = mat1 -> num_cols;
    size_t sizeOfData = m1Rows*m2Cols* sizeof(int);

    matrix_sf *productMatrix = malloc(sizeof(matrix_sf) + sizeOfData);
    if(!productMatrix){
        exit(1);
    }
    else{
        productMatrix -> name = "#";
        productMatrix -> num_rows = m1Rows;
        productMatrix -> num_cols = m2Cols;
    }

    for(int i = 0; i < m1Rows; i++){
        for(int j = 0; j < m2Cols; j++){
            int total = 0; 
            for(int k = 0; k < compare; k++){
                total = mat1 -> values[i * compare + k] * mat2 -> values[k * m2Cols + j];
            }
        }
    }
    

   return productMatrix;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    //Steps: same as prev but with diff calculations 
    int rows = mat -> num_cols;
    int cols = mat -> num_rows;
    size_t sizeOfData = rows*cols* sizeof(int);

    matrix_sf * tMatrix = malloc(sizeof(matrix_sf) + sizeOfData);
    if(!tMatrix){
        exit(1);
    }
    else{
        tMatrix -> name = "#";
        tMatrix -> num_rows = rows; 
        tMatrix -> num_cols = cols;
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; cols; j++){
            tMatrix -> values[i*cols + j] = mat -> values[j * mat -> num_cols + i]; 
        }
    }

    return tMatrix;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    //Steps: TODO 
    char *ptr = expr;
    int rows = stroul(ptr, &ptr, 10);
    int cols = stroul(ptr, &ptr, 10);
    size_t sizeOfData = rows*cols* sizeof(int);
    
    matrix_sf *mat = malloc(sizeof(matrix_sf) + sizeOfData);
    if(!mat){
        exit(1);
    }
    else{
        mat -> name = "#";
        mat -> num_rows = rows; 
        mat -> num_cols = cols;
    }

    while(*ptr && (*ptr != '[')){
        ptr++;
    }
    ptr++;

    for(int i = 0; i < rows*cols; i++){
        mat -> values[i] = stroul(ptr, &ptr, 10);
        while(*ptr && isspace(*ptr)){
            ptr++;
        }
        if(*ptr == ';'){
            ptr++;
        }

    }

    return mat;
}

char* infix2postfix_sf(char *infix) {
    int infixLen = strlen(infix);

    char *post = malloc(infixLen + 1); 
    char *stack = malloc(infixLen * sizeof(char));
    if(!post || !stack){
        exit(1);
    }
    else{
    }

    int topStack = -1;
    int iPost = 0; // index for postfix

    for(int i = 0; i < infixLen; i++){
        char c = infix[i];
        
        if(isspace(c)){
        }
        if(isalpha(c)){
            post[iPost++] = c;
        }
        else if(c == '('){
            stack[++topStack] = c;
        }
        else if(c == ')'){
            while( (topStack != -1) && (stack[topStack] != '(') ){
                post[iPost++] = stack[topStack--];
            }
            topStack--;
        }
        else{
            int precedense = 0;
            switch (c)
            {
            case '\'' : precedense = 3;
                /* code */
                break;
            case '*' : precedense = 2;
                /* code */
                break;
            case '+' : precedense = 1;
                /* code */
                break;
            default:
                break;
            }

            while( (topStack != -1) && (stack[topStack] != '(') ){
                int peek = 0;

                switch (stack[topStack])
                {
                case '\'' : peek = 3;
                    /* code */
                    break;
                case '*' : peek = 2;
                    /* code */
                    break;
                case '+' : peek = 1;
                    /* code */
                    break;
                default:
                    break;
                }

                if(precedense <= peek){
                    post[iPost] = stack[topStack--];
                }
                else{
                    break;
                }

            }
            stack[++topStack] = c;

        }
    }
    while(topStack != -1){
        post[iPost] = stack[topStack--];
    }
    post[iPost] = '\0';
    free(stack);

    return post;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    char *post = infix2postfix_sf(expr);
    int postLen = strlen(post);
    matrix_sf **stack = malloc(postLen * sizeof(matrix_sf*));

    if(!stack){
        exit(1);
    }
    int topStack = -1;

    for(int i = 0; post[i] != '\0'; i++){
        char c = post[i];

        if(isalpha(c)){
            matrix_sf *mat = find_bst_sf(c,root);
            stack[++topStack] = mat;
        }
        else if(c == '\''){
            matrix_sf *m1 = stack[topStack--];
            matrix_sf *res = transpose_mat_sf(m1);
            stack[++topStack];

            if(!isalpha(m1 -> name)){
                free(m1);
            }
        }
        else if(c == '*' || c == '+'){
            matrix_sf *m2 = stack[topStack--];
            matrix_sf *m1 = stack[topStack--];
            matrix_sf *res = NULL;

            if(c == '+'){
                res = add_mats_sf(m1,m2);
            }
            else{
                res = mult_mats_sf(m1,m2);
            }
            stack[++topStack] = res; 
            
            if(!isalpha(m1 -> name)){
                free(m1);
            }
            if(!isalpha(m2 -> name)){
                free(m2);
            }
        }
    }

    matrix_sf *finalRes = stack[topStack--];
    finalRes -> name = name;
    free(post);
    free(stack);
    return finalRes;
}

matrix_sf *execute_script_sf(char *filename) {
//Refrence prev HW 
    FILE *file = fopen(filename,"r");

    if(file == NULL){
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    bst_sf *root = NULL;
    matrix_sf *lastLineMatrix = NULL;

    while((read = getline(&line, &len, file)) != -1){
        char *ptr = line;
        while(*ptr && isspace(*ptr)){
            ptr++;
        }
        if(*ptr =='\0'){
            continue;
        }

        char matName = *ptr;
        ptr++;
        while(*ptr && (*ptr != '\0')){
            ptr++;
        }
        while(*ptr && isspace(*ptr)){
            ptr++;
        }

        char *ln = strchr(ptr, '\n');
        if(ln){
            matrix_sf *newMat = NULL;
        }

        // if(){

        // }

    }



   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
