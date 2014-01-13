#include "main.h"






int YUV420(HWND hDlg)
{
	FILE *yuvfile;
	int Array_72x88[72][88];
	int	Array_144x88[144][88];
	int	Array_144x176[144][176];
	int cb[144][88],cr[144][88];

	long int Len_Y = 176 * 144 , Len_U = 88 * 72, Len_V = 88 * 72,Size;
	int a,b,c,d,i,j,m,n;
	int Height = 144, Width = 176;
	err=fopen_s(&yuvfile ,szFile1,"rb");
	if(err)
	{
		MessageBox(NULL, L"fopen Failed", L"Error", MB_OK);
		return 0;
	}

	fseek(yuvfile,0L,SEEK_END);
	No_OF_FRAMES = ftell(yuvfile) / (Len_Y + Len_U + Len_V);
	rewind(yuvfile);
	//Converting 4:2:0 YUV to 4:2:2 YUV

	for ( Frame_Count = 0 ; Frame_Count < No_OF_FRAMES ; Frame_Count++ )
	{


		for ( m = 0; m < 144; m++)
			for ( n = 0; n < 176; n++)
				y[m][n] = fgetc(yuvfile);                      //Y values



		for ( Loop = 1 ; Loop <= 2; Loop++)
		{
			m = n = 0 ;

			Size = Loop == 1 ? Len_U : Len_V;
			for ( i = 0; i < Size; i++ ) 
			{
				Array_72x88[m][n++] = fgetc(yuvfile);     //U and V value from YUV420
				if ( n > 87 ) 
				{
					n = 0;
					m++;
				}
			} 


			for ( j = 0; j < 88 ; j++ )
				for ( i = 0; i < 144 ; i++)

					if ( ! ( i % 2 ) )
					{
						a = (i>>1)-2;
						b = (i>>1)-1;
						c = (i>>1);
						d = (i>>1)+1;

						a = a < 0 ? 0 : a;
						b = b < 0 ? 0 : b;
						c = c < 0 ? 0 : c;
						d = d < 0 ? 0 : d;

						a = a >= (Height>>1) ? (Height>>1)-1 : a ;
						b = b >= (Height>>1) ? (Height>>1)-1 : b;
						c = c >= (Height>>1) ? (Height>>1)-1 : c;
						d = d >= (Height>>1) ? (Height>>1)-1 : d;


						Array_144x88[i][j] = ( - 3 * Array_72x88[a][j] + 29 * Array_72x88[b][j] \
							+ 111 * Array_72x88[c][j] - 9 * Array_72x88[d][j] + 64 ) >> 7;
					}

					else
					{
						a = (i-3) >> 1;
						b = (i-1) >> 1;
						c = (i+1) >> 1;
						d = (i+3) >> 1;

						a = a < 0 ? 0 : a;
						b = b < 0 ? 0 : b;
						c = c < 0 ? 0 : c;
						d = d < 0 ? 0 : d;

						a = a >= (Height>>1) ? (Height>>1)-1 : a ;
						b = b >= (Height>>1) ? (Height>>1)-1 : b;
						c = c >= (Height>>1) ? (Height>>1)-1 : c;
						d = d >= (Height>>1) ? (Height>>1)-1 : d;

						Array_144x88[i][j] = ( - 3 * Array_72x88[a][j] + 29 * Array_72x88[b][j] \
							+ 111 * Array_72x88[c][j] - 9 * Array_72x88[d][j] + 64 ) >> 7;

					}
					for ( i = 0; i < 144 ; i++)
						for ( j = 0; j < 88 ; j++ ) 
						{
							if(Loop==1)
								cb[i][j]=Array_144x88[i][j];
							else
								cr[i][j]=Array_144x88[i][j];
						}


		} // END OF FOR ( Loop ) 

	} // END OF FOR ( Frame_Count)


	/*Converting 4:2:2 YUV to 4:4:4 YUV*/



	for ( Loop = 1 ; Loop <= 2; Loop++)
	{
		m = n = 0 ;

		Size = Loop == 1 ? Len_U : Len_V;

		for ( i = 0; i < Size; i++ ) 
		{
			if(Loop==1)
				Array_144x88[m][n++] = cb[m][n++];
			else
				Array_144x88[m][n++] = cr[m][n++];

			if ( n > 87 ) 
			{
				n = 0;
				m++;
			}
		} 
		for ( i = 0; i < 144 ; i++)
			for ( j = 0; j < 176 ; j++ ) 
				if ( ! ( j % 2 ) )
				{
					a = (j>>1)-2;
					b = (j>>1)-1;
					c = (j>>1);
					d = (j>>1)+1;

					a = a < 0 ? 0 : a;
					b = b < 0 ? 0 : b;
					c = c < 0 ? 0 : c;
					d = d < 0 ? 0 : d;

					a = a >= (Width>>1) ? (Width>>1)-1 : a ;
					b = b >= (Width>>1) ? (Width>>1)-1 : b;
					c = c >= (Width>>1) ? (Width>>1)-1 : c;
					d = d >= (Width>>1) ? (Width>>1)-1 : d;



					Array_144x176[i][j] = ( - 3 * Array_144x88[i][a] + 29 * Array_144x88[i][b] \
						+ 111 * Array_144x88[i][c] - 9 * Array_144x88[i][d] + 64 ) >> 7;
				}
				else
				{
					a = (j-3) >> 1;
					b = (j-1) >> 1;
					c = (j+1) >> 1;
					d = (j+3) >> 1;

					a = a < 0 ? 0 : a;
					b = b < 0 ? 0 : b;
					c = c < 0 ? 0 : c;
					d = d < 0 ? 0 : d;

					a = a >= (Width>>1) ? (Width>>1)-1 : a ;
					b = b >= (Width>>1) ? (Width>>1)-1 : b;
					c = c >= (Width>>1) ? (Width>>1)-1 : c;
					d = d >= (Width>>1) ? (Width>>1)-1 : d;

					Array_144x176[i][j] = ( - 3 * Array_144x88[i][a] + 29 * Array_144x88[i][b] \
						+ 111 * Array_144x88[i][c] - 9 * Array_144x88[i][d] + 64 ) >> 7;

				}


				for ( i = 0; i < 144 ; i++)
					for ( j = 0; j < 176 ; j++ ) 
						if(Loop==1)
							u[i][j]=Array_144x176[i][j];
						else
							v[i][j]=Array_144x176[i][j];

	} // END OF FOR ( Loop ) 
	flag=1;
	Display(hDlg);
	fclose(yuvfile);
	return 1;
}
int Display(HWND hDlg)
{
	int C,D,E;

	GetClientRect(hDlg, &rClt2);
	Xoffset=(rClt2.right-176)/2;
	Yoffset=(rClt2.bottom-144)/2;

	for ( Frame_Count = 0 ; Frame_Count < No_OF_FRAMES ; Frame_Count++ )
	{
		for ( int m = 0; m < 144; m++)
			for (int  n = 0; n < 176; n++)
			{
				C = y[m][n] - 16;
				D = u[m][n] - 128;
				E = v[m][n] - 128;


				Red[m][n] = ( 298 * C + 409 * E + 128) >> 8;
				Green[m][n] = ( 298 * C - 100 * D - 208 * E + 128) >> 8;
				Blue[m][n] = ( 298 * C + 516 * D + 128) >> 8;


				if (Red[m][n] > 255) Red[m][n] = 255;

				if (Green[m][n] > 255) Green[m][n] = 255;

				if (Blue[m][n] > 255) Blue[m][n] = 255;

				if (Red[m][n] < 0) Red[m][n] = 0;

				if (Green[m][n] < 0) Green[m][n] = 0;

				if (Blue[m][n] < 0) Blue[m][n] = 0;

			}
	}


	if(saveflag==1)
	{
		if(saveBMP(hDlg))
			MessageBoxA(NULL, "BMP file saved", "Success", MB_OK);
		saveflag=0;
		return 1;
	}


	hDc     = GetDC(hDlg);


	if(grayscale==1)
	{
		for( int m=0; m<144; ++m)
			for( int n=0; n<176; ++n)
			{
				if(!(SetPixel(hDc, Xoffset+n, Yoffset+m, RGB(y[m][n],y[m][n],y[m][n]))))
					MessageBoxA(NULL, "SetPixel Failed", "Error", MB_OK);
			}
	}
	else 
	{

		for( int m=0; m<144; ++m)
			for( int n=0; n<176; ++n)
			{
				if(!(SetPixel(hDc, Xoffset+n, Yoffset+m, RGB(Red[m][n],Green[m][n], Blue[m][n]))))
					MessageBoxA(NULL, "SetPixel Failed", "Error", MB_OK);
			}
	}
	grayscale=0;
	return 1;
}
