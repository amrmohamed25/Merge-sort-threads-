#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct
{
    int left,right;
    int *arr;
} Element;//struct used to pass data to a thread


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int nL = m - l + 1;//number of elements in the left subarray = mid-left+1
    int nR = r - m;//number of elements in the right subarray = right-mid

    int L[nL], R[nR];//initializing arrays that will be used to merge
    for (i = 0; i < nL; i++)
        L[i] = arr[l + i];//filling the left subarray with the elements that are in the left region
    for (j = 0; j < nR; j++)
        R[j] = arr[m + 1 + j];//filling the right subarray with the elements that are in the right region

    i=0;
    j=0;
    k=l;//k is the correct position of the element in the original array
    while (i < nL && j < nR)
    {
        if (L[i] <= R[j])//checking the smallest and placing it in its correct position in the original array
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < nL)//if one array ended placing elements then place all the remaining elements from the other array
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < nR)//if one array ended placing elements then place all the remaining elements from the other array
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void* mergeSort(void* arg)
{
    Element *data=arg;//the struct that passes data to threads
    if (data->left < data->right)//recurse if left<right
    {
        int m = (data->right + data->left) / 2;//mid=(right+left)/2
        Element element1,element2;//initializing structs that will hold data used by threads
        element1.left=data->left;//begining
        element1.right=m;//mid
        element1.arr=data->arr;//pointer to the array

        element2.left=m+1;//middle + 1 (the other half of the array)
        element2.right=data->right;//end of the array
        element2.arr=data->arr;//pointer to the array

        pthread_t newThread1,newThread2;

        pthread_create(&newThread1, NULL, mergeSort, (void *) &element1);//recursive call for the first half of the subarray
        pthread_create(&newThread2, NULL, mergeSort, (void *) &element2);//recursive call for the second half of the subarray

        pthread_join(newThread1,NULL );//joining threads when finishing
        pthread_join(newThread2,NULL );
        merge(data->arr, data->left, m, data->right);//merging the array

    }

}


int getInput(char *token)//this function convert a string to int using atoi -> ascii to integer
{
    char *numbers=malloc(strlen(token));
    strcpy(numbers,token);
    int temp=atoi(numbers);
    free(numbers);
    return temp;
}

void printArray(int arr[],int n)
{
    for(int i=0; i<n; i++)
        printf("%d ",arr[i]);
    printf("\n\n");
}

int main(int argc,char** argv)
{
    //char filename[100];//input file to scan from
    //printf("Please enter name of the file:\n");
    //fgets(filename,100,stdin);//scanning input
    //strtok(filename," \n");//removing new line and spaces

    FILE *fp;
    fp=fopen(argv[1],"r");
    if(fp==NULL)//checking if file wasn't there
    {
        printf("File not found\n");
        return 0;
    }
    char *line=NULL;
    size_t line_size=0;
    getline(&line,&line_size,fp);
    char *token=strtok(line," \n");//removing new line and spaces
    if(token==NULL)
    {
        printf("Incorrect file format\n");
        return 0;
    }
    int numberOfElements=getInput(token);//scanning the number of elements which will be sorted
    if(numberOfElements<=0)//if number of elements is less or equal to zero break
    {
        printf("You should enter a positive integer\n");
        return 0;
    }
    int array[numberOfElements];//the array that will be sorted
    int i=0;
    while(getline(&line,&line_size,fp)!=-1)
    {
        token=strtok(line," \n");
        while(token)
        {
            array[i++]=getInput(token);
            token=strtok(NULL," \n");
        }
    }
    if(i!=numberOfElements) //if user entered in the file elements more than the size exit the program
    {
        printf("Incorrect file format\n");
        return 0;
    }
    Element data;//this struct is used in passing data in each recursive call
    data.arr=array;//a pointer to the array is passed
    data.left=0;//beginning of the array
    data.right=numberOfElements-1;//end of the array

    pthread_t firstThread;
    pthread_create(&firstThread, NULL, mergeSort, (void *) &data);
    pthread_join(firstThread,NULL );//joining threads when finishing

    printArray(array,numberOfElements);
    FILE * pFile;
    pFile=fopen("6304_output.txt", "w");
    if(pFile!=NULL)
    {
        fprintf(pFile,"Sorted array: ");
        for(int i=0; i<numberOfElements; i++)
        {
            fprintf(pFile,"%d ",array[i]);//write output in the file
        }

    }
    fclose(pFile);
    return 0;
}
