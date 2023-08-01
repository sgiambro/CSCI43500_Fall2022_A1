//Gradient

#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>

#define x1 750
#define y1 500




int main(){

	FILE* inp;
	FILE* outp;
	unsigned char img1[y1][x1], img2[y1][x1], img3[y1][x1] , output[y1][x1] , output2[y1][x1] , TX[3][3] , TY[3][3] , FX[5][5] , FY[5][5];
	
	int valH = 0;
	int valV = 0;
	int sum = 0;
	int gradient = 0;
	
	//3x3 horizontal
	TX[0][0] = -1; TX[0][1] = 0; TX[0][2] = 1; 
	TX[1][0] = -2; TX[1][1] = 0; TX[1][2] = 2;  
	TX[2][0] = -1; TX[2][1] = 0; TX[2][2] = 1;

	//3x3 vertical
	TY[0][0] = -1; TY[0][1] = -2; TY[0][2] = -1;    
	TY[1][0] =  0; TY[1][1] =  0; TY[1][2] =  0;    
	TY[2][0] =  1; TY[2][1] =  2; TY[2][2] =  1;
	
	//5x5 horizontal -- std::cout << value << "====";
	FX[0][0] = -1; FX[0][1] = -2; FX[0][2] = 0; FX[0][3] = 2; FX[0][4] = 1; 
	FX[1][0] = -2; FX[1][1] = -4; FX[1][2] = 0; FX[1][3] = 4; FX[1][4] = 2; 
	FX[2][0] = -4; FX[2][1] = -8; FX[2][2] = 0; FX[2][3] = 8; FX[2][4] = 4; 
	FX[3][0] = -2; FX[3][1] = -4; FX[3][2] = 0; FX[3][3] = 4; FX[3][4] = 2;
	FX[4][0] = -1; FX[4][1] = -2; FX[4][2] = 0; FX[4][3] = 2; FX[4][4] = 1;

	//5x5 vertical
	FY[0][0] = -1; FY[0][1] = -2; FY[0][2] = -4; FY[0][3] = -2; FY[0][4] = -1; 
	FY[1][0] = -2; FY[1][1] = -4; FY[1][2] = -8; FY[1][3] = -4; FY[1][4] = -2; 
	FY[2][0] =  0; FY[2][1] =  0; FY[2][2] =  0; FY[2][3] =  0; FY[2][4] =  0; 
	FY[3][0] =  2; FY[3][1] =  4; FY[3][2] =  8; FY[3][3] =  4; FY[3][4] =  2;
	FY[4][0] =  1; FY[4][1] =  2; FY[4][2] =  4; FY[4][3] =  2; FY[4][4] =  1;
	
	
	//unesco---------------------------------------------------------------------------------------------------------------
	inp = fopen("unesco-1.raw" , "rb");
	fread(img1 , 1 , y1*x1 , inp);
	
	
	//3x3 gradient
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			valH =   (img1[j - 1][i - 1] * TX[0][0]) + (img1[j - 1][i] * TX[0][1]) + (img1[j - 1][i + 1] * TX[0][2])
					+ (img1[j][i - 1] * TX[1][0])     + (img1[j][i] * TX[1][1])     + (img1[j][i + 1] * TX[1][2])
					+ (img1[j + 1][i - 1] * TX[2][0]) + (img1[j + 1][i] * TX[2][1]) + (img1[j + 1][i + 1] * TX[2][2]);
					
			sum = (img1[j - 1][i + 1] * TX[0][2]) + 
				  (img1[j][i + 1] * TX[1][2]) + 
				  (img1[j + 1][i + 1] * TX[2][2]);	  
			if (sum == 0) sum = 1;
			
			valH = valH / sum;
			
					
			valV =   (img1[j - 1][i - 1] * TY[0][0]) + (img1[j - 1][i] * TY[0][1]) + (img1[j - 1][i + 1] * TY[0][2])
					+ (img1[j][i - 1] * TY[1][0])     + (img1[j][i] * TY[1][1])     + (img1[j][i + 1] * TY[1][2])
					+ (img1[j + 1][i - 1] * TY[2][0]) + (img1[j + 1][i] * TY[2][1]) + (img1[j + 1][i + 1] * TY[2][2]);
					
			sum = (img1[j + 1][i - 1] * TY[2][0]) + 
				  (img1[j + 1][i] * TY[2][1]) + 
				  (img1[j + 1][i + 1] * TY[2][2]);
			if (sum == 0) sum = 1;
			
			valV = valV / sum;
			
			
			gradient = sqrt( (valH*valH) + (valV*valV) );				
			
			output[j][i] = gradient;
			
		}
	}
	
	outp = fopen("unescoThreeGradient.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//3x3 Edge
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			if( output[j][i]>output[j][i-1] && output[j][i]>=output[j][i+1] && output[j][i]>220 || 
				output[j][i]<output[j][i-1] && output[j][i]<=output[j][i+1] && output[j][i]<-220) {
				
				output2[j][i] = 200;
			}
			else output2[j][i] = 0;
			
		}	
	}
	
	outp = fopen("unescoThreeEdge.raw" , "wb");
	fwrite(output2 , 1 , y1*x1 , outp);
	fclose(outp);
	
	
	//5x5 gradient
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			valH   =   (img1[j - 2][i - 2] * FX[0][0]) + (img1[j - 2][i -1] * FX[0][1]) + (img1[j - 2][i] * FX[0][2]) + (img1[j - 2][i + 1] * FX[0][3]) + (img1[j - 2][i + 2] * FX[0][4])
					+ (img1[j - 1][i - 2] * FX[1][0]) + (img1[j - 1][i -1] * FX[1][1]) + (img1[j - 1][i] * FX[1][2]) + (img1[j - 1][i + 1] * FX[1][3]) + (img1[j - 1][i + 2] * FX[1][4])
					+ (img1[j][i - 2] * FX[2][0]) + (img1[j][i -1] * FX[2][1]) + (img1[j][i] * FX[2][2]) + (img1[j][i + 1] * FX[2][3]) + (img1[j][i + 2] * FX[2][4])
					+ (img1[j + 1][i - 2] * FX[3][0]) + (img1[j + 1][i -1] * FX[3][1]) + (img1[j + 1][i] * FX[3][2]) + (img1[j + 1][i + 1] * FX[3][3]) + (img1[j + 1][i + 2] * FX[3][4])
					+ (img1[j + 2][i - 2] * FX[4][0]) + (img1[j + 2][i -1] * FX[4][1]) + (img1[j + 2][i] * FX[4][2]) + (img1[j + 2][i + 1] * FX[4][3]) + (img1[j + 2][i + 2] * FX[4][4]);
			
			sum = (img1[j - 2][i + 1] * FX[0][3]) + (img1[j - 2][i + 2] * FX[0][4]) + 
				  (img1[j - 1][i + 1] * FX[1][3]) + (img1[j - 1][i + 2] * FX[1][4]) +
				  (img1[j][i + 1] * FX[2][3]) + (img1[j][i + 2] * FX[2][4]) +
				  (img1[j + 1][i + 1] * FX[3][3]) + (img1[j + 1][i + 2] * FX[3][4]) +
				  (img1[j + 2][i + 1] * FX[4][3]) + (img1[j + 2][i + 2] * FX[4][4]);
			if (sum == 0) sum = 1;
			
			valH = valH / sum;
			
			
			valV   =   (img1[j - 2][i - 2] * FY[0][0]) + (img1[j - 2][i -1] * FY[0][1]) + (img1[j - 2][i] * FY[0][2]) + (img1[j - 2][i + 1] * FY[0][3]) + (img1[j - 2][i + 2] * FY[0][4])
					+ (img1[j - 1][i - 2] * FY[1][0]) + (img1[j - 1][i -1] * FY[1][1]) + (img1[j - 1][i] * FY[1][2]) + (img1[j - 1][i + 1] * FY[1][3]) + (img1[j - 1][i + 2] * FY[1][4])
					+ (img1[j][i - 2] * FY[2][0]) + (img1[j][i -1] * FY[2][1]) + (img1[j][i] * FY[2][2]) + (img1[j][i + 1] * FY[2][3]) + (img1[j][i + 2] * FY[2][4])
					+ (img1[j + 1][i - 2] * FY[3][0]) + (img1[j + 1][i -1] * FY[3][1]) + (img1[j + 1][i] * FY[3][2]) + (img1[j + 1][i + 1] * FY[3][3]) + (img1[j + 1][i + 2] * FY[3][4])
					+ (img1[j + 2][i - 2] * FY[4][0]) + (img1[j + 2][i -1] * FY[4][1]) + (img1[j + 2][i] * FY[4][2]) + (img1[j + 2][i + 1] * FY[4][3]) + (img1[j + 2][i + 2] * FY[4][4]);
			
			sum = (img1[j + 1][i - 2] * FY[3][0]) + (img1[j + 1][i -1] * FY[3][1]) + 
				  (img1[j + 1][i] * FY[3][2]) + (img1[j + 1][i + 1] * FY[3][3]) + 
				  (img1[j + 1][i + 2] * FY[3][4]) + (img1[j + 2][i - 2] * FY[4][0]) + 
				  (img1[j + 2][i -1] * FY[4][1]) + (img1[j + 2][i] * FY[4][2]) + 
				  (img1[j + 2][i + 1] * FY[4][3]) + (img1[j + 2][i + 2] * FY[4][4]);
			if (sum == 0) sum = 1;
			
			valV = valV / sum;
			
			
			gradient = sqrt( (valH*valH) + (valV*valV) );  					
			
			output[j][i] = gradient;
			
		}
	}
	
	outp = fopen("unescoFiveGradient.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 Edge
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			if( output[j][i]>output[j][i-1] && output[j][i]>=output[j][i+1] && output[j][i]>150 || 
				output[j][i]<output[j][i-1] && output[j][i]<=output[j][i+1] && output[j][i]<-150) {
				
				output2[j][i] = 200;
			}
			else output2[j][i] = 0;
			
		}	
	}
	
	outp = fopen("unescoFiveEdge.raw" , "wb");
	fwrite(output2 , 1 , y1*x1 , outp);
	fclose(outp);
		
	fclose(inp);	
	
	//Trees -------------------------------------------------------------------------------------------------------------
	inp = fopen("trees.raw" , "rb");
	fread(img2 , 1 , y1*x1 , inp);
	
	//3x3 Gradient
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			valH =   (img2[j - 1][i - 1] * TX[0][0]) + (img2[j - 1][i] * TX[0][1]) + (img2[j - 1][i + 1] * TX[0][2])
					+ (img2[j][i - 1] * TX[1][0])     + (img2[j][i] * TX[1][1])     + (img2[j][i + 1] * TX[1][2])
					+ (img2[j + 1][i - 1] * TX[2][0]) + (img2[j + 1][i] * TX[2][1]) + (img2[j + 1][i + 1] * TX[2][2]);
			
			sum = (img2[j - 1][i + 1] * TX[0][2]) + 
				  (img2[j][i + 1] * TX[1][2]) + 
				  (img2[j + 1][i + 1] * TX[2][2]);
			if (sum == 0) sum = 1;
			
			valH = valH / sum;
						
						
			valV =   (img2[j - 1][i - 1] * TY[0][0]) + (img2[j - 1][i] * TY[0][1]) + (img2[j - 1][i + 1] * TY[0][2])
					+ (img2[j][i - 1] * TY[1][0])     + (img2[j][i] * TY[1][1])     + (img2[j][i + 1] * TY[1][2])
					+ (img2[j + 1][i - 1] * TY[2][0]) + (img2[j + 1][i] * TY[2][1]) + (img2[j + 1][i + 1] * TY[2][2]);
			
			sum = (img2[j + 1][i - 1] * TY[2][0]) + 
				  (img2[j + 1][i] * TY[2][1]) + 
				  (img2[j + 1][i + 1] * TY[2][2]);
			if (sum == 0) sum = 1;
			
			valV = valV / sum;
			
			
			gradient = sqrt( (valH*valH) + (valV*valV) );  					
			
			output[j][i] = gradient;
			
		}
	}
	
	outp = fopen("treesThreeGradient.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//3x3 Edge
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			if( output[j][i]>output[j][i-1] && output[j][i]>=output[j][i+1] && output[j][i]>220 || 
				output[j][i]<output[j][i-1] && output[j][i]<=output[j][i+1] && output[j][i]<-220) {
				
				output2[j][i] = 200;
			}
			else output2[j][i] = 0;
			
		}	
	}
	
	outp = fopen("treesThreeEdge.raw" , "wb");
	fwrite(output2 , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 Gradient
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			valH =   (img2[j - 2][i - 2] * FX[0][0]) + (img2[j - 2][i -1] * FX[0][1]) + (img2[j - 2][i] * FX[0][2]) + (img2[j - 2][i + 1] * FX[0][3]) + (img2[j - 2][i + 2] * FX[0][4])
					+ (img2[j - 1][i - 2] * FX[1][0]) + (img2[j - 1][i -1] * FX[1][1]) + (img2[j - 1][i] * FX[1][2]) + (img2[j - 1][i + 1] * FX[1][3]) + (img2[j - 1][i + 2] * FX[1][4])
					+ (img2[j][i - 2] * FX[2][0]) + (img2[j][i -1] * FX[2][1]) + (img2[j][i] * FX[2][2]) + (img2[j][i + 1] * FX[2][3]) + (img2[j][i + 2] * FX[2][4])
					+ (img2[j + 1][i - 2] * FX[3][0]) + (img2[j + 1][i -1] * FX[3][1]) + (img2[j + 1][i] * FX[3][2]) + (img2[j + 1][i + 1] * FX[3][3]) + (img2[j + 1][i + 2] * FX[3][4])
					+ (img2[j + 2][i - 2] * FX[4][0]) + (img2[j + 2][i -1] * FX[4][1]) + (img2[j + 2][i] * FX[4][2]) + (img2[j + 2][i + 1] * FX[4][3]) + (img2[j + 2][i + 2] * FX[4][4]);
			
			sum = (img2[j - 2][i + 1] * FX[0][3]) + (img2[j - 2][i + 2] * FX[0][4]) + 
				  (img2[j - 1][i + 1] * FX[1][3]) + (img2[j - 1][i + 2] * FX[1][4]) +
				  (img2[j][i + 1] * FX[2][3]) + (img2[j][i + 2] * FX[2][4]) +
				  (img2[j + 1][i + 1] * FX[3][3]) + (img2[j + 1][i + 2] * FX[3][4]) +
				  (img2[j + 2][i + 1] * FX[4][3]) + (img2[j + 2][i + 2] * FX[4][4]);
			if (sum == 0) sum = 1;
			
			valH = valH / sum;
			
			
			valV =   (img2[j - 2][i - 2] * FY[0][0]) + (img2[j - 2][i -1] * FY[0][1]) + (img2[j - 2][i] * FY[0][2]) + (img2[j - 2][i + 1] * FY[0][3]) + (img2[j - 2][i + 2] * FY[0][4])
					+ (img2[j - 1][i - 2] * FY[1][0]) + (img2[j - 1][i -1] * FY[1][1]) + (img2[j - 1][i] * FY[1][2]) + (img2[j - 1][i + 1] * FY[1][3]) + (img2[j - 1][i + 2] * FY[1][4])
					+ (img2[j][i - 2] * FY[2][0]) + (img2[j][i -1] * FY[2][1]) + (img2[j][i] * FY[2][2]) + (img2[j][i + 1] * FY[2][3]) + (img2[j][i + 2] * FY[2][4])
					+ (img2[j + 1][i - 2] * FY[3][0]) + (img2[j + 1][i -1] * FY[3][1]) + (img2[j + 1][i] * FY[3][2]) + (img2[j + 1][i + 1] * FY[3][3]) + (img2[j + 1][i + 2] * FY[3][4])
					+ (img2[j + 2][i - 2] * FY[4][0]) + (img2[j + 2][i -1] * FY[4][1]) + (img2[j + 2][i] * FY[4][2]) + (img2[j + 2][i + 1] * FY[4][3]) + (img2[j + 2][i + 2] * FY[4][4]);
			
			sum = (img2[j + 1][i - 2] * FY[3][0]) + (img2[j + 1][i -1] * FY[3][1]) + 
				  (img2[j + 1][i] * FY[3][2]) + (img2[j + 1][i + 1] * FY[3][3]) + 
				  (img2[j + 1][i + 2] * FY[3][4]) + (img2[j + 2][i - 2] * FY[4][0]) + 
				  (img2[j + 2][i -1] * FY[4][1]) + (img2[j + 2][i] * FY[4][2]) + 
				  (img2[j + 2][i + 1] * FY[4][3]) + (img2[j + 2][i + 2] * FY[4][4]);
			if (sum == 0) sum = 1;
			
			valV = valV / sum;
			
			
			gradient = sqrt( (valH*valH) + (valV*valV) );  					
			
			output[j][i] = gradient;
			
		}
	}
	
	outp = fopen("treesFiveGradient.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 Edge
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			if( output[j][i]>output[j][i-1] && output[j][i]>=output[j][i+1] && output[j][i]>150 || 
				output[j][i]<output[j][i-1] && output[j][i]<=output[j][i+1] && output[j][i]<-150) {
				
				output2[j][i] = 200;
			}
			else output2[j][i] = 0;
			
		}	
	}
	
	outp = fopen("treesFiveEdge.raw" , "wb");
	fwrite(output2 , 1 , y1*x1 , outp);
	fclose(outp);
	
	
	fclose(inp);
	
	//Circle---------------------------------------------------------------------------------------------------------------
	inp = fopen("circle.raw" , "rb");
	fread(img3 , 1 , y1*x1 , inp);
	
	
	//3x3 Gradient
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			valH =   (img3[j - 1][i - 1] * TX[0][0]) + (img3[j - 1][i] * TX[0][1]) + (img3[j - 1][i + 1] * TX[0][2])
					+ (img3[j][i - 1] * TX[1][0])     + (img3[j][i] * TX[1][1])     + (img3[j][i + 1] * TX[1][2])
					+ (img3[j + 1][i - 1] * TX[2][0]) + (img3[j + 1][i] * TX[2][1]) + (img3[j + 1][i + 1] * TX[2][2]);
			
			sum = (img3[j - 1][i + 1] * TX[0][2]) + 
				  (img3[j][i + 1] * TX[1][2]) + 
				  (img3[j + 1][i + 1] * TX[2][2]);
			if (sum == 0) sum = 1;
			
			valH = valH / sum;	
			
			
			valV =   (img3[j - 1][i - 1] * TY[0][0]) + (img3[j - 1][i] * TY[0][1]) + (img3[j - 1][i + 1] * TY[0][2])
					+ (img3[j][i - 1] * TY[1][0])     + (img3[j][i] * TY[1][1])     + (img3[j][i + 1] * TY[1][2])
					+ (img3[j + 1][i - 1] * TY[2][0]) + (img3[j + 1][i] * TY[2][1]) + (img3[j + 1][i + 1] * TY[2][2]);
			
			sum = (img3[j + 1][i - 1] * TY[2][0]) + 
				  (img3[j + 1][i] * TY[2][1]) + 
				  (img3[j + 1][i + 1] * TY[2][2]);
			if (sum == 0) sum = 1;
			
			valV = valV / sum;
			
			
			gradient = sqrt( (valH*valH) + (valV*valV) );  					
			
			output[j][i] = gradient;
			
		}
	}
	
	outp = fopen("circleThreeGradient.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//3x3 Edge
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			if( output[j][i]>output[j][i-1] && output[j][i]>=output[j][i+1] && output[j][i]>220 || 
				output[j][i]<output[j][i-1] && output[j][i]<=output[j][i+1] && output[j][i]<-220) {
				
				output2[j][i] = 200;
			}
			else output2[j][i] = 0;
			
		}	
	}
	
	outp = fopen("circleThreeEdge.raw" , "wb");
	fwrite(output2 , 1 , y1*x1 , outp);
	fclose(outp);
	
	
	
	//5x5 Gradient
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			valH =   (img3[j - 2][i - 2] * FX[0][0]) + (img3[j - 2][i -1] * FX[0][1]) + (img3[j - 2][i] * FX[0][2]) + (img3[j - 2][i + 1] * FX[0][3]) + (img3[j - 2][i + 2] * FX[0][4])
					+ (img3[j - 1][i - 2] * FX[1][0]) + (img3[j - 1][i -1] * FX[1][1]) + (img3[j - 1][i] * FX[1][2]) + (img3[j - 1][i + 1] * FX[1][3]) + (img3[j - 1][i + 2] * FX[1][4])
					+ (img3[j][i - 2] * FX[2][0]) + (img3[j][i -1] * FX[2][1]) + (img3[j][i] * FX[2][2]) + (img3[j][i + 1] * FX[2][3]) + (img3[j][i + 2] * FX[2][4])
					+ (img3[j + 1][i - 2] * FX[3][0]) + (img3[j + 1][i -1] * FX[3][1]) + (img3[j + 1][i] * FX[3][2]) + (img3[j + 1][i + 1] * FX[3][3]) + (img3[j + 1][i + 2] * FX[3][4])
					+ (img3[j + 2][i - 2] * FX[4][0]) + (img3[j + 2][i -1] * FX[4][1]) + (img3[j + 2][i] * FX[4][2]) + (img3[j + 2][i + 1] * FX[4][3]) + (img3[j + 2][i + 2] * FX[4][4]);
			
			sum = (img3[j - 2][i + 1] * FX[0][3]) + (img3[j - 2][i + 2] * FX[0][4]) + 
				  (img3[j - 1][i + 1] * FX[1][3]) + (img3[j - 1][i + 2] * FX[1][4]) +
				  (img3[j][i + 1] * FX[2][3]) + (img3[j][i + 2] * FX[2][4]) +
				  (img3[j + 1][i + 1] * FX[3][3]) + (img3[j + 1][i + 2] * FX[3][4]) +
				  (img3[j + 2][i + 1] * FX[4][3]) + (img3[j + 2][i + 2] * FX[4][4]);
			if (sum == 0) sum = 1;
			
			valH = valH / sum;
						
			
			valV =   (img3[j - 2][i - 2] * FY[0][0]) + (img3[j - 2][i -1] * FY[0][1]) + (img3[j - 2][i] * FY[0][2]) + (img3[j - 2][i + 1] * FY[0][3]) + (img3[j - 2][i + 2] * FY[0][4])
					+ (img3[j - 1][i - 2] * FY[1][0]) + (img3[j - 1][i -1] * FY[1][1]) + (img3[j - 1][i] * FY[1][2]) + (img3[j - 1][i + 1] * FY[1][3]) + (img3[j - 1][i + 2] * FY[1][4])
					+ (img3[j][i - 2] * FY[2][0]) + (img3[j][i -1] * FY[2][1]) + (img3[j][i] * FY[2][2]) + (img3[j][i + 1] * FY[2][3]) + (img3[j][i + 2] * FY[2][4])
					+ (img3[j + 1][i - 2] * FY[3][0]) + (img3[j + 1][i -1] * FY[3][1]) + (img3[j + 1][i] * FY[3][2]) + (img3[j + 1][i + 1] * FY[3][3]) + (img3[j + 1][i + 2] * FY[3][4])
					+ (img3[j + 2][i - 2] * FY[4][0]) + (img3[j + 2][i -1] * FY[4][1]) + (img3[j + 2][i] * FY[4][2]) + (img3[j + 2][i + 1] * FY[4][3]) + (img3[j + 2][i + 2] * FY[4][4]);
			
			sum = (img3[j + 1][i - 2] * FY[3][0]) + (img3[j + 1][i -1] * FY[3][1]) + 
				  (img3[j + 1][i] * FY[3][2]) + (img3[j + 1][i + 1] * FY[3][3]) + 
				  (img3[j + 1][i + 2] * FY[3][4]) + (img3[j + 2][i - 2] * FY[4][0]) + 
				  (img3[j + 2][i -1] * FY[4][1]) + (img3[j + 2][i] * FY[4][2]) + 
				  (img3[j + 2][i + 1] * FY[4][3]) + (img3[j + 2][i + 2] * FY[4][4]);
			if (sum == 0) sum = 1;
			
			valV = valV / sum;
			
			
			gradient = sqrt( (valH*valH) + (valV*valV) );  					
			
			output[j][i] = gradient;
			
		}
	}
	
	outp = fopen("circleFiveGradient.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 Edge
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			if( output[j][i]>output[j][i-1] && output[j][i]>=output[j][i+1] && output[j][i]>150 || 
				output[j][i]<output[j][i-1] && output[j][i]<=output[j][i+1] && output[j][i]<-150) {
				
				output2[j][i] = 200;
			}
			else output2[j][i] = 0;
			
		}	
	}
	
	outp = fopen("circleFiveEdge.raw" , "wb");
	fwrite(output2 , 1 , y1*x1 , outp);
	fclose(outp);

	
	fclose(inp);

}//end main **/