/*
Considering a 9.5 Hours daily working and mandatory 47.5 hours working in a 5 day office week,
this program will show the total working hours and total required hours in a week to meet the office policy.
*/

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
