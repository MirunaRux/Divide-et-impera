#include <iostream>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;

struct punct
{
    int x,y;
}X, dreapta;
vector <punct> v,y;

int n,i,j,a,b,c,d,e,f,g,h,xmin,ymin,xminn, yminn,aa,bb,cc,dd,ee,fff,ggg,hh;
double s=1000000000,smin1=1000000000,smin2=1000000000, smin=1000000000, s1=1000000000, s2=1000000000, s3=1000000000;
    ifstream ff("date.in");
  ofstream gg("date.out");
double Euclid (punct A , punct B)
{
      return (sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)));
}

bool comparare (punct A, punct B)
{
    return ((A.x<B.x) || (A.x==B.x) && (A.y<B.y));
}
bool comp (punct A, punct B)
{
    return (A.y<B.y);
}
void Solutie (int st, int dr);
void SolutieS(int st, int dr)                      //apelul recursiv pt partea stanga
{
 if((st+dr)>2){
                if((dr-st+1)==2) {s=Euclid(v[st],v[dr]);   a=v[st].x; b=v[st].y;  aa=v[dr].x; bb=v[dr].y;}
                else if((dr-st+1)==3){ s1=Euclid(v[st],v[dr]); c=v[st].x; d=v[st].y; cc=v[dr].x; dd=v[dr].y;
                    s2=Euclid(v[st],v[st+1]);  e=v[st].x; f=v[st].y; ee=v[st+1].x; fff=v[st+1].y;
                    s3=Euclid(v[st+1],v[dr]);  g=v[st+1].x; h=v[st+1].y; ggg=v[dr].x; hh=v[dr].y;
                    }
                    if(smin>s) {smin=s; xmin=a; ymin=b;xminn=aa; yminn=bb;}
                    if(smin>s1)  {smin=s1; xmin=c; ymin=d; xminn=cc; yminn=dd;}
                    if(smin>s2)   {smin=s2; xmin=e; ymin=f; xminn=ee; yminn=fff;}
                    if(smin>s3)  {smin=s3; xmin=g; ymin=h; xminn=ggg; yminn=hh;}

              Solutie(st,dr);



 }


}

void SolutieD(int stt , int drr)                     //apelul recursiv pt partea dreapta
{
 if((drr-stt+1)>2){
                   if((drr-stt+1)==2) {s=Euclid(v[stt],v[drr]); a=v[stt].x; b=v[stt].y;  aa=v[drr].x; bb=v[drr].y;}
                   else if((drr-stt+1)==2){ s1=Euclid(v[stt],v[drr]); c=v[stt].x; d=v[stt].y; cc=v[drr].x; dd=v[drr].y;
                    s2=Euclid(v[stt],v[stt+1]); e=v[stt].x; f=v[stt].y; ee=v[stt+1].x; fff=v[stt+1].y;
                    s3=Euclid(v[stt+1],v[drr]); g=v[stt+1].x; h=v[stt+1].y; ggg=v[drr].x; hh=v[drr].y;
                    }
                    if(smin>s) {smin=s; xmin=a; ymin=b; xminn=aa; yminn=bb;}
                    if(smin>s1) {smin=s1; xmin=c; ymin=d; xminn=cc; yminn=dd;}
                    if(smin>s2) {smin=s2; xmin=e; ymin=f; xminn=ee; yminn=fff;}
                    if(smin>s3) {smin=s3; xmin=g; ymin=h; xminn=ggg; yminn=hh;}

               Solutie(stt,drr);

 }


}
void Dunga()
{
    sort(y.begin(),y.end(),comp);
for(i=0; i<y.size(); i++)
    for(j=i+1; j<y.size() && j<=i+7; j++)


{

    if(smin>Euclid(y[i],y[j])) {smin=Euclid(y[i],y[j]); xmin=y[i].x; ymin=y[i].y; xminn=y[j].x; yminn=y[j].y;}
}
y.clear();
}
void Solutie (int st, int dr)
{ dreapta.x=(st+dr)/2;
 if((dr-st+1)>2)   {SolutieS(st,dreapta.x);
                    SolutieD(dreapta.x+1,dr);
 }

if(smin1<smin) smin=smin1;
if(smin2<smin) smin=smin2;

for(i=0;i<n;i++)
{
    if(abs(v[i].x-dreapta.x)<smin) y.push_back(v[i]);
}
Dunga();
}



int main()
{

ff>>n;
for(i=1;i<=n;i++)
   {

    ff>>X.x>>X.y;
v.push_back(X);
   }
sort(v.begin(),v.end(),comparare);

if(n==2) {smin=Euclid(v[0],v[1]);
xmin=v[0].x; ymin=v[0].y;
xminn=v[1].x; yminn=v[1].y;}

else if(n==3)
{
    s=Euclid(v[0],v[1]);
    if(smin>s) { smin=s; xmin=v[0].x; ymin=v[0].y; xminn=v[1].x; yminn=v[1].y;}
    s1=Euclid(v[1],v[2]);
    if(smin>s1) { smin=s1; xmin=v[1].x; ymin=v[1].y; xminn=v[2].x; yminn=v[2].y;}
    s2=Euclid(v[0],v[2]);
    if(smin>s2) { smin=s2; xmin=v[0].x; ymin=v[0].y; xminn=v[2].x; yminn=v[2].y;}

}
else
{
Solutie(0,n-1);

}
gg<<fixed<<setprecision(6)<<smin<<endl;
gg<<xmin<<" "<<ymin<<endl;
gg<<xminn<<" "<<yminn;

  ff.close();
  gg.close();


    return 0;
}
