#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dynamic_array {
    int capacity;
    int size;
    void** elements;
} dynamic_array;

void init_array(dynamic_array* array) {
    
    array -> capacity = 2;
    array -> size = 0;
    array -> elements = (void**) malloc(array -> capacity * sizeof(void*));

    for(int i = 0; i < array -> capacity; i++){
        array -> elements[i] = NULL;
    }   
}

void put_element(dynamic_array* array, void* element) {

    if(array -> size == array -> capacity){
        int doubleCapacity = array -> capacity * 2;

        void**  doubleElements = (void**) malloc(doubleCapacity * sizeof(void*));

        for (int i = 0; i < doubleCapacity; i++){
            if(i >= doubleCapacity / 2)
                doubleElements[i] = NULL;
            else
                doubleElements[i] = array -> elements[i];
        }
        
        doubleElements[array -> size] = element;
        array -> capacity = doubleCapacity;
        free(array -> elements);
        array -> elements = doubleElements;
    } else{
        for(int i = 0; i < array->capacity; i++){
            if (array -> elements[i] == NULL){
                array -> elements[i] = element;
                break;
            }
        }
    }

    array -> size++;
}

void remove_element(dynamic_array* array, int position) {

    array -> elements[position] = NULL;
    array -> size--;

    if(array -> size == array -> capacity / 2 && array -> capacity > 2){
        int halfCapacity = array -> capacity / 2;
        void** halfElements = (void**) malloc(halfCapacity * sizeof(void*));
        
        int j = 0;
        for (int i = 0; i < array -> capacity; i++){
            if (array -> elements[i] != NULL){
                halfElements[j] = array -> elements[i];
                j++;
            }
        }

        free(array -> elements);
        array -> elements = halfElements;
        array->capacity = halfCapacity;
    }
}

void* get_element(dynamic_array* array, int position) {

    return array -> elements[position];
}

typedef struct song {
    char* name;
    float duration;
} song;

int print_cases_and_get_users_number(){

    printf("1- Add a song\n");
    printf("2- Delete a song\n");
    printf("3- Display all songs\n");
    printf("4- Exit\n");

    int userNumber;
    printf("\nEnter a number: ");
    scanf("%d", &userNumber);

    return userNumber;
}

void when_users_number_is_1(dynamic_array* array){
    song* usersSong = (song*) malloc(sizeof(song));
    usersSong -> name = (char*) malloc(64 * sizeof(char));

    printf("Enter the song name to be added: ");
    scanf("%s", usersSong -> name);

    printf("Enter the duration: ");
    scanf("%f", &usersSong -> duration); 

    put_element(array, usersSong); 
}

void when_users_number_is_2(dynamic_array* array){

    int songExist = 0;

    if(array -> size != 0){
        
        char* songName = (char*) malloc(64 * sizeof(char));
        printf("Enter the song name to be removed: ");
        scanf("%s", songName);

        for(int i = 0; i < array -> capacity; i++){
            song* element = (song*) get_element(array, i);

            if (element != NULL){
                if(strcmp(element -> name, songName)==0){
                    songExist = 1;
                    remove_element(array, i);
                    break;
                }
            }
        }
    }else
        printf("No song removed in the list!\n");

    if(songExist == 0)
        printf("The song not found in the list!\n");
}

void when_users_number_is_3(dynamic_array* array){
    
    printf("\nALL SONGS\n\n");

    if(array -> size > 0){
        for (int i = 0; i < array -> capacity; i++){
            song* element = (song*) get_element(array, i);
            
            if(element != NULL){
                printf("Song name: %s, duration: %f\n", element -> name, element -> duration);
            }
        }
    }else
        printf("No song displayed in the list!\n");
}

int main(){

    dynamic_array* dynamicArrayOfSongs = (dynamic_array*) (malloc(sizeof(dynamic_array)));
    init_array(dynamicArrayOfSongs);

    while(1){
        int usersNumber = print_cases_and_get_users_number();

        if (usersNumber==1){
            when_users_number_is_1(dynamicArrayOfSongs);
        }else if (usersNumber==2){
            when_users_number_is_2(dynamicArrayOfSongs);
        }else if(usersNumber==3){
            when_users_number_is_3(dynamicArrayOfSongs);
        }else if(usersNumber==4){
            break;
        }else{
            printf("(%d) INVALID NUMBER! ENTER ONLY (1, 2, 3, 4)\n", usersNumber);
        }

        printf("--------------------------------------------------\n");
    }

    return 0;
}