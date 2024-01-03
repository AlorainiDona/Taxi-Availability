#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Taxi{
   int id;
   char driver[20]; //first and last name
   char category[20]; //The category could be one of the following: “standard”, “Business” or “Family”.
   char plate[7]; //The format of the plate number: 3 alphabet characters and 3 digits.
   char color[20]; //represents the car’s color
   float rate; //represents the driver’s rate 
   float minCharge; //epresents the minimum charge of the trip car according to the car category
   char state; //The state could be “A” which indicates the driver is available and ready for a trip, or “R” which indicates the driver is in a ride currently.
   struct Taxi *next; //self-referential structure pointer.
};

struct Taxi *list = NULL;

void addTripCar();
void setTripCar(char* category,float* rate);
void writeCarsInRide(char* fileName);
void printList();

//////////////////MAIN//////////////////

int main()
{
//Call the function addTripCar to read the content of written trip cars information
   addTripCar();

//Call the function printList to print the cars information as early described, (i.e, after reading the initial information in the txt file )
   printf("The Available Trip Cars:\n"); 
   printList();

//Call the function setTripCar with the following given shaded information: 
   char *category1 = "Business";
   float rate1 = 4.5;

   char *category2 = "Family";
   float rate2 = 5.0;
   
   char *category3 = "Family";
   float rate3 = 4.0;

   char *category4 = "standard";
   float rate4 = 3.4;
   
   char *category5 = "standard";
   float rate5 = 5.0;

   setTripCar(category1 , &rate1);
   setTripCar(category2 , &rate2);
   setTripCar(category3 , &rate3);
   setTripCar(category4 , &rate4);
   setTripCar(category5 , &rate5);


//Call the function printList to print the cars information as early described,after set some cars to be in a ride
   printf("--------------------------------------------------------------\n"); 
   printf("The Cars in Ride:\n"); 
   printList();

//Call the function writeCarsInRide to update the txt file with cars in trip.
   char *fileName = "Taxies.txt";
   writeCarsInRide(fileName);

}


   //////////////////Methods//////////////////
   
void addTripCar(){

   struct Taxi *head  = NULL , *current; 
   FILE* fp;
   int count=0,c; 

   if(fp = fopen("Taxies.txt", "r")){
   
      while ((c = getc(fp)) != '\n'); // to ignore the first line.
   
      do{
         (c = getc(fp));
         if(c == '\n') count++;
      }while(c != EOF);
   
      fseek(fp,0,SEEK_SET); // or rewind.
   
      while ((c = getc(fp)) != '\n'); // to ignore the first line.
   
      for( int i = 0 ; i < count ; i++){
         struct Taxi  *TaxiNode = (struct Taxi*) malloc(sizeof(struct Taxi));
         if(TaxiNode != NULL){
            fscanf(fp,"%d %s %s %s %s %f %f", &(TaxiNode->id),TaxiNode->driver,TaxiNode->category,TaxiNode->plate,
               TaxiNode->color, &(TaxiNode->rate),&(TaxiNode->minCharge));
            TaxiNode->state = 'A'; 
            TaxiNode->next = NULL;
         }
         else{
            printf("Error allocating memory");
            return;
         }
      
         if( head == NULL){
            head = TaxiNode;
            current = head; 
         }
         else{
            current->next = TaxiNode; 
            current = current->next;}
      }
      list = head;
      fclose(fp);
      return;
   } 
   printf("File could not be opened.");
   return;
}

void setTripCar(char *category , float *rate)
{
   if(list==NULL){
      printf("empty list");
      return;
   }
   struct Taxi*cur= list;
   while(cur->next!=NULL)
   {
      if(strcmp( cur->category , category )  == 0   && cur->rate==*rate){
         cur->state='R';
         return;
      }
      cur= cur->next;
   }
   if(strcmp( cur->category , category )  == 0   && cur->rate==*rate){//for the last node
      cur->state='R';
      return;
   }
}
   
void writeCarsInRide(char * fileName) { 
   if (list == NULL) {
      printf("List is empty.\n");
      return;
   }

   FILE* fp = fopen(fileName, "a");
   if (fp == NULL) { // to check if the file was opened successfully
      printf("There was an error found while trying to open the file.\n");
      return;
   }

   fprintf(fp, "---------------------------------------------------------------------------------\n");
   fprintf(fp, "The trip Cars:\n"); //followed the header format written in the note
   fprintf(fp, "%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s \n", "ID", "Driver", "Category", "Plate", "Rate", "State"); //header, seperated by tabs
   struct Taxi * record = list; // starts with the first record in the list
   while (record != NULL) {
      if (record->state == 'R') {
         fprintf(fp, "%d\t\t%-6s\t\t%-8s\t\t%s\t\t%-4.1f\t\t%c \n", record->id, record->driver, record->category, record->plate, record->rate, record->state); //appends info of the trip cars, state = R
      }
      record = record->next;
   }

   fclose(fp);
}

void printList()
{
   if(list == NULL)
   {
      printf("EMPTY LIST \n");
      return;
   }
   struct Taxi *current = list;
   printf("id \t driver \t category \t plate \t \t color \t \t rate \t \t minChar \t state \n"); //header, seperated by tabs
   while(current != NULL)
   {
      printf("%d \t %-10s \t %-8s \t %-6s \t %-8s \t %-6.1f \t %-8.2f \t %c\n",current->id , current->driver ,current->category , current->plate , current->color , current->rate , current->minCharge , current->state);
      current = current->next;
   }
}