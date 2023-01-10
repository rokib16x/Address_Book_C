#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char first_name[20];
    char last_name[20];
    char phone[20];
} Contact;

Contact contacts[60];
int contacts_count;

void add_contact() {
    Contact *contact = contacts + contacts_count;

    puts("Enter First Name:");
    scanf("%s", &contact->first_name);

    puts("Enter Last Name: ");
    scanf("%s", &contact->last_name);

    puts("Enter Phone Number: ");
    scanf("%s", &contact->phone);

    puts("Contact Saved.");
    contacts_count++;
}

void edit_contact(int index) {
    Contact *contact = contacts + index;

    if (index >= contacts_count || index < 0) {
        puts("ERROR: Invalid Contact ID");
        return;
    }

    printf("Current First Name: %s\n", contact->first_name);
    puts("Enter First Name:");
    scanf("%s", &contact->first_name);

    printf("Current Last Name: %s\n", contact->last_name);
    puts("Enter Last Name: ");
    scanf("%s", &contact->last_name);

    printf("Current Phone Number: %s\n", contact->phone);
    puts("Enter Phone Number: ");
    scanf("%s", &contact->phone);


    puts("Contact Edited.");
}

void delete_contact(int index) {
    Contact *contact, *last;

    if (index >= contacts_count || index < 0) {
        puts("ERROR: Invalid Contact ID");
        return;
    }

    contact = contacts + index;
    last = contacts + contacts_count - 1;

    strcpy(contact->first_name, last->first_name);
    strcpy(contact->last_name, last->last_name);
    strcpy(contact->phone, last->phone);

    contacts_count--;
}

void show_contacts() {
    int i;
    Contact *contact;

    puts("ID \t Full Name \t Phone Number");
    for (i = 0; i < contacts_count; i++) {
        contact = contacts + i;

        printf("%i \t %s %s \t %s\n", i + 1, contact->first_name, contact->last_name, contact->phone);
    }
}
void search_contacts() {
    int i;
    Contact *contact;
    char name[40];
    char l_name[40];

    printf("Enter First name: ");
    scanf("%s", name);
    puts("ID \t Full Name \t Phone Number");
    int count = 0;
    for (i = 0; i < contacts_count; i++) {
        if (contact->first_name == name) {
            printf("%i \t %s %s \t %s\n", i + 1, contact->first_name, contact->last_name, contact->phone);
            count++;
        }
    }
    if(count == 0){
        printf("Contact Not Found\n");
    }
}

char read_string(char *s, FILE *file) {
    char i, c;

    i = 0;
    s[0] = 0;

    while (1) {
        c = fgetc(file);

        if (c == 0) {
            s[i] = 0;
            return i;
        } else if (c == EOF) {
            return -1;
        } else {
            s[i] = c;
            i++;
        }
    }
}

void load_contacts() {
    char r, *s;
    FILE *file = fopen("contacts.txt", "r");

    if (!file)
        return;

    contacts_count = 0;

    while (1) {
        s = contacts[contacts_count].first_name;

        r = read_string(s, file);

        if (r < 0)
            break;

        s = contacts[contacts_count].last_name;
        read_string(s, file);

        s = contacts[contacts_count].phone;
        read_string(s, file);

        contacts_count++;
    }

    fclose(file);
}

void save_contacts() {
    int i;
    Contact *contact;
    FILE *file = fopen("contacts.txt", "w");

    if (!file)
        return;

    for (i = 0; i < contacts_count; i++) {
        contact = contacts + i;

        fputs(contact->first_name, file);
        fputc(0, file);

        fputs(contact->last_name, file);
        fputc(0, file);

        fputs(contact->phone, file);
        fputc(0, file);
    }

    fclose(file);
}

int get_command() {
    char c;
    printf("\n\n\t\t\t  MENU\t\t\n\n");
    printf("\t1.Add New   \t2.Modify   \t3.Delete  \t4.List  \t5.Exit");
    puts("\n\n\nEnter Command:");
    scanf("%s", &c);

    switch (c) {
        case '1':
            add_contact();
            break;

        case '2':
            printf("Enter Contact ID: ");
            scanf("%i", &c);
            edit_contact(c - 1);
            break;

        case '3':
            printf("Enter Contact ID: ");
            scanf("%i", &c);
            delete_contact(c - 1);
            break;

        case '4':
            show_contacts();
            break;

        case '5':
            puts("Goodbye");
            return 0;

        default:
            puts("ERROR: Invalid Command");
            break;
    }

    puts("");
    return 1;
}

int main() {
    load_contacts();

    while (get_command());

    save_contacts();

    return 0;
}
 