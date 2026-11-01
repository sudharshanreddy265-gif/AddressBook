#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount==0){
        printf("Sorry No contacts to display\n");
        return;
    }
    printf("The Total contacts are %d\n",addressBook->contactCount);
    printf("---------------------------------------------------\n");
    printf("%-5s %-15s %-15s %-25s\n","S.No","Name","Phone","Email");
    printf("---------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%-5d ",i+1);
        printf("%-15s ",addressBook->contacts[i].name);
        printf("%-15s ",addressBook->contacts[i].phone);
        printf("%-25s ",addressBook->contacts[i].email);
        printf("\n");
    }
    printf("---------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    
    loadContactsFromFile(addressBook);

}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); 
    // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook->contactCount==100){
        printf("Address book is full!");
        return;
    }
    getchar();
    //giving 3 attempts to user for invalid names
    int validname = 0;
    for(int i=3;i>0;i--){
        printf("enter a name: ");
        if(fgets(addressBook->contacts[addressBook->contactCount].name,50,stdin)!=NULL){
            addressBook->contacts[addressBook->contactCount].name[strcspn(addressBook->contacts[addressBook->contactCount].name,"\n")]='\0';

            if(addressBook->contacts[addressBook->contactCount].name[0]>='0' && addressBook->contacts[addressBook->contactCount].name[0]<='9' ){
                printf("Invalid name! Name cannot start with a number. You have %d attempt(s) left.\n", i - 1);
            }
            else {
                // If it passes the checks, it's a valid name!
                validname = 1;
                break; // Exit the loop and move on to phone number
            }
        }
    }
    //checking user used all 3 attempts
    if (!validname) {
        printf("Too many invalid attempts. Returning to main menu.\n");
        return;
    }
    


    //phone number checking validiations
    int valid = 0;
    char temp[20];

    for(int i=3;i>0;i--){
        printf("enter phone number with (10 digits and starting should be 6 and 9): ");
        if(fgets(temp,sizeof(temp),stdin)!=NULL){
            temp[strcspn(temp,"\n")] = '\0';

            //checking only 10 digits are not
            if(strlen(temp)!=10){
                printf("its invalid more than 10 digits you have only %d attempts left\n",i-1);
                continue;
            }
            //checking uniquenes of a number
            int duplicate = 0;
            for(int j=0;j<addressBook->contactCount;j++){
                if(strcmp(temp,addressBook->contacts[j].phone)==0){
                    duplicate = 1;
                    break;
                }
            }
            if(duplicate){
                printf("this phone number is already exists in contacts!! youhave %d limits\n",i-1);
                continue;
            }

            //checking all are numbers are not
            int allnum = 1;
            for(int k=0;k<10;k++){
                if(temp[k]<'0' || temp[k]>'9'){
                    allnum = 0;
                    break;
                }
            }
            if(!allnum){
                printf("all are should be numbers only you have only %d attempts\n",i-1);
                continue;
            }

            //starting should be 6 to 9 only
            
            if(temp[0]<'6' || temp[0]>'9'){
                printf("starting number should be 6 to 9 only you have %d attempts\n",i-1);
                continue;

            }
            strcpy(addressBook->contacts[addressBook->contactCount].phone,temp);
            valid = 1;
            break;
        }
        
    }
    if(!valid){
        printf("you have raeched 3 attempts limit");
        return;
    }
    
    
    
    //email checking constarints
    int validemail = 0;
    char temp1[50];
    for(int i=3;i>0;i--){
        printf("enter a email with lowercase start: ");
        if(fgets(temp1,sizeof(temp1),stdin)!=NULL){
            temp1[strcspn(temp1,"\n")]='\0';
        }
        //checking first character
        if(temp1[0]<'a' || temp1[0]>'z'){
            printf("email should start with small letters .you have only %d limits",i-1);
            continue;
        }
        //checking @ count
        int count = 0;
        int index = -1;
        for(int i=0;temp1[i]!='\0';i++){
            if(temp1[i]=='@'){
                count++;
                index = i;
            }
        }
        if(count!=1){
            printf("@ should be only once.you have only attempts %d",i-1);
            continue;
        }
            //checking for .com occurence
            char *comPtr = strstr(temp1, ".com");
            if (comPtr == NULL) {
                printf("Invalid! Email must contain '.com'. You have %d attempt(s) left.\n", i - 1);
                continue;
            }

            // Make sure '.com' appears only once 
            if (strstr(comPtr + 4, ".com") != NULL) {
                printf("Invalid! '.com' can appear only once. You have %d attempt(s) left.\n", i - 1);
                continue;
            }
            
            if (comPtr < temp1 + index) {
                printf("Invalid! '.com' cannot appear before '@'. You have %d attempt(s) left.\n", i - 1);
                continue;
            }

            //No characters are allowed after .com
            if (strlen(comPtr) != 4) {
                printf("Invalid! No characters are allowed after '.com'. You have %d attempt(s) left.\n", i - 1);
                continue;
            }
            //checking only 5 letters between @ and .
            int count1 =0;
            for(int j = index+1;temp1[j]!='.';j++){
                count1++;
            }
            if(count1>5){
                printf("there must be only 5 letters between @ and .\n");
                continue;
            }
            int dupemail = 0;
            for(int k = 0;k<addressBook->contactCount;k++){
                if(strcmp(temp1,addressBook->contacts[k].email)==0){
                    dupemail = 1;
                    break;
                }
            }
            if(dupemail){
                printf("Entered email already exists!! you have %d limits\n",i-1);
                continue;
            }
            //if.com appers before @ is invalid
            
            //if above all cases passed then
            strcpy(addressBook->contacts[addressBook->contactCount].email,temp1);
            validemail = 1;
            break;
    }
    if(!validemail){
        printf("You have reached 3 attempts limit for email. Returning to main menu.\n");
        return;
    }
    addressBook->contactCount++;
    printf("contact was suucessfully added\n");


    
}

void searchContact(AddressBook *addressBook) 
{   
    int option;
    /* Define the logic for search */
    do{
        printf("1.Name\n");
        printf("2.Phoneno\n");
        printf("3.Email\n");
        printf("4.Exit\n");
        printf("enter a option u want to search: ");
        scanf("%d",&option);
        while(getchar()!='\n');
        switch(option){
            case 1:{
                char temp[50];
                int validname = 0;
                for(int i=3;i>0;i--){
                    printf("Enter a name: ");
                    if(fgets(temp, sizeof(temp), stdin) != NULL) {
                        temp[strcspn(temp, "\n")] = '\0';}
                    if(isdigit(temp[0])){
                        printf("Name can't start with digits,you have %d limits",i-1);
                        continue;
                    }else{
                        validname = 1;
                        break;
                    }
                }
                if(!validname){
                    printf("You have reached 3 attempts\n");
                    return;
                }
                int found = 0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if(strcmp(temp,addressBook->contacts[i].name)==0){
                        found=1;
                    }
                }
                if(!found){
                    printf("No contact was found with that name\n");
                    break;
                }
                if(found){
                    printf("---------------------------------------------------\n");
                    printf("%-5s %-15s %-15s %-25s\n","S.No","Name","Phone","Email");
                    printf("---------------------------------------------------\n");
                    for(int i=0;i<addressBook->contactCount;i++){
                        if(strcmp(temp,addressBook->contacts[i].name)==0){
                            printf("%-5d %-15s %-15s %-25s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            found = 1;
                        }
                    }
                }
            break;
            }
            case 2:{
                int validphone=0;
                char ph[20];
                for(int i=3;i>0;i--){
                    printf("enter a PH number: ");
                    if(fgets(ph,sizeof(ph),stdin)!=NULL){
                        ph[strcspn(ph,"\n")]='\0';
                    }
                    int count = 0;
                    if(strlen(ph)!=10){
                        printf("Phone number should be 10 digits.You have %d limits\n",i-1);
                        continue;
                    }
                    if(ph[0]>='0' && ph[0]<'6'){
                        printf("ph no can't start with btwn 0 to 6,you have %d limits\n",i-1);
                        continue;
                    }
                    //checking all are numbers are not
                    int allnum = 1;
                    for(int k=0;k<10;k++){
                        if(ph[k]<'0' || ph[k]>'9'){
                            allnum = 0;
                            break;
                        }
                    }
                    if(!allnum){
                        printf("all are should be numbers only you have only %d attempts\n",i-1);
                        continue;
                    }
                    validphone = 1;
                    break;
                }
                if(!validphone){
                    printf("You have reached all attempts\n");
                    return;
                }
                int found = 0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if(strcmp(ph,addressBook->contacts[i].phone)==0){
                        found = 1;
                        break;
                    }
                }
                if(!found){
                    printf("No contact was found with that number\n");
                    break;
                }
                if(found){
                    printf("---------------------------------------------------\n");
                    printf("%-5s %-15s %-15s %-25s\n","S.No","Name","Phone","Email");
                    printf("---------------------------------------------------\n");
                    for(int i=0;i<addressBook->contactCount;i++){
                        if(strcmp(ph,addressBook->contacts[i].phone)==0){
                            printf("%-5d %-15s %-15s %-25s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        }
                    }
                }  
            break;   
            }
            case 3:{
                int validem = 0;
                char tempem[50];
                for(int i=3;i>0;i--){
                    printf("enter the email: ");
                    if(fgets(tempem,sizeof(tempem),stdin)!=NULL){
                        tempem[strcspn(tempem,"\n")]='\0';
                    }
                    if(tempem[0]>='A' && tempem[0]<='Z'){
                        printf("email should start only lower case you have %d limits",i-1);
                        continue;
                    }
                    int count = 0;
                    int index = -1;
                    for(int j=0;tempem[j]!='\0';j++){
                        if(tempem[j]=='@'){
                            count++;
                            index = j;
                        }
                    }
                    if(count!=1){
                        printf("Must be only one @ you have %d limits",i-1);
                        continue;
                    }
                    char *ptr = strstr(tempem,".com");
                    if(ptr==NULL){
                        printf("must should be .com in email you have %d limits",i-1);
                        continue;
                    }
                    if(strstr(ptr+4,".com")!=NULL){
                        printf("2 .com are present make must be only one .com you have %d limits",i-1);
                        continue;
                    }
                    //checking letters between @ and .com
                    int letcount = 0;
                    for(int k=index+1;tempem[k]!='.';k++){
                        letcount++;
                    }
                    if(letcount!=5){
                        printf("must be only 5 letters between @ and .com %d limits",i-1);
                        continue;
                    }
                    validem = 1;
                    break;
                    
                }
                if(!validem) {
                    printf("You have reached maximum attempts. Returning to search menu.\n");
                    return;
                }
                //searching in our records
                    int emfound = 0;
                    int emindex = -1;
                    for(int i=0;i<addressBook->contactCount;i++){
                        if(strcmp(tempem,addressBook->contacts[i].email)==0){
                            emfound = 1;
                            emindex = i;
                            break;
                        }
                    }
                    if(!emfound){
                        printf("No contact is found with that email\n");
        
                    }else{
                        printf("\n--------------------------------------------------------------------\n");
                        printf("%-5s %-15s %-15s %-25s\n", "S.No", "Name", "PhoneNo", "Email");
                        printf("--------------------------------------------------------------------\n");
                        printf("%-5d %-15s %-15s %-25s\n",emindex+1,addressBook->contacts[emindex].name,addressBook->contacts[emindex].phone,addressBook->contacts[emindex].email);
                    }
            break;
            }
            case 4:
                return;
        }
    }while(option!=4);   
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    if(addressBook->contactCount==0){
        printf("No contacts are there for edit\n");
        return;
    }                                   
	while(getchar()!='\n');
    char temp[50];
    printf("enter a name of contact to edit:");
    fgets(temp,sizeof(temp),stdin);
    temp[strcspn(temp,"\n")] = '\0';

    int foundin[100];
    int match = 0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(temp,addressBook->contacts[i].name)==0){
            if (match == 0) {
                printf("\n--------------------------------------------------------------------\n");
                printf("%-5s %-15s %-15s %-25s\n", "S.No", "Name", "PhoneNo", "Email");
                printf("--------------------------------------------------------------------\n");
            }
            printf("%-5d %-15s %-15s %-25s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            foundin[match++] = i;
        }
    }
    if(match==0){
        printf("No contact was found with that name\n");
        return;
    }
    printf("--------------------------------------------------------------------\n");
    //asking user to pick a serial No
    int sno;
    printf("choose a serial number u want to edit: ");
    scanf("%d",&sno);
    while(getchar()!='\n');

    //mapping to original array indexx to edit
    int reqindex = -1;
    for(int j=0;j<match;j++){
        if(foundin[j]+1==sno){
            reqindex = foundin[j];
            break;
        }
    }
    //edit sub menu
    int option;
    do{
        printf("1.edit name\n");
        printf("2.edit phoneno\n");
        printf("3.edit email\n");
        printf("4.exit\n");
        printf("choose one option u want to do : ");
        scanf("%d",&option);
        while(getchar()!='\n');
        switch(option){
            case 1:{
                char new[50];
                int validname = 0;
                for(int i=3;i>0;i--){
                    printf("enter a new name: ");
                    if(fgets(new,sizeof(new),stdin)!=NULL){
                        new[strcspn(new,"\n")] = '\0';
                    
                        if(isdigit(new[0])){
                            printf("starting letter should not contain digits,You have %d limits\n",i-1);
                            continue;
                        }
                        validname = 1;
                        break;
                
                    }
                }
                if(validname){
                    strcpy(addressBook->contacts[reqindex].name,new);
                    printf("Name updated Successfully\n");

                }
            break;
            }
            case 2:{
                char newph[20];
                int validph = 0;
                for(int i=3;i>0;i--){
                    printf("enter a new phone number: ");
                    if(fgets(newph,sizeof(newph),stdin)!=NULL){
                        newph[strcspn(newph,"\n")] = '\0';

                        if(strlen(newph)!=10){
                            printf("Phone number should be 10 digits,you have %d limits\n",i-1);
                            continue;
                        }
                        int digitcase = 0;
                        for(int j=0;j<10;j++){
                            if (!isdigit(newph[j])) {
                                digitcase = 1;
                            }
                        }
                        if(digitcase){
                            printf("phone number should contain only digits,you have %d limits\n",i-1);
                            continue;
                        }   
                        if(newph[0]<'6' || newph[0]>'9'){
                            printf("phoneno should start within 6 to 9 only ,you have %d limits\n",i-1);
                            continue;
                        }
                        int dup = 0;
                        for(int k=0;k<addressBook->contactCount;k++){
                            if(k==reqindex){
                                continue;
                            }
                            if(strcmp(newph,addressBook->contacts[k].phone)==0){
                                dup = 1;
                                break;
                            }
                        }
                        if(dup){
                            printf("Already this phone number exists,you have %d limits\n",i-1);
                            continue;

                        }
                        validph = 1;
                        break;
                    }

                }
                if(!validph){
                    printf("You have reached maximum attempts. Phone number not updated.\n");
                    break;
                }
                if(validph){
                    strcpy(addressBook->contacts[reqindex].phone,newph);
                    printf("Phone number updated succesfully\n");
                }
            break;
            }
            case 3:{
                char temp1[50];
                int validemail = 0;
                for(int i=3;i>0;i--){
                    printf("enter a email u wanto update:");
                    if(fgets(temp1,sizeof(temp1),stdin)!=NULL){
                        temp1[strcspn(temp1,"\n")] = '\0';
                    }
                    if(!isValidEmail(temp1)){
                        printf("Invalid email format! You have %d attempt(s) left.\n", i - 1);
                        continue;
                    }
                    //duplicate email
                    int dupemail = 0;
                    for(int j=0;j<addressBook->contactCount;j++){
                        if(j==reqindex){
                            continue;
                        }
                        if(strcmp(temp1,addressBook->contacts[j].email)==0){
                            dupemail = 1;
                            break;
                        }
                    }
                    if(dupemail){
                        printf("Entered email already exists! You have %d attempt(s) left.\n", i - 1);
                        continue;
                    }

                    strcpy(addressBook->contacts[reqindex].email,temp1);
                    printf("email updated successfully\n");
                    validemail = 1;
                    break;

                }
                if(!validemail){
                    printf("you have reached 3 attempts limit\n");

                }
                break;
            }
            case 4:{
                printf("exiting from this menu");
                break;
            }
            default:
                printf("invalid choice\n");
                
        }

    }while(option!= 4);
    

        
}

void deleteContact(AddressBook *addressBook)
{  
     /* Define the logic for deletecontact */
    if(addressBook->contactCount==0){
        printf("No contacts are availble to delete!");
        return;
    }
    char temp[50];
    printf("enter a name u want to delte: ");
    while(getchar()!='\n');
    if(fgets(temp,sizeof(temp),stdin)!=NULL){
        temp[strcspn(temp,"\n")] = '\0';
    }

    int foundind[100];
    int count = 0;
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(temp,addressBook->contacts[i].name)==0){
            if(count==0){
                printf("\n--------------------------------------------------------------------\n");
                printf("%-5s %-15s %-15s %-25s\n", "S.No", "Name", "PhoneNo", "Email");
                printf("--------------------------------------------------------------------\n");
            }
            printf("%-5d %-15s %-15s %-25s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            foundind[count++] = i;
        }
    }
    if(count==0){
        printf("No contact are found with that name!");
        return;
    }
    printf("--------------------------------------------------------------------\n");
    //exact s.no taking part
    int ind = -1;
    printf("enter a S.No u want to delete: ");
    scanf("%d",&ind);
    while(getchar()!='\n');
    int targetind = -1;
    for(int i=0;i<count;i++){
        if(foundind[i]+1==ind){
            targetind = foundind[i];
            break;
        }
    }
    if(targetind ==-1){
        printf("invalid serial number selected\n");
        return;
    }
    char confirm;
    printf("Are you sure you want to delete(y/n):");
    scanf("%c",&confirm);
    while(getchar()!='\n');

    if(confirm!='y' && confirm!='Y'){
        printf("deletion was cancelled");
        return;
    }

    for(int i=targetind;i<addressBook->contactCount-1;i++){
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("contact deleted successfully");
}

// Returns 1 if valid, 0 if all 3 attempts failed
// This function takes an email string and returns 1 if valid, or 0 if invalid
int isValidEmail(char *email) {
    // 1. Check first character
    if (email[0] < 'a' || email[0] > 'z') {
        return 0; 
    }
    
    // 2. Check @ count and index
    int count = 0;
    int index = -1;
    for (int j = 0; email[j] != '\0'; j++) {
        if (email[j] == '@') {
            count++;
            index = j;
        }
    }
    if (count != 1) return 0;
    
    // 3. Check for .com occurrence
    char *comPtr = strstr(email, ".com");
    if (comPtr == NULL) return 0;

    // 4. Make sure '.com' appears only once
    if (strstr(comPtr + 4, ".com") != NULL) return 0;
    
    // 5. Check letters between @ and .
    int count1 = 0;
    for (int j = index + 1; email[j] != '.'; j++) {
        count1++;
    }
    if (count1 > 5 || count1 == 0) return 0; // Ensures there are letters between them

    return 1; // If it passes everything, it's valid!
}
// Returns 1 if valid, 0 if invalid format
int isValidPhoneFormat(char *phone) {
    // 1. Check length (must be exactly 10 digits)
    if (strlen(phone) != 10) {
        return 0;
    }

    // 2. Check if all characters are digits
    for (int k = 0; k < 10; k++) {
        if (phone[k] < '0' || phone[k] > '9') {
            return 0;
        }
    }

    // 3. Check starting digit (must be 6 to 9)
    if (phone[0] < '6' || phone[0] > '9') {
        return 0;
    }

    return 1; // All format checks passed!
}