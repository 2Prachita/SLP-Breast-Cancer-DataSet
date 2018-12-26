#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>

using namespace std;

int AT;
int CASE_train;
int CASE_test;

float normalise (float x, float minn, float maxx, float a)
{
	return((x-a)/(maxx-minn));
}

int main()
{
	FILE *out;
	out = fopen("training_output.txt","w");
	cout<<"ENTER THE NO OF ATTRIBUTES\n";
	cin>>AT;
	//printf("%d",AT);
	cout<<"ENTER THE NO OF TRAINING CASES\n";
	cin>>CASE_train;
	//printf("%d",CASE_train);
	cout<<"ENTER THE NO OF TESTING CASES\n";
	cin>>CASE_test;
	//printf("%d",CASE_test);
	
	float test_data[CASE_test][AT];
	float train_data[CASE_train][AT];
	float out_d_test[CASE_test],out_d_train[CASE_train];
	float W[AT]={0,0,0,0,0,0,0,0,0};
	
	
			//READING INPUT
	
	
	
	FILE *fp;		
	char name[10];
	float c;
	
	cout<<"ENTER INPUT FILE NAME\n";
	cin>>name;
	//printf("%s",name);					//TRAINING DATA
	
	fp = fopen(name,"r");
	
	if(fp==NULL)
	{
		cout<<"ERROR READING INPUT FILE\n";
	}

	for(int i=0; i<CASE_train; i++)
	{
		for(int j=0; j<AT + 1; j++)
		{
			if(j<AT)
			{	
				fscanf(fp,"%f",&c);
				train_data[i][j]=c;
				//cout<<train_data[i][j]<<"  ";	
			}
			else
			{
				fscanf(fp,"%f",&c);
				out_d_train[i]=c;
				//cout<<out_d_train[i]<<"  ";
			}
		}
	//	cout<<endl;
	}
	
	if(!(feof(fp)))
	{
		fclose(fp);
	}
	//cout<<endl<<endl<<endl;
	cout<<"ENTER TEST FILE NAME\n";
	cin>>name;
														//TESTING DATA READ
	fp = fopen(name,"r");
	
	if(fp==NULL)
	{
		cout<<"ERROR READING INPUT FILE\n";
	}

	for(int i=0; i<CASE_test; i++)
	{
		for(int j=0; j<AT + 1; j++)
		{
			if(j<AT)
			{	
				fscanf(fp,"%f",&c);
				test_data[i][j]=c;
				//cout<<test_data[i][j]<<"  ";	
			}
			else
			{
				fscanf(fp,"%f",&c);
				out_d_test[i]=c;
				//cout<<out_d_test[i]<<"  ";
			}
		}
		//	cout<<endl;
	}
	
	if(!(feof(fp)))
	{
		fclose(fp);
	}
	
	
					//NORMALISATION
					
					
	float test[CASE_test][AT], train[CASE_train][AT];
	float test_des[CASE_test], train_des[CASE_train];
	float min=10000, max=0, avg=0;
	
	for(int i=0; i<AT; i++)
	{
		for(int j = 0; j < CASE_train; j++ )
		{
			avg=avg+train_data[j][i];
			if(train_data[j][i] > max)
			{
				max = train_data[j][i];
			}
			else if ( train_data[j][i] < min)
			{
				min = train_data[j][i];
			}
		}
		for(int j = 0; j<CASE_test; j++ )
		{
			avg=avg+test_data[j][i];
			if(test_data[j][i] > max)
			{
				max = test_data[j][i];
			}
			else if ( test_data[j][i] < min)
			{
				min = test_data[j][i];
			}
		}
		avg=avg/(CASE_test+CASE_train);
		/*cout<<endl;
		cout<<endl;
		
		cout<<"MIN : "<<min<<endl;
		cout<<"MAX : "<<max<<endl;
		cout<<"AVG : "<<avg<<endl;
		cout<<endl;
		cout<<endl;*/
		
		for(int j = 0; j < CASE_train; j++)
		{
			train[j][i] = normalise(train_data[j][i] , min, max, avg);
			//cout<<train[j][i]<<"  "; 
		}
		cout<<endl;
		for(int j = 0; j < CASE_test; j++)
		{
			test[j][i] = normalise(test_data[j][i] , min, max, avg);
			//cout<<test[j][i]<<"  ";
		}
		cout<<endl;
	}
	
	
	for(int i = 0; i < CASE_train; i++)
	{
		for(int j = 0; j < AT; j++)
		{
			if(train[i][j] > 0 )
			{
				train[i][j] = 1 ;
				//cout<<train[i][j]<<"  ";
			}
			else
			{
				train[i][j] = -1 ;
				//cout<<train[i][j]<<"  ";
			}
		}
		//cout<<endl;
	}
	
	for(int i = 0; i < CASE_test; i++)
	{
		for(int j = 0; j < AT; j++)
		{
			if(test[i][j] > 0 )
			{
				test[i][j] = 1 ;
				//cout<<test[i][j]<<"  ";
			}
			else
			{
				test[i][j] = -1 ;
				//cout<<test[i][j]<<"  ";
			}
		}
		//cout<<endl;
	}
	
	for(int i = 0; i < CASE_train; i++)
	{
		if(out_d_train[i] == 1)
		{
			train_des[i] = 1;
			cout<<train_des[i]<<"  ";
		}
		else
		{
			train_des[i] = -1;
			cout<<train_des[i]<<"  ";	
		}
		cout<<endl;
	}
	
	for(int i = 0; i < CASE_test; i++)
	{
		if(out_d_test[i] == 1)
		{
			test_des[i] = 1;
			cout<<test_des[i]<<"  ";
		}
		else
		{
			test_des[i] = -1;
			cout<<test_des[i]<<"  ";	
		}
		cout<<endl;
	}

	
					//TRAINING
	
	
	int Epoch =174, count = 0, flag = 0; 
	float Learning_rate = 0.2, Cal_out, v = 0;

	while( Epoch > 0 && flag == 0)
	{
		cout<<"EPOCH : "<<Epoch<<endl;
		fprintf(out,"EPOCH : %d\n",Epoch);
		
		for(int i = 0; i < CASE_train; i++)
		{
			cout<<"INPUT : "<<i<<endl;
			fprintf(out,"INPUT : %d\n",i);
			cout<<"WEIGHTS :";
			fprintf(out,"WEIGHTS : \n");
			
			for(int j = 0; j < AT; j++)
			{
				cout<<W[j]<<" ";
				fprintf(out,"%f  ",W[j]);
			}
			fprintf(out,"\n");
			cout<<endl;
			for(int j = 0; j < AT; j++)
			{
					v = v + ( train[i][j]*W[j]);	//LINEAR COMBINER
			}
			v=v+0;
			if(v >= 0)
			{
				Cal_out = 1;
				cout<<"CALCULATED OUTPUT : "<<Cal_out<<endl;
				fprintf(out,"CALCULATED OUTPUT : %f \n",Cal_out);
			}
			else
			{
				Cal_out=-1;
				cout<<"CALCULATED OUTPUT : "<<Cal_out<<endl;
				fprintf(out,"CALCULATED OUTPUT : %f \n",Cal_out);
			}
			cout<<"DESIRED OUTPUT : "<<train_des[i]<<endl;
			fprintf(out,"DESIRED OUTPUT : %f \n",train_des[i]);
			if(Cal_out != train_des[i])
			{
							//CHANGING WEIGHTS
				
				cout<<"\t \t \t MISSCLASSIFIED"<<endl;
				fprintf(out,"\t \t \t MISSCLASSIFIED \n");
				int a=0;
				for(a=0; a<AT; a++)
				{
					W[a]=W[a]+Learning_rate*(-Cal_out+train_des[i])*train[i][a];
					//count=0;
				}
			}
			else
			{
				cout<<"\t \t \t CLASSIFIED"<<endl;
				fprintf(out,"\t \t \t CLASSIFIED \n");
			}	
		}
		/*if(count <= 94 && count > 70)
		{
			flag = 1;
		}
		else
		{
			flag = 0;
		}*/	
		Epoch--;
	} 
	//cout<<"MISSCLASSIFICATION !"<<count<<endl;
	cout<<"FINAL WEIGHTS :";
	fprintf(out,"FINAL WEIGHTS : ");
	for(int j = 0; j < AT; j++)
	{
		cout<<W[j]<<" ";
		fprintf(out,"%f  ",W[j]);
	}
	fclose(out);
	out = fopen("testing_output.txt","w");
	fprintf(out,"FINAL WEIGHTS : ");
	for(int j = 0; j < AT; j++)
	{
		//cout<<W[j]<<" ";
		fprintf(out,"%f  ",W[j]);
	}
	fprintf(out,"\n");
	count=0;
	for(int i = 0; i < CASE_test; i++)
	{
		cout<<"\nTEST : "<<i<<endl;
		fprintf(out,"\nTEST : %d\n",i);
		for(int j = 0; j < AT; j++)
		{
			v = v + ( test[i][j]*W[j]);	//LINEAR COMBINER
		}
		if(v >= 0)
		{
			Cal_out = 1;
			cout<<"CALCULATED OUTPUT : "<<Cal_out<<endl;
			fprintf(out,"CALCULATED OUTPUT : %f \n",Cal_out);
		}
		else
		{
			Cal_out=-1;
			cout<<"CALCULATED OUTPUT : "<<Cal_out<<endl;
			fprintf(out,"CALCULATED OUTPUT : %f \n",Cal_out);
		}
		cout<<"DESIRED OUTPUT : "<<test_des[i]<<endl;
		fprintf(out,"DESIRED OUTPUT : %f \n",train_des[i]);
		if(Cal_out != test_des[i])
		{
			cout<<"MISSCLASSIFIED \n\n";
			fprintf(out,"MISSCLASSIFIED \n\n");
			count++;
		}
		
	}
	int cls;
	cls=(CASE_test) - (count); 
	cout<<(CASE_test-count )<<" OF "<<CASE_test<<endl;
	fprintf(out,"%d  OF  %x \n",cls,CASE_test);
	
	float accuracy = (float)(CASE_test-count )/(float) CASE_test ;
	cout<<"ACCURACY : "<<accuracy<<endl;
	fprintf(out,"ACCURACY : %f \n\n",accuracy);
	fclose(out);
	return(0);
}
