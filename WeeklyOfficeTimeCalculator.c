/*
Considering a 9.5 Hours daily working and mandatory 47.5 hours working in a 5 day office week,
this program will show the total working hours and total required hours in a week to meet the office policy.
*/
//BASE CODE : 7-46
//MODIFIED CODE : 51 - 123

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


#include<stdio.h>

int *total_time_calculator(int arrHours[], int arrMinutes[]){
    static int resultBox1[10];
    int hourCounter = 0, minutesCounter = 0, totalHours;
    for(int i = 0 ; i < 4 ; i++){
        hourCounter += arrHours[i];
        minutesCounter += arrMinutes[i];
    }
    while(minutesCounter > 60){
        minutesCounter -= 60;
        totalHours += 1;
    }
    totalHours += hourCounter;
    resultBox1[0] = totalHours;
    resultBox1[1] = minutesCounter;
    return resultBox1;
    
}

int *extra_or_required_working_hours(int arrHourMinutes[]){
    //arrHourMinutes = {Hours,Minutes}
    static int resultBox2[10];
    int temp;
    int condition_time = (arrHourMinutes[0] * 60) + 30;
    int required_time = 2850;        //47.5 hrs to minutes
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

int main(){
    int arrHours[4];
    int arrMinutes[4];
    int *Final_Result_Box1, *Final_Result_Box2;
    char arrDays[5][10]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
    for(int i = 0 ; i < 4 ; i++){
        printf("Enter the Working Hours for %s :- ", arrDays[i]);
        scanf("%d", &arrHours[i]);
        printf("Enter the Total Minutes (Except Hours) for %s :- ", arrDays[i]);
        scanf("%d", &arrMinutes[i]);
    }
    Final_Result_Box1 = total_time_calculator(arrHours,arrMinutes);
    printf("*************************************************************\n");
    printf("Your Total Weekly Working Hours are %d Hours and %d Minutes\n", Final_Result_Box1[0], Final_Result_Box1[1]);
    Final_Result_Box2 = extra_or_required_working_hours(Final_Result_Box1);
    printf("*************************************************************\n");
    printf("You are required to Work %d Hours and %d Minutes more on Friday\n", Final_Result_Box2[0], Final_Result_Box2[1]);
    printf("*************************************************************\n");
}
