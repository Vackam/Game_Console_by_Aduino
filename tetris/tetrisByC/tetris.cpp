#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

int btn_left = 2, btn_right=3, btn_3=4;
int x, y, rotat, blockType;
void sumList(int block_list[16][10], int map_list[16][10]);
int is_crash(int list1[16][10], int list2[16][10]);

int what_height(int map[16][10]){
  // 가장 높이 있는 부분의 좌표를 반환한다. 
  // return : 가장 높이 있는 부분의 좌표 
  // parameter : 배경 데이터  
  for(int i = 15; i>=0; i--){
    for(int j=0; j<10; j++){
      if(map[i][j]) break;
      else return(i);
    }
  }
}

void rotate_block(int block_list[16][10], int map_list[16][10]){
 	// 블럭을 x, y를 중심으로 90도 돌린다. 
 	// return : 없음
	// parameter : 블럭 데이터, 배경 데이터
	int list[16][10];
  	for (int r=0; r<16; r++){
    	for (int c=0; c<10; c++){
      		list[r][c] = block_list[r][c]; 
    	}
  	}
  	int lastRotat=rotat;
	if (blockType==1){
		if (rotat==0){
			rotat=1;
			block_list[y][x-1]=0;
			block_list[y][x-2]=0;
			block_list[y][x+1]=0;
			block_list[y+1][x]=1;
			block_list[y-1][x]=1;
			block_list[y+2][x]=1;
		}else {
			rotat=0;
			block_list[y][x-1]=1;
			block_list[y][x-2]=1;
			block_list[y][x+1]=1;
			block_list[y+1][x]=0;
			block_list[y-1][x]=0;
			block_list[y+2][x]=0;
		}
	} else if (blockType!=2){
		for (int r=y-1; r<=y+1; r++){
			for (int c=x-1; c<x+1; c++){
				block_list[y][x-1]=list[y+1][x];
				block_list[y][x+1]=list[y-1][x];
				block_list[y+1][x]=list[y][x+1];
				block_list[y-1][x]=list[y][x-1];
				block_list[y+1][x-1]=list[y+1][x+1];
				block_list[y-1][x-1]=list[y+1][x-1];
				block_list[y-1][x+1]=list[y-1][x-1];
				block_list[y+1][x+1]=list[y-1][x+1];
			}
		}
	}

  
  	if (is_crash(block_list, map_list)){
    	for (int r=0; r<16; r++){
      		for (int c=0; c<10; c++){
        		block_list[r][c] = list[r][c]; 
      		}
    	}
    	rotat = lastRotat;
  	}
}

void random_block(int block_list[16][10]){
  // 랜덤으로 블럭을 소환한다. 
  //return : 없음  
  //parameter : 블럭 데이터
  srand(time(0)); 
  int num = rand()%7;
  blockType=num;
  switch(num) {
    case 0:
      block_list[0][5]=1;
      block_list[0][4]=1;
      block_list[1][5]=1;
      block_list[1][6]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 1:
      block_list[0][3]=1;
      block_list[0][4]=1;
      block_list[0][5]=1;
      block_list[0][6]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 2:
      block_list[1][4]=1;
      block_list[0][4]=1;
      block_list[0][5]=1;
      block_list[1][5]=1;
      y=0; x=5;
      break;
    case 3:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[1][5]=1;
      block_list[1][4]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 4:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][5]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 5:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][4]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 6:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][6]=1;
      y=0; x=5;
	  rotat=0;
      break;
  }
}


void graphic(int list1[16][10], int list2[16][10]){
  // 블럭 데이터와 배경 데이터를 합쳐서 텍스트로 출력한다. 
  //return : 없음  
  //parameter : 블럭 데이터, 배경 데이터  
  printf("////////////////////////////////////////\n");
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      printf(" %s", (list1[r][c]||list2[r][c])?"@": ".");
    }
    printf("\n");
  }
  printf("/////////////////////////////////////////\n");
}

int is_crash(int list1[16][10], int list2[16][10]){  
  // 블럭 데이터와 배경 데이터가 곂치는 부분이 있는지 확인한다. 
  // return : 곂치는 지에 대한 boolean 값 
  // parameter : 블럭 데이터와 배경 데이터  
  int sum1=0, sum2=0;
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      if (2==list1[r][c]+list2[r][c]){
        return 1;
      }
    }
  }  
  return 0;
}

int drop_block(int block_list[16][10], int map_list[16][10]){
  // 블럭을 한칸 밑으로 이동시키고 밑이 막혔을 때는 그 블럭을 배경에 추가하고 새로운 블럭을 추가한다. 
  // return : 블럭이 밑으로 이동했는지에 대한 boolean 값  
  // 블럭 데이터와 배경 데이터  
  int list[16][10];
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      list[r][c] = block_list[r][c]; 
    }
  }
  for (int r=14; r>=0; r--){
    for (int c=0; c<10; c++){
      block_list[r+1][c] = block_list[r][c]; 
    }
  }
  for (int c=0; c<10; c++){
    block_list[0][c]=0;
  }
  if (is_crash(block_list, map_list)){
    for (int r=0; r<16; r++){
      for (int c=0; c<10; c++){
        block_list[r][c] = list[r][c]; 
      }
    }
    sumList(block_list, map_list);
    random_block(block_list);
  }else {
    y+=1;
    return 1;
  }
}

void sumList(int block_list[16][10], int map_list[16][10]){
  // 블럭데이터에 있는 블럭을 배경 데이터에 추가하고 블럭 데이터는 초기화한다. 
  // return : 없음 
  // parameter : 블럭데이터와 배경데이터  
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      if (block_list[r][c])
        map_list[r][c]=block_list[r][c];
      block_list[r][c]=0; 
    }
  }
} 

void move_block(int block_list[16][10], int map_list[16][10], int moveDirection){
  // 횡방향으로 블럭을 이동시킨다.  
  //return : 없음  
  //parameter : 블럭데이터와 배경데이터, 이동 방향 (왼쪽 -1, 오른쪽 +1) 
  int list[16][10];
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      list[r][c] = block_list[r][c]; 
    }
  }

  for (int r=0; r<16; r++){
     for (int c=(moveDirection==-1?1:9); c!=(moveDirection==-1?10:-1); c=c-moveDirection){
      block_list[r][c+moveDirection] = block_list[r][c];
    }
  }
  
  if (is_crash(block_list, map_list)){
    for (int r=0; r<16; r++){
      for (int c=0; c<10; c++){
        block_list[r][c] = list[r][c]; 
      }
    }
  }else{
    x+=moveDirection;
  }
}

void erase_line(int map_list[16][10], int block_list[16][10]){
  // 한 줄이 꽉 찼는지 검사하고 꽉 찼으면 지운다. 
  //return : 없음  
  //parameter : 배경데이터, 블럭데이터  
  for (int r=14; r>0; r--){
    int sumOfLine=0;
    for (int c=1; c<9; c++){
      sumOfLine+=map_list[r][c];
    }
    if (sumOfLine==8){
      for (int r2=r-1; r2>=0; r2--){
        for (int c=0; c<10; c++){
          map_list[r2+1][c] = map_list[r2][c]; 
        }
      }
      graphic(map_list, block_list);
    }
  }
}

int main(void){

    int map_list[16][10]={
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
  };
  int block_list[16][10]={
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  };
  long currentTime, lastTime=clock(); 
  random_block(block_list);
  while(1){
    currentTime = clock();

    erase_line(map_list, block_list);
    
    if (lastTime+1000 <= currentTime){
      drop_block(block_list, map_list);
      graphic(map_list, block_list);
      lastTime=clock();
    }

    if (GetAsyncKeyState(VK_LEFT)){
      move_block(block_list, map_list, -1);
      Sleep(500);
    } else if (GetAsyncKeyState(VK_RIGHT)){
      move_block(block_list, map_list, 1);
      Sleep(500);
    } else if (GetAsyncKeyState(VK_LSHIFT)){
    	rotate_block(block_list, map_list);
    	Sleep(500);
	} else if (GetAsyncKeyState(VK_DOWN)){
		drop_block(block_list, map_list);
		Sleep(100);
	}
  }
}
