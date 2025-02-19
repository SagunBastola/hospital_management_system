#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

FILE *fp;

//structue part 
typedef struct patient{
    int id;
    char pname[20];
    int age;
    char gender[10] ,address[50] , symptomes[255] , checkby_doctor[20];
    char date[10];
    
    }patient;

    typedef struct doctor{
        int docid;
        char dname[20];
        char docaddress[50] ,specialized[50];
        char date[10];

    }doc;

    

    // sub function part

    void admit_patient(){
        

        patient p;
        time_t t;// time_t is a datatype in <time.h> 
        struct tm *time_info;
        char buffer[20];
        time(&t);// store time in the variable
        time_info = localtime(&t);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info); // localtime():Converts the time to the local time zone. converts the time in human readable formate
        //strftime: . converts the time in human readable formate
        
        strcpy(p.date, buffer);     // copy the string value of p.date into buffer


        fp = fopen("patient.txt", "ab");

        printf("Enter Patient id: ");
        scanf("%d", &p.id);
        while (getchar() != '\n');  // Clear input buffer
    
        printf("\nEnter Patient name: \t");    
        scanf("%[^\n]s", p.pname);
        while (getchar() != '\n');  // Clear input buffer

        printf("\nEnter Patient gender: \t");
        scanf("%[^\n]s", p.gender);
        while (getchar() != '\n');  // Clear input buffer

        printf("\nEnter Age:\t");
        scanf("%d", &p.age);
        while (getchar() != '\n');  // Clear input buffer
    
        printf("\nEnter Patient Address:\t ");
        scanf("%[^\n]s", p.address);
        while (getchar() != '\n');  // Clear input buffer
    
        printf("\nEnter Patient symptomes: \t");
        scanf("%[^\n]s", p.symptomes);
        while (getchar() != '\n');  // Clear input buffer

        printf("\nEnter Patient checkup doctor: \t");
        scanf("%[^\n]s", p.checkby_doctor);
        while (getchar() != '\n');  // Clear input buffer
    
        fwrite(&p, sizeof(p), 1, fp);
        fclose(fp);
        printf("\nPatient Added Successfully");



    }


    void discharge_patient() {
        patient p;
        int id, f = 0;
        system("cls");
        printf("<== Discharge Patient ==>\n\n");
        printf("Enter Patient id to discharge: ");
        scanf("%d", &id);
    
        FILE *fp, *ft;  // Declare file pointers locally
    
        fp = fopen("patient.txt", "rb");
    
        ft = fopen("temp.txt", "wb");
    
        while (fread(&p, sizeof(p), 1, fp) == 1) {
            if (id == p.id) {
                f = 1;  // Found the patient, but don't write it to new file
            } else {
                fwrite(&p, sizeof(p), 1, ft);
            }
        }
    
        fclose(fp);
        fclose(ft);
    
        if (f == 1) {
            remove("patient.txt");
            rename("temp.txt", "patient.txt");
            printf("\n\nPatient Discharged Successfully.\n");
        } else {
            printf("\n\nRecord Not Found!\n");
            remove("temp.txt");  // Cleanup temp file
        }
    }


void available_doctor() {
    doc d;
    FILE *fp;

    fp = fopen("doc_status.txt", "rb"); 
    
    printf("\n\t\t\t\tAvailable Doctor\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("\t\tID\t\t\t|\t\tName\t\t|\t\tEntry time|\n");
    printf("----------------------------------------------------------\n");
    while(fread(&d, sizeof(d),1,fp)!=0){
        printf("\t\t%d\t\t\t|\t\t%s\t\t|\t\t%s|\n",d.docid,d.dname,d.date);

    }

    fclose(fp);


 

    fclose(fp); 
}

void patient_list()
{
        patient p;
        FILE *fp;
        fp=fopen("patient.txt","rb");
        printf("\n\t\t\t\tPatient List\n");
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("\nID\t|\tName\t|\tAge\t|\tGender\t|\tAddress\t|\tsymptomes\t\t|\t\tChecked By\t|\tAdmit Date\n");
        while(fread(&p,sizeof(p),1,fp)==1)
        {
            printf("%d", p.id);
            printf("\t|\t%s", p.pname);
            printf("\t|\t%d", p.age);
            printf("\t|\t%s", p.gender);
            printf("\t|\t%s", p.address);
            printf("\t\t|\t\t%s", p.symptomes);
            printf("\t|\t%s", p.checkby_doctor);
            printf("\t|\t%s",p.date);
            printf("\n");
        }
        fclose(fp);
}

int appointment() {   
    int i = 0, dokid, choice, found = 0;
    doc s;

    printf("Doctors are only available for 3 hours in this hospital:\n");
    printf("1. 9:00-10:00\n");
    printf("2. 10:00-11:00\n");
    printf("3. 11:00-12:00\n");

    printf("Enter the doctor ID: ");
    scanf("%d", &dokid);

    FILE *fp = fopen("doctor.txt", "rb+");

    if (fp == NULL) {
        printf("Error: Could not open doctor.txt\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.docid == dokid) {
            found = 1;

            printf("Doctor Name: %s\n", s.dname);
            printf("Doctor Address: %s\n", s.docaddress);
            printf("Doctor Specialized: %s\n", s.specialized);
            printf("Doctor Availability: %d/%d/%d\n", s.date[0], s.date[1], s.date[2]);

            printf("Enter the timing you want to book:\n");
            printf("1. 9:00-10:00\n");
            printf("2. 10:00-11:00\n");
            printf("3. 11:00-12:00\n");
            scanf("%d", &choice);

            if (choice < 1 || choice > 3) {
                printf("Invalid choice!\n");
                fclose(fp);
                getch();
                return;
            }

            if (s.date[choice - 1] == 0) {
                s.date[choice - 1] = 1;
                printf("Appointment booked successfully\n");
                getch();
            } else {
                printf("Appointment already booked\n");
                fclose(fp);
                getch();
                return 0;
            }

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            getch();
            break;
        }
        getch();
    }

    fclose(fp);

    if (!found) {
        printf("Doctor not found\n");
    }
}

    

void add_doctor() {
    FILE *fp;
    doc d;

    // Get current date & time
    time_t t;
    struct tm *time_info;
    char buffer[20];
    time(&t);
    time_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);

    fp = fopen("doctor.txt", "ab");

    if (fp == NULL) {
        printf("Error: Could not open doctor.txt\n");
        return;
    }

    printf("\nNew Doctor ID:\t");
    scanf("%d", &d.docid);
    getchar(); // Clear newline from buffer

    printf("\nEnter Doctor Name:\t");
    scanf("%[^\n]", d.dname);
    getchar();

    printf("\nEnter Doctor Address:\t");
    scanf("%[^\n]", d.docaddress);
    getchar();

    printf("\nEnter Doctor Specialization:\t");
    scanf("%[^\n]", d.specialized);
    getchar();

    // Initialize appointment slots
    d.date[0] = 0; // 9:00-10:00
    d.date[1] = 0; // 10:00-11:00
    d.date[2] = 0; // 11:00-12:00

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);

    printf("\nDoctor added successfully!\n");
}


void doc_entry(){
    doc d;
    fp = fopen("doc_status.txt","ab");

    time_t t;
    struct tm *time_info;
    char buffer[20];
    time(&t);
    time_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d %H:%M:%S", time_info); 
    strcpy(d.date, buffer);


    printf("\n enter your id:\t");
    scanf("%d", &d.docid);
    while (getchar() != '\n');  // Clear input buffer

    printf("\n Enter doctor name:\t");
    scanf("%[^\n]s", d.dname);
    while (getchar() != '\n');  // Clear input buffer

    fwrite(&d, sizeof(d),1,fp);
    fclose(fp);
    printf("\n Entry varified\n");
}



void doc_exit(){
    doc d;
    int id,f;
    printf("\n enter your id:\t");
    scanf("%d",&id);
    fflush(stdin);
    FILE *fp, *ft;  // Declare file pointers locally
    
    fp = fopen("doc_status.txt", "rb");

    ft = fopen("temp1.txt", "wb");

    while (fread(&d, sizeof(d), 1, fp) == 1) {
        if (id == d.docid) {
            f = 1;  // Found the patient, but don't write it to new file
        } else {
            fwrite(&d, sizeof(d), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);
    if (f == 1) {
        remove("doc_status.txt");
        rename("temp1.txt", "doc_status.txt");
        printf("\n\nExit Granted.\n");
    } else {
        printf("\n\nNo entry Found!\n");
        remove("temp1.txt");  // Cleanup temp file
    }
}


int main(){

    int choice;
     // infinite loop in while(true) ; the loop can be countered by switch statement
     while(1){  
        printf("\t\t\t\t<-------Hospital Management system------->\n\n");
        printf("\t1. Admit Patient\n");
        printf("\t2. Discharge Patient\n");
        printf("\t3. Patient List\n");
        printf("\t4. Available Doctor\n");
        printf("\t5. Add Doctor\n");
        printf("\t6. Appointment\n");
        printf("\t7. Doctor Entry\n");
        printf("\t8. Doctor Exit\n");
        printf("\t0. Exit\n");
        printf("\n------------------------------------------------------");
        printf("\nEnter your choice :\t");
        scanf("%d",&choice);
        while (getchar() != '\n');  // Clear input buffer


        switch (choice) {
            case 1:
                admit_patient();
                break;
            case 2:
                discharge_patient();
                break;
            case 3:
                patient_list();
                break;
            case 4:
                available_doctor();
                break;
            case 5:
                add_doctor();
                break;
            case 6:
            	appointment();
            	break;
            case 7:
                doc_entry();
                break;
            case 8:
                doc_exit();
                break;
            case 0:
                printf("Exiting program...\n");
                exit(0); 
            default:
                printf("Invalid choice! Try again.\n");
        }
        printf("\n\n\t\t Press any key to continue---");
        getchar();
     }





    return 0;
}