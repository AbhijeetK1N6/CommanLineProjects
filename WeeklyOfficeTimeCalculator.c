/*
Considering a 9.5 Hours daily working and mandatory 47.5 hours working in a 5 day office week,
this program will show the total working hours and total required hours in a week to meet the office policy.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// BASE CODE : 441 - 481                   MODIFIED CODE : 244 - 435                  FINAL CODE : 11 - 234 /////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FINAL CODE : Program with options to choose input as DAILY WORKING HOURS or DAILY IN/OUT TIME -

#include<stdio.h>
#include<stdlib.h>
int numDay,emp_id;
int required_time = 2850; //47.5 hrs to minutes
char emp_name[15];
char arrDays[5][10]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
int arrHours[4];
int arrMinutes[4];
int *Final_Result_Box1, *Final_Result_Box2, *Final_Result_Box3;

//FORCASE 2
struct Time {
    int hours;
    int minutes;
};

// Function to calculate total minutes worked
int calculateTotalMinutes(struct Time inTime, struct Time outTime) {
    int inMinutes = inTime.hours * 60 + inTime.minutes;
    int outMinutes = outTime.hours * 60 + outTime.minutes;
    return outMinutes - inMinutes;
}

// Function to convert minutes to hours and minutes
// Function to convert minutes to hours and minutes
int *convertToHoursAndMinutes(int totalMinutes) {
    int *HourMinuteBox = malloc(2 * sizeof(int));
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    HourMinuteBox[0] = hours;
    HourMinuteBox[1] = minutes;
    return HourMinuteBox;
}


//Function to Calculate remaining time for the coming days
int *extra_or_required_working_hours(int arrHourMinutes[]){
    //arrHourMinutes = {Hours,Minutes}
    static int resultBox2[10];
    int temp;
    int condition_time = (arrHourMinutes[0] * 60) + 30;
    if(condition_time > required_time ){
        if(arrHourMinutes[1] < 30){
            temp = 30 + arrHourMinutes[1];
            arrHourMinutes[0] = arrHourMinutes[0] - 47 - 1;
        }
        else{
            temp = arrHourMinutes[1] - 30;
            arrHourMinutes[0] = arrHourMinutes[0] - 47;
        }
    }
    if(condition_time < required_time ){
        if(arrHourMinutes[1] > 30){
            temp = 60 - arrHourMinutes[1] + 30;
            arrHourMinutes[0]= 47 - arrHourMinutes[0] - 1;
        }
        else{
            temp = 30 - arrHourMinutes[1];
            arrHourMinutes[0] = 47 - arrHourMinutes[0];
        }
    }
    resultBox2[0] = arrHourMinutes[0];
    resultBox2[1] = temp;
    return resultBox2;
}

//Counts the total worked hours & Minutes for the week and return as array
// Counts the total worked hours & Minutes for the week and return as array
int *total_time_calculator(int arrHours[], int arrMinutes[]) {
    static int resultBox1[10];
    int hourCounter = 0, minutesCounter = 0, totalHours = 0; // Initialize totalHours
    for (int i = 0; i < numDay; i++) {
        hourCounter += arrHours[i];
        minutesCounter += arrMinutes[i];
    }
    while (minutesCounter >= 60) {
        minutesCounter -= 60;
        totalHours += 1;
    }
    totalHours += hourCounter;
    resultBox1[0] = totalHours;
    resultBox1[1] = minutesCounter;
    return resultBox1;
}


//Function to balance the required working hours for the coming days
int *time_balancer(int a, int b, int numDay){
    static int resultBox3[10];
    int required_minutes = (a*60) + b;
    if(numDay > 0 ){
        int minutes_each_day = required_minutes/(5-numDay);
        int temp = minutes_each_day;
        resultBox3[0] = minutes_each_day/60;
        resultBox3[1] = temp%60;
        return resultBox3;
    }
    else{
        return 0;
    }
}

//FUnction to choose mode of the input
int choicer(void){
    int a;
    printf("Press (1) to Input Hours\nPress (2) to Input TimeStamps\nChoose your Input type from above :-");
        scanf("%d",&a);
        printf("**************************************************************************************************************************\n");
    if(a==1 || a==2){
        return a;
    }
    else{
        printf("Wrong Choice!!\nPlease retry\n");
        choicer();
    }
}

//CASE - 1
int hourstamper(){
    for(int i = 0 ; i < numDay ; i++){
        printf("Enter the Working Hours for %s in (HH MM) Format :- ", arrDays[i]);
        scanf("%d %d", &arrHours[i],&arrMinutes[i]);
    }
    Final_Result_Box1 = total_time_calculator(arrHours,arrMinutes);
    printf("**************************************************************************************************************************\n");
    printf("Total Weekly Working Hours are %d Hours and %d Minutes\n", Final_Result_Box1[0], Final_Result_Box1[1]);
        
    int condition_time = (Final_Result_Box1[0] * 60) + 30;
    Final_Result_Box2 = extra_or_required_working_hours(Final_Result_Box1);
    printf("**************************************************************************************************************************\n");
//
    if(numDay==4){
        if(condition_time > required_time){
        printf("Hey %s, you have already worked %d Hours and %d Minutes Over Time, you don't need to work on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
        printf("**************************************************************************************************************************\n");
        }
        else{
             printf("Hey %s, you are required to Work %d Hours and %d Minutes more on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
            printf("**************************************************************************************************************************\n");
        }
    }
    else{
        Final_Result_Box3 = time_balancer(Final_Result_Box2[0], Final_Result_Box2[1],numDay);
        if(Final_Result_Box3 == 0){
            printf("Hey %s You have not worked in this Week.. :(",emp_name);
        }
        else{
            printf("Hey %s For a Balanced Work Life, you can do %d Hours and %d Minutes daily for the next %d Days.\n",emp_name, Final_Result_Box3[0], Final_Result_Box3[1], 5-numDay);
            ("**************************************************************************************************************************\n");
        }
    }
}

//CASE - 2
int timestamper(){
    struct Time inTime, outTime;
    int daily_minutes_adder;
    int *p, *z;
    static int adder[12];
    const int standardShiftMinutes = 9 * 60 + 30; // 9 hours 30 minutes
    for(int i = 0 ; i < numDay ; i++){
        printf("Enter Punch-IN time for %s in (HH MM) :- ",arrDays[i]);
        scanf("%d %d", &inTime.hours, &inTime.minutes);
        printf("Enter Punch-OUT time for %s in (HH MM) Format :- ",arrDays[i]);
        scanf("%d %d", &outTime.hours, &outTime.minutes);
        int totalMinutes = calculateTotalMinutes(inTime, outTime);
        p = convertToHoursAndMinutes(totalMinutes);
        arrHours[i] = p[0];
        arrMinutes[i] = p[1];
        free(p); // Free the dynamically allocated memory
        daily_minutes_adder += totalMinutes;
    }  
    Final_Result_Box1 = total_time_calculator(arrHours,arrMinutes);
    printf("**************************************************************************************************************************\n");
    printf("Total Weekly Working Hours are %d Hours and %d Minutes\n", Final_Result_Box1[0], Final_Result_Box1[1]);
        
    int condition_time = (Final_Result_Box1[0] * 60) + 30;
    Final_Result_Box2 = extra_or_required_working_hours(Final_Result_Box1);
    printf("**************************************************************************************************************************\n");
        //
    if(numDay==4){
        if(condition_time > required_time){
        printf("Hey %s, you have already worked %d Hours and %d Minutes Over Time, you don't need to work on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
        printf("**************************************************************************************************************************\n");
        }
        else{
             printf("Hey %s, you are required to Work %d Hours and %d Minutes more on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
            printf("**************************************************************************************************************************\n");
        }
    }
    else{
        Final_Result_Box3 = time_balancer(Final_Result_Box2[0], Final_Result_Box2[1],numDay);
        if(Final_Result_Box3 == 0){
            printf("Hey %s You have not worked in this Week.. :(",emp_name);
        }
        else{
            printf("Hey %s For a Balanced Work Life, you can do %d Hours and %d Minutes daily for the next %d Days.\n",emp_name, Final_Result_Box3[0], Final_Result_Box3[1], 5-numDay);
            ("**************************************************************************************************************************\n");
        }
    }
}

//MAIN Function
int main(){
    int mode;
    printf("**************************************************************************************************************************\n");
    printf("Enter your Name :- ");
    gets(emp_name);
    printf("Enter you Employee ID :- ");
    scanf("%d",&emp_id);
    printf("**************************************************************************************************************************\n");
    printf("How Many Days you have Worked till now? : - ");
    scanf("%d",&numDay);
    printf("**************************************************************************************************************************\n");
    mode = choicer();
    if(mode == 1){
        hourstamper();
    }
    else if(mode == 2){
        timestamper();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GitHub Link : https://github.com/AbhijeetK1N6
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MODIFIED CODE : Program with DAILY WORKING HOURS INPUT only-

#include<stdio.h>
int required_time = 2850; //47.5 hrs to minutes

struct Time {
    int hours;
    int minutes;
};

// Function to calculate total minutes worked
int calculateTotalMinutes(struct Time inTime, struct Time outTime) {
    int inMinutes = inTime.hours * 60 + inTime.minutes;
    int outMinutes = outTime.hours * 60 + outTime.minutes;
    return outMinutes - inMinutes;
}

// Function to convert minutes to hours and minutes
void convertToHoursAndMinutes(int totalMinutes) {
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    printf("Total hours worked: %d hours and %d minutes.\n", hours, minutes);
}
//////////////
int timestamper(){
    struct Time inTime, outTime;
    const int standardShiftMinutes = 9 * 60 + 30; // 9 hours 30 minutes
        
    //for(int i = 0 ; i < numDay ; i++){}
    printf("Enter in-time (hours minutes): ");
    scanf("%d %d", &inTime.hours, &inTime.minutes);
    
    printf("Enter out-time (hours minutes): ");
    scanf("%d %d", &outTime.hours, &outTime.minutes);
    
    int totalMinutes = calculateTotalMinutes(inTime, outTime);
    convertToHoursAndMinutes(totalMinutes);
    
    // Calculate extra time worked
    int extraMinutes = totalMinutes - standardShiftMinutes;
    if (extraMinutes > 0) {
        int extraHours = extraMinutes / 60;
        int extraRemainingMinutes = extraMinutes % 60;
        printf("Extra time worked: %d hours and %d minutes.\n", extraHours, extraRemainingMinutes);
    } else {
        printf("No extra time worked.\n");
    }
}
/////


int choicer(void){
    int a;
    printf("Press (1) to Input Hours\nPress (2) to Input TimeStamps\nChoose your Input type from above :-");
        scanf("%d",&a);
        printf("*************************************************************\n");
    if(a==1 || a==2){
        return a;
    }
    else{
        printf("Wrong Choice!!\nPlease retry\n");
        choicer();
    }
}

int *total_time_calculator(int arrHours[], int arrMinutes[], int n){
    static int resultBox1[10];
    int hourCounter = 0, minutesCounter = 0, totalHours;
    for(int i = 0 ; i < n ; i++){
        hourCounter += arrHours[i];
        minutesCounter += arrMinutes[i];
    }
    while(minutesCounter >= 60){
        minutesCounter -= 60;
        totalHours += 1;
    }
    totalHours += hourCounter;
    resultBox1[0] = totalHours;
    resultBox1[1] = minutesCounter;
    return resultBox1;
    
}

int *time_balancer(int a, int b, int numDay){
    static int resultBox3[10];
    int required_minutes = (a*60) + b;
    if(numDay > 0 ){
        int minutes_each_day = required_minutes/(5-numDay);
        int temp = minutes_each_day;
        resultBox3[0] = minutes_each_day/60;
        resultBox3[1] = temp%60;
        return resultBox3;
    }
    else{
        return 0;
    }
}

int *extra_or_required_working_hours(int arrHourMinutes[]){
    //arrHourMinutes = {Hours,Minutes}
            
    static int resultBox2[10];
    int temp;
    int condition_time = (arrHourMinutes[0] * 60) + 30;
    
    if(condition_time > required_time ){
        if(arrHourMinutes[1] < 30){
            temp = 30 + arrHourMinutes[1];
            arrHourMinutes[0] = arrHourMinutes[0] - 47 - 1;
        }
        else{
            temp = arrHourMinutes[1] - 30;
            arrHourMinutes[0] = arrHourMinutes[0] - 47;
        }
    }
    
    if(condition_time < required_time ){
        if(arrHourMinutes[1] > 30){
            temp = 60 - arrHourMinutes[1] + 30;
            arrHourMinutes[0]= 47 - arrHourMinutes[0] - 1;
        }
        else{
            temp = 30 - arrHourMinutes[1];
            arrHourMinutes[0] = 47 - arrHourMinutes[0];
        }
    }
    
    resultBox2[0] = arrHourMinutes[0];
    resultBox2[1] = temp;
    return resultBox2;
}

//Code by @AbhijeetK1N6

int main(){
    int arrHours[4];
    int arrMinutes[4];
    int mode;
    int *Final_Result_Box1, *Final_Result_Box2, *Final_Result_Box3, emp_id, numDay;
    char emp_name[15];
    int required_time = 2850;        //47.5 hrs to minutes
    char arrDays[5][10]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
    printf("*************************************************************\n");
    printf("Enter your Name :- ");
    gets(emp_name);
    printf("Enter you Employee ID :- ");
    scanf("%d",&emp_id);
    printf("*************************************************************\n");
    printf("How Many Days you have Worked till now? : - ");
    scanf("%d",&numDay);
    printf("*************************************************************\n");
    
    mode = choicer();
    if(mode == 1){
        for(int i = 0 ; i < numDay ; i++){
            printf("Enter the Working Hours for %s :- ", arrDays[i]);
            scanf("%d", &arrHours[i]);
            printf("Enter the Total Minutes (Except Hours) for %s :- ", arrDays[i]);
            scanf("%d", &arrMinutes[i]);
        }
        Final_Result_Box1 = total_time_calculator(arrHours,arrMinutes,numDay);
        printf("*************************************************************\n");
        printf("Total Weekly Working Hours are %d Hours and %d Minutes\n", Final_Result_Box1[0], Final_Result_Box1[1]);
        
        int condition_time = (Final_Result_Box1[0] * 60) + 30;
        Final_Result_Box2 = extra_or_required_working_hours(Final_Result_Box1);
        printf("*************************************************************\n");
        //
        if(numDay==4){
            if(condition_time > required_time){
            printf("Hey %s, you have already worked %d Hours and %d Minutes Over Time, you don't need to work on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
            printf("*************************************************************\n");
            }
            else{
                 printf("Hey %s, you are required to Work %d Hours and %d Minutes more on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
                printf("*************************************************************\n");
            }
        }
        else{
            Final_Result_Box3 = time_balancer(Final_Result_Box2[0], Final_Result_Box2[1],numDay);
            if(Final_Result_Box3 == 0){
                printf("Hey %s You have not worked in this Week.. :(",emp_name);
            }
            else{
                printf("Hey %s For a Balanced Work Life, you can do %d Hours and %d Minutes daily for the next %d Days.",emp_name, Final_Result_Box3[0], Final_Result_Box3[1], 5-numDay);
            }
        }
    }
    else if(mode == 2){
        timestamper(numDay);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BASE CODE :

#include<stdio.h>
int time_calculator(int arr1[], int arr2[]){
    int summer1=0,summer2=0,tot_hr,tot_min,temp;
    for(int i=0;i<4;i++){
        summer1+=arr1[i];
        summer2+=arr2[i];
    }
    do{
        summer2-=60;
        tot_hr+=1;
    }while(summer2>60);
    tot_hr+=summer1;
    printf("*************************************************************\n");
    printf("Total Weekly Working Hours are %d Hours and %d Minutes\n",tot_hr,summer2);
    if(summer2>30){
        temp=60-summer2+30;
        tot_hr=47-tot_hr-1;
    }
    else{
        temp=30-summer2;
        tot_hr=47-tot_hr;
    }
    printf("*************************************************************\n");
    printf("You need to Work %d Hours and %d Minutes more on Friday\n",tot_hr,temp);
    printf("*************************************************************\n");
}

int main(){
    int hour[4];
    int mint[4];
    for(int i=0;i<4;i++){
        printf("Enter the Working Hours for Day %d :- ",i+1);
        scanf("%d",&hour[i]);
        printf("Enter the Total Minutes (Except Hours) for Day %d :- ",i+1);
        scanf("%d",&mint[i]);
    }
    //printf("%d",time_calculator(hour[4],mint[4]));
    time_calculator(hour,mint);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
