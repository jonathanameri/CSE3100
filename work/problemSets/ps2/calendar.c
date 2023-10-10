#include <stdio.h>
#include "calendar.h"

int numDaysInMonth(int month, int year){
	switch(month){
		case JAN:
			return 31;
			break;
		case FEB:
			if((year%100!=0&&year%4==0)||year%400==0){
				return 29;
				break;
			}
			else{
				return 28;
				break;
			}
		case MAR:
			return 31;
			break;
		case APR:
			return 30;
			break;
		case MAY:
			return 31;
			break;
		case JUN:
			return 30;
			break;
		case JUL:
			return 31;
			break;
		case AUG:
			return 31;
			break;
		case SEP:
			return 30;
			break;
		case OCT:
			return 31;
			break;
		case NOV:
			return 30;
			break;
		case DEC:
			return 31;
			break;
		default:
			return -1;
	}
}

int numFirstMondays(int startYear, int endYear, int janFirstWeekday)
{
	int i = startYear;
	int ct=0;
	while(i<=endYear){
		for(int m = 1; m <= 12; m++){
			if(janFirstWeekday==1)
				ct++;
			janFirstWeekday = (janFirstWeekday + numDaysInMonth(m, i))%7;
		}
		i++;
	}
	return ct;
}
