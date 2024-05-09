#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int numDay,emp_id;
int required_time = 2850; //47.5 hrs = 2850 minutes
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

//NewlyAdded by K1N6 //24-04-2024
struct Time addTime(struct Time t, double hours) {
    double totalMins = t.hours * 60 + t.minutes + hours * 60;
    struct Time result;
    result.hours = (int) totalMins / 60;
    result.minutes = (int) totalMins % 60;
    return result;
}

// Function to calculate total minutes worked
int calculateTotalMinutes(struct Time inTime, struct Time outTime) {
    int inMinutes = inTime.hours * 60 + inTime.minutes;
    int outMinutes = outTime.hours * 60 + outTime.minutes;
    return outMinutes - inMinutes;
}

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
int *time_balancer(int a, int b){
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
    printf("Press (1) to Input Hours\nPress (2) to Input TimeStamps\nChoose your Input type from above : ");
        scanf("%d",&a);
        printf("************************************************************************************************************************\n");
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
    printf("************************************************************************************************************************\n");
    printf("Total Weekly Working Hours are %d Hours and %d Minutes\n", Final_Result_Box1[0], Final_Result_Box1[1]);
        
    int condition_time = (Final_Result_Box1[0] * 60) + 30;
    Final_Result_Box2 = extra_or_required_working_hours(Final_Result_Box1);
    printf("************************************************************************************************************************\n");
//
    if(numDay==4){
        if(condition_time > required_time){
        printf("Hey %s, you have already worked %d Hours and %d Minutes Over Time, you don't need to work on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
        printf("************************************************************************************************************************\n");
        }
        else{
            printf("Hey %s, you are required to Work %d Hours and %d Minutes more on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
            printf("************************************************************************************************************************\n");
        }
    }
    else{
        Final_Result_Box3 = time_balancer(Final_Result_Box2[0], Final_Result_Box2[1]);
        if(Final_Result_Box3 == 0){
            printf("Hey %s You have not worked in this Week.. :(",emp_name);
        }
        else{
            printf("Hey %s, you are required to Work %d Hours and %d Minutes more this week\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
            printf("************************************************************************************************************************\n");
            printf("For a Balanced Work Life, you can do %d Hours and %d Minutes daily for the next %d Days.\n", Final_Result_Box3[0], Final_Result_Box3[1], 5-numDay);
            printf("************************************************************************************************************************\n");
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
    printf("************************************************************************************************************************\n");
    printf("Total Weekly Working Hours are %d Hours and %d Minutes\n", Final_Result_Box1[0], Final_Result_Box1[1]);
        
    int condition_time = (Final_Result_Box1[0] * 60) + 30;
    Final_Result_Box2 = extra_or_required_working_hours(Final_Result_Box1);
    printf("************************************************************************************************************************\n");
        //
    if(numDay==4){
        if(condition_time > required_time){
        printf("Hey %s, you have already worked %d Hours and %d Minutes Over Time, you don't need to work on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
        printf("************************************************************************************************************************\n");
        }
        else{
            printf("Hey %s, you are required to Work %d Hours and %d Minutes more on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
            printf("************************************************************************************************************************\n");
        }
    }
    else{
        Final_Result_Box3 = time_balancer(Final_Result_Box2[0], Final_Result_Box2[1]);
        if(Final_Result_Box3 == 0){
            printf("Hey %s You have not worked in this Week.. :(",emp_name);
        }
        else{
            if(numDay==4){
                printf("Hey %s, you are required to Work %d Hours and %d Minutes more on Friday\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
                printf("************************************************************************************************************************\n");
            }
            else{
                printf("Hey %s, you are required to Work %d Hours and %d Minutes more this week\n", emp_name, Final_Result_Box2[0], Final_Result_Box2[1]);
                printf("************************************************************************************************************************\n");
                printf("For a Balanced Work Life, you can do %d Hours and %d Minutes daily for the next %d Days.\n", Final_Result_Box3[0], Final_Result_Box3[1], 5-numDay);
                printf("************************************************************************************************************************\n");
            }
            
            
        }
    }
}

//MAIN Function
int main(){
    int mode,inpAbhi;
    system("color 0A");
    printf("************************************************************************************************************************\n");
    printf("\nInstructions:-\n1) Do not count present day in Number of Days worked.\n2) Press 1 if you have already calculated your daily hours.\n3) Press 2 if you want didn't calculated your daily hours and want to Enter PUNCH-IN and PUNCH-OUT Time\n4) (HH MM) stand for (Hours Minutes)\n5) Enter the time in specified format only. Take care of the space between (HH MM)\n\n");
    system("color 57");    //to change console color     (    SYNTAX : system("Background_Color+Text_Color");    )
    printf("\n************************************************************************************************************************\n");
    printf("\nEnter your Name : ");
    gets(emp_name);
    //printf("Enter you Employee ID : ");
    //scanf("%d",&emp_id);
    printf("\n************************************************************************************************************************\n");
    printf("Hii %s\n",emp_name);
    printf("Press (1)to get your today's Out time\nPress (2) to go to Week hours Calculator :- ");
    scanf("%d",&inpAbhi);
    if(inpAbhi==1){
        struct Time t;
        printf("Enter your today's Punch-in time (hours minutes): ");
        scanf("%d %d", &t.hours, &t.minutes);
        
        struct Time laterTime = addTime(t, 9.5);
        printf("Today, you can Punch-out at:- %d : %d \n", laterTime.hours, laterTime.minutes);
        getch();
    }
    else{
        printf("************************************************************************************************************************\n");
        printf("Enter Number of Days you have worked in this Week : ");
        scanf("%d",&numDay);
        printf("************************************************************************************************************************\n");
        mode = choicer();
        if(mode == 1){
            hourstamper();
        }
        else if(mode == 2){
            timestamper();
        }
        printf("\n");
        printf("************************************************************************************************************************\n");
        printf("***************************** [ Code Available on : https://github.com/AbhijeetK1N6 ] **********************************\n");
        printf("************************************************************************************************************************\n");
        printf("\n");
        getch();
    }
    
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////GitHub Link : https://github.com/AbhijeetK1N6///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Pin 8 44
2Do 9 13
Po 17 57
*/
