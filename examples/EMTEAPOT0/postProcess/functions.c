FILE* fp;

char LINE[256];
int sFFULL[12];
int eFFULL[12];

int parsedLINE=0;
double allSP1x[1000];

char printDTFULL[5];
char  parsedSP1x[22];
char parsedSP1xP[22];

void nullNums(){
 int i=0;
 for(i=0;i<22;i++){
  parsedSP1x[i] ='\0';
  parsedSP1xP[i]='\0';
 }
}

void nullLine(){
 int i=0;
 for(i=0;i<256;i++){
  LINE[i]='\0';
 }
}

void parseLine(){
 int i=0,j=0,k=0,c=0; 
 int line=0;
 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 if(c=='-')parsedSP1x[k++]=c;
 else{parsedSP1x[k++]='+';parsedSP1x[k++]=c;}
 do{
  c=LINE[i++];
  parsedSP1x[k++]=c;
 }while(c != ' ');
 eFFULL[j-1]=i-2;
// printf("\n");
// printf("(atof) parsedSP1x: %+21.14e\n",atof(parsedSP1x));
 allSP1x[parsedLINE++]=atof(parsedSP1x);
// printf("(chars)parsedSP1x: ");
// for(k=0;k<22;k++)printf("%c",parsedSP1x[k]);
 nullNums();

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;

 do{
  c=LINE[i++];
 }while(c == ' ');
 sFFULL[j++]=i-1;
 do{
  c=LINE[i++];
 }while(c != ' ');
 eFFULL[j-1]=i-2;
}

int getNumLines(char*SP){
 fp=fopen (SP,"r");
 int ch=0,lines=0;
 do{
  ch = getc(fp);
  if (ch == '\n'){
   lines++;
  }
 }while (ch != EOF);
 fclose (fp);
 return lines;
}

int fillSP1x(char*SP){
 int ch=0,i=0,lines=0;
 fp=fopen (SP,"r");

// printf("enter double fillSP1()\n");

 do{
  ch = getc(fp);
  if (ch == '\n'){
   allSP1x[lines++]=atof(parsedSP1x);
   LINE[i++]=ch;
// lines++;
   parseLine();
   nullLine();
   i=0;
  }
  else{
   LINE[i++]=ch;
  }
 }while (ch != EOF);
 fclose(fp);
 return lines;
}
