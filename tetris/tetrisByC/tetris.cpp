#include <stdio.h>
#include <time.h>

void sumList(int block_list[16][10], int map_list[16][10]);

int what_height(int map[16][10]){
	// ���� ��Ʈ������ ���̸� ���Ѵ�.
	// return ���� ���� ���� ����Ѵ�.
	// parameter : �� ������
	for(int i = 15; i>=0; i--){
		for(int j=0; j<10; j++){
			if(map[i][j]) break;
			else return(i);
		}
	}
}

void graphic(int list1[16][10], int list2[16][10]){
	//list1�� list2�� ���ļ� �ؽ�Ʈ�� ����Ѵ�.
	//return ���� ����.
	//parameter : �� �����Ϳ� �� ������ 
	printf("////////////////////////////////////////\n");
	for (int r=0; r<16; r++){
		for (int c=0; c<10; c++){
			printf(" %d", list1[r][c]||list2[r][c]);
		}
		printf("\n");
	}
	printf("/////////////////////////////////////////\n");
}

int is_crash(int list1[16][10], int list2[16][10]){  
	// list1�� list2�� ��ġ�� �ȼ��� �ֳ� �˻��Ѵ�.
	// return : ����
	// parameter : �� �����Ϳ� �� ������ 
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
	// list�� ����� block�� ������ ����Ʈ����.(����Ʈ������ �浹�� ������) 
	// return �浹 ���� �� 0, �浿���� �ʾ��� �� 1 
	// ���� ����� list , maplist
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
	}else {
		return 1;
	}
}

void sumList(int block_list[16][10], int map_list[16][10]){
	//block list�� �ִ�block�� map_list�� �ű��.
	// return ����
	// parameter �� ������, �� ���� �� 
	for (int r=0; r<16; r++){
		for (int c=0; c<10; c++){
			if (block_list[r][c])
				map_list[r][c]=block_list[r][c];
			block_list[r][c]=0; 
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
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},	
	};
	int block_list[16][10]={
	{0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
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
	while(1){
		currentTime = clock();
		if (lastTime+1000 <= currentTime){
			drop_block(block_list, map_list);
			graphic(map_list, block_list);
			lastTime=clock();
		}
		
	}
	
}


