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
 char*SP;
 int ch=0,i=0;
 if(sp==1)SP="../propagate/out/StndrdPrtcl1";
 if(sp==2)SP="../propagate/out/StndrdPrtcl2";
 if(sp==3)SP="../propagate/out/StndrdPrtcl3";
 if(sp==4)SP="../propagate/out/StndrdPrtcl4";
 fp=fopen (SP,"r");

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
