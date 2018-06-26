#include "timeANDvotes.h"

Date
get_time(char* timestr)
{
	char timestri[strlen(timestr)];
	strcpy(timestri,timestr);
	char year[4] = "";
	char month[2] = "";
	char day[2] = "";

	int i = 0;
	int j = 0;

	for(i = 0 ;i < 4; i++){
		year[i] = timestr[i];
	}

	year[4] = '\0';
	int yEar = atoi(year);

	j = 0;

	for(i = 5 ;i < 7; i++){
		month[j] = timestri[i];
		j++;
	}

	month[2] = '\0';
	int mOnth = atoi(month);

	j = 0;

	for(i = 8 ;i < 10; i++){
		day[j] = timestri[i];
		j++;
	}

	day[2] = '\0';
	int dAy = atoi(day);

	return (createDate(dAy,mOnth,yEar));
}