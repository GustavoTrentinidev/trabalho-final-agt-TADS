#include <stdio.h>

int a[50], b[50];
int countA = 0, countB = 0;
int c[100], countC = 0;

int main(){
    int user_option = 0;
    while( user_option != 7){
        countC = 0;
        printf("\nSelecione uma opcao: \n");
        printf("1 - Inserir valores em um dos conjuntos (A ou B): \n");
        printf("2 - Remocao de todos os valores de um dos conjuntos (A ou B): \n"); 
        printf("3 - Exibicao dos valores dos conjuntos: \n"); 
        printf("4 - Uniao dos dois conjuntos (juntar): \n"); 
        printf("5 - Intercecao dos conjuntos (soma): \n"); 
        printf("6 - Diferenca dos conjuntos (subtracao, A - B ou B - A): \n"); 
        printf("7 - Sair do programa. \n"); 
        scanf("%i", &user_option);
        
        if(user_option == 1 || user_option == 2){
            chooseVector(user_option);
        }else if(user_option == 3){
            showVector('A', a, countA);
            showVector('B', b, countB);
        }else if(user_option == 4){
            joinVectors();
        } else if( user_option == 5){
            intersection();
        } else if (user_option == 6){
            difference();
        }
    }
    return 0;
}

int insertValues(char vetor_letra, int vetor[50], int count);

void chooseVector(int opcao){
    char vetor_letra;
    int i;
    printf("Selecione o vetor para modificar (A ou B): \n");
    scanf(" %c", &vetor_letra);
    vetor_letra = toupper(vetor_letra);
    printf("Selecionou o vetor %c \n", vetor_letra);
    int value = 1;
    if(vetor_letra == 'A'){
        if(opcao == 1){
            countA = insertValues(vetor_letra, a, countA);
        } else if( opcao == 2){
            cleanVector(vetor_letra, a, countA);
            countA = 0;
        }
    } else if (vetor_letra == 'B'){
        if(opcao == 1){
            countB = insertValues(vetor_letra, b, countB);
        }else if( opcao == 2){
            cleanVector(vetor_letra, b, countB);
            countB = 0;
        }
    }
}

int isValueInArray(int value, int vetor[50], int count) {
    int i;
    for (i = 0; i < count; i++) {
        if (vetor[i] == value) {
            return 1;
        }
    }
    return 0;
}

int insertValues(char vetor_letra, int vetor[50], int count){
    int value = 1;
    do{
        printf("Insira um valor para adicionar no vetor %c (0 para parar): \n", vetor_letra);
        scanf("%d", &value);
        if(value != 0){
            if (isValueInArray(value, vetor, count)) {
                printf("O valor %d ja esta no vetor, insira outro.\n", value);
            } else {
                vetor[count] = value;
                count++;
            }
        }
    }while(value != 0 && count < 50);
    return count;
}

void showVector(char vetor_letra, int vetor[100], int count){
    int i;
    if(count == 0){
        printf("\nO vetor %c esta vazio.\n", vetor_letra);
    }else{
        printf("\nValores dentro do vetor %c: \n", vetor_letra);
        printf("[");
        for(i=0; i<count; i++){
            if (i + 1 == count){
                printf("%d", vetor[i]);
            }else{
                printf("%d, ", vetor[i]);
            }
        }
        printf("] \n\n");
    }
}

void cleanVector(char vetor_letra, int vetor[100], int count){
    printf("\nRemovendo todos os elementos do vetor %c.\n", vetor_letra);
    int i;
    for(i=0; i<count; i++){
        vetor[count] = NULL;
    }
}

void joinVectors(){
    int i;
    for(i=0;i<countA;i++){
        c[countC] = a[i];
        countC++;
    }
    for(i=0;i<countB;i++){
        if (!isValueInArray(b[i],c,countC)){
            c[countC] = b[i];
            countC++;
        }
    }
    printf("Uniao entre A e B\n");
    showVector('C',c,countC);
}

void intersection(){
    int i, j;
    for (i=0; i<countA; i++){
        for(j=0; j<countB; j++){
            if(a[i] == b[j]){
                c[countC] = a[i];
                countC++;
            }
        }
    }
    printf("Intersecao entre A e B\n");
    showVector('C',c,countC);
}

void difference(){
    int value;
    printf("Selecione 1 para (A - B) \nSelecione 2 para (B - A): \n");
    scanf(" %d", &value);
    int i, j;
    int higherVector = 0;
    if (countA>countB){
        higherVector = countA;
    }else{
        higherVector = countB;
    }
    for (i=0; i<higherVector; i++){
        if(value == 1){
            c[countC] = a[i] - b[i]; 
        }else if (value == 2){
            c[countC] = b[i] - a[i];
        }
        countC++;
    }
    if(value == 1){
        printf("\nResultado de A - B\n");
    }else {
        printf("\nResultado de B - A\n");
    }
    showVector('C',c,countC);
}