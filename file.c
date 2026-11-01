#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp;
    fp = fopen("contacts.txt","w");
    if(fp==NULL){
        printf("unable to load file!");
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fp,"%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.txt", "r"); // Make sure this matches your save filename!
    if (fp == NULL) {
        // If the file doesn't exist yet, it's just the first time running—totally fine!
        return; 
    }

    // Read line by line until the file ends
    while (fscanf(fp, "%s %s %s", addressBook->contacts[addressBook->contactCount].name,
                                  addressBook->contacts[addressBook->contactCount].phone,
                                  addressBook->contacts[addressBook->contactCount].email) == 3) {
        addressBook->contactCount++;
    }

    fclose(fp);
}
