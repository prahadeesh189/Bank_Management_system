#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// data structures
typedef struct custPersonalData{

    char * name;
    unsigned long long int acc_no;
    int age;
    char  * DOB;
    unsigned long long int contact_no;
    char * address;
}custPersonalData;

typedef struct custAccountData{

    unsigned long long int acc_no;
    unsigned long long int accBalance;
    char * DOJ;
    char * branch;
}custAccountData;

typedef struct pdNode{

    custPersonalData * data;
    struct pdNode * next;
}pdNode; 

typedef struct adNode{

    custAccountData * data;
    struct adNode * next;
}adNode; 

typedef struct charList{

    char val;
    struct charList * next;
}charList;

//functions to manage DB (CRUD)
void createDB();

// functions to get/manipulate data (input)
custPersonalData * getCustPersonalData();
custAccountData * getCustAccountData();

void createAcc();
void delACC();
void delACCDE();
void editAcc();

void showData();
int deposit_withdraw_Money();
int transferMoney();

unsigned long long int accountNoGenerator();

char personalDataFile[] = "~pathForYourComputer/custPersonaldataDB.dat";
char accountDataFile[]  = "~pathForYourComputer/custAccountdataDB.dat";

void main(){

    createDB();

    system("color f0");

    while ( 1 ){

        system( "cls" );

        printf("\n***** MENU *****\n");
        printf("\n 1 - create Account ");
        printf("\n 2 - delete Account ");
        printf("\n 3 - show Data ");
        printf("\n 4 - edit Account ");
        printf("\n 5 - transfer Money ");
        printf("\n 6 - deposit Money ");
        printf("\n 7 - withdraw Money ");
        printf("\n 0 - EXIT MENU ");
        printf("\n****************\n");
        
        int cmd , cnt;
        printf("\n...command : ");
        scanf("%d", &cmd );

        unsigned long long int mn, mn1, mn2;
        unsigned long int mn3;

        switch ( cmd ){
                
            case 1:
                fflush(stdin);
                createAcc();
                printf("\n\n:::: PRESS 1 TO CONTINUE : ");
                scanf("%d", &cnt );
                if ( cnt != 1 ){
                    printf("\n\n***** MENU EXIT *****\n\n");
                    system("color 0f");
                    return;
                }
                
                break;
            case 2:
                printf("Enter the Account No. : ");
                scanf("%llu" , &mn );

                delACC( mn );

                printf("\n\n:::: PRESS 1 TO CONTINUE : ");
                scanf("%d", &cnt );
                if ( cnt != 1 ){
                    printf("\n\n***** MENU EXIT *****\n\n");
                    system("color 0f");
                    return;
                }
                break;
            case 3:
                
                printf("Enter the Account No. : ");
                scanf("%llu" , &mn );

                printf("\n\n***** Personal Data *****\n");
                // showPersonalData( mn );
                showData( mn , 2 );
                printf("\n***** Account Data  *****\n");
                // showACCData( mn );
                showData( mn , 1 );

                printf("\n\n:::: PRESS 1 TO CONTINUE : ");
                scanf("%d", &cnt );
                if ( cnt != 1 ){
                    printf("\n\n***** MENU EXIT *****\n\n");
                    system("color 0f");
                    return;
                }
                break;
            case 4:

                printf("Enter the Account No. : ");
                scanf("%llu" , &mn );
                fflush(stdin);

                editAcc(mn);

                printf("\n\n:::: PRESS 1 TO CONTINUE : ");
                scanf("%d", &cnt );
                if ( cnt != 1 ){
                    printf("\n\n***** MENU EXIT *****\n\n");
                    system("color 0f");
                    return;
                }
                break;
            case 5:

                printf("Enter the From Account No. : ");
                scanf("%llu" , &mn1 );
                printf("Enter the To   Account No. : ");
                scanf("%llu" , &mn2 );
                printf("Enter the Amount : ");
                scanf("%lu" , &mn3 );

                if (transferMoney( mn1 , mn2, mn3 ) < 0 )
                    printf("\n***** TRANSACTION CANCELLED *****\n");
                else
                    printf("\n***** TRANSACTION SUCCESS *****\n");

                printf("\n***** FROM Account Data  *****\n");
                // showACCData( mn1 );
                showData( mn1 , 1 );

                printf("\n***** TO Account Data  *****\n");
                // showACCData( mn2 );
                showData( mn2 , 1 );

                printf("\n\n:::: PRESS 1 TO CONTINUE : ");
                scanf("%d", &cnt );
                if ( cnt != 1 ){
                    printf("\n\n***** MENU EXIT *****\n\n");
                    system("color 0f");
                    return;
                }
                break;
            case 6:
                printf("Enter the Account No. : ");
                scanf("%llu" , &mn2 );
                printf("Enter the Amount : ");
                scanf("%lu" , &mn3 );                


                if (  deposit_withdraw_Money( mn2 , mn3 , 1 ) < 0 )
                    printf("\n***** DEPOSTION CANCELLED *****\n");
                else{
                    printf("\n***** DEPOSTION SUCCESS *****\n");

                    printf("\n***** Account Data  *****\n");
                    showData( mn2 , 1 );
                }
                printf("\n\n:::: PRESS 1 TO CONTINUE : ");
                scanf("%d", &cnt );
                if ( cnt != 1 ){
                    printf("\n\n***** MENU EXIT *****\n\n");
                    system("color 0f");
                    return;
                }
                break;
            case 7:

                printf("Enter the Account No. : ");
                scanf("%llu" , &mn2 );
                printf("Enter the Amount : ");
                scanf("%lu" , &mn3 ); 
                
                if (  deposit_withdraw_Money( mn2 , mn3 , 2 ) < 0 )
                    printf("\n***** WITHDRAWAL CANCELLED *****\n");
                else{
                    printf("\n***** WITHDRAWAL SUCCESS *****\n");

                    printf("\n***** Account Data  *****\n");
                    showData( mn2 , 1 );
                }
                printf("\n\n:::: PRESS 1 TO CONTINUE : ");
                scanf("%d", &cnt );
                if ( cnt != 1 ){
                    printf("\n\n***** MENU EXIT *****\n\n");
                    system("color 0f");
                    return;
                }
                break;
            case 0:
                printf("\n\n***** MENU EXIT *****\n\n");
                system("color 0f");
                return;
                break;
            
            default:
                printf("\n***** Invalid Command *****\n");
                system("color 0f");
                return;
                break;
        }

    }


}

void editAcc(unsigned long long int acc_no){


    FILE * fptr3 = fopen(personalDataFile , "r");
    int lenn = 0;
    while (1){
        char c = fgetc( fptr3 );
        if( feof( fptr3 )) 
            break;
        else
            lenn++;
    }

    fclose( fptr3 );

    if ( lenn <= 0 ){
        printf("\n\n***** DB IS EMPTY *****\n\n");
        return;
    }

    FILE * fptr = fopen(personalDataFile , "r");

    char c;
    int foundFlag = 0;
    charList * dataHEAD = NULL , * dataLAST = NULL;

    unsigned long long int temp1;

    while (1){
        c = fgetc( fptr );
        if( feof( fptr )) break;
        charList * strrHEAD = NULL , * strrLAST = NULL;

        while(1) {
    
            charList * newNode = (charList *)malloc( sizeof(charList) );
            newNode->val = c;
            newNode->next = NULL;

            if ( strrHEAD == NULL ){
                strrHEAD = strrLAST = newNode;
            }
            else{
                strrLAST->next = newNode ; 
                strrLAST = newNode;
            }
                        
            c = fgetc( fptr );
            if( c == '\n' ){
                break;
            }
        }
        charList * newNode = (charList *)malloc( sizeof(charList) );
        newNode->val = '\n';
        newNode->next = NULL;

        if ( strrHEAD == NULL )
            strrHEAD = strrLAST = newNode;
        else{
            strrLAST->next = newNode;
            strrLAST = newNode;
        }

        custPersonalData * cpd = (custPersonalData *)malloc( sizeof(custPersonalData) );
        cpd->acc_no = 0;
        unsigned long long int mul = 100000000000 ;
        charList * s = strrHEAD;  
        int i = 0;
        for ( ; s->val != '|' ; i++ , s = s->next ){
            cpd->acc_no += (( s->val -48)*mul)     ;
            mul /= 10;
        }
        i++;

        if ( cpd->acc_no != acc_no ){

            s = strrHEAD; 
            for (; s != NULL  ; s = s->next ){

                charList * newNode = (charList *)malloc( sizeof(charList) );
                newNode->val = s->val;
                newNode->next = NULL;

                if ( dataHEAD == NULL )
                    dataHEAD = dataLAST = newNode;
                else{
                    dataLAST->next = newNode;
                    dataLAST = newNode;
                }
        
            }   

        }
        else{            
            temp1 = cpd->acc_no;
            foundFlag = 1;
        }
        
    }

    fclose(fptr);

    if ( foundFlag ==0 ){
        printf("\n***** ACCOUNT NOT FOUND *****\n");
        return;
    }
    
    custPersonalData * cppd = (custPersonalData *)malloc( sizeof( custPersonalData ) );
    cppd = getCustPersonalData();
    cppd->acc_no = temp1;

    // printf("%llu %s %d %s %s %lu\n" , cppd->acc_no , cppd->name , cppd->age , cppd->DOB , cppd->address , cppd->contact_no );

    FILE * fptr1 = fopen(personalDataFile , "w+");

    charList * s = dataHEAD;
    while ( s != NULL ){
        // printf("%c" , s->val );
        fputc( s->val , fptr1 );
        s = s->next;
    }

    fclose( fptr1 );

    *(cppd->name + (strlen(cppd->name)-1) ) = '\0';
    *(cppd->DOB + (strlen(cppd->DOB)-1) ) = '\0';
    *(cppd->address + (strlen(cppd->address)-1) ) = '\0';

    FILE * fptr2 = fopen(personalDataFile , "a");
    fprintf( fptr2, "%llu|%s|%d|%s|%s|%llu\n" , cppd->acc_no , cppd->name , cppd->age , cppd->DOB , cppd->address , cppd->contact_no );
    fclose( fptr2 );

    printf("\n*****  ALTERED DATA *****\n");
    // showPersonalData( temp1 );
    showData( temp1 , 2 );
}

void delACC( unsigned long long int acc_no ){


    FILE * fptr3 = fopen(personalDataFile , "r");
    int lenn = 0;
    while (1){
        char c = fgetc( fptr3 );
        if( feof( fptr3 )) 
            break;
        else
            lenn++;
    }

    fclose( fptr3 );

    if ( lenn <= 0 ){
        printf("\n\n***** DB IS EMPTY *****\n\n");
        return;
    }

    

    FILE * fptr = fopen(personalDataFile , "r");

    char c;
    charList * data1HEAD = NULL , * data1LAST = NULL; 
    int foundFlag = 0;

    while (1){
        c = fgetc( fptr );
        if( feof( fptr )) break;

        charList * strrHEAD = NULL , *strrLAST = NULL ;
        while(1) {

            charList * newNode = (charList *)malloc( sizeof(charList) );
            newNode->val = c;
            newNode->next = NULL;
            if ( strrHEAD == NULL )
                strrHEAD = strrLAST = newNode;
            else{
                strrLAST->next = newNode;
                strrLAST = newNode;
            }
            
            c = fgetc( fptr );
            if( c == '\n' )
                break;
        }

        charList * newNode = (charList *)malloc( sizeof(charList) );
        newNode->val = '\n';
        newNode->next = NULL;
        if ( strrHEAD == NULL )
            strrHEAD = strrLAST = newNode;
        else{
            strrLAST->next = newNode;
            strrLAST = newNode;
        }

        custPersonalData * cpd = (custPersonalData *)malloc( sizeof(custPersonalData) );
        cpd->acc_no = 0;
        unsigned long long int mul = 100000000000 ;
        int i = 0;

        charList * s = strrHEAD;
        for ( ; s->val != '|' ; i++ , s = s->next ){
            cpd->acc_no += (( s->val -48)*mul)     ;
            mul /= 10;
        }
        i++;

        s = strrHEAD;

        if ( cpd->acc_no != acc_no ){
 
            for (int i = 0;  s != NULL  ; i++ , s = s->next ){

                charList * newNode = (charList *)malloc( sizeof(charList) );
                newNode->val = s->val;
                newNode->next = NULL;

                if ( data1HEAD == NULL ){
                    data1HEAD = data1LAST = newNode;
                }
                else{
                    data1LAST->next = newNode;
                    data1LAST = newNode;
                }
        
            }         
        }
        else{
            foundFlag = 1;
        }
        
    }
    fclose(fptr);

    if ( foundFlag == 0 ){
        printf("\n***** ACCOUNT NOT FOUND *****\n");
        return ; 
    }
    
    
    FILE * fptr1 = fopen(personalDataFile , "w+");

    charList * s = data1HEAD;
    while ( s != NULL ){
        fputc( s->val , fptr1 );
        s = s->next;
    }
    fclose( fptr1 );
   

    delACCDE(acc_no);
}

void delACCDE( unsigned long long int acc_no ){

    FILE * fptr3 = fopen(accountDataFile , "r");
    int lenn = 0;
    while (1){
        char c = fgetc( fptr3 );
        if( feof( fptr3 )) 
            break;
        else
            lenn++;
    }

    fclose( fptr3 );

    if ( lenn <= 0 ){
        printf("\n\n***** DB IS EMPTY *****\n\n");
        return;
    }

    FILE * fptr = fopen(accountDataFile , "r");

    char c;
    charList * data1HEAD = NULL , * data1LAST = NULL; 
    int foundFlag = 0;

    while (1){
        c = fgetc( fptr );
        if( feof( fptr )) break;

        charList * strrHEAD = NULL , *strrLAST = NULL ;

        while(1) {
            

            charList * newNode = (charList *)malloc( sizeof(charList) );
            newNode->val = c;
            newNode->next = NULL;

            if ( strrHEAD == NULL )
                strrHEAD = strrLAST = newNode;
            else{
                strrLAST->next = newNode;
                strrLAST = newNode;
            }
            
            c = fgetc( fptr );
            if( c == '\n' ){
                break;
            }
        }

        charList * newNode = (charList *)malloc( sizeof(charList) );
        newNode->val = '\n';
        newNode->next = NULL;

        if ( strrHEAD == NULL ){
            strrHEAD = strrLAST = newNode;
        }
        else{
            strrLAST->next = newNode;
            strrLAST = newNode;
        }

        custAccountData * cpd = (custAccountData *)malloc( sizeof(custAccountData) );
        cpd->acc_no = 0;
        unsigned long long int mul = 100000000000 ;
        int i = 0;
        charList * s = strrHEAD;
        for ( ; s->val != '|' ; i++ , s = s->next ){
            cpd->acc_no += (( s->val -48)*mul)     ;
            mul /= 10;
        }
        i++;


        if ( cpd->acc_no != acc_no ){
            
            charList * s = strrHEAD;
            for (int i = 0;  s != NULL  ; i++ , s = s->next ){

                charList * newNode = (charList *)malloc( sizeof(charList) );
                newNode->val = s->val;
                newNode->next = NULL;

                if ( data1HEAD == NULL ){
                    data1HEAD = data1LAST = newNode;
                }
                else{
                    data1LAST->next = newNode;
                    data1LAST = newNode;
                }
        
            } 

        }
        else{
            foundFlag = 1;
        }
        
    }
    fclose(fptr);
        
    if ( foundFlag  == 0 ){
        printf("\n***** ACCOUNT NOT FOUND *****\n");
        return ;
    }
    

    FILE * fptr1 = fopen(accountDataFile , "w+");

    charList * s = data1HEAD;
    while ( s != NULL ){
        // printf("%c" , s->val );
        fputc( s->val , fptr1 );
        s = s->next;
    }
    fclose(fptr1);

    if ( foundFlag == 1 ){
        printf("\n***** ACCOUNT DELETED *****\n");
        return ; 
    }
}

void createDB(){

    int flg1 = 0;
    int flg2 = 0;

    FILE * fpp = fopen( personalDataFile , "r");
    if ( fpp != NULL )
        flg1 = 1;    
    
    fclose(fpp);

    FILE * fpa = fopen( accountDataFile , "r");
    if ( fpa != NULL )
        flg2 = 1;
    fclose(fpa);

    if ( flg1 == 0 ){
        FILE * fpp1 = fopen(personalDataFile , "w+");
        fclose(fpp1);
    }
    
    if ( flg2 == 0 ){
        FILE * fpa1 = fopen(accountDataFile , "w+");
        fclose(fpa1);
    }

}

unsigned long long int accountNoGenerator( custPersonalData * cpd , custAccountData * cad ){

    char accNo[13] = "";
    int p = 0;

    int i = *(cpd->name+0)-32;

    accNo[0] = i/10+48;
    accNo[1] = i%10+48;

    i = *(cpd->name+1)-32;

    accNo[2] = i/10+48;
    accNo[3] = i%10+48;

    p = 4;

    accNo[p] = *(cpd->DOB+0);p++;
    accNo[p] = *(cpd->DOB+1);p++;
    accNo[p] = *(cad->DOJ+0);p++;
    accNo[p] = *(cad->DOJ+1);p++;

    i = *(cad->branch+0)-32;

    accNo[8] = i/10+48;
    accNo[9] = i%10+48;

    i = *(cad->branch+1)-32;

    accNo[10] = i/10+48;   
    accNo[11] = i%10+48;   

    p = 4; 

    unsigned long long int mul = 100000000000 ;
    unsigned long long int result = 0;

    for (int i = 0; i < 12 ; i++){
        result += ((accNo[i]-48)*mul);
        mul /= 10; 
    }

    return result;
}

void createAcc(){

    custPersonalData * cpd = (custPersonalData *)malloc( sizeof( custPersonalData ) );
    custAccountData * cad = (custAccountData *)malloc( sizeof( custAccountData ) );

    cpd = getCustPersonalData();
    cad = getCustAccountData();

    cpd->acc_no = cad->acc_no = accountNoGenerator( cpd ,cad );

    *(cpd->name + (strlen(cpd->name)-1) ) = '\0';
    *(cpd->DOB + (strlen(cpd->DOB)-1) ) = '\0';
    *(cpd->address + (strlen(cpd->address)-1) ) = '\0';
    *(cad->DOJ + (strlen(cad->DOJ)-1) ) = '\0';
    *(cad->branch + (strlen(cad->branch)-1) ) = '\0';

    FILE * fptr , * fpa ;

    fptr = fopen(personalDataFile , "a");
    fprintf( fptr , "%llu|%s|%d|%s|%s|%llu\n" , cpd->acc_no , cpd->name , cpd->age , cpd->DOB , cpd->address , cpd->contact_no );
    fclose(fptr);

    fpa = fopen(accountDataFile , "a");
    fprintf( fpa , "%llu|%llu|%s|%s\n", cad->acc_no , cad->accBalance, cad->DOJ ,cad->branch );
    fclose(fpa);

    printf("\n\n***** ACCOUNT CREATED WITH ACCOUNT NUMBER : %llu  *****\n\n" , cpd->acc_no );
    
    // printf("%llu|%s|%d|%s|%s|%d\n" , cpd->acc_no , cpd->name , cpd->age , cpd->DOB , cpd->address , cpd->contact_no );
    // printf("%llu|%llu|%s|%s\n", cad->acc_no , cad->accBalance, cad->DOJ ,cad->branch);
}

custPersonalData * getCustPersonalData(){

    custPersonalData * cpd = (custPersonalData *) malloc( sizeof(custPersonalData) ) ; 

    cpd->name = (char * )malloc( sizeof(char)*1024 );
    cpd->DOB = (char * )malloc( sizeof(char)*1024 );
    cpd->address = (char * )malloc( sizeof(char)*1024 );

    printf("Enter the Name : ");
    fgets( cpd->name , sizeof(cpd->name)*1024 , stdin);

    printf("Enter the address : ");

    fflush(stdin);
    fgets( cpd->address , sizeof(cpd->address)*1024, stdin); 
    printf("Enter the DOB(date of birth) : ");

    fflush(stdin);
    fgets( cpd->DOB , sizeof(cpd->DOB)*1024, stdin); 

    fflush(stdin);
    printf("Enter the age : ");
    scanf("%d", &cpd->age );  
    
    printf("Enter the contact no : ");
    scanf("%llu", &cpd->contact_no );   
    fflush(stdin);

    return cpd;
}

custAccountData * getCustAccountData(){

    custAccountData * cad = (custAccountData *)malloc( sizeof(custAccountData) ); 

    cad->branch = (char *)malloc( sizeof(char)*1024 );
    cad->DOJ = (char *)malloc( sizeof(char)*1024 );

    printf("Enter the Branch : ");
    fflush(stdin);
    fgets( cad->branch , sizeof(cad->branch)*1024, stdin);
    fflush(stdin);
    cad->accBalance = 0;
    printf("Enter the DOJ(date of joining) : ");
    fgets( cad->DOJ , sizeof(cad->DOJ)*1024, stdin);
    fflush(stdin);

    return cad;
}

void showData( unsigned long long int acc_no , int mode ){

    FILE * fptr3 = fopen(accountDataFile , "r");
    int lenn = 0;
    while ( lenn <= 150 ){
        char c = fgetc( fptr3 );
        if( feof( fptr3 )) 
            break;
        else
            lenn++;
    }

    fclose( fptr3 );

    if ( lenn <= 0 ){
        printf("\n\n***** DB IS EMPTY *****\n\n");
        return;
    }

    FILE * fptr;

    if ( mode == 1 )
        fptr = fopen(accountDataFile , "r");
    else if ( mode == 2 )
        fptr = fopen(personalDataFile , "r");
    

    int foundFlag = 0;
    char c1;
    while (1){
        c1 = fgetc( fptr );
        if( feof( fptr )) break;
        charList * strHEAD = NULL , * strLAST = NULL ;

        while(1) {

            charList * newNode = (charList *)malloc( sizeof(charList) );
            newNode->val = c1;
            newNode->next = NULL;
            if ( strHEAD == NULL ){
                strHEAD = strLAST = newNode;
            }
            else{
                strLAST->next = newNode;
                strLAST = newNode;
            }
            
            c1 = fgetc( fptr );
            if( c1 == '\n' ){
                break;
            }
        }

        charList * newNode = (charList *)malloc( sizeof(charList) );
        newNode->val = '\n';
        newNode->next = NULL;
        if ( strHEAD == NULL ){
            strHEAD = strLAST = newNode;
        }
        else{
            strLAST->next = newNode;
            strLAST = newNode;
        }    


        unsigned long long int accNo = 0;
        unsigned long long int mul = 100000000000 ;
        int i = 0;
        charList * s = strHEAD;
        for ( ;  s->val != '|' ; i++ , s = s->next ){
            accNo += (( s->val -48)*mul)     ;
            mul /= 10;
        }
        i++;

        if ( accNo == acc_no ){

            if ( mode == 1 ){

                s = strHEAD;

                printf("Account Number  : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }       
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("Account Balance : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }       
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("Date of Join    : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }       
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("Branch          : ");
                while ( s != NULL ){

                    if(s->val == '\n' ){
                        s = s->next;
                        break;         
                    }       
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");

            }
            else if ( mode == 2 ){

                s = strHEAD;
                
                printf("Account Number : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }       
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("Name           : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }       
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("Age            : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }               
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("Date of Birth  : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }                   
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("Address        : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }                  
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
                printf("\n");
                printf("contact No     : ");
                while ( s != NULL ){

                    if(s->val == '|' ){
                        s = s->next;
                        break;         
                    }                
                    else
                        printf("%c" , s->val );
                    s = s->next;
                }
            }
            
            foundFlag = 1;
            break;
        }


    }
    
    fclose(fptr);  
    if ( foundFlag ==0 ){
        printf("\n***** ACCOUNT NOT FOUND *****\n");
        return;
    }
     
}

int transferMoney(unsigned long long int from_acc_no , unsigned long long int to_acc_no ,unsigned long int moneyToBeDrawn){

    FILE * fptr3 = fopen(accountDataFile , "r");
    int lenn = 0;
    while (1){
        char c = fgetc( fptr3 );
        if( feof( fptr3 )) 
            break;
        else
            lenn++;
    }

    fclose( fptr3 );

    if ( lenn <= 0 ){
        printf("\n\n***** DB IS EMPTY *****\n\n");
        return -1;
    }

    int l = deposit_withdraw_Money(from_acc_no , moneyToBeDrawn , 2 );
    if ( l < 0 )
        return -1;
    
    l = deposit_withdraw_Money(to_acc_no , moneyToBeDrawn , 1 );
    if ( l < 0 )
        return -1;
}

int deposit_withdraw_Money(unsigned long long int acc_no ,unsigned long int amountMoney , int mode ){

    FILE * fptr3 = fopen(accountDataFile , "r");
    int lenn = 0;
    while (1){
        char c = fgetc( fptr3 );
        if( feof( fptr3 )) 
            break;
        else
            lenn++;
    }

    fclose( fptr3 );

    if ( lenn <= 0 ){
        printf("\n\n***** DB IS EMPTY *****\n\n");
        return -1;
    }

    FILE * fptr = fopen(accountDataFile , "r");


    adNode * head = NULL , * last = NULL ;
    custAccountData * tobeChanged = (custAccountData *)malloc( sizeof(custAccountData) );

    char c;

    int foundFlag = 0;
    while (1){
        c = fgetc( fptr );
        if( feof( fptr )) break;

        charList * strrHEAD = NULL , *strrLAST = NULL ;
        while(1) {

            charList * newNode = (charList *)malloc( sizeof(charList) );
            newNode->val = c;
            newNode->next = NULL;
            
            if ( strrHEAD == NULL )
                strrHEAD = strrLAST = newNode;
            else{
                strrLAST->next = newNode;
                strrLAST = newNode;
            }
            
            c = fgetc( fptr );
            if( c == '\n' )
                break;
        }

        charList * newNode = (charList *)malloc( sizeof(charList) );
        newNode->val = '\n';
        newNode->next = NULL;
        
        if ( strrHEAD == NULL )
            strrHEAD = strrLAST = newNode;
        else{
            strrLAST->next = newNode;
            strrLAST = newNode;
        }
        

        custAccountData * cacd = (custAccountData *)malloc( sizeof(custAccountData) );
        cacd->acc_no = 0;
        unsigned long long int mul = 100000000000 ;
        int i = 0;
        charList * s = strrHEAD;
        for ( ; s->val != '|' ; i++ , s = s->next ){
            cacd->acc_no += (( s->val -48)*mul)     ;
            mul /= 10;
        }
        s = s->next;

            int j;
            char * bal = (char *)malloc( sizeof(char) );
            j = 0;
            mul = 1;
            for ( ; s->val != '|' ; i++ , j++ , s = s->next ){
                bal = (char *)realloc( bal , sizeof(char) * (1+j) );
                *(bal+j) = s->val;
                mul *= 10;
            }
            *(bal + j) = '\0';

            mul /= 10;
            cacd->accBalance = 0;

            for (int k = 0 ; *(bal+k) != '\0' ; k++){
                cacd->accBalance += ((*(bal+k)-48)*mul);
                mul /= 10;
            } 
            s = s->next;    

            cacd->DOJ = (char *)malloc( sizeof(char) );
            j = 0;
            for (; s->val != '|' ; i++ , j++ , s = s->next ){
                cacd->DOJ = realloc( cacd->DOJ , sizeof(char)*(j+1) );
                *(cacd->DOJ+j) = s->val ;
            }
            *(cacd->DOJ+j)= '\0';
            s = s->next;

            cacd->branch = (char *)malloc( sizeof(char) );
            j = 0;
            for (; s->val != '\n' ; i++ , j++ , s = s->next ){
                cacd->branch = realloc( cacd->branch , sizeof(char)*(j+1) );
                *(cacd->branch+j) = s->val ;
            }
            *(cacd->branch+j)= '\0';



        if ( cacd->acc_no != acc_no ){


            adNode * newNode = (adNode *)malloc( sizeof(adNode) ); 
            newNode->data = cacd;

            if (head == NULL){
                newNode->next = NULL;
                last = head = newNode;
            }
            else{
                newNode->next = NULL;
                last->next = newNode;
                last = newNode;
            }         


        }
        else{
            tobeChanged = cacd;
            foundFlag = 1;
        }
    }

    fclose(fptr);

    if ( foundFlag == 0  ){
        printf("\n***** ACCOUNT NOT FOUND *****\n");
        return -1;
    }

    if( mode == 1 ){

        // Deposit

        tobeChanged->accBalance = tobeChanged->accBalance + (long int) amountMoney;

        FILE * fpa = fopen(accountDataFile , "w+");
        fprintf( fpa , "%llu|%llu|%s|%s\n", tobeChanged->acc_no , tobeChanged->accBalance, tobeChanged->DOJ ,tobeChanged->branch );
        fclose(fpa);    


        FILE * fptr = fopen(accountDataFile , "a");
        adNode * s = head;
        while ( s != NULL ){
            fprintf( fptr , "%llu|%llu|%s|%s\n", (s->data)->acc_no , (s->data)->accBalance, (s->data)->DOJ , (s->data)->branch );
            // printf("%llu|%llu|%s|%s\n", (s->data)->acc_no , (s->data)->accBalance, (s->data)->DOJ , (s->data)->branch);
            s = s->next;
        }
        fclose(fptr);

        return 1;
    }
    else if ( mode == 2 ) {

        // withdraw

        if (  (tobeChanged->accBalance) < (long int) amountMoney  ){
            printf("\n***** NOT ENOUGH MONEY *****\n");
            return -1;
        }
        else{

            tobeChanged->accBalance = tobeChanged->accBalance - (long int) amountMoney;

            FILE * fpa = fopen(accountDataFile , "w+");
            fprintf( fpa , "%llu|%llu|%s|%s\n", tobeChanged->acc_no , tobeChanged->accBalance, tobeChanged->DOJ ,tobeChanged->branch );
            fclose(fpa);    

            FILE * fptr = fopen(accountDataFile , "a");
            adNode * s = head;
            while ( s != NULL ){
                fprintf( fptr , "%llu|%llu|%s|%s\n", (s->data)->acc_no , (s->data)->accBalance, (s->data)->DOJ , (s->data)->branch );
                // printf("%llu|%llu|%s|%s\n", (s->data)->acc_no , (s->data)->accBalance, (s->data)->DOJ , (s->data)->branch);
                s = s->next;
            }
            fclose(fptr);  
        }
        return 1;
        
    }

}
