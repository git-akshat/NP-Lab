/* Author: Natesh M Bhat */
/******************************************************************
Write a program to divide the message into variable length frames
and sort them and display the message at the receiving side.
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct{
	int id ; 
	int len ; 
	char buffer[100] ; 
} Frame ;

Frame frames[100] ;
int totalFrames = 0 ; 
int maxFrameLength ; 
	
void buildFrames(char * msg){
	int msgPointer =0 ; 
	while(msgPointer<strlen(msg)){
		int len = rand()%maxFrameLength + 1 ;
		frames[totalFrames].id = totalFrames ; 
		frames[totalFrames].len = len ; 
		strncpy(frames[totalFrames].buffer , msg + msgPointer  , len) ; 
		totalFrames++ ; 
		msgPointer+=len ; 
	}
}

void shuffleFrames(){
	for(int i =0 ; i < totalFrames ; i++){
		int j = rand()%(i+1) ;
		Frame temp = frames[i] ; 
		frames[i] = frames[j] ; 
		frames[j] = temp ;
	}
}

void showFrames(){
	printf("Frames are : \n") ; 
	printf("Frame id\t\tFrame len\t\tData : \n"  ) ;
	for(int i =0 ;i < totalFrames ; i++){
		printf("%d\t\t\t%d\t\t\t%s\n", frames[i].id , frames[i].len , frames[i].buffer) ; 		
	}
	printf("\n\n") ;
}

void sortFrames(){
	for(int i =0 ;i < totalFrames ;i++){
		for(int j =0  ; j<totalFrames-i-1 ; j++){
				if(frames[j].id >frames[j+1].id)
				{
					Frame temp = frames[j] ; 
					frames[j] = frames[j+1] ; 
					frames[j+1] = temp ;
				}
		}
	}
}

int main(void){
	srand(time(0)) ; 
	char msg[1000]  ; 
	printf("Enter max frame length : " ); scanf("%d" , &maxFrameLength) ; 
	printf("Enter message : ") ; gets(msg) ; 
	gets(msg) ;
	buildFrames(msg) ; 
	showFrames() ; 
	shuffleFrames() ; 
	printf("\nSimulating delay at router and the shuffled received frames : ") ; 
	showFrames() ; 
	sortFrames() ; 
	printf("\nReceiver after reordering the frames : ") ; 
	showFrames() ; 
}

/*
Enter max frame length : 5
Enter message : This is a very big message used for simulating frame shuffle and sorting
Frames are : 
Frame id	Frame len	Data : 
0			3			Thi
1			2			s 
2			3			is 
3			5			a ver
4			4			y bi
5			4			g me
6			4			ssag
7			5			e use
8			2			d 
9			2			fo
10			1			r
11			4			 sim
12			4			ulat
13			2			in
14			5			g fra
15			1			m
16			3			e s
17			5			huffl
18			1			e
19			4			 and
20			2			 s
21			3			ort
22			5			ing


Simulating delay at router and the shuffled received frames : Frames are : 
Frame id	Frame len	Data : 
19			4			 and
17			5			huffl
21			3			ort
3			5			a ver
15			1			m
1			2			s 
5			4			g me
7			5			e use
13			2			in
9			2			fo
14			5			g fra
16			3			e s
12			4			ulat
18			1			e
22			5			ing
8			2			d 
0			3			Thi
20			2			 s
6			4			ssag
4			4			y bi
10			1			r
2			3			is 
11			4			 sim
*/