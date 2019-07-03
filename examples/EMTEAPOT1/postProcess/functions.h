//extern char*rootDir;
//char*rootDir;
char*rootDir;
char*ABScosMu_iX;
char*ABSbeta_iX;
char*ABSStndrdPrtcl1;
char*ABSStndrdPrtcl2;
char*ABSStndrdPrtcl3;
char*ABSStndrdPrtcl4;

FILE*fp;
char LINE[256];
int lines=0;

double  SP1x[1000],SP1xP[1000];
double  SP2x[1000],SP2xP[1000];
double  SP3x[1000],SP3xP[1000];
double  SP4x[1000],SP4xP[1000];

double SPx[1000];
int strtFldSPx[12];
int enddFldSPx[12];

double SPxP[1000];
int strtFldSPxP[12];
int enddFldSPxP[12];

char  parsedSPx[22];
char parsedSPxP[22];

double SPy[1000];
int strtFldSPy[12];
int enddFldSPy[12];

double SPyP[1000];
int strtFldSPyP[12];
int enddFldSPyP[12];

char  parsedSPy[22];
char parsedSPyP[22];

void setABS(){
 int i=0;
 rootDir        =(char *)calloc(200,sizeof(char));
 ABScosMu_iX    =(char *)calloc(200,sizeof(char));
 ABSbeta_iX     =(char *)calloc(200,sizeof(char));
 ABSStndrdPrtcl1=(char *)calloc(200,sizeof(char));
 ABSStndrdPrtcl2=(char *)calloc(200,sizeof(char));
 ABSStndrdPrtcl3=(char *)calloc(200,sizeof(char));
 ABSStndrdPrtcl4=(char *)calloc(200,sizeof(char));

 getcwd(rootDir,200);
 for(i=strlen(rootDir)-11;i<strlen(rootDir);i++)rootDir[i]='\0';

 strcpy(ABScosMu_iX,rootDir);
 ABScosMu_iX=strcat(ABScosMu_iX,"postProcess/out/cosMu_iX");
 strcpy(ABSbeta_iX,rootDir);
 ABSbeta_iX=strcat(ABSbeta_iX,"postProcess/out/cosMu_iX");

 strcpy(ABSStndrdPrtcl1,rootDir);
 ABSStndrdPrtcl1=strcat(ABSStndrdPrtcl1,"propagate/out/StndrdPrtcl1");
 strcpy(ABSStndrdPrtcl2,rootDir);
 ABSStndrdPrtcl2=strcat(ABSStndrdPrtcl2,"propagate/out/StndrdPrtcl2");
 strcpy(ABSStndrdPrtcl3,rootDir);
 ABSStndrdPrtcl3=strcat(ABSStndrdPrtcl3,"propagate/out/StndrdPrtcl3");
 strcpy(ABSStndrdPrtcl4,rootDir);
 ABSStndrdPrtcl4=strcat(ABSStndrdPrtcl4,"propagate/out/StndrdPrtcl4");
}

void printABS(){
 printf("rootDir %s\n",rootDir);
 printf("ABScosMu_iX %s\n",ABScosMu_iX);
 printf("ABSbeta_iX %s\n",ABSbeta_iX);
 printf("ABSStndrdPrtcl1 %s\n",ABSStndrdPrtcl1);
 printf("ABSStndrdPrtcl2 %s\n",ABSStndrdPrtcl2);
 printf("ABSStndrdPrtcl3 %s\n",ABSStndrdPrtcl3);
 printf("ABSStndrdPrtcl4 %s\n",ABSStndrdPrtcl4);
}

void nullNums(){
 int i=0;
 for(i=0;i<22;i++){
  parsedSPx[i] ='\0';
  parsedSPxP[i]='\0';
 }
}

void nullLine(){
 int i=0;
 for(i=0;i<256;i++){
  LINE[i]='\0';
 }
}

                             // "outer loop", processSP, based on "\n", has index lines
void parseLine(){            // this method parses the current line
 int i=0;                    // i is character index in line
 int j=0;                    // j is field index in line
 int k=0;                    // k is character index in field of interest
 int c=0; 

 do{                         // ONE
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;

 do{                         // TWO
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;

 do{                         // THREE
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;

 k=0;                        // redundant
 do{                         // FOUR - x
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 if(c=='-'){parsedSPx[k++]=c;}//printf("c==- %c\n",c);}
 else{parsedSPx[k++]='+';parsedSPx[k++]=c;}//printf("c!=- %c\n",c);}
 do{
  c=LINE[i++];
  parsedSPx[k++]=c;
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;
 SPx[lines]=atof(parsedSPx);//printf("SPx[lines] %+e\n",SPx[lines]);
 nullNums();

 k=0;
 do{                         // FIVE - xP
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPxP[j++]=i-1;
 if(c=='-')parsedSPxP[k++]=c;
 else{parsedSPxP[k++]='+';parsedSPxP[k++]=c;}
 do{
  c=LINE[i++];
  parsedSPxP[k++]=c;
 }while(c != ' ');
 enddFldSPxP[j-1]=i-2;
 SPxP[lines]=atof(parsedSPxP);
 nullNums();

 do{                         // SIX - y
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;

 do{                         // SEVEN - yP
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;

 do{                         // EIGHT - t
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;

 do{                         // NINE - e
  c=LINE[i++];
 }while(c == ' ');
 strtFldSPx[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 enddFldSPx[j-1]=i-2;
}

int getNumLines(char*SP){
 fp=fopen (SP,"r");
 int ch=0;
 do{
  ch = getc(fp);
  if (ch == '\n'){
   lines++;
  }
 }while (ch != EOF);
 fclose (fp);
 return lines;
}

//int processSP(char*SP){
  int processSP(int sp){
printf("enter processSP\n");
/*
printf("rootDir %s\n",rootDir);
printf("ABScosMu_iX %s\n",ABScosMu_iX);
printf("ABSStndrdPrtcl1 %s\n",ABSStndrdPrtcl1);
*/
 char*SP;
//int ch=0,i=0;
  int      i=0;
 char ch;
/*
 if(sp==1)SP="../propagate/out/StndrdPrtcl1";
 if(sp==2)SP="../propagate/out/StndrdPrtcl2";
 if(sp==3)SP="../propagate/out/StndrdPrtcl3";
 if(sp==4)SP="../propagate/out/StndrdPrtcl4";
*/
/*
 if(sp==1)SP=ABSStndrdPrtcl1;
 if(sp==2)SP=ABSStndrdPrtcl2;
 if(sp==3)SP=ABSStndrdPrtcl3;
 if(sp==4)SP=ABSStndrdPrtcl4;
*/
 if(sp==1)fp=fopen(ABSStndrdPrtcl1,"r");
 if(sp==2)fp=fopen(ABSStndrdPrtcl2,"r");
 if(sp==3)fp=fopen(ABSStndrdPrtcl3,"r");
 if(sp==4)fp=fopen(ABSStndrdPrtcl4,"r");
// fp=fopen (SP,"r");
// printf("fp %p\n",fp);

 lines=0;
 do{
  ch = getc(fp);
  if (ch == '\n'){
   LINE[i++]=ch;
   parseLine();
   lines++;
   nullLine();
   i=0;
  }
  else{
   LINE[i++]=ch;
  }
 }while (ch != EOF);
 fclose(fp);

 if(sp==1){for(i=0;i<lines;i++){SP1x[i]=SPx[i];SP1xP[i]=SPxP[i];}};
 if(sp==2){for(i=0;i<lines;i++){SP2x[i]=SPx[i];SP2xP[i]=SPxP[i];}};
 if(sp==3){for(i=0;i<lines;i++){SP3x[i]=SPx[i];SP3xP[i]=SPxP[i];}};
 if(sp==4){for(i=0;i<lines;i++){SP4x[i]=SPx[i];SP4xP[i]=SPxP[i];}};
/*
printf("ABSStndrdPrtcl1 %s\n",ABSStndrdPrtcl1);
printf("ABScosMu_iX %s\n",ABScosMu_iX);
printf("rootDir %s\n",rootDir);
*/
printf("leave processSP\n");
 return lines;
}

//void printArray(double arr[3][3]){
char printArray(double arr[3][3]){
 int i,j;
 for(i=1;i<3;i++){
  for(j=1;j<3;j++){
   printf("      %+.17e ",arr[i][j]);
  }
  printf("\n");
 }
 return ' ';
}

double traceArray(double arr[3][3]){
 int i=0;
 double t=0;
 for(i=1;i<3;i++){
  t=t+arr[i][i];
 }
 return t;
}
 

double determinantArray(double arr[3][3]){
 double det=0;
 return arr[1][1]*arr[2][2]-arr[1][2]*arr[2][1];
}

void scaleArray(double arr[3][3],double f){
 int i,j;
 for(i=1;i<3;i++){
  for(j=1;j<3;j++){
   arr[i][j]=f*arr[i][j];;
  }
 }
}

//void inverseArray(double**input,double**output){
  void inverseArray(double input[3][3],double output[3][3]){
 double det=determinantArray(input);
// printf("inverseArray: det %+.17e\n",det);
 output[1][1]=+input[2][2]/det;
 output[2][2]=+input[1][1]/det;
 output[1][2]=-input[1][2]/det;
 output[2][1]=-input[2][1]/det;
}

void multiplyArrays(double left[3][3],double right[3][3],double product[3][3]){

 product[1][1]=left[1][1]*right[1][1]+left[1][2]*right[2][1];
 product[1][2]=left[1][1]*right[1][2]+left[1][2]*right[2][2];

 product[2][1]=left[2][1]*right[1][1]+left[2][2]*right[2][1];
 product[2][2]=left[2][1]*right[1][2]+left[2][2]*right[2][2];

}

void copyArray(double LHS[3][3],double RHS[3][3]){
 int i=0,j=0;
 for(i=0;i<3;i++){
  for(j=0;j<3;j++){
   LHS[i][j]=RHS[i][j];
  }
 }
}

/*
double** inverseArray(double arr[3][3]){
 double**inv={ {0,0,0}, {0,0,0}, {0,0,0}};
 double det=determinantArray(arr);
 printf("inverseArray: det %+.17e\n",det);
 inv[1][1]=+arr[2][2]/det;
 inv[2][2]=+arr[1][1]/det;
 inv[1][2]=-arr[2][1]/det;
 inv[2][1]=-arr[1][2]/det;
 return inv;
}
*/
