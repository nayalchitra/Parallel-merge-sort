#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX 7
#define N 2
int a[]={9,5,1,3,10,8,2};

struct v
{
	int l;
	int h;
};

void  merge(int l,int mid,int n)
{
	int i,j,k;
	int n1=mid-l+1;
	int n2=n-mid;
	int L[n1],R[n2];
	for(i=0;i<n1;i++)
		L[i] = a[l+i];
	for(j=0;j<n2;j++)
		R[j] = a[mid+1+j];
	i=0;j=0;k=l;
	while(i<n1 && j<n2)
	{
		if(L[i]<=R[j])
		{
			a[k]=L[i];
			i++;
		}
		else
		{
			a[k]=R[j];
			j++;
		}
		k++;
	}
	while(i<n1)
	{
		a[k]=L[i];
		k++;
		i++;
	}
	while(j<n2)
	{
		a[k]=R[j];
		k++;
		j++;
	}
}

void* mergesort(void * arg)
{
	struct v *data=arg;
	int mid = ((data->l)+(data->h))/2;
	struct v p[N];
	pthread_t thread[N];
	p[0].l=(data->l);
	p[0].h=mid;
	p[1].l=(mid+1);
	p[1].h=(data->h);
	if((data->l) < (data->h))
	{
		int i;
		for(i=0;i<N;i++)
			pthread_create(&thread[i],NULL,mergesort,&p[i]);
		for(i=0;i<N;i++)
			pthread_join(thread[i],NULL);
		merge(data->l,mid,data->h);
	}
}

int main(int argc, char * argv[])
{
	
	pthread_t t;
	struct v *data=(struct v*)malloc(sizeof(struct v));
	data->l=0;
	data->h=MAX-1;
	pthread_create(&t,NULL,mergesort,data);
	pthread_join(t,NULL);
	int i;	
	printf("sorted array is \n");
	for(i=0;i<MAX;i++)
		printf("%d ",a[i]);
	printf("\n");
}
