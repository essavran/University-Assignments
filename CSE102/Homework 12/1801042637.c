#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
	char c;
	int frequency;
	struct Tree * left;
	struct Tree * right;
} Tree;

int ** read_reference(char * file_name, int * size);
int is_there(char c, int ** arr, int size);
Tree * huffman_tree(Tree ** heap, int **arr, int size);
Tree * create_leaf(char c, int frequency);
void insert(Tree * leaf, Tree ** heap, int * counter);
Tree * delete(Tree ** heap, int * counter);
void huffman(Tree * tree, int ** huffman_coding, int ** arr, int size);
void coding(Tree * tree, int ** huffman_coding, char * code, int * arrf);
void read_encrypting_decode(int ** huffman_coding);
char solve_code(int ** huffman_coding, char * str, int count, int i);
int current = 0;

void main(){
	int size = 0;
	int ** arr;
	arr = read_reference("reference.txt", &size);
	int ** huffman_coding;
	Tree * tree;
	/*memory allocate to main array*/
	huffman_coding = (int **)malloc(sizeof(int *));
	huffman_coding[0] = (int *)malloc(size * sizeof(int));
	for(int i = 1; i<size; i++){
		huffman_coding = (int **)realloc(huffman_coding, sizeof(int *)*(i+1));
		huffman_coding[i] = (int *)malloc(size * sizeof(int));
	}
	huffman(tree, huffman_coding, arr, size);
	/*Print Huffman Coding*/
	printf("HUFFMAN CODING TABLE\n");
	printf("--------------------\n");
	for(int i=0; i<size; i++){
		if(huffman_coding[i][0] == 10) printf("%2d. letter: \\n\tcode: ", i);
		else printf("%2d. letter: %c\tcode: ", i, (char)huffman_coding[i][0]);
		for(int k=1; huffman_coding[i][k] != -1; k++){
			printf("%d",huffman_coding[i][k]);
		}
		printf("\n");
	}
	read_encrypting_decode(huffman_coding);
}

void read_encrypting_decode(int ** huffman_coding){
	int memory1 = 0,
		memory2 = 0,
		index = 0,
		inp;;
	char * string;
	/*Read message.txt*/
	FILE * fp = fopen("message.txt", "r");

	string = (char *)malloc(sizeof(char));
	inp = fscanf(fp, "%c", &string[index]);

	while( inp != EOF ){
		index++;
		string = (char *)realloc(string, sizeof(char)*(index+1));
		inp = fscanf(fp, "%c", &string[index]);
	}
	index++;
	string = (char *)realloc(string, sizeof(char)*(index+1));
	string[index] = '\0';
	fclose(fp);
	/*Read and write endoded.dat*/
	int flag=0;
	FILE * fp2 = fopen("encoded.dat","w"); //for clean the file
	fclose(fp2);
	fp2 = fopen("encoded.dat","r+b");//read and write

	/*write*/
	for(int i=0; string[i] != '\0'; i++){
		flag=0;
		for(int j=0; huffman_coding[j][0] != (int)string[i]; j++){
			flag = j+1;
		}
		for(int k=1; huffman_coding[flag][k] != -1; k++){
			fprintf(fp2, "%d", huffman_coding[flag][k]);
			memory1++;
		//	fwrite(&huffman_coding[flag][k], sizeof(Tree **), 1, fp);
		}
		fprintf(fp2, " ");
	}
	fseek(fp2, SEEK_SET, SEEK_SET); /*Turn to beginning of the file*/
	/*Read*/
	char * str;
	index = 0;
	str = (char *)malloc(sizeof(char));
	inp = fscanf(fp2, "%c", &str[index]);
	while( inp != EOF ){
		index++;
		str = (char *)realloc(str, sizeof(char)*(index+1));
		inp = fscanf(fp, "%c", &str[index]);
	}
	index++;
	str = (char *)realloc(str, sizeof(char)*(index+1));
	str[index] = '\0';
	/*Coding*/
	int flag2 = 0;
	int count = 0;
	int size = 0;
	char * letters;
	for(int i=0; str[i] != '\0'; i++){	
		count = 0;
		size++;
		for(int j=i; (int)str[j] != 32; j++){
			count++;
			flag2 = j+1;
		}
		if(size == 1){
			letters = (char *)malloc(sizeof(char));
		}
		else{
			letters = (char *)realloc(letters, sizeof(char)*size);
		}
		*(letters + size - 1) = solve_code(huffman_coding, str, count, i);
		i = flag2;
	}
	*(letters+size) = '\0';
	fclose(fp2);
	/*Write decoded.txt*/
	FILE *fp3 = fopen("decoded.txt","w");
	fprintf(fp3, "%s\n", letters);
	memory2 = (sizeof(letters)-1) * 8;	
	fclose(fp3);
	/*compare memories*/
	printf("----------------------------------\n");
	printf("-> encryption (encoded.dat): %d bit\n", memory1);
	printf("-> decryption (decoded.txt): %d bit\n", memory2);
	printf("-> the file size difference: %d bit\n", abs(memory1-memory2));
}

char solve_code(int ** huffman_coding, char * str, int count, int i){
	int counter = 0; 
	int temp = 0, n;
	for(int m=0; m<39; m++){
		counter = 0;
		temp = i;
		n = 1;
		while( (int)str[temp] - 48 == huffman_coding[m][n] ){
			counter++;
			temp++;
			n++;
		}	
	if(counter == count) return (char)huffman_coding[m][0];/*Return letter which is*/
	}
}


void huffman(Tree * tree, int ** huffman_coding, int ** arr, int size){
	Tree * heap[size];
	int ** temp;
	temp = arr;
	tree = huffman_tree(heap, temp, size);
	int * array = (int *)calloc(size, sizeof(int));
	char code[size];
	code[0] = '\0';
	coding(tree, huffman_coding, code, array);
}

void coding(Tree * tree, int ** huffman_coding, char * code, int * arr){
	int size;
	char left[40], right[40];
    if(tree->left==NULL && tree->right==NULL){
 		huffman_coding[current][0] = (int)tree->c;
		for (int i = 0; i < strlen(code); ++i){
			huffman_coding[current][i+1] = (int)code[i] - 48;
		}
		huffman_coding[current][(strlen(code))+1] = -1;
		current++;
		return; //do nothing
    }
    
    size = strlen(code);
    strcpy(left, code);
    strcpy(right, code);
    
    left[size] = '0';
    left[size+1] = '\0';
    coding(tree->left, huffman_coding, left, arr);

    right[size] = '1';
    right[size+1] = '\0';
    coding(tree->right, huffman_coding, right, arr);
}

Tree * create_leaf(char c, int frequency){
	Tree * leaf = (Tree *)malloc(sizeof(Tree));
	leaf->c = c;
	leaf->frequency = frequency;
	leaf->left = NULL;
	leaf->right = NULL;
	return leaf;
}

Tree * huffman_tree(Tree ** heap, int **arr, int size){
	int counter = 0;
	heap[0] = (Tree *)malloc(sizeof(Tree));
	heap[0]->frequency = 0;
	for(int i=0; i<size; i++){
		Tree * leaf = create_leaf( (char)arr[i][0], arr[i][1] );
		counter++;
		heap[counter] = leaf;
		
		int x = counter;

		while( heap[x/2]->frequency > leaf->frequency ){
			heap[x] = heap[x/2];
			x /= 2;
		}
		heap[x] = leaf;		
	}
	
	for(int i=0; i<size-1; i++){
		Tree * left = delete(heap, &counter);
		Tree * right = delete(heap, &counter);
		Tree * temp = (Tree *)malloc(sizeof(Tree));
		temp->c = 0;
		temp->frequency = left->frequency + right->frequency;
		temp->left = left;
		temp->right = right;
		counter++;
		heap[counter] = temp;
		
		int x = counter;

		while( heap[x/2]->frequency > temp->frequency ){
			heap[x] = heap[x/2];
			x /= 2;
		}
		heap[x] = temp;	
	}
	Tree * tree = delete(heap, &counter);
	return tree;
}


Tree * delete(Tree ** heap, int * counter){
	Tree * min, * last;
	int temp, leaf;
	min = heap[1];
	last = heap[(*counter)--];
	for(temp = 1; temp*2<=*counter; temp = leaf){
		leaf = temp*2;
		if(leaf != *counter && heap[leaf+1]->frequency < heap[leaf]->frequency){
			leaf++;
		}
		if(last->frequency > heap[leaf]->frequency){
			heap[temp] = heap[leaf];
		}
		else{
			break;
		}
	}
	heap[temp] = last;
	return min;
}

int ** read_reference( char * file_name, int * size){
	
	FILE * fp = fopen(file_name, "r");
	int ** arr;
	char c;
	int index = 0,
		flag = 0;

	/*arr[i][j] = *(*(arr+i)+j)*/

	fscanf(fp, "%c", &c);
	
	arr = (int **)malloc(sizeof(int *));
	arr[index] = (int *)malloc(2*sizeof(int));
	
	arr[index][0] = (int)c;
	arr[index][1] = 1;

	index++;

	while( fscanf(fp, "%c", &c) != EOF ){	
		flag = is_there(c, arr, index);			
		if(flag == -1){
			arr = (int **)realloc(arr, sizeof(int *)*(index+1));
			arr[index] = (int *)malloc(2*sizeof(int));
			arr[index][0] = (int)c;
			arr[index][1] = 1;
			index++;
		}
		else{ 
			arr[flag][1]++;
		}
	}
	/*Last char of the file*/
	flag = is_there(c, arr, index);				
	if(flag == -1){
		arr = (int **)realloc(arr, sizeof(int *)*(index+1));
		arr[index] = (int *)malloc(2*sizeof(int));//2*
		arr[index][0] = (int)c;
		arr[index][1] = 1;
		index++;
	}
	else{ 
		arr[flag][1]++;
	}
	*size = index;
	fclose(fp);
	return arr;
}

int is_there(char c, int ** arr, int index){
	int counter = -1;
	for(int i=0; i<index; i++){
		if(arr[i][0] == (int)c ){
			counter = i;
			break;
		}
	}
	return counter;
}
